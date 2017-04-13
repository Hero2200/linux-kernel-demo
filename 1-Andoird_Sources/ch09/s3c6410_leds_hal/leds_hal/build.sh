source ~/drivers/common.sh
cd $OK6410_ANDROID_SRC_PATH
source ./build/envsetup.sh
cd $S3C6410_ANDROID_SRC_PATH/hardware/leds_hal
mm
cd ~/drivers/ch09/s3c6410_leds_hal/leds_hal
cp $S3C6410_ANDROID_SRC_PATH/out/target/product/generic/system/lib/hw/led_hal.default.so .

find_devices
if [ "$selected_device" == "" ]; then
    exit
else
    adb -s $selected_device push ./led_hal.default.so /system/lib/hw
fi


 

     
