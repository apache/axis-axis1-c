@echo off
echo This test assumes a server URL of http://localhost:8080/axis/servlet/
echo Deploying the addressbook2 service...
java org.apache.axis.client.http.AdminClient deploy.xml
echo .
echo Running demo...
java samples.addressbook.Main
