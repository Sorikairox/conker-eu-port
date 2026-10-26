# Renaming functions (P322)

Rule (user request 2026-10-26): when a session touches or reads a function, it gives it an explicit, readable name
and keeps the original asm name in a comment (`/* was func_XXXXXXXX */`). Renames go through one script so the
default eu build stays byte-identical.

- Table: `tools/eu_port/names.tsv` = `old<TAB>new<TAB>short description`. It is the source of truth.
- Script: `tools/eu_port/rename.py` (run from the repo root after `eval "$(tools/eu_port/wt.sh env <name>)"`).

## Workflow
1. Read the function (and its callers) and pick a snake_case name that says what it does (`cutscene_can_skip`, not
   `scene_func`). Add a row to `names.tsv`.
2. Dry run: `tools/eu_port/rename.py --check` lists every file/line it would change, the symbol it adds and where
   the `/* was ... */` comment goes. Read it. It stops when the new name is already used for something else.
3. Apply: `tools/eu_port/rename.py` (all rows; or `tools/eu_port/rename.py func_XXXXXXXX` for one row). Rows already
   applied are skipped, so re-running the whole table is safe (do it after a merge that brings new uses of an old name).
4. Verify: `tools/eu_port/rename.py --verify` = no old name left in scope + `verify_all.sh` (clean re-split, must
   stay byte-identical) + the NON_MATCHING link. Then the usual checks (protocheck, implicit_scan, ...), and for
   port-web `port/web/run.sh census && port/web/run.sh build`.
5. Commit the table row together with the changes it made.

## What it changes
- Whole-word uses (also `_name`, `__wrap_name`, `__real_name`) in tracked files under `conker/src_eu`,
  `conker/include`, the EU symbol / undefined-symbol lists, `conker/Makefile`, `conker.eu.yaml`, `port/` (Makefile
  `--wrap` and `EXPORTED_FUNCTIONS` lists, `port/tools` tables, platform C) and `tools/` (registries such as
  `tools/port/verify_registry.tsv`, `platform_replaced.tsv`, difftest selftest cases), plus the difftest setup and
  mutant files named in `verify_registry.tsv` (live inputs even though they sit under `docs/`).
- `conker/symbol_addrs.eu.txt`: splat calls every unlisted function `func_<EU address>`. The script appends
  `new = 0x<EU address>; // type:func` (address from `conker/build/conker.eu.map`, with a `// was old` line above), or
  renames the entry in place when the old name is listed (US names mapped to EU addresses). The re-split then names
  the asm file, glabel, jal and data-table references after the new name; `asm/` and `*_auto.txt` are generated.
- Tracked files whose path contains the old name are `git mv`ed (e.g. `tools/port/difftest/cases/func_X.c`).
- `/* was old */` is inserted above the C definition in `conker/src_eu` (above the GLOBAL_ASM pragma if there is no C).
- difftest knobs (RET/OUTW/ARGMEM/...) are keyed by EU addresses, so they need no change.

## What it leaves alone
`conker/src` (US version) and the US/debug/ects symbol files, every `*.md`, `docs/` (session docs, HANDOFF),
`*.log`, `port_work/`, historical logs (`tools/eu_port/repair_log.tsv`, `tools/port/pilot/`), vendored tools, and any
`was old` text. A header in `conker/include` that the US source also uses gets a warning (the US build is not kept).

## Limits
- Other branches (port, port-b, eu, eu-wt-*) still use the old names: after merging them, re-run the script
  (step 3) so new uses get renamed; textual conflicts on the renamed lines must be resolved by hand.
- Some analysis tools only recognise `func_[0-9A-F]{8}` names (e.g. port/tools/n64mem.py, stubcalls.py,
  m2c_sanity.py call scans, port/tools/bootpath.py, difftest def_intfirst / function-size fallback). They take sizes
  and addresses from the ELF first, but renamed functions may drop out of their call lists until they learn names.
