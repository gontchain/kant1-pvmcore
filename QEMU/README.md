### Проект симулятора архитектуры Ethereum

* Для работы после клонирования проекта требуется единожды запустить скрипт (**ВНИМАНИЕ**, требуется ввести **пароль** от sudo):
```
./first-start
```

* Для компиляции эмулятора необходимо из каталога qemu/ выполнить:
```
./configure --target-list=ppdl-softmmu --extra-cflags="-fPIC -D EVM" --enable-debug --disable-werror --disable-pie --disable-curses --disable-sdl --disable-vnc --disable-xen --disable-kvm
make
```

* Для запуска бинарных файлов из-под эмулятора необходимо из каталога qemu/ выполнить (**только после компиляции эмулятора**):
```
./ppdl-softmmu/qemu-system-ppdl -nodefaults -nographic -kernel /path/to/bin_file
``` 
доступны ещё опции:
```
-nodebug - отключение вывода отладочной информации
-ctrace - вывод трассы выполнения
-regtrace - вывод трассы изменения значений регистров
-memtrace - вывод трассы обращений по адресам памяти
```
