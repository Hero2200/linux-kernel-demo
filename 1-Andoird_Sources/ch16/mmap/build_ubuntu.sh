# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=${PWD}
gcc -o user_mmap ${PWD}/user_mmap.c
testing=$(lsmod | grep  "mmap_shared")
if [ "$testing" != "" ]; then
    rmmod mmap_shared  
fi
insmod ${PWD}/mmap_shared.ko
 
