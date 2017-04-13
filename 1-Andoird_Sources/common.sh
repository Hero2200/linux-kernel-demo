UBUNTU_KERNEL_PATH=/usr/src/linux-headers-3.2.0-29-generic
S3C6410_KERNEL_PATH=/root/kernel/linux_kernel_2.6.36
EMULATOR_KERNEL_PATH=/root/kernel/goldfish

OK6410_ANDROID_SRC_PATH=/working/android2.3.4_src
S3C6410_ANDROID_SRC_PATH=/working/android2.3.4_src


export PATH=$PATH:/root/compilers/arm-eabi-4.4.3/bin

selected_device=""  #  "":无可用Android设备
selected_target=1  #  选择目标,  1: ubuntu linux  2: Android设备

function select_target()
{
    echo "1：Ubuntu Linux"
    echo "2：S3C6410开发板"
    echo "3：Android模拟器"
    read -p "请选择要在那类设备上运行（1）" selected_target
    if [ "$selected_target" == "" ]; then
       selected_target=1
    fi
}
function select_target_noemulator()
{
    echo "1：Ubuntu Linux"
    echo "2：S3C6410开发板"
    read -p "请选择要在那类设备上运行（1）" selected_target
    if [ "$selected_target" == "" ]; then
       selected_target=1
    fi
}
function find_devices()
{
	device_list=$(adb devices)
        
        if [ "${device_list:0:4}" != "List" ]; then
	    device_list=$(adb devices)
	    if [ "${device_list:0:4}" != "List" ]; then
		exit
            fi
        fi
	value=$(echo $device_list | cut -d' ' -f5)
	if [ "$value" == "" ]; then
	    echo "无可用Android设备"
	else
            selected_device=$value   # 假设只有1个设备
	    value=$(echo $device_list | cut -d' ' -f7)

	    #  多个设备
	    if [ "$value" != "" ]; then
	       i=5
	       index=1
	       value="~~~"
	       echo "可用设备列表"
	       while [ "" == "" ]
	       do          
		  value=$(echo $device_list | cut -d' ' -f$i)
		  let "i=$i+2"
		  if [ "$value" == "" ]; then
		      break;
		  fi
		  echo "$index: $value"
		  let "index=$index+1"
	       done       
	       read -p "您想选择哪个Android设备？请输入序号(1)：" number
	       if [ "$number" == "" ]; then
		   number=1
	       fi
	       let "number=3 + $number * 2"
	       selected_device=$(echo $device_list | cut -d' ' -f$number)
	    fi
	fi
}


