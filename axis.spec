# Axis C++ spec file
#
%define _axis_name axis-c
%define _axis_version 1.2
%define _axis_release 1
%define _axis_prefix "/usr/local/Axis"

Summary: Axis C++ web service
Vendor: Apache
Name: %{_axis_name}
Version: %{_axis_version}
Release: %{_axis_release}
Copyright: GPL
Group: Axis C++ software
Packager: Valentin Kuznetsov <vek3@cornell.edu>
Source: %{_axis_name}-%{_axis_version}.tar.gz
URL: http://www.lns.cornell.edu/public/CLEO/
BuildRoot: %{_tmppath}/%{_axis_name}
#AutoReqProv: no
BuildRequires: expat expat-devel xerces-c xerces-c-devel httpd httpd-devel
Requires: expat expat-devel xerces-c xerces-c-devel httpd httpd-devel
Provides: Axis C++ web service
Prefix: %{_axis_prefix}

%changelog
* Wed Sep 23 2004 Valentin Kuznetsov <vek3@cornell.edu>
- First attempt to build cleo RPMs

%description

%prep

%setup
echo setup

%build
libtoolize --force
aclocal
autoconf
autoheader
touch NEWS README ChangeLog AUTHORS
automake --add-missing --gnu
export AXISCPP_HOME=$RPM_BUILD_DIR/$RPM_PACKAGE_NAME-$RPM_PACKAGE_VERSION
./configure --libdir=$AXISCPP_HOME/bin --bindir=$AXISCPP_HOME/bin
gmake
gmake install

# build samples/server part
cd $AXISCPP_HOME/samples/server
touch NEWS README ChangeLog AUTHORS
libtoolize --force
aclocal
autoconf
autoheader
touch NEWS README ChangeLog AUTHORS
automake --add-missing --gnu
./configure --libdir=$AXISCPP_HOME/webservices
gmake
gmake install

#cd $AXISCPP_HOME/samples/client
#touch NEWS README ChangeLog AUTHORS
#libtoolize --force
#aclocal
#autoconf
#autoheader
#touch NEWS README ChangeLog AUTHORS
#automake --add-missing --gnu
#./configure --libdir=$AXISCPP_HOME/handlers --bindir=$AXISCPP_HOME/samples/client/
#gmake
#gmake install

%install
#gmake install
mkdir -p $RPM_BUILD_ROOT/usr/local/Axis/lib
cp -r $RPM_BUILD_DIR/$RPM_PACKAGE_NAME-$RPM_PACKAGE_VERSION/bin/* $RPM_BUILD_ROOT/usr/local/Axis/lib
cp -r $RPM_BUILD_DIR/$RPM_PACKAGE_NAME-$RPM_PACKAGE_VERSION/deploy $RPM_BUILD_ROOT/usr/local/Axis/
cp -r $RPM_BUILD_DIR/$RPM_PACKAGE_NAME-$RPM_PACKAGE_VERSION/webservices $RPM_BUILD_ROOT/usr/local/Axis/
#cp -r $RPM_BUILD_DIR/$RPM_PACKAGE_NAME-$RPM_PACKAGE_VERSION/handlers $RPM_BUILD_ROOT/usr/local/Axis/

%clean
rm -rf $RPM_BUILD_ROOT
rm -rf $RPM_BUILD_DIR/$RPM_PACKAGE_NAME-$RPM_PACKAGE_VERSION

%files
%defattr(-,root,root)
/usr/local/Axis

