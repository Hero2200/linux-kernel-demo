read -p '是否唤醒所有等待completion完成的执行单元（0：不唤醒，1：唤醒）？' completion_type
if  [ "$completion_type" != "0" ] && [ "$completion_type" != "1" ]; then
    completion_type=0
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
