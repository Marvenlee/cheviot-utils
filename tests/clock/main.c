#define LOG_LEVEL_WARN

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


/*
 *
 */
int main (int argc, char *argv[])
{
  int sc;
  struct timespec ts;
  clockid_t clock_id;
    
  if (argc < 2) {
    printf("usage: clock clockid\n");
    exit(EXIT_FAILURE);
  }
  
  clock_id = strtoul(argv[1], NULL, 10);  
  
  printf("sizeof timespec: %d\n", (int)sizeof(struct timespec));
  printf("sizeof clockid_t: %d\n", (int)sizeof(clockid_t));
  printf("sizeof time_t: %d\n", (int)sizeof(time_t));
  printf("sizeof long: %d\n", (int)sizeof(long));
  printf("sizeof ts tv_sec: %d\n", (int)sizeof ts.tv_sec);
  printf("sizeof ts tv_nsec: %d\n", (int)sizeof ts.tv_nsec);
  
  sc = clock_gettime(clock_id, &ts);
  
  printf("sc: %d, timespec tv_sec:%u, tv_nsec:%u\n", sc, (uint32_t)ts.tv_sec, (uint32_t)ts.tv_nsec);

  return 0;  
}

