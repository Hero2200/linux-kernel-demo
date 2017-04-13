module_name="abc"
temp=$(lsmod | grep "^""$module_name"" ")
#判断驱动是否安装
if [ "$temp" == "" ]; then
    echo "module <"$module_name"> does not exist！"
    exit
fi
