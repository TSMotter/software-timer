rm -rf build
cmake -S . -B build -D TARGET_GROUP=release
cmake --build build -j 2
