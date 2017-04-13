# build_ubuntu.sh
source /root/drivers/common.sh
make   -C  $UBUNTU_KERNEL_PATH  M=$PWD
gcc -static -g -o gdb_debug $PWD/gdb_debug.c
testing=$(lsmod | grep  "printk_demo")
#  如果printk_demo驱动已安装，先卸载printk_demo驱动
if [ "$testing" != "" ]; then
    rmmod printk_demo
fi
#  安装printk_demo驱动
insmod $PWD/printk_demo.ko

testing=$(lsmod | grep  "proc_demo")
#  如果proc_demo驱动已安装，先卸载proc_demo驱动
if [ "$testing" != "" ]; then
    rmmod proc_demo
fi
#  安装proc_demo驱动
insmod $PWD/proc_demo.ko

testing=$(lsmod | grep  "bug_demo")
#  如果bug_demo驱动已安装，先卸载bug_demo驱动
if [ "$testing" != "" ]; then
    rmmod bug_demo
fi
#  安装bug_demo驱动
insmod $PWD/bug_demo.ko

