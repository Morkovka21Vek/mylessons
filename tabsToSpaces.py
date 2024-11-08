import os
import sys

filesList = []

if sys.argv[-1].lower() in ["all", "-a", "--all"]:
    filesList = [os.path.join(os.getcwd(), path) for path in os.listdir(os.getcwd()) if not os.path.isdir(path)]
elif sys.argv[-1].lower() in ["ex", "-e", "--ex"]:
    filesList = [os.path.join(os.getcwd(), path) for path in os.listdir(os.getcwd()) if not os.path.isdir(path) and sys.argv[-2] in path]
elif sys.argv[-1].lower() in ["help", "-h", "--help"]:
    print("Эта программа предназначена для замены табуляций на пробелы, доступные команды:\n\t-a --all\tПреабразует все файлы в текущем каталоге\n\t<искать в названии> -e --ex\tПреабразует только файлы в названии которых есть некоторые заданные символы\n\t<Путь к файлу>\tПреобразует 1 файл по заданному пути")

else:
    filesList = [os.path.join(os.getcwd(), sys.argv[-1])]
    #filesList = [sys.argv[-1]]

for file in filesList:
    print("Преобразование файла: ", file)
    if input("Можно преобразовать?[Y/n]") != "n":
        with open(file, 'r+') as f:
            text = f.read()
            text = text.replace("\t", "  ")
            f.seek(0)
            f.write(text)
            f.truncate()

