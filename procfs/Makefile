#
# Makefile by appleboy <appleboy.tw AT gmail.com>
# Modified by fleuria <me.ssword AT gmail.com>
#
obj-m = procfs.o
KPATH :=/lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)

all:
	$(MAKE) -C $(KPATH) M=$(PWD) modules

clean:
	$(MAKE) -C $(KPATH) M=$(PWD) clean

insmod: all
	sudo rmmod procfs.ko; true
	sudo insmod procfs.ko

cat: insmod
	cat /proc/Moe
