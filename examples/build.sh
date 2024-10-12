export NDK_PATH=/home/mocul/c_test/android/android-ndk-r25c
export TOOLCHAIN=$NDK_PATH/toolchains/llvm/prebuilt/linux-x86_64
export TARGET=aarch64-linux-android
export API=21

# 设置编译器和工具路径
export CC=$TOOLCHAIN/bin/$TARGET$API-clang
export CXX=$TOOLCHAIN/bin/$TARGET$API-clang++
export AR=$TOOLCHAIN/bin/$TARGET-ar
export LD=$TOOLCHAIN/bin/$TARGET-ld

$CXX -fPIC -shared -static-libstdc++ -o test.so main.cpp /home/mocul/c_test/android/Dobby/build/android/arm64-v8a/libdobby.a -llog -landroid -I../include -I./
#$CXX -o test main.cc /home/mocul/c_test/android/Dobby/build/android/arm64-v8a/libdobby.a -llog -landroid