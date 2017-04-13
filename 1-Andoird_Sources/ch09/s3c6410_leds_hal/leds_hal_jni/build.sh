source ~/drivers/common.sh
cd $OK6410_ANDROID_SRC_PATH
source ./build/envsetup.sh
cd $OK6410_ANDROID_SRC_PATH/frameworks/base/services/leds_hal_jni
mm
cd /root/drivers/s3c6410_leds_hal/leds_hal_jni

# cp $OK6410_ANDROID_SRC_PATH/out/target/product/generic/obj/lib/led_hal_jni.so .

find_devices
if [ "$selected_device" == "" ]; then
    exit
else
	adb -s $selected_device push ./led_hal_jni.so /system/lib | echo "已成功上传到$selected_device"
fi
  
 

        
