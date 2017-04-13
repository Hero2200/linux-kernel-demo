source /root/drivers/common.sh
select_target
if [ $selected_target == 1 ]; then
    source build_ubuntu.sh
elif [ $selected_target == 2 ]; then
    source build_s3c6410.sh
elif [ $selected_target == 3 ]; then
    source build_emulator.sh
fi
