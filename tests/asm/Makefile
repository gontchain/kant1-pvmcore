ifndef VERBOSE
MAKEFLAGS += --no-print-directory
endif

GASLIMIT=0x0
export GASLIMIT

.SILENT: compare test-cemu test-qemu

all:
	$(MAKE) -C lt
	$(MAKE) -C gt
	$(MAKE) -C slt
	$(MAKE) -C sgt
	$(MAKE) -C eq
	$(MAKE) -C iszero
	$(MAKE) -C and
	$(MAKE) -C or
	$(MAKE) -C xor
	$(MAKE) -C not
	$(MAKE) -C byte
	$(MAKE) -C add
	$(MAKE) -C sub
	$(MAKE) -C mul
	$(MAKE) -C div
	$(MAKE) -C sdiv
	$(MAKE) -C mod
	$(MAKE) -C smod
	$(MAKE) -C addmod
	$(MAKE) -C mulmod
	$(MAKE) -C exp
	$(MAKE) -C signextend
	$(MAKE) -C gaslimit
	$(MAKE) -C gas
	$(MAKE) -C gasprice
	$(MAKE) -C address
	$(MAKE) -C balance
	$(MAKE) -C origin
	$(MAKE) -C caller
	$(MAKE) -C callvalue
	$(MAKE) -C codesize
	$(MAKE) -C extcodesize
	$(MAKE) -C sha3
	$(MAKE) -C msize
	$(MAKE) -C sload

test-qemu:
	@rm -rf passes
	@rm -rf fails
	$(MAKE) -C lt test-qemu
	$(MAKE) -C gt test-qemu
	$(MAKE) -C slt test-qemu
	$(MAKE) -C sgt test-qemu
	$(MAKE) -C eq test-qemu
	$(MAKE) -C iszero test-qemu
	$(MAKE) -C and test-qemu
	$(MAKE) -C or test-qemu
	$(MAKE) -C xor test-qemu
	$(MAKE) -C not test-qemu
	$(MAKE) -C byte test-qemu
	$(MAKE) -C add test-qemu
	$(MAKE) -C sub test-qemu
	$(MAKE) -C mul test-qemu
	$(MAKE) -C div test-qemu
	$(MAKE) -C mod test-qemu
	$(MAKE) -C smod test-qemu
	$(MAKE) -C addmod test-qemu
	$(MAKE) -C mulmod test-qemu
	$(MAKE) -C exp test-qemu
	$(MAKE) -C signextend test-qemu
	$(MAKE) -C gaslimit test-qemu
	$(MAKE) -C gaslimit test-qemu GASLIMIT=0xffff
	$(MAKE) -C gas test-qemu
	$(MAKE) -C gas test-qemu GASLIMIT=0xffff
	$(MAKE) -C gasprice test-qemu
	# with segfault $(MAKE) -C address test-qemu
	# with segfault $(MAKE) -C balance test-qemu
	# with segfault $(MAKE) -C origin test-qemu
	# with segfault $(MAKE) -C caller test-qemu
	$(MAKE) -C callvalue test-qemu
	$(MAKE) -C codesize test-qemu
	$(MAKE) -C sha3 test-qemu
	$(MAKE) -C msize test-qemu
	$(MAKE) -C sload test-qemu
	# with segfault $(MAKE) -C extcodesize test-qemu

	echo "\nTest Result Summary:"
	echo "\tPASS: \c"
	if [ -f passes ]; then \
		echo "`cat passes | wc -l`"; \
	else \
		echo "0"; \
	fi
	echo "\tFAILS: \c"
	if [ -f fails ]; then \
		echo "`cat fails | wc -l`\n"; \
	else \
		echo "0\n"; \
	fi

test-cemu:
	@rm -rf passes
	@rm -rf fails
	$(MAKE) -C lt test-cemu
	$(MAKE) -C gt test-cemu
	$(MAKE) -C slt test-cemu
	$(MAKE) -C sgt test-cemu
	$(MAKE) -C eq test-cemu
	$(MAKE) -C iszero test-cemu
	$(MAKE) -C and test-cemu
	$(MAKE) -C or test-cemu
	$(MAKE) -C xor test-cemu
	$(MAKE) -C not test-cemu
	$(MAKE) -C byte test-cemu
	$(MAKE) -C add test-cemu
	$(MAKE) -C sub test-cemu
	$(MAKE) -C mul test-cemu
	$(MAKE) -C div test-cemu
	$(MAKE) -C mod test-cemu
	$(MAKE) -C smod test-cemu
	$(MAKE) -C addmod test-cemu
	$(MAKE) -C mulmod test-cemu
	$(MAKE) -C exp test-cemu
	$(MAKE) -C signextend test-cemu
	$(MAKE) -C gaslimit test-cemu
	$(MAKE) -C gaslimit test-cemu GASLIMIT=0xffff
	$(MAKE) -C gas test-cemu
	$(MAKE) -C gas test-cemu GASLIMIT=0xffff
	$(MAKE) -C gasprice test-cemu
	# with segfault $(MAKE) -C address test-cemu
	# with segfault $(MAKE) -C balance test-cemu
	# with segfault $(MAKE) -C origin test-cemu
	# with segfault $(MAKE) -C caller test-cemu
	$(MAKE) -C callvalue test-cemu
	$(MAKE) -C codesize test-cemu
	$(MAKE) -C sha3 test-cemu
	$(MAKE) -C msize test-cemu
	$(MAKE) -C sload test-cemu
	# with segfault $(MAKE) -C extcodesize test-cemu

	echo "\nTest Result Summary:"
	echo "\tPASS: \c"
	if [ -f passes ]; then \
		echo "`cat passes | wc -l`"; \
	else \
		echo "0"; \
	fi
	echo "\tFAILS: \c"
	if [ -f fails ]; then \
		echo "`cat fails | wc -l`\n"; \
	else \
		echo "0\n"; \
	fi

