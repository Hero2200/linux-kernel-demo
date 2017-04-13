# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=$PWD
gcc -static  -o ta $PWD/test_atomic.c
testing=$(lsmod | grep  "atomic")
#  如果atomic驱动已安装，先卸载atomic驱动
if [ "$testing" != "" ]; then
    rmmod atomic
fi
#  安装atomic驱动
insmod $PWD/atomic.ko atom=$atom

