Rem get command line options
echo off
set URL_PREFIX="http://localhost/axis"
set BIN_PREFIX=C:\obj\samples
while getopts u:p:h o
do      case "$o" in
        u)      URL_PREFIX=$OPTARG;;
        h)      echo "Usage: $0 [-u] [-help]"
                echo "  -u     URL prefix of services. Default is http://localhost/axis"
rem                exit 1;;
        esac
done

echo "-----------------------------"

echo "running base..."
echo "-----------------------------"
%BIN_PREFIX%\base %URL_PREFIX%/base

echo "-----------------------------"

echo "running groupB..."
echo "-----------------------------"
%BIN_PREFIX%\groupB %URL_PREFIX%/groupB

echo "-----------------------------"

echo "running doclitbase..."
echo "-----------------------------"
%BIN_PREFIX%\doclitbase %URL_PREFIX%/baseDL

echo "-----------------------------"

echo "running doclitgroupB..."
echo "-----------------------------"
%BIN_PREFIX%\doclitgroupB %URL_PREFIX%/groupBDL

echo "-----------------------------"

