#利用Android源代码编译
#source ~/drivers/common.sh
#cd $OK6410_ANDROID_SRC_PATH
#source ./build/envsetup.sh
#cd $OK6410_ANDROID_SRC_PATH/development/read_write_dev
#mm
#cd ~/drivers/read_write_dev
#cp $OK6410_ANDROID_SRC_PATH/out/target/product/generic/system/bin/rwdev .
#adb push $OK6410_ANDROID_SRC_PATH/out/target/product/generic/system/bin/rwdev /data/local/rwdev

#  直接利用交叉编译器进行编译
arm-none-linux-gnueabi-gcc -static  -o  /root/drivers/read_write_dev/rwdev  /root/drivers/read_write_dev/rw_dev.c
adb push /root/drivers/read_write_dev/rwdev /data/local/rwdev



  
 
 
