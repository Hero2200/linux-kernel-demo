obj-m := demo.o
demo-objs := completion.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	make -C $(KDIR) M=$(PWD) modules

cl:
	make -C $(KDIR) M=$(PWD) clean
