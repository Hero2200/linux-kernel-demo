source /root/drivers/common.sh
ip='192.168.17.150'
gateway='192.168.17.254'
if [ "$1" != "" ]; then
    ip=$1
fi
if [ "$2" != "" ]; then
    gateway=$2
fi
find_devices 
adb -s $selected_device shell "/system/busybox/sbin/ifconfig eth0 $ip"
adb -s $selected_device shell "/system/busybox/sbin/route add default gw $gateway"

