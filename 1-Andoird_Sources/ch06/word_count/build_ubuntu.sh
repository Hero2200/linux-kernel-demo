# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=${PWD}
testing=$(lsmod | grep  "word_count")
if [ "$testing" != "" ]; then
    rmmod word_count
fi
insmod ${PWD}/word_count.ko

