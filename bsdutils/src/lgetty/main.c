/*
 * Copyright 2019  Marven Gilhespie
 *
 * Licensed under the Apache License, segment_id 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// #define LOG_LEVEL_INFO

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/debug.h>
#include <sys/signal.h>
#include <sys/stat.h>
#include <sys/syscalls.h>
#include <unistd.h>
#include <sys/syslimits.h>


// Shell path and args
#define SHELL_PATH    "/bin/ksh"
#define SHELL_ARG1    "-l"

// Prototypes
void print_greeting(void);


/* @brief   lgetty, a bare minimum getty that starts a shell as root with no login
 *
 * NOTE: This will be replaced by the full BSD getty once it and login are able to run.
 */
int main(int argc, char **argv)
{
  char *sh_argv[3];

  print_greeting();
  
  sh_argv[0] = SHELL_PATH;
  sh_argv[1] = SHELL_ARG1;
  sh_argv[2] = NULL;

  execve((const char *)SHELL_PATH, sh_argv, NULL);
    
  log_error("lgetty failed to exec %s", SHELL_PATH);  
  
	_exit(8);

}


/* @brief   Print a CheviotOS greeting
 *
 */
void print_greeting(void)
{
//  printf("\033[0;0H\033[0J\r\n");
  printf("  \033[34;1m   .oooooo.   oooo                               o8o                .   \033[37;1m      .oooooo.    .ooooooo.  \n");
  printf("  \033[34;1m  d8P'  `Y8b  `888                               `^'              .o8   \033[37;1m     d8P'  `Y8b  d8P'   `Y8b \n");
  printf("  \033[34;1m 888           888 .oo.    .ooooo.  oooo    ooo oooo   .ooooo.  .o888oo \033[37;1m    888      888 Y88bo.      \n");
  printf("  \033[34;1m 888           888P^Y88b  d88' `88b  `88.  .8'  `888  d88' `88b   888   \033[37;1m    888      888  `^Y8888o.  \n");
  printf("  \033[34;1m 888           888   888  888ooo888   `88..8'    888  888   888   888   \033[37;1m    888      888      `^Y88b \n");
  printf("  \033[34;1m `88b    ooo   888   888  888    .o    `888'     888  888   888   888 . \033[37;1m    `88b    d88' oo     .d8P \n");
  printf("  \033[34;1m  `Y8bood8P'  o888o o888o `Y8bod8P'     `8'     o888o `Y8bod8P'   `888' \033[37;1m     `Y8bood8P'  `^888888P'  \n");
  printf("\n");
  printf("\033[0m\n\n");
}



