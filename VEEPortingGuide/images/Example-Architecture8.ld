/*
*****************************************************************************
**  File        : LinkerScript.ld
*****************************************************************************
*/

SECTIONS
{
  .text_ro :
  {
    . = ALIGN(4);

    *libgcc.a:(.text .text.*)
    *lib_a-nano*.o(.text .text.*)
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.rodata.microej.features)

    . = ALIGN(4);
  } >FLASH

  .rodata_ro :
  {
    . = ALIGN(4);

    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    *(.rodata.microej.soar.*)
    *(.rodata.microej.resource.*)

    . = ALIGN(4);
  } >FLASH

  .bss_rw :
  {
    . = ALIGN(4);
    *(.bss)
    *(.bss*)
    *(COMMON)
    
    *(.bss.microej.stacks)
    *(.bss.microej.runtime)
    *(.bss.microej.heap)
    *(.bss.microej.immortals)

    . = ALIGN(4);
  } >DTCM


}
