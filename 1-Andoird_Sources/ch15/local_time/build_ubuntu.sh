# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=${PWD}
gcc -o user_local_time ${PWD}/user_local_time.c
testing=$(lsmod | grep  "local_time")
if [ "$testing" != "" ]; then
    rmmod local_time  
fi
insmod ${PWD}/local_time.ko

