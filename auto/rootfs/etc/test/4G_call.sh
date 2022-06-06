time=1
while [ $time -le 10 ]
do
	echo -e "try $time...\n"
	if [ -c /dev/ttyUSB2 ];then
		if [ $time -ge 2 ];then
			#echo "sleep 3s"
			sleep 3
		fi
		for((i=0;i<=2;i++));
		do
			#echo "i is $i"
			#pppd call quectel-ppp &
			#sleep 3
			if [ "$(ifconfig | grep ppp)" ];then
				echo "ppp connected!"
				exit 0
			fi
			pppd call quectel-ppp &
			sleep 10
		done
		exit -1
	else
		sleep 1
		let time+=1
	fi
done
