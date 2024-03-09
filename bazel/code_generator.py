#!/usr/bin/python3

from argparse import ArgumentParser
from shutil import copyfile
from sys import exit


def main():
    parser = ArgumentParser()
    parser.add_argument('--header_template', required=True)
    parser.add_argument('--header_output', required=True)
    parser.add_argument('--source_template', required=True)
    parser.add_argument('--source_output', required=True)
    args = parser.parse_args()
    # This is a toy example where we just copy the template files to the destination. I'm sure Hodges can dream up
    # something a bit more elaborate.
    copyfile(args.header_template, args.header_output)
    copyfile(args.source_template, args.source_output)
    return 0


if __name__ == '__main__':
    exit(main())