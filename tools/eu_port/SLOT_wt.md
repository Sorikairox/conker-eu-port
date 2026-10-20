# Slot: worktree a (parallel session)

You work in the **git worktree** ~/conker-wt/a (branch `eu-wt-a`). Another agent works in
the main checkout ~/conker: never touch ~/conker, its `conkerdev` container, or branch `eu`.

- **In every shell, before any tool:** `cd ~/conker-wt/a && eval "$(tools/eu_port/wt.sh env a)"`
  (your container is `conkerdev-a`).
- Read tools/eu_port/AGENT_BRIEF.md and follow it exactly. Then HANDOFF.md, and
  docs/IDO_SHAPES.md before matching.
- Keep job outputs under conker/build_port/ in the worktree (not the shared Claude
  scratchpad).
- **Never pkill/pgrep by name on the host**, since that kills the other agent's jobs.
  Kill only PIDs you started, or your own /work/<id> jobs on the Mac mini.
- **Slice:** game files whose name ends in a hex offset **at or above 0x130000**, plus
  init (src_eu/init_*, src_eu/libultra/**) and debugger (src_eu/debugger*). Don't touch
  game files below 0x130000.
- Shared headers: only add lines or change single prototypes, then run check_files.py on
  everything.
- Commit on `eu-wt-a` only; never merge into `eu` (the coordinator does that).
- Budget: 2 work commits or about 40 functions tried, plus the hand-off commit. No
  background processes of yours may be left running.
- Hand-off: update HANDOFF's current state and next steps compactly, and add
  docs/sessions/sNN.md.
- **Hard context cap:** count your tool calls. After about 150, stop new work regardless of the
  function budget and do the hand-off. Keep tool outputs short (head/grep, no big asm dumps).
