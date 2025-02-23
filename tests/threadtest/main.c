#define LOG_LEVEL_INFO

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/debug.h>
#include <sys/syscalls.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syslimits.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>


// test variable
pthread_mutex_t mutex;
int test_ret = 0;


/*
 *
 */
void *test_routine(void *arg)
{
  int *ret;
  
  log_info ("thread argument '%s'\n", arg);
  log_info("test thread %s: thread:%08x", arg, (uint32_t)pthread_self());

  pthread_print(pthread_self());

  for (int t=0; t<10; t++) {  
    pthread_mutex_lock(&mutex);

    log_info("** thread %s, locked, cnt:%d", arg, t);

    sleep(1);

    pthread_mutex_unlock(&mutex);   

    sleep(1);
  }
    
  pthread_exit(arg);
}


/*
 *
 */
int main (int argc, char *argv[])
{
  pthread_t thread1;
  pthread_t thread2;
  char *ret;
  int sc;
  
  log_info("pthreadtest starting");
  log_info("main thread: %08x", (uint32_t)pthread_self());
  pthread_print(pthread_self());

  log_info("pthreadtest initializing mutex");  
  
  pthread_mutex_init(&mutex, NULL);
    
  log_info("pthreadtest creating thread-1");
  
  if (pthread_create(&thread1, NULL, test_routine, "thread-1") != 0) {
    log_error("pthread_create() error");
    exit(EXIT_FAILURE);
  }

  sleep(1);
  log_info("pthreadtest creating thread-2");
  
  if (pthread_create(&thread2, NULL, test_routine, "thread-2") != 0) {
    log_error("pthread_create() error");
    exit(EXIT_FAILURE);
  }

  log_info("main thread sleep for 20 seconds before joining");
  sleep(10);

  log_info("pthreadtest joining thread-1");

  if ((sc = pthread_join(thread1, (void **)&ret)) != 0) {
    log_error("pthread_join() error, %s", strerror(sc));
    exit(EXIT_FAILURE);
  }

  if (ret != NULL) {
    log_info("thread1 exited with: %s \n", ret);
  } else {
    log_error("thread1 exited with null return value\n");    
  }  

  log_info("pthreadtest joining thread-2");

  if (pthread_join(thread2, (void *)&ret) != 0) {
    log_error("pthread_join() error");
    exit(EXIT_FAILURE);
  }

  if (ret != NULL) {
    log_info("thread2 exited with: %s \n", ret);
  } else {
    log_error("thread2 exited with null return value\n");    
  }  


  log_info("pthreadtest complete");

  return 0;  
}


