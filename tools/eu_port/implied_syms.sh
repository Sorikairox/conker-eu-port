#!/bin/bash
# Print SYM lines (symbol = implied EU address) for C functions given as file:func pairs.
# Run from conker/ inside the container.
for pair in "$@"; do
  f=${pair%%:*}; fn=${pair##*:}
  python3 ../tools/eu_port/check_funcs.py "$f" "$fn" -s
done
