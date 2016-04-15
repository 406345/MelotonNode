#!/bin/sh
rm -rf cmakebuild
CMaker project:MelotonNode compiler:clang++ head:*.h src:*.cpp,*.c src:*.cc,*.cpp,*.hpp lib:lib/libMaratonFramework.a,lib/libuv.a,lib/libprotobuf.a flag:-std=c++11-pthread out:exe debug:true 
cd cmakebuild
cmake ./
make -j 4
