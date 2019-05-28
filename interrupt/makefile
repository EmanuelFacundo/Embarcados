CHAIN=$(CHAINPATH)arm-none-eabi
CFLAGS=-mcpu=cortex-a8 -march=armv7-a -mfpu=vfp -mfloat-abi=softfp
AFLAGS=-mfpu=neon -mcpu=cortex-a8
IPATH=-Iinc/
SRC=src/
OBJ=obj/
BIN=bin/

all: app

app: start.o cpu.o main.o gpio.o pad.o control_module.o clock_module.o interrupt.o
	$(CHAIN)-ld $(OBJ)start.o $(OBJ)cpu.o $(OBJ)main.o $(OBJ)gpio.o $(OBJ)pad.o $(OBJ)control_module.o $(OBJ)clock_module.o $(OBJ)interrupt.o -T $(SRC)memmap.ld -o $(OBJ)main.elf
	$(CHAIN)-objcopy $(OBJ)main.elf $(BIN)spl.boot -O binary
	cp $(BIN)spl.boot /tftpboot/appGpio.bin

start.o: $(SRC)start.s
	$(CHAIN)-as $(AFLAGS) $(SRC)start.s -o $(OBJ)start.o

cpu.o: $(SRC)cpu.c
	$(CHAIN)-gcc $(AFLAGS) $(IPATH) -c $(SRC)cpu.c -o $(OBJ)cpu.o

main.o: $(SRC)main.c
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)main.c -o $(OBJ)main.o
                                        
gpio.o: $(SRC)gpio.c                          
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)gpio.c -o $(OBJ)gpio.o
 
pad.o: $(SRC)pad.c                            
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)pad.c -o $(OBJ)pad.o

control_module.o: $(SRC)control_module.c
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)control_module.c -o $(OBJ)control_module.o

clock_module.o: $(SRC)clock_module.c
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)clock_module.c -o $(OBJ)clock_module.o

interrupt.o: $(SRC)interrupt.c
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)interrupt.c -o $(OBJ)interrupt.o

copy:
	cp $(BIN)spl.boot /tftpboot/appGpio.bin

clean:
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)*.elf
	rm -rf $(BIN)*.boot

dump:
	$(CHAIN)-objdump -D $(OBJ)main.elf
