# Force-clean ROM check WITHOUT committing (user wants matches left uncommitted).
cd '/mnt/c/Users/ssyla/OneDrive/Desktop/conker/conker decomp' && . .venv/bin/activate
rm -f conker/build/conker.us.bin build/conker.us.z64
make -C conker >/tmp/rom_make.log 2>&1; echo "make rc=$?"
sha1sum conker/build/conker.us.bin
make -C conker replace >>/tmp/rom_make.log 2>&1 && make -j >>/tmp/rom_make.log 2>&1; echo "outer rc=$?"
sha1sum build/conker.us.z64
echo "want 842e3d348e3c8ae0039e2ab367ad492f9b5266d8 / 4cbadd3c4e0729dec46af64ad018050eada4f47a"
