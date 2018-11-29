# Проект симулятора Ethereum Virtual Machine


## Начальная настройка проекта

### Инструкции для Linux

Для начала работы после клонирования проекта требуется единожды запустить скрипт (**ВНИМАНИЕ**, требуется ввести **пароль** от sudo):
```
./first-start
```
будет выполнено подключение необходимых модулей, а также установлены необходимые пакеты для сборки и работы симуляторов **go-ethereum**, **cemu** и **qemu**.

### Инструкции для Windows

Для начала работы после клонирования проекта требуется:
1. Установить среду [Cygwin](https://cygwin.com/install.html), а также необходимые пакеты для сборки проекта:
  * autoconf
  * automake
  * libmpc-devel
  * libmpfr-devel
  * libgmp-devel
  * gawk
  * bison
  * flex
  * texinfo
  * patchutils
  * gcc-core
  * gcc-g++
  * zlib-devel
  * libexpat-devel
  * make
  * libintl-devel
  * python2
  * mingw64-x86_64-gcc-g++
  * mingw64-x86_64-gcc-core
  * mingw64-x86_64-glib2.0
  * mingw64-x86_64-pixman
  * mingw64-x86_64-pkg-config
  * mingw64-x86_64-curl
  * mingw64-x86_64-gtk3
  * mingw64-x86_64-libssh2
  * mingw64-x86_64-libtasn1
  * mingw64-x86_64-nettle
  * mingw64-x86_64-ncurses
  * mingw64-x86_64-gnutls

2. Установить [solidity compiler для Windows](https://github.com/ethereum/solidity/releases/), а также пакет [Microsoft Visual C++ 2015 Redistributable](https://www.microsoft.com/en-us/download/details.aspx?id=52685). После распаковки архива с компилятором в нужное место (напр., *С:\solc*) добавить путь в переменную окружения PATH.

3. Установить MS Visual Studio (рекомендуется MS Visual Studio 2017), необходимую для сборки cemu и его библиотек

4. Загрузить и собрать [SystemC](http://www.accellera.org/downloads/standards/systemc) (строго рекомендуется версия 2.3.2). Для сборки использовать MS Visual Studio. Каталог SystemC расположить по пути *C:\systemc-2.3.2*.

*Примечание:* для использования библиотеки evm (*QEMU/qemu/ppdl-softmmu/libevm-ppdl.dll*) и симулятора (*QEMU/qemu/ppdl-softmmu/qemu-system-ppdl.exe*) под Windows необходимо добавить путь к библиотекам MinGW к переменной PATH (напр., *C:\cygwin64\usr\x86_64-w64-wingw32\sys-root\mingw\bin*).

*Примечание:* при использовании **gVm1** из Visual Studio вышеуказанные манипуляции с PATH проделывать необязательно.


## Сборка проекта

* Для сборки проекта необходимо выполнить:
```
./build-all
```  
будут собраны симуляторы **go-ethereum** (только Linux), **cemu** (только Linux) и **qemu**, а также тесты системы тестирования.

*Примечание:* для сборки CEMU под Windows используется MS Visual Studio (*C:\Users\alex\Desktop\kant1-pvmcore\emulator\models\evm\simulator\VC14\simulator.sln*)

Индикацией успешной сборки является наличие:
* **Linux**:
  1. бинарных файлов симуляторов:
      * *ethereum/build/bin/evm*
      * *emulator/bins/cemu*
      * *QEMU/qemu/ppdl-softmmu/qemu-system-ppdl*
  2. библиотек архитектуры:
      * *emulator/models/evm/simulator/evm.so*
      * *QEMU/qemu/ppdl-softmmu/libevm-ppdl.so*
  3. бинарных файлов тестов:
      * *tests/asm/test_name/test_name.bin*
* **Windows**:
  1. бинарных файлов симуляторов:
      * *emulator/bins/cemu.exe*
      * *QEMU/qemu/ppdl-softmmu/qemu-system-ppdl.exe*
  2. библиотек архитектуры:
      * *emulator/models/evm/simulator/bins/evm.dll*
      * *QEMU/qemu/ppdl-softmmu/libevm-ppdl.dll*
  3. бинарных файлов тестов:
      * *tests/asm/test_name/test_name.bin*

*Примечание:* в Windows выполнение любых команд необходимо производить из терминала Cygwin.


## Тестирование


### Запуск полного тестирования со сравнением

Для запуска тестов необходимо перейти в каталог *tests/asm/* и выполнить одну из команд:
```
make compare
make test-cemu
make test-qemu
```  

Система запустит поочередно каждый тест в двух симуляторах, сравнит выходные данные и выдаст результат теста:

* `make compare` запускает сравнение QEMU vs CEMU
* `make test-cemu` запускает сравнение CEMU vs EVM (только Linux)
* `make test-qemu` запускает сравнение QEMU vs EVM (только Linux)

По завершении тестирования будет дана сводка по количеству пройденных тестов в формате:
```
Test Result Summary:
    PASS: XXX
    FAIL: YYY
```


### Запуск отдельных тестов на симуляторе

Можно проводить запуск конкретных тестов на каком-либо симуляторе. Для этого необходимо перейти в каталог теста (напр., *tests/asm/add/*) и выполнить одну из команд:
```
make run-qemu
make run-cemu
make run-evm (только Linux)
```

Будет произведен запуск теста на соответствующем симуляторе и показан результат работы.
*Примечание:* опции запуска симуляторов описаны в файле *tests/asm/Makefile.in* в соответствующих секциях.
