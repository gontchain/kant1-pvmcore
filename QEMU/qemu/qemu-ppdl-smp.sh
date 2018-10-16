#!/usr/bin/env sh

if [ -z "$1" ]
then
    echo "Необходимо ввести полный путь до первого бинарного файла"
    exit 1
fi

if [ -z "$2" ]
then
    echo "Необходимо ввести полный путь до второго бинарного файла"
    exit 2
fi

rm -f shared_mem

./ppdl-linux-user/qemu-ppdl $1 &
./ppdl-linux-user/qemu-ppdl $2

rm -f shared_mem
