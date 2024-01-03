#!python
import argparse
import os


def hej():
    print("hej")

def main():
    print("bajskporv")
    parser = argparse.ArgumentParser()
    parser.add_argument("input_file")
    parser.add_argument("output_file")
    args = parser.parse_args()
    print("input fille " + args.input_file)
    print("utput fille " + args.output_file)
    hej()

    
if __name__ == "__main__":
    main()
    
