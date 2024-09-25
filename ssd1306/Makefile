obj-m += ssd1306_driver.o
ssd1306_driver-objs := ssd1306.o ssd1306_ctl.o

SRC = "/home/anhbt/Documents/bucket/Beaglebone/bb-kernel"

KERNEL_SRC = ${SRC}/KERNEL
CROSS = ${SRC}/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KERNEL_SRC) M=$(PWD) modules

build_app:
	/home/anhbt/Documents/bucket/Beaglebone/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc -o app_serial_driver app_serial_driver.c

clean:
	make -C $(KERNEL_SRC) M=$(shell pwd) clean

copy:
	scp ssd1306_driver.ko debian@192.168.0.101:/home/debian
