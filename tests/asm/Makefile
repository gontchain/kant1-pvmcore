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

run:
	$(MAKE) -C lt run
	$(MAKE) -C gt run
	$(MAKE) -C slt run
	$(MAKE) -C sgt run
	$(MAKE) -C eq run
	$(MAKE) -C iszero run
	$(MAKE) -C and run
	$(MAKE) -C or run
	$(MAKE) -C xor run
	$(MAKE) -C not run
	$(MAKE) -C byte run
	$(MAKE) -C add run
	$(MAKE) -C sub run
	$(MAKE) -C mul run
	$(MAKE) -C div run
	$(MAKE) -C mod run
	$(MAKE) -C smod run
	$(MAKE) -C addmod run
	$(MAKE) -C mulmod run
	$(MAKE) -C exp run
	$(MAKE) -C signextend run
	$(MAKE) -C gaslimit run GASLIMIT=0xfff
	$(MAKE) -C gas run GASLIMIT=0xfff
	$(MAKE) -C gasprice run
	$(MAKE) -C address run
	$(MAKE) -C balance run
	$(MAKE) -C origin run
	$(MAKE) -C caller run
	$(MAKE) -C callvalue run
	$(MAKE) -C codesize run
	$(MAKE) -C extcodesize run

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
