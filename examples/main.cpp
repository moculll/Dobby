#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <pthread.h>
#include <iostream>
#include <android/log.h>

#include "dobby.h"

#include "more2Inject.h"

#define DEBUG_LOG(fmt, ...) \
    do { \
        __android_log_print(ANDROID_LOG_DEBUG, More2::GameInstance::getTag(), fmt, ##__VA_ARGS__); \
    } while(0)

namespace More2 {
const char *GameInstance::TAG = "More2Inject";
GameInstance *GameInstance::instance = nullptr;

bool GameInstance::saveToFile(const char *fileName, const char *buf, size_t size)
{
    std::ofstream outFile(fileName, std::ios::out | std::ios::binary);
    if (!outFile) 
        return false;
    outFile.write(buf, size);
    if (!outFile)
        return false;
    outFile.close();
    return true;
}

std::string GameInstance::abs2absCustomPath(std::string origin, std::string dstPath)
{
    size_t lastSlash = origin.find_last_of("/\\");
    std::string tmp = origin;

    if (lastSlash != std::string::npos) {
        tmp = origin.substr(lastSlash + 1);
    }
    
    dstPath += tmp;
    return dstPath;
    
}

} /* More2 */


namespace Hook {
    
#define install_hook(name, origin, fn_ret_t, fn_args_t...) \
    fn_ret_t (*origin)(fn_args_t); \
    fn_ret_t fake_##name(fn_args_t); \
    __attribute__((constructor)) static void install_hook_##name() { \
        void *sym_addr = DobbySymbolResolver(NULL, #name); \
        DobbyHook(sym_addr, (dobby_dummy_func_t)fake_##name, (dobby_dummy_func_t *)&origin); \
        DEBUG_LOG("install hook %s:%p:%p\n", #name, sym_addr, origin); \
    } \
    fn_ret_t fake_##name(fn_args_t)

/* cocos2d::LuaStack::luaLoadBuffer */
install_hook(_ZN7cocos2d8LuaStack13luaLoadBufferEP9lua_StatePKciS4_, orig_luaLoadBuffer, int64_t, int64_t a1, int64_t a2, const char *buf, int size, int64_t path)
{
    std::string filePath = (char *)path;
    std::string newFilePath = More2::GameInstance::abs2absCustomPath(filePath, "/data/data/com.more2.fkmj.pixel/files/more2/");
    
    DEBUG_LOG("[save2] %s", newFilePath.c_str());
    More2::GameInstance::saveToFile(newFilePath.c_str(), buf, size);
    return orig_luaLoadBuffer(a1, a2, buf, size, path);
}

} /* Hook */



void initFunc()
{

    
}

__attribute__((constructor)) void entrypoint() {

    pthread_t initFuncHandle;
    pthread_create(&initFuncHandle, NULL, (void *(*)(void *))initFunc, NULL);
}
