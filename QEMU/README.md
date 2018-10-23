### Проект симулятора архитектуры Ethereum

* Для работы после клонирования проекта требуется единожды запустить скрипт (**ВНИМАНИЕ**, требуется ввести **пароль** от sudo, а также **логин и пароль** от GitLab'а):
```
./first-start
```

* Если возникла необходимость обновить подмодули, нужно выполнить (**ВНИМАНИЕ**, требуется ввести **логин и пароль** от GitLab'а):
```
./update-submodules
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
-showtrace - вывод трассы выполнения
-regtrace - вывод трассы изменения значений регистров
-memtrace - вывод трассы обращений по адресам памяти
-tick - отображение количества тактов
-rv - изменение регистра, из которого берётся результат эмуляции
-nosm - отключение semihosting'а
```

* Для отладки бинарных файлов из-под gdb необходимо из каталога qemu/ выполнить (**только после компиляции эмулятора и подключения toolchain'а**):
```
./ppdl-softmmu/qemu-system-ppdl -gdb tcp::1221 -nodefaults -nographic -kernel /path/to/bin_file &
nm-gdb /path/to/bin_file
```  
затем в открывшимся отладчике выполнить:
```
(gdb) target remote 127.0.0.1:1221
(gdb) load
далее можно заниматься отладкой, например:
(gdb) b main
(gdb) c
(gdb) print $pc
```
