#!/bin/bash

#get command line options
GET_URL=""
GET_PORT=""
while getopts u:p:h o
do      case "$o" in
        u)      GET_URL=$OPTARG;;
        p)      GET_PORT=$OPTARG;;
        h)      echo "Usage: $0 [-u] [-p] [-help]"
                echo "  -u     URL of the server apache running"
                echo "  -p     PORT of the server apache running"
                exit 1;;
        esac
done


echo "-----------------------------"

echo "running base..."
echo "-----------------------------"
./base ${GET_URL} ${GET_PORT}

echo "-----------------------------"

echo "running cbase..."
echo "-----------------------------"
./cbase ${GET_URL} ${GET_PORT}

echo "-----------------------------"


echo "running groupB..."
echo "-----------------------------"
./groupB ${GET_URL} ${GET_PORT}

echo "-----------------------------"

echo "running cgroupB..."
echo "-----------------------------"
./cgroupB ${GET_URL} ${GET_PORT}

echo "-----------------------------"

echo "running doclitbase..."
echo "-----------------------------"
./doclitbase ${GET_URL} ${GET_PORT}

echo "-----------------------------"

echo "running doclitgroupB..."
echo "-----------------------------"
./doclitgroupB ${GET_URL} ${GET_PORT}

echo "-----------------------------"

exit
