#!/bin/sh

#get command line options
GET_URL=""
GET_PORT=""
BIN_PREFIX=${AXISCPP_DEPLOY}/bin
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
${BIN_PREFIX}/base ${GET_URL} ${GET_PORT}

echo "-----------------------------"

echo "running groupB..."
echo "-----------------------------"
${BIN_PREFIX}/groupB ${GET_URL} ${GET_PORT}

echo "-----------------------------"

#echo "running cgroupB..."
#echo "-----------------------------"
#${BIN_PREFIX}/cgroupB ${GET_URL} ${GET_PORT}

echo "-----------------------------"

echo "running doclitbase..."
echo "-----------------------------"
${BIN_PREFIX}/doclitbase ${GET_URL} ${GET_PORT}

echo "-----------------------------"

echo "running doclitgroupB..."
echo "-----------------------------"
${BIN_PREFIX}/doclitgroupB ${GET_URL} ${GET_PORT}

echo "-----------------------------"

exit
