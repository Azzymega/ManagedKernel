
ENTRY(_start)

SECTIONS
{

	. = 1M;
 	KernelStart = .;

	.text :
	{
		*(.multiboot)
		*(.text)
	}

	/* Read-only data. */
	.rodata ALIGN(4K) :
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data ALIGN(4K) :
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss ALIGN(4K) :
	{
		*(COMMON)
		*(.bss)
	}
	KernelEnd = ALIGN(4K);
	/* The compiler may produce other sections, by default it will put them in
	   a segment with the same name. Simply add stuff here as needed. */
}