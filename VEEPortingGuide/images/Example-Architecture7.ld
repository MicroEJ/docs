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

    . = ALIGN(4);
  } >FLASH

  .rodata_ro :
  {
    . = ALIGN(4);

    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    *(.text.soar)
    *(.rodata.resources)
    *(.text.features.installed)

    . = ALIGN(4);
  } >FLASH

  .bss_rw :
  {
    . = ALIGN(4);
    *(.bss)
    *(.bss*)
    *(COMMON)
    
    *(.bss.vm.stacks.java)
    *(ICETEA_HEAP)
    *(_java_heap)
    *(_java_immortals)
    *(.bss.features.installed)    

    . = ALIGN(4);
  } >RAM
}
