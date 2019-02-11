/* Based on http://denyadzi.github.io/blog/2014/12/25/assembly-hello-world-code-for-stm32f4discovery/ */

MEMORY
{
    FLASH (rx): ORIGIN = 0x8000000,     LENGTH = 1024K
    RAM (! rx): ORIGIN = 0x20000000,    LENGTH =192K
}

_estack = 0x20020000;
REGION_ALIAS("REGION_TEXT", FLASH);
REGION_ALIAS("REGION_INT_VECTORS", FLASH);

ENTRY(_start)

SECTIONS {
  .int_vector_table : {
    *(.int_vector_table)
  } > REGION_INT_VECTORS
  .text : {
    *(.text)
  } > REGION_TEXT
}
