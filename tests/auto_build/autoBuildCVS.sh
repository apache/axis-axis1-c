#!/bin/sh
# *** Set CVS related variables ***
./rmlog.sh
CVSROOT=":pserver:anoncvs:anoncvs@cvs.apache.org:/home/cvspublic"
HOME_DIR=$PWD
CHECKOUT_DIR=cvsautobuild
LOG=${HOME_DIR}/log
ERROR_LOG=${HOME_DIR}/log_error
#SOURCE_BUILD_MESSAGES=${HOME_DIR}/log_source_build_messages_`date +%Y-%m-%d@%H:%M:%S`
#SOURCE_BUILD_ERRORS=${HOME_DIR}/log_source_build_errors_`date +%Y-%m-%d@%H:%M:%S`
SOURCE_BUILD_MESSAGES=${HOME_DIR}/log_source_build_messages
SOURCE_BUILD_ERRORS=${HOME_DIR}/log_source_build_errors
SOURCE_INSTALL_MESSAGES=${HOME_DIR}/log_source_install_messages
SOURCE_INSTALL_ERRORS=${HOME_DIR}/log_source_install_errors

export CVSROOT HOME_DIR CHECKOUT_DIR LOG ERROR_LOG SOURCE_BUILD_MESSAGES SOURCE_BUILD_ERRORS

#Setting environment variables. User may change the default values to fit his own environment

XERCESC_HOME=${XERCESC_HOME:-/usr/local/xerces-c-src2_2_0}
EXPAT_HOME=${EXPAT_HOME:-/usr/local/expat1957}
APACHE2_HOME=${APACHE2_HOME:-/usr/local/apache2}
APACHE_HOME=${APACHE_HOME:-/usr/local/apache}
AXISCPP_HOME=${HOME_DIR}/${CHECKOUT_DIR}
AXISCPP_DEPLOY=${AXISCPP_DEPLOY:-/usr/local/axiscpp_deploy}
LD_LIBRARY_PATH=${AXISCPP_DEPLOY}/lib 
PATH="/usr/bin:/usr/local/bin:$PATH"
export LD_LIBRARY_PATH AXISCPP_DEPLOY XERCESC_HOME EXPAT_HOME APACHE2_HOME APACHE_HOME AXISCPP_HOME PATH

#get command line options
GET_CVS="true"
USE_APACHE="1"
while getopts n:a:h o
do	case "$o" in
	n)	GET_CVS="false";;
	a)	USE_APACHE=$OPTARG;;
	h)	echo "Usage: $0 [-nocvc] [-help]"
		echo "Chekout from cvs:"
		echo "	-nocvc	Do not chekout from cvs; Default is to checkout"				
		exit 1;;
	esac
done

# *** Get the update from CVS ***
echo Getting CVS Update from ${CVSROOT}
cd ${HOME_DIR}

if [ ${GET_CVS} = "true" ]
then
    if test -d ./cvsautobuild; then
        cvs -d ${CVSROOT} update -dC ${CHECKOUT_DIR}
    else
        cvs -d ${CVSROOT} checkout -d ${CHECKOUT_DIR} ws-axis/c
    fi
fi

#if [ $? = 0 ]
if [ $? -eq 0 ]
then
	echo CVS Update  Sucessfull 
	echo `date` CVS Update  Sucessfull >> ${LOG}
else
	echo CVS Update Failed 
	echo `date` CVS Update Failed >> ${LOG}
	exit
fi



# *** Build Source ***
echo Starting Source Build
cd ${AXISCPP_HOME}
echo Build messages of build @ `date` > ${SOURCE_BUILD_MESSAGES}
echo Build errors/warnings of build @ `date` > ${SOURCE_BUILD_ERRORS}
cp -f ../build.sh ./build.sh
sh build.sh >> ${SOURCE_INSTALL_MESSAGES} 2>>${SOURCE_INSTALL_ERRORS}

echo Installing...
echo Install messages of build @ `date` > ${SOURCE_INSTALL_MESSAGES}
echo Install errors/warnings of build @ `date` > ${SOURCE_INSTALL_ERRORS}
make install >> ${SOURCE_INSTALL_MESSAGES} 2>>${SOURCE_INSTALL_ERRORS}

if [ $? = 0 ]
then
    echo Source Build/Install  Sucessfull
    echo `date` Source Build/Install  Sucessfull >> ${LOG}
else
    echo Source Build/Install Failed
    echo `date` Source Build/Install Failed >> ${LOG}
    if test -f $HOME_DIR/mailto; then
        cat $HOME_DIR/log_source_build_messages $HOME_DIR/log_source_install_messages $HOME_DIR/log | mutt -s "[test-results]Axis C++ Autobuild and regression test" -a "$HOME_DIR/log_source_build_errors" -a "$HOME_DIR/log_source_install_errors" -x axis-c-dev@ws.apache.org
    fi
    exit
fi

echo See the following log files for details
echo "	Summary log 			:${LOG}"
echo "	Build messages 			:${SOURCE_BUILD_MESSAGES}"
echo "	Build errors/warnings 		:${SOURCE_BUILD_ERRORS}"


cd ${HOME_DIR}
rm -f testcases/build/buildTestCase.log
rm -f testcases/build/runTestCase.log

# *** Deploy with Apache 2 ***
echo Start deploy with apache2 using expat parser library
sed 's/xercesc/expat/g' ${AXISCPP_DEPLOY}/bin/deploy_apache2.sh > ${AXISCPP_DEPLOY}/bin/deploy_apache2_auto.sh
sed 's/9090/80/g' testcases/platform/linux/test.config > ./test.config
cp -f test.config testcases/platform/linux
cp -f ${AXISCPP_DEPLOY}/lib/libaxiscpp_mod2.so ${APACHE2_HOME}/modules/
sh ${AXISCPP_DEPLOY}/bin/deploy_apache2_auto.sh

if [ $? = 0 ]
then
        echo Apache2 Start  Sucessfull
        echo `date` Apache Start  Sucessfull >> ${LOG}
else
        echo Apache2 Start Failed
        echo `date` Apache Start Failed >> ${LOG}
	exit
fi

echo "running the tests"
sh ./runAllTests.sh

# *** Deploy with Apache 1 ***

echo "Start deploy with apache1 using expat parser library"
sed 's/xercesc/expat/g' ${AXISCPP_DEPLOY}/bin/deploy_apache.sh > ${AXISCPP_DEPLOY}/bin/deploy_apache_auto.sh
sed 's/80/9090/g' ${HOME_DIR}/testcases/platform/linux/test.config > ./test.config
cp -f test.config ${HOME_DIR}/testcases/platform/linux
cp -f ${AXISCPP_DEPLOY}/lib/libaxiscpp_mod.so ${APACHE_HOME}/libexec/
sh ${AXISCPP_DEPLOY}/bin/deploy_apache_auto.sh

if [ $? = 0 ]
then
        echo Apache Start  Sucessfull
        echo `date` Apache Start  Sucessfull >> ${LOG}
else
        echo Apache Start Failed
        echo `date` Apache Start Failed >> ${LOG}
	exit
fi

echo "running the tests"
sh runAllTests.sh

#Only if there is a file called mailto in the current folder, do the step.
#If you need to mail results create a file called mailto in the current
#folder. This file has no meaning except this purpose
if test -f $HOME_DIR/mailto; then
    cat  $HOME_DIR/runTestCase.log | mutt -s "[test-results]Axis C++ Autobuild and regression test" -a "$HOME_DIR/buildTestCase.log" -x axis-c-dev@ws.apache.org
fi
