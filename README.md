v3d
===

Real time raytracer

#To build

##Unix

###Using provided script,
./scripts/cmake.sh

###Using cmake
cmake -DCMAKE_BUILD_TYPE=Release . -G"Unix Makefiles"
make
./v3d

To debug,
cmake -DCMAKE_BUILD_TYPE=Debug . -G"Unix Makefiles"




