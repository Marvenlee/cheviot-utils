#define LOG_LEVEL_WARN

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/debug.h>
#include <sys/dirent.h>
#include <sys/signal.h>
#include <sys/stat.h>
#include <sys/syscalls.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <limits.h>
#include <sys/syslimits.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/termios.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/resource.h>


#define MAX_PROC_ENTRIES 128


/*
 *
 */
int main (int argc, char *argv[])
{
  void *buf;
  struct cpu_usage *cu;
  bool batch = false;
  bool silent = false;
  uint64_t now_usec;
  struct timespec now_ts;
  int cnt;
  int c;
  int max_process;
   
  while ((c = getopt(argc, argv, "bs")) != -1) {
    switch (c) {
    case 'b':
      batch = true;
      break;
    case 's':
      silent = true;
      break;
    default:
      break;
    }
  }

  max_process = sysconf(_SC_PROCESS_MAX);

  buf = malloc(sizeof(struct cpu_usage) * max_process);
  
  if (buf == NULL) {
    return -1;
  }

  while(1) {
    cnt = _swi_get_cpu_usage(buf, sizeof(struct cpu_usage) * max_process);

    if (silent) {
      break;
    }

    if (!batch) {
      printf("\033[0;0H\033[0J");
    }
    
    printf("    PID USER          PR   CPU      TIME+ COMMAND \n");

    cu = (struct cpu_usage *)buf;

    for (int t=0; t < cnt; t++) {
      printf("%7u %10u %5u %3u.%1u %10d %s\n", 
             cu->tid, cu->uid, cu->priority, 
             (uint32_t)cu->usage_permille / 10,
             (uint32_t)cu->usage_permille % 10,
             (uint32_t)cu->uptime_sec, cu->name);            
      cu++;
    }
    
    if (batch) {
      break;
    }
    
    sleep(2);
  }
  
  return 0;
}

