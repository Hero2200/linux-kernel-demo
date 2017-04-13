# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=$PWD

testing=$(lsmod | grep  "no_queue_block")
if [ "$testing" != "" ]; then
    rmmod no_queue_block
fi
#  安装simple_block驱动
insmod $PWD/no_queue_block.ko