compare:
	@rm -rf passes
	@rm -rf fails
	$(MAKE) -C lt compare
	$(MAKE) -C gt compare
	$(MAKE) -C slt compare
	$(MAKE) -C sgt compare
	$(MAKE) -C eq compare
	$(MAKE) -C iszero compare
	$(MAKE) -C and compare
	$(MAKE) -C or compare
	$(MAKE) -C xor compare
	$(MAKE) -C not compare
	$(MAKE) -C byte compare
	$(MAKE) -C add compare
	$(MAKE) -C sub compare
	$(MAKE) -C mul compare
	$(MAKE) -C div compare
	$(MAKE) -C mod compare
	$(MAKE) -C smod compare
	$(MAKE) -C addmod compare
	$(MAKE) -C mulmod compare
	$(MAKE) -C exp compare
	$(MAKE) -C signextend compare
	$(MAKE) -C gaslimit compare
	$(MAKE) -C gaslimit compare GASLIMIT=0xffff
	$(MAKE) -C gas compare
	$(MAKE) -C gas compare GASLIMIT=0xffff
	$(MAKE) -C gasprice compare
	# with segfault $(MAKE) -C address compare
	# with segfault $(MAKE) -C balance compare
	# with segfault $(MAKE) -C origin compare
	# with segfault $(MAKE) -C caller compare
	$(MAKE) -C callvalue compare
	$(MAKE) -C codesize compare
	$(MAKE) -C sha3 compare
	$(MAKE) -C msize compare
	$(MAKE) -C sload compare
	# with segfault $(MAKE) -C extcodesize compare

	echo "\nTest Result Summary:"
	echo "\tPASS: \c"
	if [ -f passes ]; then \
		echo "`cat passes | wc -l`"; \
	else \
		echo "0"; \
	fi
	echo "\tFAILS: \c"
	if [ -f fails ]; then \
		echo "`cat fails | wc -l`\n"; \
	else \
		echo "0\n"; \
	fi

run-qemu:
	$(MAKE) -C lt run-qemu
	$(MAKE) -C gt run-qemu
	$(MAKE) -C slt run-qemu
	$(MAKE) -C sgt run-qemu
	$(MAKE) -C eq run-qemu
	$(MAKE) -C iszero run-qemu
	$(MAKE) -C and run-qemu
	$(MAKE) -C or run-qemu
	$(MAKE) -C xor run-qemu
	$(MAKE) -C not run-qemu
	$(MAKE) -C byte run-qemu
	$(MAKE) -C add run-qemu
	$(MAKE) -C sub run-qemu
	$(MAKE) -C mul run-qemu
	$(MAKE) -C div run-qemu
	$(MAKE) -C sdiv run-qemu
	$(MAKE) -C mod run-qemu
	$(MAKE) -C smod run-qemu
	$(MAKE) -C addmod run-qemu
	$(MAKE) -C mulmod run-qemu
	$(MAKE) -C exp run-qemu
	$(MAKE) -C signextend run-qemu
	$(MAKE) -C gaslimit run-qemu
	$(MAKE) -C gaslimit run-qemu GASLIMIT=0xfff
	$(MAKE) -C gas run-qemu
	$(MAKE) -C gas run-qemu GASLIMIT=0xfff
	$(MAKE) -C gasprice run-qemu
	$(MAKE) -C address run-qemu
	$(MAKE) -C balance run-qemu
	$(MAKE) -C origin run-qemu
	$(MAKE) -C caller run-qemu
	$(MAKE) -C callvalue run-qemu
	$(MAKE) -C codesize run-qemu
	$(MAKE) -C extcodesize run-qemu
	$(MAKE) -C sha3 run-qemu
	$(MAKE) -C msize run-qemu
	$(MAKE) -C sload run-qemu

