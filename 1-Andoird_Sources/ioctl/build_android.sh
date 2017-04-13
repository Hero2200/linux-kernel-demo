cd /working/android2.3.4_src/
source ./build/envsetup.sh
cd /working/android2.3.4_src/development/ioctl
mm
cd ~/drivers/ioctl
cp /working/android2.3.4_src/out/target/product/generic/system/bin/ioctl .
adb push /working/android2.3.4_src/out/target/product/generic/system/bin/ioctl /data/local/ioctl
adb shell /data/local/ioctl
