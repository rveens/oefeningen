#!/bin/bash

sudo insmod helloworld.ko initial_data="APPEL"
sudo mknod /dev/helloworld c 251 0
sudo chmod 777 /dev/helloworld
