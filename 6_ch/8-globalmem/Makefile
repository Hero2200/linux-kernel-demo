obj-m = demo.o
demo-objs = chr_dev.o
KDIR :=/lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
cl:
	make -C $(KDIR) M=$(PWD) clean
