cp word_count.c word_count.c.bak
cp ./read_write/word_count.c .
make -C  /usr/src/linux-headers-3.0.0-15-generic  M=/root/drivers/ch06/word_count
testing=$(lsmod | grep  "word_count")
if [ "$testing" != "" ]; then
    rmmod word_count
fi
insmod word_count.ko
echo 'hello lining' > /dev/wordcount
cat /dev/wordcount
cp word_count.c.bak word_count.c
rm word_count.c.bak
