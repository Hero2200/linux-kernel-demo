# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=${PWD}
testing=$(lsmod | grep  "wait_queue")
if [ "$testing" != "" ]; then
    rmmod wait_queue
fi
insmod ${PWD}/wait_queue.ko

