# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=${PWD}
testing=$(lsmod | grep  "slab_cache")
if [ "$testing" != "" ]; then
    rmmod slab_cache  
fi
insmod ${PWD}/slab_cache.ko
 
