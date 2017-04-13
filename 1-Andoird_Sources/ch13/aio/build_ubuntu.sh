# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=${PWD}
gcc ${PWD}/test_aio_rw.c -o test_aio_rw -lrt
gcc ${PWD}/test_read_signal.c -o test_read_signal -lrt
gcc ${PWD}/test_callback.c -o test_callback -lrt
testing=$(lsmod | grep  "aio_signal")
if [ "$testing" != "" ]; then
    rmmod aio_signal
fi
insmod ${PWD}/aio_signal.ko

