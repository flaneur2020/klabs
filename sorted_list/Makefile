MOD = sorted_list
KPATH :=/lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)
obj-m = $(MOD).o

all:
	$(MAKE) -C $(KPATH) M=$(PWD) modules

clean:
	$(MAKE) -C $(KPATH) M=$(PWD) clean

insmod: all
	sudo rmmod $(MOD).ko; true
	sudo insmod $(MOD).ko

log: 
	tail -f /var/log/messages
