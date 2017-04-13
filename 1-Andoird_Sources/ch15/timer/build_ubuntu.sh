# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=${PWD}
gcc -o test_timer ${PWD}/test_timer.c
testing=$(lsmod | grep  "timer_demo")
if [ "$testing" != "" ]; then
    rmmod timer_demo
fi
insmod ${PWD}/timer_demo.ko

