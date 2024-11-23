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
#include <sys/mman.h>



/* @brief   Ad-hoc test of file access
 *
 * @param   argc, unused
 * @param   argv, unused
 * @return  0 on success, non-zero on failure
 *
 * Modify as necessary to test functionality of file access.
 *
 * TODO:  Create more comprehensive test suite.
 */
int main(int argc, char **argv)
{
  struct stat st;
  int sc;
	char *buf;
	int fd;
	ssize_t sz;
		
  printf("**** character device read write test ****\n");
  printf("opening /dev/echo\n");
  
  if ((fd = open("/dev/echo", O_RDWR)) < 0) {
    printf("failed to open /dev/echo\n");
    return -1;
  }

  sleep(1);
  
	uint32_t *buffer_out, *buffer_in;
	
	buffer_out = mmap((void *)0x40000000, 1024 * 4, PROT_READ | PROT_WRITE, 0, -1, 0);
	buffer_in = mmap((void *)0x40080000, 1024 * 4, PROT_READ | PROT_WRITE, 0, -1, 0);

	if (buffer_out == NULL || buffer_in == NULL) {
		printf("Failed to allocate buffers\n");
		close(fd);
		return 0;
	}	

  printf("preparing test data\n");
	sleep(1);
	
	for (int t=0;t < 1024; t++) {
		buffer_out[t] = t | (t<<16);
	}

	printf("writing out test data\n");
	sleep(1);
	
	sc = write(fd, buffer_out, 1024 * 4);

	if (sc != 4 * 1024) {
		printf("Failed to write test data :%d\n", sc);
		close(fd);
		return 0;	
	}

	printf("readback test data\n");
	sleep(1);
  
  ssize_t total_read = 0;	
  ssize_t nbytes = 0;
  ssize_t remaining = 1024 * 4;
  
	while (total_read < 1024 * 4) {
  	nbytes = read(fd, buffer_in + total_read, remaining);

    if (nbytes == 0) {
      printf("read returned 0\n");
    }
    
    if (nbytes < 0) {
      printf(" read returned %d, %s\n", nbytes, strerror(nbytes));
      exit(-1);
    }
    
    total_read += nbytes;
    remaining -= nbytes;
  }
  
  
  printf("compare data\n");
	sleep(1);
  
  for (int t=0; t< 1024; t++) {
	  if (buffer_out[t] != buffer_in[t]) {
		  printf("readback failed at: %d, expected:%08x, got:%08x\n", t, buffer_out[t], buffer_in[t]);
	  }
  }
  
	printf("\n---- done ----\n");

	close(fd);
	return 0;
}




