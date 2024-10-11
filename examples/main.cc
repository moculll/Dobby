#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
#include <android/log.h>
#define LOG_TAG "TEST"
void testfunc() {
  for (int i = 0; i < 99999; i++) {
    __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "---------------------%d------------------------", i);
    usleep(100000);
  }
  return;
}
__attribute__((constructor)) void entrypoint() {
  pthread_t socket_server;
  pthread_create(&socket_server, NULL, (void *(*)(void *))testfunc, NULL);
}
