LL = buildDir/libKe.a

MIPS64EL:
	ld.lld -T Targets/Scripts/MIPS64EL.ld -o kernel.elf $(LL)

MIPS64BE:
	ld.lld -T Targets/Scripts/MIPS64BE.ld -o kernel.elf $(LL)

I686:
	ld.lld -T Targets/Scripts/I686.ld -o kernel.elf $(LL)

RISCV64:
	ld.lld -T Targets/Scripts/RISCV64.ld -o kernel.elf $(LL)