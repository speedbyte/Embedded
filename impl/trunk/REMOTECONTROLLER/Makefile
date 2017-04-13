ARCH := arm
UNAME := $(shell uname -m)
ifeq ($(UNAME),armv6l)
	KDIR := /usr/src/linux/
else
	CROSS_COMPILE:=/home/user/rpi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-
	KDIR := /home/user/rpi/linux-rt-rpi/
endif

ifneq ($(KERNELRELEASE),)
	obj-m := ppmDemux.o
else

default:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KDIR) M=$(PWD) modules
endif

clean:
	rm -rf *.ko *.o .*.cmd .tmp_versions Module.symvers
	rm -rf modules.order *.mod.c
