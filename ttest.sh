rm -rf build
cmake -S . -B build -D TARGET_GROUP=test
cmake --build build -j 2
make test -C ./build/ ARGS='-VV'
