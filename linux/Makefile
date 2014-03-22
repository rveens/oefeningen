obj-m += helloworld.o

# Uncomment to turn off debug messages
DEBUG = y

ifeq ($(DEBUG),y)
	DEBUGFLAGS = -O -g -DHELLOWORLD_DEBUG
else
	DEBUGFLAGS = -O2
endif

KBUILD_EXTRA_SYMBOLS := /usr/src/nvidia-331-331.49/Module.symvers
EXTRA_CFLAGS := -I/usr/src/nvidia-331-331.49 $(DEBUGFLAGS)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
