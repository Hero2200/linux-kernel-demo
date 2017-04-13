# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=${PWD}
gcc ${PWD}/test_signal.c -o test_signal
gcc ${PWD}/test_io_signal.c -o test_io_signal
gcc ${PWD}/test_rw_signal.c -o test_rw_signal
testing=$(lsmod | grep  "signal")
if [ "$testing" != "" ]; then
    rmmod signal
fi
insmod ${PWD}/signal.ko

