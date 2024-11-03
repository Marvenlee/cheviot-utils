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


// Prototypes
void print_usage(void);


/* @brief   Shutdown command to reboot or power off the device
 *
 * Usage: shutdown how
 *        how = reboot or poweroff
 *
 * TODO: 
 * Should only be done by root, and only a single instance.
 * Could run a shutdown script to terminate user processes and services.
 * Send signal to init/root task to terminate subprocesses.
 */
int main (int argc, char *argv[])
{
  int how;
  
  if (argc < 2) {
    print_usage();    
    exit(EXIT_FAILURE);
  }
  
  if (strcmp(argv[1], "reboot") == 0) {
    how = SHUTDOWN_REBOOT;
  } else if (strcmp(argv[1], "poweroff") == 0) {
    how = SHUTDOWN_POWEROFF; 
  } else if (strcmp(argv[1], "--help") == 0) {
    print_usage();
    exit(EXIT_SUCCESS); 
  } else {
    printf("Unknown option: %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
    
  cheviot_reboot(how);
  return 0;  
}


/*
 *
 */
void print_usage(void)
{
    printf("usage: shutdown [how]\n"
           "       how:  reboot, poweroff\n");
}

