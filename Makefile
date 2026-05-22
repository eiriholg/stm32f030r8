TARGET  = blink
CROSS   = arm-none-eabi-
CC      = $(CROSS)gcc
OBJCOPY = $(CROSS)objcopy

CFLAGS  = -mcpu=cortex-m0 -mthumb -Os -Wall -Wextra -ffreestanding -fno-common
LDFLAGS = -T linker.ld -nostartfiles -Wl,--gc-sections

SRCS = src/main.c src/startup.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET).bin

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

flash: $(TARGET).bin
	st-flash write $< 0x08000000

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin

.PHONY: all flash clean