run-evm:
	$(MAKE) -C lt run-evm
	$(MAKE) -C gt run-evm
	$(MAKE) -C slt run-evm
	$(MAKE) -C sgt run-evm
	$(MAKE) -C eq run-evm
	$(MAKE) -C iszero run-evm
	$(MAKE) -C and run-evm
	$(MAKE) -C or run-evm
	$(MAKE) -C xor run-evm
	$(MAKE) -C not run-evm
	$(MAKE) -C byte run-evm
	$(MAKE) -C add run-evm
	$(MAKE) -C sub run-evm
	$(MAKE) -C mul run-evm
	$(MAKE) -C div run-evm
	$(MAKE) -C sdiv run-evm
	$(MAKE) -C mod run-evm
	$(MAKE) -C smod run-evm
	$(MAKE) -C addmod run-evm
	$(MAKE) -C mulmod run-evm
	$(MAKE) -C exp run-evm
	$(MAKE) -C signextend run-evm
	$(MAKE) -C gaslimit run-evm
	$(MAKE) -C gaslimit run-evm GASLIMIT=0xfff
	$(MAKE) -C gas run-evm
	$(MAKE) -C gas run-evm GASLIMIT=0xfff
	$(MAKE) -C gasprice run-evm
	$(MAKE) -C address run-evm
	$(MAKE) -C balance run-evm
	$(MAKE) -C origin run-evm
	$(MAKE) -C caller run-evm
	$(MAKE) -C callvalue run-evm
	$(MAKE) -C codesize run-evm
	$(MAKE) -C extcodesize run-evm
	$(MAKE) -C sha3 run-evm
	$(MAKE) -C msize run-evm
	$(MAKE) -C sload run-evm

run-cemu:
	$(MAKE) -C lt run-cemu
	$(MAKE) -C gt run-cemu
	$(MAKE) -C slt run-cemu
	$(MAKE) -C sgt run-cemu
	$(MAKE) -C eq run-cemu
	$(MAKE) -C iszero run-cemu
	$(MAKE) -C and run-cemu
	$(MAKE) -C or run-cemu
	$(MAKE) -C xor run-cemu
	$(MAKE) -C not run-cemu
	$(MAKE) -C byte run-cemu
	$(MAKE) -C add run-cemu
	$(MAKE) -C sub run-cemu
	$(MAKE) -C mul run-cemu
	$(MAKE) -C div run-cemu
	$(MAKE) -C sdiv run-cemu
	$(MAKE) -C mod run-cemu
	$(MAKE) -C smod run-cemu
	$(MAKE) -C addmod run-cemu
	$(MAKE) -C mulmod run-cemu
	$(MAKE) -C exp run-cemu
	$(MAKE) -C signextend run-cemu
	$(MAKE) -C gaslimit run-cemu
	$(MAKE) -C gaslimit run-cemu GASLIMIT=0xfff
	$(MAKE) -C gas run-cemu
	$(MAKE) -C gas run-cemu GASLIMIT=0xfff
	$(MAKE) -C gasprice run-cemu
	$(MAKE) -C address run-cemu
	$(MAKE) -C balance run-cemu
	$(MAKE) -C origin run-cemu
	$(MAKE) -C caller run-cemu
	$(MAKE) -C callvalue run-cemu
	$(MAKE) -C codesize run-cemu
	$(MAKE) -C extcodesize run-cemu
	$(MAKE) -C sha3 run-cemu
	$(MAKE) -C msize run-cemu
	$(MAKE) -C sload run-cemu

clean:
	$(MAKE) -C lt clean
	$(MAKE) -C gt clean
	$(MAKE) -C slt clean
	$(MAKE) -C sgt clean
	$(MAKE) -C eq clean
	$(MAKE) -C iszero clean
	$(MAKE) -C and clean
	$(MAKE) -C or clean
	$(MAKE) -C xor clean
	$(MAKE) -C not clean
	$(MAKE) -C byte clean
	$(MAKE) -C add clean
	$(MAKE) -C sub clean
	$(MAKE) -C mul clean
	$(MAKE) -C div clean
	$(MAKE) -C sdiv clean
	$(MAKE) -C mod clean
	$(MAKE) -C smod clean
	$(MAKE) -C addmod clean
	$(MAKE) -C mulmod clean
	$(MAKE) -C exp clean
	$(MAKE) -C signextend clean
	$(MAKE) -C gaslimit clean
	$(MAKE) -C gas clean
	$(MAKE) -C gasprice clean
	$(MAKE) -C address clean
	$(MAKE) -C balance clean
	$(MAKE) -C origin clean
	$(MAKE) -C caller clean
	$(MAKE) -C callvalue clean
	$(MAKE) -C codesize clean
	$(MAKE) -C extcodesize clean
	$(MAKE) -C sha3 clean
	$(MAKE) -C msize clean
	$(MAKE) -C sload clean
