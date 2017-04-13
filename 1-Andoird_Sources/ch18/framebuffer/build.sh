source /root/drivers/common.sh
arm-none-linux-gnueabi-gcc -static  -o lcd ${PWD}/lcd.c
find_devices 
if [ "$selected_device" == "" ]; then 
    exit
else
    adb -s $selected_device push ${PWD}/lcd /data/local
fi


