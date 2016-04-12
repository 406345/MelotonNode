#!/bin/sh
rm -rf cmakebuild
CMaker project:maraton compiler:clang++ head:*.h src:*.cpp,*.c src:*.cc,*.cpp,*.hpp lib:lib/libmaraton.a,lib/libuv.a,lib/libprotobuf.a flag:-std=c++11-pthread out:exe 
cd cmakebuild
cmake ./
make -j 4
