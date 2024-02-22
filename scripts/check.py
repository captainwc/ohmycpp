import os
import argparse
import subprocess


def check_memleak(target):
    """check memory leak for target"""
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    cmd = [
        "valgrind",
        "--leak-check=full",
        "--show-leak-kinds=all",
        "--track-origins=yes",
        "--verbose",
        root + "/build/bin/" + target,
    ]
    result = subprocess.run(cmd, capture_output=True, text=True)
    # output_lines = result.stdout.splitlines()
    # last_five_lines = output_lines[-8:]
    print(result.stdout)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("target", help="target to check", default="lctest", nargs="?")
    args = parser.parse_args()
    check_memleak(args.target)
