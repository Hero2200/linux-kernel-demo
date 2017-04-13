# build.sh
source ~/drivers/common.sh
kernel_path=$EMULATOR_KERNEL_PATH
if [ "$2" == "6410" ]; then
    kernel_path=$S3C6410_KERNEL_PATH
fi
make  -C  $kernel_path  M=/root/drivers/force_kill_driver
read -p "Please input module name:" module_name

which_device=""
if [ "$1" != "" ]; then 
    which_device="-s $1"
fi
adb $which_device push /root/drivers/force_kill_driver/force_kill_driver.ko /data/local

temp=$(adb $which_device shell lsmod | grep "^""$module_name"" ")

#判断驱动是否安装
if [ "$temp" == "" ]; then
    echo "module <"$module_name"> does not exist！"
    exit
fi
module_line=$(adb $which_device shell cat /proc/kallsyms | grep cleanup_module | grep $module_name)
echo $module_line
echo "-----------"
if [ "$module_line" != "" ]; then
    echo $module_line
    read -p "kill?(y/n)" yn
    # 如果输入y，开始杀指定的驱动
    if [ "$yn" == "y" ]; then
        module_address=$(adb $which_device shell echo $module_line | cut -d' ' -f1)
        # 将16进制转换成10进制
        # module_address=$((16#$module_address))
	testing=$(adb $which_device shell lsmod | grep  "force_kill_driver")
        if [ "$testing" != "" ]; then
            adb $which_device shell rmmod force_kill_driver
        fi
        adb $which_device shell insmod /data/local/force_kill_driver.ko module_address="$module_address"
        adb $which_device shell rmmod $module_name
        echo "<"$module_name"> is killed！"        
    fi
fi



