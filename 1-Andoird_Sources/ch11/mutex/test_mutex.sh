cat /dev/mutex &
sleep 2
echo data > /dev/mutex

