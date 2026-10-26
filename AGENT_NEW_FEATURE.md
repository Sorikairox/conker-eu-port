# Feature agent brief

## Review of the previous briefs (P325/P326)

- **Too long:** each was about 3,000 characters, and most of it repeated rules already in `orchestrator.md` section 2.
- **Stale paths since P329:** `docs/port/sessions/P32x.md`, `docs/port/sessions/p322/check.sh` and `p320/run.sh` no longer exist. Use `tools/eu_port/check.sh`, `tools/port/scripts/warp.sh` and `docs/port/HANDOFF.md`.
- **Slow test route:** the old briefs used the 4-minute new-game route. `?warp=29` reaches gameplay in about 30 s.
- **Fix:** the brief below states the feature and how to prove it, and points to section 2 for the rules.

## Template

Fill in `<…>` and send. Keep it to one feature, or two small ones.

```
You are session P<NNN> of the Conker EU browser port. Budget ~150 tool calls.
Worktree ~/conker-wt/web (branch port-web). Before any repo tool:
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH; eval "$(tools/eu_port/wt.sh env web)"
Read orchestrator.md section 2 (rules) and the PLAN_NEW_FEATURE.md row.

Feature #<N>: "<name>". <one or two sentences on what the player sees>.
Start from: <function / file hints, or "grep tools/eu_port/names.tsv for …">.

Do:
1. Find where the original behaviour lives. Note the original values.
2. Add the change behind #ifdef PORT + port_option(PORT_OPT_<X>), as the existing options in
   port/ultra/port_options.h and port/web/main.js do. Off = exactly the N64 behaviour.
3. Prove it in the browser: tools/port/scripts/warp.sh with ?opt=<key>:1 vs off.
   Use screenshots or a measured number, and look at the screenshots yourself.
4. tools/eu_port/check.sh GREEN + tools/port/scripts/holdl.sh (5789 / 0x29 at 5795, no traps).
5. One commit for the feature, with a message that explains how it works (the user learns from it).
   Rename anything you touch that still has a vague name (names.tsv + apply_names.sh).
6. Update PLAYING.md (Options), PLAN_NEW_FEATURE.md (status), the HANDOFF.md session entry and
   the sessions.tsv row. Then run tools/eu_port/deploy_web.sh and tools/eu_port/backup_push.sh.

If you are blocked or denied permission, stop and report the exact command.
Report: commit hash, what the option does (original vs new), the evidence, and whether it was deployed.
```
