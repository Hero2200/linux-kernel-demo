source /root/drivers/common.sh
find_devices
if [ "$selected_device" != "" ]; then
    adb -s $selected_device pull $1 $2
fi
