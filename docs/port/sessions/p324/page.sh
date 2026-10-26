#!/bin/bash
# P324: quick headless page check (muted, det=2): page.sh SECS "STEPS" [EXTRA_QUERY]; STEPS = audprobe.js PROBE_STEPS
# (MS:eval:EXPR, MS:keydown:CODE, MS:keyup:CODE, MS:shot:PATH). Prints only the eval:/screenshot: lines.
cd ~/conker-wt/web || exit 1
while [ "$(ps -axo command | grep -v grep | grep -c 'headless=new')" -gt 0 ]; do sleep 20; done
PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$2" port/web/audprobe.sh "app=game&det=2&nohidepause=1${3:-}" "$1" 2>&1 | grep -E '^(eval|screenshot):'
