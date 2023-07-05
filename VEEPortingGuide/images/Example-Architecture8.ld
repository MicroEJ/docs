/* Linker Script Template for Architecture 8.x */
SECTIONS
{
  /* .text sections (code) */
  .text_ro :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
  } >ROM

  /* .rodata sections (constants, strings, etc.) */
  .rodata_ro :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    *(.rodata.microej.soar)
    *(.rodata.microej.resource.*)
    *(.rodata.microej.features)
  } >ROM
  
  /* readwrite region initializers (mandatory) */
  .data :
  {
    . = ALIGN(4);
    *(.data)
    *(.data*)
  } >RAM AT> ROM
  
  /* .bss sections (statics, buffers, etc.) */
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
    *(.bss.microej.features)
  } >RAM
}
