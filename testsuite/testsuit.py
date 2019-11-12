from math import *
from argparse import ArgumentParser as AP
from difflib import unified_diff as ud
from pathlib import Path
import pdb
import subprocess as sp
from termcolor import colored

""" diff: Create two list
the first one will be the reference and the other one ours
then apply sys.stdout.writelines(ud(ref, ourresult, fromfile=ref, tofile=student))
use yml file
test per categories
"""

"""stdin = "ls"
ref = sp.run(["bash", "--posix"], capture_output = True, text = True, input = stdin)
mytest = sp.run([binary], capture_output = True, text = True, input = stdin)
"""

def runs(args, stdin):
    return sp.run(args, capture_output=True, text=True, input=stdin)

def diff(ref, mytest):
    ref = ref.splitlines(keepends=True)
    mytest = mytest.splitlines(keepends=True)
    return ''.join(ud(ref, mytest, fromfile="ref", tofile="mytest"))

def do_test(binary, stdin):
    ref = runs(["bash", "--posix"], stdin)
    mytest = runs([binary], stdin)

    assert ref.stdout == mytest.stdout, \
    f"stdout differs:\n{diff(ref.stdout, mytest.stdout)}"

    assert ref.stderr == mytest.stderr, \
    f"stderr differs:\n{diff(ref.stderr, mytest.stderr)}"

    assert ref.returncode == mytest.returncode, \
    f"return code differs:\n{diff(ref.returncode, mytest.returncode)}"



if __name__ == '__main__':
    parser = AP(description = "Test suit")
    parser.add_argument('bin', metavar = 'BIN')
    args = parser.parse_args()
    binary = Path(args.bin).absolute()
    for testcase in ["ls", "ls -la"]:
        try:
            do_test(binary, testcase)
        except AssertionError as err:
            print(f"[{colored('Not Passed', 'red')}]")
            print(err)
        else:
            print(f"[{colored('Passed', 'green')}]")
