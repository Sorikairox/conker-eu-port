#!/bin/bash
# P106: run a shell command in conkerdev-port at /conker/conker (worktree conker/ dir)
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
exec docker exec -w /conker/conker conkerdev-port bash -c "$*"
