ENTRY(Reset_Handler)

/* Fine della RAM (Inizio 0x20000000 + Dimensione 128KB) */
_estack = 0x20020000;    

_Min_Heap_Size = 0x200;      /* Spazio riservato all'Heap */
_Min_Stack_Size = 0x400;     /* Spazio riservato allo Stack */

/* Mappa di memoria fisica */
MEMORY
{
  FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 512K
  RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
  /* Vettore degli interrupt (deve andare all'inizio della Flash) */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >FLASH

  /* Il codice di programma */
  .text :
  {
    . = ALIGN(4);
    *(.text)           
    *(.text*)          
    . = ALIGN(4);
  } >FLASH

  /* Dati in sola lettura (es. costanti, stringhe) */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

  /* Variabili inizializzate (vengono copiate da Flash a RAM all'avvio) */
  _sidata = LOADADDR(.data);
  .data :
  {
    . = ALIGN(4);
    _sdata = .;        
    *(.data)           
    *(.data*)          
    . = ALIGN(4);
    _edata = .;        
  } >RAM AT> FLASH

  /* Variabili non inizializzate (azzerate all'avvio) */
  .bss :
  {
    _sbss = .;         
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;         
    __bss_end__ = _ebss;
  } >RAM

  /* Verifica dello spazio minimo rimasto per Heap e Stack */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM
}