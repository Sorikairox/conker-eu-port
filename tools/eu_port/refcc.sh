#!/bin/bash
# s90: compile every .c of a reference decomp with IDO 5.3 (-O2 -mips2) into an objdir for srcmatch.py.
# usage: refcc.sh <srcroot> <objdir> [rounds=12] [extra cc flags...]   (paths relative to the repo root)
# Missing headers become empty stubs in <objdir>.stub/, undefined identifiers become
# `#define X <unique n>` lines in <objdir>.stub/gen_ids.h (force-included through a wrapper .c),
# repeated for up to <rounds> rounds. Failures: <objdir>.fail.txt. Generic -I list: ., include,
# include/PR, include/ultra64, src, src/include, src/game, the file's dir, then the stubs.
# Example: tools/eu_port/refcc.sh tools/goldeneye build_port/s90/ge 12 -DVERSION_US -DBYTEMATCH -DTARGET_N64
OPT=${OPT:--O2}; R=${CONKER_ROOT:-$HOME/conker}; C=${CONKERDEV:-conkerdev}
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
src=$1; out=$2; rounds=${3:-12}; shift 3; extra=$(echo "$*" | sed 's/-I /-I/g')  # s132: no space after -I (at -O3 uld reads a separate missing dir as an input file)
st=$out.stub; mkdir -p $R/$out $R/$st; [ -f $R/$st/gen_ids.h ] || printf '#ifndef GEN_IDS_H\n#define GEN_IDS_H\n#endif\n' > $R/$st/gen_ids.h
cat > $R/$out.job.sh <<EOF
#!/bin/bash
cd /conker/$src; OUT=/conker/$out; ST=/conker/$st; mkdir -p /tmp/refcc_\$\$; W=/tmp/refcc_\$\$
: > \$OUT.fail.txt; : > \$OUT.undef.txt; : > \$OUT.hdr.txt
find . -name '*.c' -not -path './tools/*' | sed 's|^\./||' | sort | xargs -P8 -I{} bash -c '
f={}; n=\$(echo \$f | tr / _); o='\$OUT'/\$n.o; [ -s \$o ] && exit 0
printf "#include \"gen_ids.h\"\n#include \"/conker/$src/%s\"\n" \$f > '\$W'/\$n
if ! /opt/ido5.3/cc -c ${OPT:--O2} -mips2 -32 -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -Olimit 2000 -w -D_LANGUAGE_C -D_MIPS_SZLONG=32 -DF3DEX_GBI_2 $extra \
  -I. -Iinclude -Iinclude/PR -Iinclude/ultra64 -Isrc -Isrc/include -Isrc/game -I\$(dirname \$f) -I'\$ST' -o \$o '\$W'/\$n > '\$W'/\$n.err 2>&1; then
  rm -f \$o; echo "FAIL \$f \$(grep -m1 rror '\$W'/\$n.err | cut -c1-160)" >> '\$OUT'.fail.txt
  grep -o "'"'"'[A-Za-z_][A-Za-z_0-9]*'"'"' undefined" '\$W'/\$n.err | tr -d "'"'"'" | cut -d" " -f1 >> '\$OUT'.undef.txt
  grep -o "Cannot open file [^ ]* for" '\$W'/\$n.err | cut -d" " -f4 >> '\$OUT'.hdr.txt; fi'
rm -rf \$W
EOF
chmod +x $R/$out.job.sh
for i in $(seq 1 $rounds); do
  docker exec $C /conker/$out.job.sh
  sort -u -o $R/$out.undef.txt $R/$out.undef.txt; sort -u -o $R/$out.hdr.txt $R/$out.hdr.txt
  nu=$(grep -c . $R/$out.undef.txt); nh=$(grep -c . $R/$out.hdr.txt)
  echo "round $i: objs $(ls $R/$out | wc -l | tr -d ' ') fails $(grep -c . $R/$out.fail.txt) undef $nu hdr $nh"
  [ $nu = 0 ] && [ $nh = 0 ] && break
  while read h; do mkdir -p $R/$st/$(dirname $h); touch $R/$st/$h; done < $R/$out.hdr.txt
  B=$(grep -c . $R/$st/gen_ids.h); sed -i '' '$d' $R/$st/gen_ids.h
  grep -E "${UCRE:-.}" $R/$out.undef.txt | awk -v b=$B '{printf "#define %s %d\n", $1, NR+4096+b}' >> $R/$st/gen_ids.h; echo '#endif' >> $R/$st/gen_ids.h
done
