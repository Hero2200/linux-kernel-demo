# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=${PWD}
testing=$(lsmod | grep  "tasklet")
if [ "$testing" != "" ]; then
    rmmod tasklet
fi
testing=$(lsmod | grep  "wq")
if [ "$testing" != "" ]; then
    rmmod wq
fi

insmod ${PWD}/tasklet.ko
insmod ${PWD}/wq.ko

