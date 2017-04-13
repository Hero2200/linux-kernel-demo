  
sh /root/drivers/read_write_dev/build.sh
adb shell '/data/local/rwdev w /dev/s3c6410_leds_hal 5 3 0 0 0 0' 
adb shell '/data/local/rwdev r /dev/s3c6410_leds_hal 5 6'


  
  
 
