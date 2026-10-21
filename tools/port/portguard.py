"""Wrong-checkout guard for tools/port (P7). Import it first: `import portguard` (with tools/port on sys.path).

On the host it refuses (exit 3) unless
  - CONKER_ROOT is set explicitly (no ~/conker default for port tools),
  - the checkout that holds this script is CONKER_ROOT, and
  - the git toplevel of the cwd (if the cwd is in a repo) is CONKER_ROOT.
Inside a build container (/.dockerenv) it does nothing: paths there are /conker.
"""
import os, sys, subprocess


def _refuse(msg):
    sys.stderr.write('refusing: %s (run: eval "$(tools/eu_port/wt.sh env port)" in the same shell)\n' % msg)
    sys.exit(3)


def check():
    if os.path.exists('/.dockerenv'):
        return
    root = os.environ.get('CONKER_ROOT')
    if not root:
        _refuse('CONKER_ROOT is not set')
    root = os.path.realpath(os.path.expanduser(root))
    here = os.path.realpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
    if here != root:
        _refuse('script checkout %s != CONKER_ROOT %s' % (here, root))
    try:
        top = subprocess.run(['git', 'rev-parse', '--show-toplevel'], capture_output=True, text=True).stdout.strip()
    except Exception:
        top = ''
    if top and os.path.realpath(top) != root:
        _refuse('cwd repo %s != CONKER_ROOT %s' % (top, root))


check()
