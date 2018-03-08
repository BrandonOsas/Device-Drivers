/* Memory Spaces Definitions */

MEMORY
{
  RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 64K
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 256K
}

/* Sections Definitions */

SECTIONS
{
    /* for Cortex devices, the beginning of the startup code is stored in the .isr_vector section, which goes to FLASH */
    .isr_vector :
    {
    . = ALIGN(4);
        KEEP(*(.isr_vector))            /* Startup code */
    . = ALIGN(4);
    } >FLASH

    /* for some STRx devices, the beginning of the startup code is stored in the .flashtext section, which goes to FLASH */
    .flashtext :
    {
    . = ALIGN(4);
        *(.flashtext)                   /* Startup code */
    . = ALIGN(4);
    } >FLASH

    /* the program code is stored in the .text section, which goes to Flash */
    .text :
    {
        . = ALIGN(4);

        *(.text)                        /* remaining code */
        *(.text.*)                      /* remaining code */
        *(.rodata)                      /* read-only data (constants) */
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)

        . = ALIGN(4);
     _etext = .;
        /* This is used by the startup in order to initialize the .data secion */
     _sidata = _etext;
    } >FLASH

    /* This is the initialized data section
    The program executes knowing that the data is in the RAM
    but the loader puts the initial values in the FLASH (inidata).
    It is one task of the startup to copy the initial values from FLASH to RAM. */
    .data  : AT ( _sidata )
    {
        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .data secion */
        _sdata = . ;

        *(.data)
        *(.data.*)

        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .data secion */
     _edata = . ;
    } >RAM

	.bss :
	{
		_sbss = .;
		*(.bss*)
		*(COMMON)
		_ebss = .;
		_end = .;
		__end = .;
	} > RAM

    /* This is the stack section, top of stack = top of RAM */
    .stack 0x20010000 :
	{
	    . = ALIGN(4);
		_estack = .;
	} >RAM
}
