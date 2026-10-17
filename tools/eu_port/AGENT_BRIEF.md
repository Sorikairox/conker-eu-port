# Standard brief for a decompilation work session

You are one session in a chain of agents decompiling Conker's Bad Fur Day (EU) in
`~/conker`, branch `eu`. Read `HANDOFF.md` in full before doing anything.

## Rules

- Private local fork: never push, never touch the `upstream` remote. Don't modify the
  user's ROM in `~/Downloads`, and don't install system software.
- **Work alone and sequentially.** Spawn no subagents, forks, parallel agents or
  workflows. Running parallel *processes* from your own scripts is fine.
- Don't run `tools/eu_port/run.sh`; it would wipe the hand-edited sources.
- **Budget:** stop after the number of commits given in your launch message. Then do
  the hand-off below. A fresh agent continues after you, so don't push past the budget.
- **Prefer scripts to repeated manual commands.** If you do the same multi-step thing
  twice, write or extend a script under `tools/eu_port/` and document it in
  `HANDOFF.md`. Keep script output compact.

## Verification

- Authoritative check: `tools/eu_port/verify_all.sh` (repo root, on the host). It
  re-splits from scratch, then runs the code build, `check_files.py`, the full ROM
  build and a progress summary. It exits 0 only when everything matches.
  `--quick` skips the re-split.
- Inner loop: the tools listed in `HANDOFF.md` (`docker exec` container, m2c pipeline in
  `tools/eu_port/m2c/`, `check_files.py`).

## Commits

- Small batches, roughly 5–20 functions. Commit only after `verify_all.sh` (or at
  least `--quick`) passes. Run the full, non-quick version at least every few commits
  and before your last commit.
- Never leave uncommitted work at the end of a batch, and never commit a non-matching
  state.
- End every commit message with this trailer line:
  `Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>`

## Hand-off (mandatory, even if you stop early)

1. Update `HANDOFF.md`:
   - "Current state", using the numbers from `verify_all.sh`
   - what you did and which tools you added
   - hard or skipped functions and why
   - next steps
2. Commit it.
3. Final reply, kept short:
   - before/after progress (functions and bytes)
   - what you matched, by file or subsystem
   - notable findings
   - skipped functions
   - commit range
   - the last `verify_all.sh` output
