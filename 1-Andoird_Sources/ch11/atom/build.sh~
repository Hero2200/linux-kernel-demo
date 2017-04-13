atom=0
echo '0：多个进程可以同时打开/dev/atomic设备文件'
echo '1: 同时只能有1个进程打开/dev/atomic设备文件'
read -p '请给出你的选择(0):' atom
if [ "$atom" == "" ]; then
    atom=0
fi
source /root/drivers/common.sh
select_target
if [ $selected_target == 1 ]; then
    source build_ubuntu.sh
elif [ $selected_target == 2 ]; then
    source build_s3c6410.sh
elif [ $selected_target == 3 ]; then
    source build_emulator.sh
fi
