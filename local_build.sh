#!/bin/bash

exec 2>&1

export PATH=/opt/tool/broc/client:$PATH

#broc build
#broc init
#[ $? -ne 0 ] && {
#    echo 'broc init failed!!!'
#    exit 1
#}
#
#broc build
#[ $? -ne 0 ] && {
#    echo 'broc build failed!!!'
#    exit 1
#}

#output
if [ -d output ];then
    rm -rf output
fi
mkdir -p output/lib
mkdir -p output/bin

if [ -d build ];then
    rm -rf build
fi
#cmake
echo "cmake begain"
mkdir build
cd build
cmake ../ && make
[ $? -ne 0 ] && {
    echo 'cmake compile failed'
    exit 1
}
cd ../
echo "cmake end"
echo "clean cmake files"
rm -rf build
echo "clean cmake files done"

find ./output -name .git | xargs rm -rf
cd output
exit 0
