#!/bin/sh

#get command line options
URL_PREFIX=""
BIN_PREFIX=${AXISCPP_DEPLOY}/bin
while getopts u:p:h o
do      case "$o" in
        u)      URL_PREFIX=$OPTARG;;
        h)      echo "Usage: $0 [-u] [-help]"
                echo "  -u     URL prefix of services. Default is http://localhost/axis"
                exit 1;;
        esac
done


echo "-----------------------------"

echo "running base..."
echo "-----------------------------"
${BIN_PREFIX}/base ${URL_PREFIX} 

echo "-----------------------------"

echo "running groupB..."
echo "-----------------------------"
${BIN_PREFIX}/groupB ${URL_PREFIX} 

echo "-----------------------------"

#echo "running cgroupB..."
#echo "-----------------------------"
#${BIN_PREFIX}/cgroupB ${URL_PREFIX} 

echo "-----------------------------"

echo "running doclitbase..."
echo "-----------------------------"
${BIN_PREFIX}/doclitbase ${URL_PREFIX} 

echo "-----------------------------"

echo "running doclitgroupB..."
echo "-----------------------------"
${BIN_PREFIX}/doclitgroupB ${URL_PREFIX} 

echo "-----------------------------"

exit
