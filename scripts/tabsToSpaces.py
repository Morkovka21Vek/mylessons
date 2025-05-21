#!/usr/bin/env python3
import os
import argparse


def init_parser():
    parser = argparse.ArgumentParser(description='Pretty code')
    parser.add_argument('-t', '--tabs', type=int, default=0, help='Fix tabs')
    parser.add_argument('-e', '--end', help='Fix end spaces', action='store_true')
    parser.add_argument('-f', '--file', type=str, help='Input files')
    return parser.parse_args()


def getfilelist(file):
    fileslist = []
    if os.path.isdir(file):
        fileslist = [os.path.join(file, path)
                     for path in os.listdir(file) if os.path.isfile(path)]
    elif os.path.isfile(file):
        fileslist = [file]
    else:
        print("Error")
    return fileslist


def pretty(text, tabs, end):
    if tabs > 0:
        text = text.replace("\t", "".join([' ' for _ in range(tabs)]))
    if end:
        split_text = text.split("\n")
        new_text = []
        for line in split_text:
            new_text.append(line.rstrip(" "))
            text = "\n".join(new_text)
    return text


def convert(file, tabs, end):
    with open(file, 'r+') as f:
        text = f.read()
        text = pretty(text, tabs, end)
        f.seek(0)
        f.write(text)
        f.truncate()


def main(args):
    if args.file:
        fileslist = getfilelist(args.file)
    else:
        print("use --file <file/dir>")
        quit(1)


    for file in fileslist:
        if input(f"Можно преобразовать {file}?[Y/n]") != "n":
            convert(file, args.tabs, args.end)

if __name__ == "__main__":
    args = init_parser()
    main(args)
