# Wyze C++ lib test project

### CMake Build
Third party libraries should be cross-compiled for MIPS uClibc and installed to $HOME/aws-install

To build the project.
```
mkdir build && cd build

cmake .. \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_PREFIX_PATH="$HOME/aws-install" \
-DBUILD_SHARED_LIBS=OFF \
-DCMAKE_FIND_LIBRARY_SUFFIXES=".a" \
-DCMAKE_CXX_COMPILER=mips-linux-uclibc-gnu-g++ \
-DCMAKE_CXX_FLAGS="-march=mips32r2 -D_GLIBCXX_USE_C99" \
-DCMAKE_C_COMPILER=mips-linux-uclibc-gnu-gcc \
-DCMAKE_C_FLAGS="-march=mips32r2"

make VERBOSE=1

# Result is executable file `foo`
```

### Run on the device
To run `foo` on the device
```
# Download required shared libs (libatomic)
cd /media/mmc/
mkdir lib
cd lib
wget http://pivovaa-us-west-1.s3.amazonaws.com/wyze/libatomic.so.1.1.0
cp libatomic.so.1.1.0 libatomic.so.1
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/media/mmc/lib

# Download foo
cd /media/mmc/
wget http://pivovaa-us-west-1.s3.amazonaws.com/wyze/foo

# Download greeter_server
wget http://pivovaa-us-west-1.s3.amazonaws.com/wyze/greeter_server

# Run greeter_server in background
./greeter_server &

# Run foo
./foo
std::for_each: 3 4 2 8 15 267
nlohmann::json - OK
[2021-04-12 15:57:43.219] [info] Welcome to spdlog!
spdlog - OK
absl - OK
curl - OK
zlib - OK
aws Aws::InitAPI - OK
aws init_s3 begin
aws ClientConfiguration - OK
aws s3_region - OK
aws EnvironmentAWSCredentialsProvider - OK
aws s3 - OK
aws transfer - OK
aws sagemaker - OK
aws Aws::ShutdownAPI - OK
GreeterClient created - OK
Greeter received: Hello world
```
