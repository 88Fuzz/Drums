PROJECT_NAME = ElectricDrums

ARM_TOOLCHAIN = arm-none-eabi

#Micro specific definitions
PART=TM4C123GH6PM
CPU=-mcpu=cortex-m4
FPU=-mfpu=fpv4-sp-d16 -mfloat-abi=softfp

TIVAWARE_LIB_PATH=/home/kyle/ti/SW-TM4C/
TIVAWARE_LIB=${TIVAWARE_LIB_PATH}driverlib/gcc/libdriver.a
LOCAL_INCLUDES=inc/

#Program name definition for ARM GNU C compiler.
CC	= ${ARM_TOOLCHAIN}-gcc
#Program name definition for ARM GNU Linker.
LD	= ${ARM_TOOLCHAIN}-ld
#Program name definition for ARM GNU Object copy.
CP	= ${ARM_TOOLCHAIN}-objcopy
#Program name definition for ARM GNU Object dump.
OD	= ${ARM_TOOLCHAIN}-objdump
#Program name definition for ARM GNU Debugger.
DB	= ${ARM_TOOLCHAIN}-gdb

#Base arguments for C compiler.
CFLAGS=-mthumb ${CPU} ${FPU} -ffunction-sections -fdata-sections -MD -std=c99 -Wall -pedantic -c
#Library paths passed as flags.
CFLAGS+= -I${TIVAWARE_LIB_PATH} -I${LOCAL_INCLUDES} -DPART_$(PART) -DTARGET_IS_BLIZZARD_RA1

# Flags for LD
LFLAGS  = --gc-sections --entry ResetISR

# Flags for objcopy
CPFLAGS = -O binary

# Flags for objectdump
ODFLAGS = -S

# Uploader tool path.
FLASHER=lm4flash
# Flags for the uploader program.
FLASHER_FLAGS=
# Linker file name
LINKER_FILE = src/ldStart.ld

# Startup file name (W/O .c extension eg. "LM4F_startup")
STARTUP_FILE = startup_gcc

# On chip debugger 
OC_DEBUGGER=openocd

DIRS = obj bin
SRC = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,obj/%.o,$(SRC))
EXE = bin/${PROJECT_NAME}

all: dirs setupRelease $(OBJS) ${PROJECT_NAME}.axf ${PROJECT_NAME}
debug: dirs setupDebug $(OBJS) ${PROJECT_NAME}.axf ${PROJECT_NAME}

dirs:
	@mkdir -p $(DIRS)

setupDebug:
	@echo
	@echo ADDING -g option
	$(eval CFLAGS_RELEASE = ${CFLAGS} -g)

setupRelease:
	@echo
	@echo ADDING -O2 option
	$(eval CFLAGS_RELEASE = ${CFLAGS} -O2)

obj/%.o : src/%.c
	@echo
	@echo Compiling release $<
	$(CC) $(CFLAGS_RELEASE) ${<} -o ${@}

${PROJECT_NAME}.axf: $(OBJS)
	@echo
	@echo Linking $<
	$(LD) -T $(LINKER_FILE) $(LFLAGS) -o ${EXE}.axf $(OBJS) ${TIVAWARE_LIB}

${PROJECT_NAME}: ${EXE}.axf
	@echo
	@echo Creating binary $<
	$(CP) $(CPFLAGS) ${EXE}.axf ${EXE}.bin

load:
	sudo lm4flash ${EXE}.bin

loadD:
	@echo
	@echo target extended-remote :3333
	@echo monitor reset halt
	@echo load
	@echo monitor reset init
	@echo
	arm-none-eabi-gdb ${EXE}.axf

ocd:
	@echo sudo openocd --file /usr/local/share/openocd/scripts/board/ek-lm4f120xl.cfg

openocd:
	@echo sudo openocd --file /usr/local/share/openocd/scripts/board/ek-lm4f120xl.cfg

clean:
	rm bin/* obj/*
