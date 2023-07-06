set -e
export CXX=/usr/bin/g++
export CC=/usr/bin/gcc
numcpus=$(nproc)
mkdir build-jupedsim && cd build-jupedsim
cmake  ../jpscore -DCMAKE_PREFIX_PATH=/opt/jpscore-deps -DBUILD_TESTS=ON -DBUILD_JPSVIS=OFF
cmake --build . -- -j ${numcpus} -- VERBOSE=1
cmake --build . -t tests -- -j${numcpus} -- VERBOSE=1
cmake --build . -t install -- -j${numcpus} -- VERBOSE=1
cd ..
mkdir build-sumo && cd build-sumo
cmake  ../sumo -DJUPEDSIM_DIR=/usr/local
cmake --build . -- -j ${numcpus} -- VERBOSE=1
