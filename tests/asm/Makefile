GASLIMIT=0x0
export GASLIMIT

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
	# with segfault $(MAKE) -C byte compare
	$(MAKE) -C add compare
	$(MAKE) -C sub compare
	$(MAKE) -C mul compare
	$(MAKE) -C div compare
	$(MAKE) -C mod compare
	$(MAKE) -C smod compare
	# with segfault $(MAKE) -C addmod compare
	# with segfault $(MAKE) -C mulmod compare
	$(MAKE) -C exp compare
	$(MAKE) -C signextend compare
	$(MAKE) -C gaslimit compare GASLIMIT=0xfff
	$(MAKE) -C gas compare GASLIMIT=0xfff
	$(MAKE) -C gasprice compare
	# with segfault $(MAKE) -C address compare
	# with segfault $(MAKE) -C balance compare
	# with segfault $(MAKE) -C origin compare
	# with segfault $(MAKE) -C caller compare
	$(MAKE) -C callvalue compare
	$(MAKE) -C codesize compare
	$(MAKE) -C sha3 compare

	# with segfault $(MAKE) -C extcodesize compare
	@echo "\n\nTest Results:\n\tPASS: `cat passes | wc -l`\n\tFAIL: `cat fails | wc -l`\n"

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
	$(MAKE) -C mod run-evm
	$(MAKE) -C smod run-evm
	$(MAKE) -C addmod run-evm
	$(MAKE) -C mulmod run-evm
	$(MAKE) -C exp run-evm
	$(MAKE) -C signextend run-evm
	$(MAKE) -C gaslimit run-evm GASLIMIT=0xfff
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
	$(MAKE) -C mod run-cemu
	$(MAKE) -C smod run-cemu
	$(MAKE) -C addmod run-cemu
	$(MAKE) -C mulmod run-cemu
	$(MAKE) -C exp run-cemu
	$(MAKE) -C signextend run-cemu
	$(MAKE) -C gaslimit run-cemu GASLIMIT=0xfff
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
