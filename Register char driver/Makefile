obj-m += register1.o

KSRC = /lib/modules/$(shell uname -r)/build
all:
	make -C /home/user/workspace/multiple/kernel_ws/linux-4.14.202 M=${PWD} modules ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
