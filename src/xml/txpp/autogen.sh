#!/bin/bash
echo "----------------------------------"
echo "build server, client and samples"
echo "----------------------------------"
echo "clean previous build"
echo "run libtoolize."          && 
libtoolize --force              && 
echo "run aclocal."             && 
aclocal                         && 
echo "run autoconf."            && 
autoconf                        && 
echo "run autoheader."          && 
autoheader                      && 
echo "run automake."            && 
automake --add-missing --gnu    
