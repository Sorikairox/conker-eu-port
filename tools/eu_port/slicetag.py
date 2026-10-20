import sys, re
# s90: prefix srcmatch lines with LO (game < 0x130000) or HI (game >= 0x130000 / init / debugger / libultra)
for l in open(sys.argv[1]):
    f = l.split()[-1]; m = re.search(r'/game[^/]*_([0-9A-F]+)\.c$', f)
    print(('LO ' if m and int(m.group(1), 16) < 0x130000 else 'HI ') + l, end='')
