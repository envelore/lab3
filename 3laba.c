#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define ARGBUF 50
#define STRBUF 100

pid_t pid, child_pid;

void main(void)
{
	signal(SIGQUIT, SIG_IGN);
	int status;
	char *words[ARGBUF];
	char proc[STRBUF];
	char sep[] = " ";
	while(1) {
		printf("user@host:~$ ");
		gets(proc);
		int mode = 1;
		int i = 0; 
		char *ptr = strtok(proc, sep);
		while (ptr != NULL) {
			words[i++] = ptr;
			ptr = strtok (NULL, sep);
		}
			
		if (strcmp(words[0], "break") == 0)
			exit(0);
		if (strcmp(words[0], "cd") == 0) {
			chdir(words[1]);
			continue;
		}
	
		switch(pid=fork()) {
			  case -1:
			perror("fork");
			exit(1);
			  case 0:
			printf("******************************\n");
			printf("child process has been runned\n");
			printf("PID = %d\n", getpid());
			printf("Parent PID = %d\n", getppid());
			printf("Process was changed\n");
			printf("******************************\n");
			//signal(SIGINT,SIG_DFL);
			execvp(words[0],words);
			  default:
			printf("parent process ");
			printf("PID = %d\n", getpid());
			printf("child PID = %d\n",pid);
			printf("Waiting for child...\n");
			printf("******************************\n");
			child_pid = pid;
			child_pid = wait(&status);
			printf("Child has finished: PID = %d\n",child_pid);
			if (WIFEXITED(status))
				printf("Child proc exited: code %d\n",WIFEXITED(status));
			else
				printf("Child exited with error\n");
		}
	}
}

