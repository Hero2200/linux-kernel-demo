# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=${PWD}
testing=$(lsmod | grep  "mempool_cache")
if [ "$testing" != "" ]; then
    rmmod mempool_cache  
fi
insmod ${PWD}/mempool_cache.ko
 
