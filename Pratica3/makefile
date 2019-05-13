CHAIN=arm-none-eabi-
CFLAGS=-std=c99 -Wall
IPATH=-Iinc/
SRC=src/
OBJ=obj/
BIN=bin/

all: app

app: start.o gpio.o LEDBlink_and_Buton.o
	$(CHAIN)ld $(OBJ)start.o $(OBJ)gpio.o $(OBJ)LEDBlink_and_Buton.o -T $(SRC)memmap.ld -o $(OBJ)LEDBlink_and_Buton.elf
	$(CHAIN)objcopy $(OBJ)LEDBlink_and_Buton.elf $(BIN)spl.boot -O binary
	cp $(BIN)spl.boot /tftpboot/LEDBlink_and_Buton.bin

start.o: $(SRC)start.s
	$(CHAIN)as $(SRC)start.s -o $(OBJ)start.o

gpio.o:	$(SRC)gpio.c
	$(CHAIN)gcc $(CFLAGS) $(IPATH) -c $(SRC)gpio.c -o $(OBJ)gpio.o

LEDBlink_and_Buton.o: $(SRC)LEDBlink_and_Buton.c
	$(CHAIN)gcc $(CFLAGS) $(IPATH) -c $(SRC)LEDBlink_and_Buton.c -o $(OBJ)LEDBlink_and_Buton.o

copy:
	cp $(BIN)spl.boot /tftpboot/LEDBlink_and_Buton.bin

clean:
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)*.elf
	rm -rf $(BIN)*.boot
#
#dump:
#	$(CHAIN)objdump -D $(OBJ)LEDBlink_and_Buton.elf
#
