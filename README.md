# Wyze C++ lib test project

### CMake Build
Third party libraries should be cross-compiled for MIPS uClibc and installed to $HOME/aws-install

To build the project.
```
cmake .. \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_PREFIX_PATH="$HOME/aws-install" \
-DCMAKE_CXX_COMPILER=mips-linux-uclibc-gnu-g++ \
-DCMAKE_CXX_FLAGS="-march=mips32r2 -D_GLIBCXX_USE_C99"
```
