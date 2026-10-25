# P272 (port-web part, 2026-10-25): milk glass check after the func_15031C4C fix

- Merged port e6300743 (P272: func_15031C4C off-by-one, func_15031D40 two switches) -> b888a353. Clean rebuild
  (files.tsv + vbe.stamp deleted), census 0 FAIL; verify_all rc 0, protocheck 0 (1646), romabs_check 0 FAIL.
- `SHOTS="130000 160000" p271/run.sh` (det=2, muted): p272/after_130s.png, p272/after_160s.png vs p271/before_*.png.
  130 s close-up: the raised hand now holds a short block (before: empty hand). 160 s on the throne: the same object
  sits in the hand next to the foot (before: nothing). The rest of the frames is unchanged.
- The object looks opaque pink-white and blocky; whether the glass/milk shading matches N64 (translucency, texture
  0x0CBA) still needs a check against a reference capture.
