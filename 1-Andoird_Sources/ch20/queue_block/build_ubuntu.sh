# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=$PWD

testing=$(lsmod | grep  "queue_block")
if [ "$testing" != "" ]; then
    rmmod queue_block
fi
#  安装simple_block驱动
insmod $PWD/queue_block.ko
