# build.sh
source /root/drivers/common.sh
make  -C  $UBUNTU_KERNEL_PATH  M=$PWD
read -p "Please input module name:" module_name
temp=$(lsmod | grep "^""$module_name"" ")
#判断驱动是否安装
if [ "$temp" == "" ]; then
    echo "module <"$module_name"> does not exist！"
    exit
fi
module_line=$(cat /proc/kallsyms | grep __this_module | grep $module_name)

if [ "$module_line" != "" ]; then
    echo $module_line
    read -p "kill?(y/n)" yn
    # 如果输入y，开始杀指定的驱动
    if [ "$yn" == "y" ]; then
        module_address=$(echo $module_line | cut -d' ' -f1)
        # 将16进制转换成10进制
        # module_address=$((16#$module_address))
	testing=$(lsmod | grep  "force_kill_driver")
        if [ "$testing" != "" ]; then
            rmmod force_kill_driver
        fi
        insmod $PWD/force_kill_driver.ko module_address="$module_address"
        rmmod $module_name
        echo "<"$module_name"> is killed！"        
    fi
fi
