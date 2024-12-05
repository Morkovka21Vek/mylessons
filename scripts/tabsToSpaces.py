import os
import sys
import argparse

def init_parser():
    parser = argparse.ArgumentParser(description='Pretty code')
    parser.add_argument('-t', '--tabs', type=int, default=0, help='Fix tabs')
    parser.add_argument('-e', '--end', help='Fix end spaces', action='store_true')
    parser.add_argument('-f', '--file', type=str, help='Input files')
    return parser.parse_args()

def main(args):
    if os.path.isdir(args.file):
        filesList = [os.path.join(args.file, path) for path in os.listdir(args.file) if os.path.isfile(path)]
        #filesList = [os.listdir(args.file)]
    elif os.path.isfile(args.file):
        filesList = [args.file]
    else:
        print("Error")
        exit(1)

    for file in filesList:
        print("Преобразование файла: ", file)
        if input("Можно преобразовать?[Y/n]") != "n":
            with open(file, 'r+') as f:
                text = f.read()
                if args.tabs:
                    text = text.replace("\t", "".join([' ' for _ in range(args.tabs)]))
                if args.end:
                    split_text = text.split("\n")
                    new_text = []
                    for line in split_text:
                        new_text.append(line.rstrip(" "))
                    text = "\n".join(new_text)
                f.seek(0)
                f.write(text)
                f.truncate()

if __name__ == "__main__":
    args = init_parser()
    main(args)


