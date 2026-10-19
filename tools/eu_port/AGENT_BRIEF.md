# Standard brief for a decompilation work session

You are one session in a chain of agents decompiling Conker's Bad Fur Day (EU) in
`~/conker`, branch `eu`. Read `HANDOFF.md` in full before doing anything, and `docs/IDO_SHAPES.md` before any
matching work. The session history in `docs/sessions/` is reference only (grep it when a
function or tool name comes up; do not read it through).

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

## Parallel worktrees

- If you were launched in a worktree (`~/conker-wt/<name>`, branch `eu-wt-<name>`), work only there and
  never touch `~/conker` or its `conkerdev` container. **Before using any tool**, in every shell run
  `eval "$(tools/eu_port/wt.sh env <name>)"` (exports `CONKER_ROOT` and `CONKERDEV=conkerdev-<name>`);
  without it the scripts silently act on the main checkout. Commit on your branch only; the coordinator
  merges with `wt.sh merge <name>`. In a worktree read "`~/conker`" and "`conkerdev`" in this brief as
  `$CONKER_ROOT` and `$CONKERDEV` (`docker exec $CONKERDEV ...`).

## Verification

- Authoritative check: `tools/eu_port/verify_all.sh` (repo root, on the host). It
  re-splits from scratch, then runs the code build, `check_files.py`, the full ROM
  build and a progress summary. It exits 0 only when everything matches.
  `--quick` skips the re-split.
- Inner loop: the native arm64 `conkerdev` container (image `conker-arm`, see HANDOFF
  "Fast native toolchain"); recreate it from `conker-arm` if it is missing. Then the tools listed in `HANDOFF.md` (`docker exec` container, m2c pipeline in
  `tools/eu_port/m2c/`, `check_files.py`).

## Waiting and long jobs

- Never block on a long job with `sleep` or an `until pgrep ...; do sleep N; done` loop.
  It wastes wall time doing nothing.
- Start long jobs (permuter runs and sweeps, bulk gensome/screening, verify_all.sh) with
  the Bash tool's `run_in_background`. Give each one its own output file. The harness
  notifies you when it finishes.
- While it runs, do useful work that doesn't conflict with it: hand-repair other
  functions, read asm, write drafts, or screen single drafts with `try`. Don't start a
  second job that writes `conker/build` (verify_all.sh, apply.py, clean builds) while
  another one is running.
- Short jobs (under ~10 min: verify_all.sh, a single build, apply.py) run in the
  foreground with a generous Bash timeout (up to 600000 ms). Never end your turn to wait
  for them: ending a turn can hand back an interim report and end your session with
  work uncommitted.
- **Never end your turn while you have budget left.** In this harness, ending a turn
  hands back your report and ends the session, even with background jobs running.
  Sessions 36, 37 and 43 ended that way, with matched work left uncommitted.
- While a long background job runs (a permuter run, gensome on many functions), keep
  working on other functions. When you've truly nothing else to do, block with
  `tools/eu_port/waitjob.sh pid <PIDs>` or `waitjob.sh file <out> <marker>`. It waits in
  the foreground for up to 9 minutes per call; call it again if it says "still running".
  Record the PIDs of background jobs you start (`echo $!`) so you can wait on or kill
  exactly those.
- Your session is over only when the budget is used and the hand-off commit is made.
- Never sleep-poll.
- To wait for a specific condition (e.g. a file appearing), use the Monitor tool if it's
  available, not a sleep loop.
- Spread permuter streams across both machines: local `permute.sh` / `sweep.sh perm`
  plus `remote_perm.sh` (Mac mini worker, see HANDOFF), each as its own background job.

## Code quality

- When a match depends on an unnatural construct (permuter artifacts such as `new_var`
  temporaries, `int *p = &k` to pin a constant, `do {} while (0)`, `p += K+1; p--;`,
  dummy volatile or self-assignment), put a `// fakematch: <why>` comment on that line.
  These compile to the right bytes and can be cleaned up later; the label makes them
  findable (`grep -rn fakematch conker/src_eu`).

## Commits

- Small batches, roughly 5–20 functions. Commit only after `verify_all.sh` (or at
  least `--quick`) passes. Run the full, non-quick version at least every few commits
  and before your last commit.
- Never leave uncommitted work at the end of a batch, and never commit a non-matching
  state.
- End every commit message with the `Co-Authored-By:` trailer your own harness
  attribution instructions give you, naming the model you are actually running as
  (e.g. `Co-Authored-By: Claude Sonnet 5.5 <noreply@anthropic.com>` on Sonnet). Don't
  copy another model's trailer.

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
