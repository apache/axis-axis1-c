#!/bin/sh
java org.apache.axis.transport.http.SimpleAxisServer -p 9090 &

java org.apache.axis.client.AdminClient -hlocalhost -p9090 axisj/deploy.wsdd

echo
echo Run Java client
java axisj.Client

echo
echo Run C++ client
./client

