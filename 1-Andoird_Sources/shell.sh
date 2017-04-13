source /root/drivers/common.sh
find_devices
if [ "$selected_device" != "" ]; then    
    adb -s $selected_device shell $1
fi
