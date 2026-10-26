# Renaming functions (P322; port-only since P329)

Rule (user request 2026-10-26): when a session touches or reads a function, it gives it an explicit, readable name
and keeps the original asm name in a comment (`/* was func_XXXXXXXX */`). Renames go through one script so every
place that knows the name (C, headers, port tables, the frozen symbol table, test registries) changes together.

- Table: `tools/eu_port/names.tsv` = `old<TAB>new<TAB>short description`. It is the source of truth.
- Script: `tools/eu_port/rename.py` (run from the repo root after `eval "$(tools/eu_port/wt.sh env <name>)"`).
- Names and addresses of the port come from the frozen table `port/symbols/symbols.tsv` (frozen in P328 from the last
  byte-matching build; that build lives on branch `exact-byte-decomp-wip`). A rename edits the table row like any
  other use, so the address stays and the name changes.

## Workflow
1. Read the function (and its callers) and pick a snake_case name that says what it does (`cutscene_can_skip`, not
   `scene_func`). Add a row to `names.tsv`.
2. Dry run: `tools/eu_port/rename.py --check` lists every file/line it would change and where the `/* was ... */`
   comment goes. Read it. It stops when the new name is already used for something else.
3. Apply: `tools/eu_port/rename.py` (all rows; or `tools/eu_port/rename.py func_XXXXXXXX` for one row). Rows already
   applied are skipped, so re-running the whole table is safe (do it after a merge that brings new uses of an old name).
4. Verify: `tools/eu_port/rename.py --verify` = no old name left in scope + `tools/eu_port/check.sh` (implicit_scan,
   romabs_check, difftest selftest, census, web build).
5. Commit the table row together with the changes it made.

Batch flow for naming proposals: `tools/eu_port/apply_names.sh NN ...` (docs/names/PROPOSING.md) = validate the
chunks, append to names.tsv, check / apply / verify, browser hold-L test, commit, backup, deploy.

## What it changes
- Whole-word uses (also `_name`, `__wrap_name`, `__real_name`) in tracked files under `conker/src_eu`,
  `conker/include`, `port/` (Makefile `--wrap` and `EXPORTED_FUNCTIONS` lists, `port/tools` tables, platform C,
  `port/symbols/symbols.tsv` and `global_asm.tsv`) and `tools/` (registries such as `tools/port/verify_registry.tsv`,
  `platform_replaced.tsv`, difftest selftest cases, the difftest setups / mutants in `tools/port/testdata`).
- Tracked files whose path contains the old name are `git mv`ed (e.g. `tools/port/difftest/cases/func_X.c`).
- `/* was old */` is inserted above the C definition in `conker/src_eu` (also found when the `{` is on a later line
  or the definition is K&R style).
- difftest knobs (RET/OUTW/ARGMEM/...) are keyed by EU addresses, so they need no change.

## What it leaves alone
Every `*.md`, `docs/`, `*.log`, `port_work/`, `port/symbols/ido_cc.tsv` and any `was old` text. A function with no
row in the table (a C-only helper split out of an asm routine) just gets its source renamed. Asm-only functions
(platform-replaced, no C body) get a warning instead of the `/* was */` comment.

## Limits
- Other branches (port, port-b, eu, eu-wt-*, exact-byte-decomp-wip) still use the old names: after merging them,
  re-run the script (step 3) so new uses get renamed; textual conflicts on the renamed lines must be resolved by hand.
- Secondary entry points inside another function (func_150A4ED4, func_150A69A8) keep their names (apply_names.sh
  skips them).
