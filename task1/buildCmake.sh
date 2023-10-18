#! /bin/sh
project_name=$1 || (echo "no project name..." && exit)
echo $project_name
rm -rf cmake_build || echo "hii"
mkdir cmake_build
cd cmake_build && cmake .. && make && ./$project_name