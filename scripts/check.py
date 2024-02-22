import os
import argparse
import subprocess
import spdlog


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
    spdlog.info(target)
    subprocess.run(cmd)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("target", help="target to check", default="spdlogEg", nargs="?")
    args = parser.parse_args()
    check_memleak(args.target)
