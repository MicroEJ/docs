/* Linker Script Template for Architecture 7.x */
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
    *(.text.soar)
    *(.rodata.resources)
    *(.text.features.installed)
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
    *(.bss.vm.stacks.java)
    *(ICETEA_HEAP)
    *(_java_heap)
    *(_java_immortals)
    *(.bss.features.installed)
  } >RAM
}
