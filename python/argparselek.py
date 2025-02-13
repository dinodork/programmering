#!/usr/bin/env python3

import argparse


def main():
    parse_arguments()

def parse_arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description = 'Migrate a component.')
    parser.add_argument(
        "-f",
    )
    parser.add_argument(
        "-s",
        "--settings",
    )
    print("before peae")
    arguments = parser.parse_args()
    print("return shit")
    return arguments

if __name__ == "__main__":
    main()
