#include <iostream>
using namespace std;
int main(){
cout << 
"Навигация в Linux"
<< endl;
cout << 
"Показать текущий каталог: `pwd`"
<< endl;
cout << 
"Переход в домашний каталог: `cd ~` или `cd`"
<< endl;
cout << 
"Переход в родительский каталог: `cd ..`"
<< endl;
cout << 
"Переход в конкретный каталог: `cd <path>` Пример: `cd /tmp`"
<< endl;
cout << 
"Показать содержимое текущего каталога: `ls`"
<< endl;
cout << 
"Показать подробную информацию о содержимом каталога: `ls -l`"
<< endl;
cout << 
"Показать скрытые файлы в каталоге: `ls -a`"
<< endl;
cout << 
"Показать подробную информацию о содержимом и скрытые файлы в каталоге: `ls -al`"
<< endl;
cout << 
"Вывод содержимого директории в виде дерева: `tree <path>`"
<< endl;
cout << 
"Создать новый каталог: `mkdir <foldername>`"
<< endl;
cout << 
"Удалить файл: `rm <filename>`"
<< endl;
cout << 
"Удалить каталог: `rm -r <foldername>`"
<< endl;
cout << 
"Удалить пустой каталог: `rm -d <foldername>`"
<< endl;
cout << 
"Создание файла: `touch <filename>`"
<< endl;
cout << 
"Копировать файл(папку): `cp <sourcefile> <copiedfile>`"
<< endl;
cout << 
"Переименовать файл(папку): `mv <oldname> <newname>`"
<< endl;
cout << 
"Показать содержимое файла: `cat <filename>`"
<< endl;
cout << 
"Постраничный вывод содержимого файла: `less <filename>`"
<< endl;
cout << 
"Очистка экрана: `clear`"
<< endl;
cout << 
"Вывод истории команд: `history | tail -n x` - показ последних `x` команд "
<< endl;
}
