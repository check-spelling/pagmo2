#!/usr/bin/env bash

# Echo each command
set -x

# Exit on error.
set -e

# Core deps.
sudo apt-get install build-essential cmake libboost-dev libnlopt-dev libeigen3-dev coinor-libipopt-dev clang

# Create the build dir and cd into it.
mkdir build
cd build

# Clang build with address sanitizer.
CXX=clang++ CC=clang cmake ../ -DCMAKE_BUILD_TYPE=Debug -DPAGMO_BUILD_TESTS=yes -DPAGMO_WITH_EIGEN3=yes -DPAGMO_WITH_NLOPT=yes -DPAGMO_WITH_IPOPT=yes
make -j2 VERBOSE=1
ctest

set +e
set +x
