obj-m := gpio_driver_example.o

SRC = "/home/anhbt/Documents/bucket/Beaglebone"

KERNEL_SRC = ${SRC}/bb-kernel/KERNEL
CROSS = ${SRC}/bb-kernel/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KERNEL_SRC) M=$(PWD) modules

build_app:
	${SRC}/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc -o app_serial_driver app_serial_driver.c

clean:
	make -C $(KERNEL_SRC) M=$(shell pwd) clean

copy:
	scp gpio_driver_example.ko debian@192.168.0.101:/home/debian
