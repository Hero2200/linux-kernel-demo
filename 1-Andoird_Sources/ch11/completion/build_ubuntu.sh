# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=$PWD
testing=$(lsmod | grep  "completion")
if [ "$testing" != "" ]; then
    rmmod completion
fi
insmod $PWD/completion.ko completion_type=$completion_type

