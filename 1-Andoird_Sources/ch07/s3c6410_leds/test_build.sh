arm-none-linux-gnueabi-gcc -static  -o ioctl ${PWD}/test_ioctl.c
adb push ${PWD}/ioctl /data/local/ioctl
adb shell '/data/local/ioctl /dev/s3c6410_leds 1 2'
