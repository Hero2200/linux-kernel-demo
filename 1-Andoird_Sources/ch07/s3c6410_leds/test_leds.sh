for((i=0; i<16; i=i+1))
do 
n=$(echo "obase=2;$i" | bc)
echo $n
echo $n > temp
n=$(rev temp)

adb shell "echo $n > /dev/s3c6410_leds"
sleep 1
done



