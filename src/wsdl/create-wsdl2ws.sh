#!/bin/bash
#AXIS_JARS_HOME environment variable should point to axis jars.
#This will install wsdl2ws.jar in ${AXISCPP_HOME}/lib/axis

ant -lib ${AXIS_JARS_HOME} -buildfile ${AXISCPP_HOME}/src/wsdl/build.xml
