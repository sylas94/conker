#!/usr/bin/env bash
# Conker decomp toolchain bootstrap (native x86-64 Linux route).
# Run from anywhere:  /path/to/conker/setup.sh
# Installs system packages, creates the Python venv, installs deps.
# The ROM (baserom.us.z64) must already be in place; this script verifies it.

set -euo pipefail

# Repo root = the directory this script lives in (no $HOME assumption).
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$REPO"

echo "==> [1/4] Installing system packages (sudo)"
# NOTE: packages.txt lists 'libglib2.0' which does not exist on Debian/Ubuntu;
# the real package is libglib2.0-0. Use a corrected list here.
sudo apt-get update
sudo apt-get install -y \
  binutils-mips-linux-gnu \
  build-essential \
  git \
  less \
  libglib2.0-0 \
  python-is-python3 \
  python3 \
  python3-pip \
  python3-venv \
  unzip \
  wget

echo "==> [2/4] Creating Python venv (.venv)"
if [ ! -d .venv ]; then
  python3 -m venv .venv
fi
# shellcheck disable=SC1091
source .venv/bin/activate
python -m pip install --upgrade pip

echo "==> [3/4] Installing Python dependencies"
# ONE pip invocation for both files: requirements.txt pins spimdisasm/rabbitizer
# exactly, tools/n64splat/requirements.txt only asks for a floor. A single
# resolver pass makes the exact pin win. Two separate `pip install` runs happen
# to work today only because pip does not upgrade an already-satisfied package.
pip install -r requirements.txt -r tools/n64splat/requirements.txt

echo "==> [4/4] Sanity checks"
echo -n "make:               "; command -v make || { echo "MISSING"; exit 1; }
echo -n "mips-linux-gnu-as:  "; command -v mips-linux-gnu-as || { echo "MISSING"; exit 1; }

# tools/n64splat and tools/asm-processor are SUBMODULES: nothing here may patch
# them (a `git submodule update` would revert it). The extraction fixes live in
# tools/split_conker.py, which conker/Makefile's `extract` target calls. Prove
# it imports before anyone burns a full split on a broken environment.
echo -n "split_conker.py:    "
if python tools/split_conker.py --help >/dev/null 2>&1; then
  echo "OK ($(python -c 'import spimdisasm; print("spimdisasm", spimdisasm.__version__)'))"
else
  echo "BROKEN - run: python tools/split_conker.py --help"
  exit 1
fi

if [ -f baserom.us.z64 ]; then
  GOT=$(sha1sum baserom.us.z64 | cut -d' ' -f1)
  WANT=4cbadd3c4e0729dec46af64ad018050eada4f47a
  if [ "$GOT" = "$WANT" ]; then
    echo "baserom.us.z64:     OK ($GOT)"
  else
    echo "baserom.us.z64:     WRONG HASH ($GOT, want $WANT)"
  fi
else
  echo "baserom.us.z64:     MISSING (place it in $REPO)"
fi

# Activate the pre-commit gate guard (blocks tampering with the ROM verification SHA1s).
git config core.hooksPath tools/git-hooks 2>/dev/null && echo "git hooks:          core.hooksPath -> tools/git-hooks"

echo
echo "Done. Activate the venv with:  source $REPO/.venv/bin/activate"
