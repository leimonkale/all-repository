all:
	arm-linux-gcc   test.S   -o   test.o    -c    -g
	arm-linux-ld    test.o   -o   test.elf  -Ttest.lds
	arm-linux-objcopy -O binary test.elf test.bin

clean:
	rm  test.o  test.elf  test.bin
