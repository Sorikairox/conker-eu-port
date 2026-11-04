#!/usr/bin/env python3
"""P377 retrowser build: make the worker's overlay layer from its files and the page code it reuses.

    python3 port/tools/rtw_page_extract.py WEB OUT CORE [FEATURE ...]
    (port/Makefile: web port/build/rtw/gen/rtw_overlay.js web/rtw/rtw_overlay.js web/rtw/rtw_saveicon.js ...)

CORE (port/web/rtw/rtw_overlay.js) has one /* @RTW_FEATURES@ */ place: the FEATURE files go there, in order, so they
share its scope (one object, rtwOverlay). Any file may have /* @RTW_PAGE NAME,NAME@ */ places: each NAME is a block of
the page build's own code (the table below), copied verbatim from WEB/main.js or WEB/gmenu.js (those files are never
changed by this), so the worker draws with the page's code: the game font, the button faces, the options' labels and
help, the presets, the menu model, photo mode's name tables / `look` and its game-style HUD and panel. A block starts at
its first line and ends at its closing line; every block and every substitution must match exactly once, else the
build stops (a later edit of main.js / gmenu.js that moves a block is noticed, never silently dropped). The
substitutions only rename OPTIONS (the worker filters it to the options this build has) and replace photo mode's help
line (it names the page's keys)."""
import re
import sys

# NAME -> [(file, first line regex, closing line regex or None = one line, substitutions [(old, new)])]
BLOCKS = {
    'OPTIONS': [('main.js', r'^const OPTIONS = \[$', r'^\];$', [('const OPTIONS = [', 'const PAGE_OPTIONS = [')])],
    'PRESETS': [('main.js', r'^const PRESET_KEYS = ', None, []),
                ('main.js', r'^const PRESET_MODERN_ON = ', None, []),
                ('main.js', r'^const PRESETS = \{$', r'^\};$', [])],
    'MenuModel': [('gmenu.js', r'^const MenuModel = \(\(\) => \{$', r'^\}\)\(\);$', [])],
    'GameFont': [('gmenu.js', r'^const GameFont = \(\(\) => \{$', r'^\}\)\(\);$', [])],
    'GFace': [('gmenu.js', r'^const GFace = \{$', r'^\};$', [])],
    # photo mode's name tables and the Pose & Outfit choice (P358): `look`, its signature, labels, lookPush, lookChanged
    'PHOTOLOOK': [('main.js', r'^const PHOTO_ANIM_NAMES = \{$', r'^function lookChanged\(\) ', [])],
    'GPhoto': [('gmenu.js', r'^const GPhoto = \(\(\) => \{$', r'^\}\)\(\);$', [
        ("  const HELP = 'Stick / WASD move. C buttons / right stick / IJKL / mouse look. R Z / E Q up and down. D-pad / arrows: left right roll, up down zoom (wheel too). B / F the game\\'s view. L / R the game\\'s HUD. A / Space save a PNG. P / Start / Enter back to the game.';",
         "  const HELP = 'Stick move. C buttons (the right stick) look. R / Z up and down. D-pad left / right roll, up / down zoom. B the game\\'s view. L the game\\'s HUD. A saves a PNG (the host\\'s Saved files). Start or Photo back to the game. Menu: the Pose & Outfit panel; hold Menu: hide the menus.';   // P377 retrowser build (rtw_page_extract.py)"),
    ])],
}


def block(lines, name, start, end):
    hits = [i for i, l in enumerate(lines) if re.search(start, l)]
    if len(hits) != 1:
        sys.exit(f'rtw_page_extract: {name}: /{start}/ matches {len(hits)} lines (want 1)')
    i = hits[0]
    if end is None:
        return lines[i:i + 1]
    for j in range(i + 1, len(lines)):
        if re.search(end, lines[j]):
            return lines[i:j + 1]
    sys.exit(f'rtw_page_extract: {name}: no /{end}/ after line {i + 1}')


def page_code(web, names, cache={}):
    out = []
    for name in names:
        if name not in BLOCKS:
            sys.exit(f'rtw_page_extract: no block {name!r}')
        for fname, start, end, subs in BLOCKS[name]:
            if fname not in cache:
                cache[fname] = open(f'{web}/{fname}', encoding='utf-8').read().split('\n')
            text = '\n'.join(block(cache[fname], fname, start, end))
            for old, new in subs:
                if text.count(old) != 1:
                    sys.exit(f'rtw_page_extract: {fname}: substitution {old[:60]!r} matches {text.count(old)} times (want 1)')
                text = text.replace(old, new)
            # not re-indented: a template literal may span lines
            out.append(f'// ---- {name}: from port/web/{fname} (rtw_page_extract.py, verbatim{" with substitutions" if subs else ""})\n{text}')
    return '\n'.join(out)


def expand(web, src, path):
    def one(m):
        return page_code(web, [n.strip() for n in m.group(1).split(',')])
    text, n = re.subn(r'^[ \t]*/\* @RTW_PAGE ([A-Za-z0-9_,]+)@ \*/[ \t]*$', one, src, flags=re.M)
    if '/* @RTW_PAGE' in text:
        sys.exit(f'rtw_page_extract: {path}: a malformed @RTW_PAGE place')
    return text


def main():
    web, dst, core, features = sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4:]
    src = open(core, encoding='utf-8').read()
    place = '  /* @RTW_FEATURES@ */'
    if src.count(place) != 1:
        sys.exit(f'rtw_page_extract: {core} has {src.count(place)} {place.strip()} (want 1)')
    parts = [f'  // ======== {f} ========\n' + open(f, encoding='utf-8').read().rstrip() for f in features]
    src = expand(web, src.replace(place, '\n\n'.join(parts) if parts else '  // (no feature files)'), core)
    with open(dst, 'w', encoding='utf-8') as f:
        f.write('// GENERATED by port/tools/rtw_page_extract.py from port/web/rtw/rtw_overlay.js + its feature files and the page\'s '
                'main.js / gmenu.js: do not edit.\n' + src)


if __name__ == '__main__':
    main()
