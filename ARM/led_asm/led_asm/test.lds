ENTRY(_start)
    SECTIONS{
        . = 0x43e00000;
        .text : {
            test.o(.text)
                *(.text)
        }
        .data : {
            *(.data)
        }
        .bss : {
            *(.bss)
        }
    }
