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
#include <sys/syslimits.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/termios.h>
#include <sys/ioctl.h>
#include <errno.h>


char resp_buf[ARG_MAX];


/*
 *
 */
int main (int argc, char *argv[])
{
  int fd;
  int sc;
  msgiov_t siov[1];
  msgiov_t riov[1];
  
  if (argc < 3) {
    printf("usage: say server_path string_command\n");
    exit(EXIT_FAILURE);  
  }
  
  fd = open(argv[1], O_RDWR);
  
  if (fd < 0) {
    printf("error:cannot open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }  


  siov[0].addr = argv[2];
  siov[0].size = strlen(argv[2]);
  riov[0].addr = resp_buf;
  riov[0].size = sizeof resp_buf;
  
  sc = sendmsg(fd, 0, 1, siov, 1, riov);
  
  close(fd);

  if (sc < 0) {
    printf("error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  printf("response:\n%s\n", resp_buf);
  return 0;  
}


