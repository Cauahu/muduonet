#!/bin/bash

exec 2>&1

cd ..
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

sh local_build.sh

cd -

if [ -d build ];then
    rm -rf build
fi

#cmake
echo "cmake begain"
mkdir build
cd build
cmake ../
make
cd ../
echo "cmake end"
echo "clean cmake files"
rm -rf build
echo "clean cmake files done"

cp ../output/bin/* ./bin/

exit 0
