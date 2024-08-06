#!/bin/bash

if [ $# -eq 2 ]

then
memoryName=$1
arrayCapacity=$2
cd bin 
./shm_server $memoryName $arrayCapacity &
sleep 0.1

for ((i=0; i < 5; i++))
do
./shm_client $memoryName --show
echo "_________________________________________________________________"
sleep 5
done

else
echo "Wrong number of parameters"
fi