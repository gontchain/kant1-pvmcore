# Ethereum Virtual Machine simulation project


## Prequisities

### Instructions for Linux

After cloning a project run the following script once (**WARNING**, this action requires administrative privilegies):
```
./first-start
```
this will initialize all necessary modules and install packages required for building and running **go-ethereum**, **cemu** and **qemu** simulators.

### Instructions for Windows

After cloning a project, you need to install:
1. [Cygwin](https://cygwin.com/install.html) and necessary packages for it:
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

2. [Solidity compiler for Windows](https://github.com/ethereum/solidity/releases/) and [Microsoft Visual C++ 2015 Redistributable](https://www.microsoft.com/en-us/download/details.aspx?id=52685) package for it. After unpacking the compiler archive into the desired destination (e.g., *С:\solc*) add it to your system's PATH variable.

3. Install MS Visual Studio (MS Visual Studio 2017 is recommended), required for building CEMU and its libraries.

4. Download and build [SystemC](http://www.accellera.org/downloads/standards/systemc) (recommended version is 2.3.2). Use MS Visual Studio for building. Place SystemC directory at *C:\systemc-2.3.2*.

*Note:* in order to use evm library (*QEMU/qemu/ppdl-softmmu/libevm-ppdl.dll*) and simulator (*QEMU/qemu/ppdl-softmmu/qemu-system-ppdl.exe*) under Windows it is necessary to append PATH environment variable with MinGW libraries path (e.g., *C:\cygwin64\usr\x86_64-w64-wingw32\sys-root\mingw\bin*).

*Note:* if using **gVm1** from Visual Studio, PATH manipulations described above are not necessary.


## Building

* In order to build the project, run:
```
./build-all
```  
this will build **go-ethereum** (Linux only), **cemu** (Linux only) and **qemu** simulators, and tests for testing system.

*Note:* to build CEMU under Windows, use MS Visual Studio (*C:\Users\alex\Desktop\kant1-pvmcore\emulator\models\evm\simulator\VC14\simulator.sln*)

Successful build is indicated by:
* **Linux**:
  1. simulator binaries:
      * *ethereum/build/bin/evm*
      * *emulator/bins/cemu*
      * *QEMU/qemu/ppdl-softmmu/qemu-system-ppdl*
  2. architecture libraries:
      * *emulator/models/evm/simulator/evm.so*
      * *QEMU/qemu/ppdl-softmmu/libevm-ppdl.so*
  3. test binaries:
      * *tests/asm/test_name/test_name.bin*
* **Windows**:
  1. simulator binaries:
      * *emulator/bins/cemu.exe*
      * *QEMU/qemu/ppdl-softmmu/qemu-system-ppdl.exe*
  2. architecture libraries:
      * *emulator/models/evm/simulator/bins/evm.dll*
      * *QEMU/qemu/ppdl-softmmu/libevm-ppdl.dll*
  3. test binaries:
      * *tests/asm/test_name/test_name.bin*

*Note:* using any command under Windows is meant to be run under Cygwin terminal.


## Testing


### Running full comparison testing

To run the tests, go into *tests/asm/* directory and run one of the following commands:
```
make compare
make test-cemu
make test-qemu
```  

Testing system will run each test with 2 simulators, compare the output and prompt the result summary:

* `make compare` compare QEMU vs CEMU
* `make test-cemu` compare CEMU vs EVM (Linux only)
* `make test-qemu` compare QEMU vs EVM (Linux only)

At the end of testing session the result summary will be prompted in a format:
```
Test Result Summary:
    PASS: XXX
    FAIL: YYY
```


### Running particular tests

It is possible to run particular test on any simulator. To do that, go into directory of desired test (e.g., *tests/asm/add/*) and run one of the following:
```
make run-qemu
make run-cemu
make run-evm (Linux only)
```

This will run test on a selected simulator and prompt the result.
*Note:* simulators' running options are listed in *tests/asm/Makefile.in* in the appropriate sections.
