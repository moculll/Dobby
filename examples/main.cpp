#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
#include <android/log.h>

#include "dobby.h"

#include "more2Inject.h"



namespace More2 {
const char *GameInstance::TAG = "More2Inject";
GameInstance *GameInstance::instance = nullptr;


} /* More2 */


namespace Hook {
#define install_hook(name, origin, fn_ret_t, fn_args_t...) \
    fn_ret_t (*origin)(fn_args_t); \
    fn_ret_t fake_##name(fn_args_t); \
    __attribute__((constructor)) static void install_hook_##name() { \
        void *sym_addr = DobbySymbolResolver(NULL, #name); \
        DobbyHook(sym_addr, (dobby_dummy_func_t)fake_##name, (dobby_dummy_func_t *)&origin); \
        __android_log_print(ANDROID_LOG_DEBUG, More2::GameInstance::getTag(), "install hook %s:%p:%p\n", #name, sym_addr, origin); \
    } \
    fn_ret_t fake_##name(fn_args_t)

/* cocos2d::LuaStack::luaLoadBuffer */
install_hook(_ZN7cocos2d8LuaStack13luaLoadBufferEP9lua_StatePKciS4_, orig_luaLoadBuffer, int64_t, int64_t a1, int64_t a2, const char *buf, int size, int64_t path)
{
    __android_log_print(ANDROID_LOG_DEBUG, More2::GameInstance::getTag(), "get: %s", (char *)path);
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
