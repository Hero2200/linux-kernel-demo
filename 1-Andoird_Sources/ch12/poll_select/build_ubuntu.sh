# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=${PWD}
gcc -o test_select ${PWD}/test_select.c
testing=$(lsmod | grep  "poll_select")
if [ "$testing" != "" ]; then
    rmmod poll_select
fi
insmod ${PWD}/poll_select.ko


