#!/usr/bin/env bash
# Serialise everything that touches conker/build/.
#
# WHY. The build tree is global state: `make` writes build/src/*.o and asm-processor writes
# build/src/*.c intermediates, and asm-differ reads build/ through diff_settings.py, which
# hardcodes it. Two builders at once therefore interleave into each other's objects. This is
# not theoretical -- a wave lost a measurement to it (a "resume from 1000000000" line in a
# search log), and it is the nastiest possible failure because the corrupted run still
# produces a plausible NUMBER. You cannot tell a corrupted score from a real one by looking.
#
# Overriding BUILD_DIR does not fix it: the compile would move but asm-differ would still
# read build/, so the score would be taken against a stale object.
#
# USAGE -- wrap the whole build+score, not just the build, since the score reads the object:
#   tools/buildlock.sh make -s build/src/game_BC510.c.o VERSION=us
#   tools/buildlock.sh bash -c 'make -s ... && python3 ../tools/asm-differ/diff.py -o f -R --max-lines 4096'
#
# Waits rather than fails, because a builder is normally only busy for seconds. Override the
# wait with BUILDLOCK_TIMEOUT (seconds, default 900); BUILDLOCK_QUIET=1 silences the notice.
set -uo pipefail

LOCK="${BUILDLOCK_FILE:-/tmp/conker_build.lock}"
TIMEOUT="${BUILDLOCK_TIMEOUT:-900}"

[ $# -gt 0 ] || { echo "usage: buildlock.sh <command> [args...]" >&2; exit 2; }

if ! command -v flock >/dev/null 2>&1; then
  echo "buildlock: flock(1) not found -- refusing to run unserialised." >&2
  echo "  Install util-linux, or run builds strictly one at a time." >&2
  exit 3
fi

exec 9>"$LOCK" || { echo "buildlock: cannot open $LOCK" >&2; exit 3; }

if ! flock -w "$TIMEOUT" 9; then
  echo "buildlock: timed out after ${TIMEOUT}s waiting for $LOCK." >&2
  echo "  Another builder is holding it. Check for a stuck build before forcing:" >&2
  echo "    ps -eo pid,etime,args | grep -E '[m]ake|[a]sm_processor|[p]ermuter'" >&2
  exit 4
fi

if [ -z "${BUILDLOCK_QUIET:-}" ]; then
  echo "buildlock: acquired ($LOCK, pid $$)" >&2
fi

"$@"
rc=$?
[ -z "${BUILDLOCK_QUIET:-}" ] && echo "buildlock: released (rc=$rc)" >&2
exit $rc
