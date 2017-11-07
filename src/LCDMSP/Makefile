OBJECTS=MSPLCD.o Hitachi.o

GCC_DIR = C:\ti\msp430_gcc
GCC_BIN_DIR =  $(GCC_DIR)\bin
SUPPORT_FILE_DIRECTORY = $(GCC_DIR)\include

DEVICE  = msp430g2553
DEVICE_DATA = $(GCC_DIR)/msp430.dat

CC      = $(GCC_BIN_DIR)/msp430-elf-gcc
GDB     = $(GCC_BIN_DIR)/msp430-elf-gdb
GDB_AGENT = $(GCC_BIN_DIR)/gdb_agent_gui


CFLAGS = -I $(SUPPORT_FILE_DIRECTORY) -mmcu=$(DEVICE) -O2 -g
LFLAGS = -L $(SUPPORT_FILE_DIRECTORY)

all: ${OBJECTS}
	cls
	$(CC) $(CFLAGS) $(LFLAGS) $? -o $(DEVICE).out

debug: all
	CMD /C start $(GDB_AGENT) $(DEVICE_DATA)
	$(GDB) $(DEVICE).out -x gdbinit

attach: all
	$(GDB) $(DEVICE).out -x gdbinit

clean:
	del $(DEVICE).out
	del $(OBJECTS)