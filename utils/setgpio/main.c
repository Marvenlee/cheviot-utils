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
#include <sys/rpi_gpio.h>


/*
 *
 */
int main (int argc, char *argv[])
{
  int sc;
  uint32_t gpio;
  int state;
  
  if (argc < 3) {
    printf("usage: setgpio gpio state\n");
    exit(EXIT_FAILURE);  
  }
  
  if (init_gpio() != 0) {
    printf("error: cannot init libgpio\n");
    exit(EXIT_FAILURE);
  }

  gpio = strtoul(argv[1], NULL, 0);
  state = strtol(argv[2], NULL, 0);
  
  sc = set_gpio(gpio, state);
    
  fini_gpio();
  
  if (sc != 0) {
    printf("command failed, error:%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  return 0;  
}

