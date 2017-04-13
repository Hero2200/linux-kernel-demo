source /root/drivers/common.sh
find_devices
if [ "$selected_device" != "" ]; then
    adb -s $selected_device push $1 $2
fi
