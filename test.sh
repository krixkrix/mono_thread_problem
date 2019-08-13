#!/bin/bash -e

# build c# code
msbuild /v:minimal /p:Configuration=Release mono_project/testhang.sln

# build cpp code
(cd cpp_project && g++ -I/usr/lib/pkgconfig/../../include/mono-2.0 TestMain.cpp MonoBridge.cpp -o test -lmono-2.0 -lpthread)

# cp the .NET assembly
rm -rf mytest.exe
cp mono_project/testhang/bin/Release/mytest.exe .

# run test
./cpp_project/test
