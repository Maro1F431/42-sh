from math import *
from argparse import ArgumentParser as AP
from difflib import unified_diff as ud
from pathlib import Path
import pdb #Allow you to debug the code """
import subprocess as sp # Allow you to run the binary """
from termcolor import colored
import yaml #Allow you to use ymal file """


""" diff: Create two list
the first one will be the reference and the other one ours
then apply sys.stdout.writelines(ud(ref, ourresult, fromfile=ref, tofile=student))
use yml file
test per categories
"""

def runs(args, stdin):
    return sp.run(args, capture_output=True, text=True, input=stdin)

def diff(ref, mytest):
    ref = ref.splitlines(keepends=True)
    mytest = mytest.splitlines(keepends=True)
    return ''.join(ud(ref, mytest, fromfile="ref", tofile="mytest"))

def do_test(binary, testcase):
    ref = runs(["bash", "--posix"], testcase["stdin"])
    mytest = runs([binary], testcase["stdin"])

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
    with open("test.yml", "r") as test_files:
        content = yaml.safe_load(test_files)
    for testcase in content:
        try:
            do_test(binary, testcase)
        except AssertionError as err:
            print(f"[{colored('Not Passed', 'red')}]", testcase)
            print(err)
        else:
            print(f"[{colored('Passed', 'green')}]", testcase)
