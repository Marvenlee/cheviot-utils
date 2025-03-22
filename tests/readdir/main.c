#define LOG_LEVEL_INFO

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/dirent.h>
#include <sys/debug.h>
#include <sys/syscalls.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syslimits.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>



/*
 *
 */
int main (int argc, char *argv[])
{
  DIR *dirp;
  struct dirent *dp;
  char *path;
  int cnt = 0;
  
  if (argc < 2) {
    log_error("readdir path not specified");
    return -1;
  }

  log_info("readdir test");

  path = argv[1];

  if ((dirp = opendir(path)) == NULL) {
    log_error("couldn't open dir: %s", path);
    return -1;
  }

  errno = 0;
  
  do {
    if ((dp = readdir(dirp)) != NULL) {
      log_info("dirent %2d: %s\n", cnt, dp->d_name);
    }

    cnt ++;

  } while (dp != NULL);


  if (errno != 0) {
      log_info("error reading directory, errno:%d", errno);
  }
  
  closedir(dirp);
  
  log_info("readdir test complete");

  return 0;  
}


