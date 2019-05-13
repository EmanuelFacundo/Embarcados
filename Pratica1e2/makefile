CHAIN=arm-none-eabi-
CFLAGS=-std=c99 -Wall
IPATH=-Iinc/
SRC=src/
OBJ=obj/
BIN=bin/

all: app

app: start.o gpio.o LEDBlink.o
	$(CHAIN)ld $(OBJ)start.o $(OBJ)gpio.o $(OBJ)LEDBlink.o -T $(SRC)memmap.ld -o $(OBJ)LEDBlink.elf
	$(CHAIN)objcopy $(OBJ)LEDBlink.elf $(BIN)spl.boot -O binary
	cp $(BIN)spl.boot /tftpboot/LEDBlink.bin

start.o: $(SRC)start.s
	$(CHAIN)as $(SRC)start.s -o $(OBJ)start.o

gpio.o:	$(SRC)gpio.c
	$(CHAIN)gcc $(CFLAGS) $(IPATH) -c $(SRC)gpio.c -o $(OBJ)gpio.o

LEDBlink.o: $(SRC)LEDBlink.c
	$(CHAIN)gcc $(CFLAGS) $(IPATH) -c $(SRC)LEDBlink.c -o $(OBJ)LEDBlink.o

copy:
	cp $(BIN)spl.boot /tftpboot/LEDBlink.bin

clean:
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)*.elf
	rm -rf $(BIN)*.boot
#
#dump:
#	$(CHAIN)objdump -D $(OBJ)LEDBlink.elf
#
