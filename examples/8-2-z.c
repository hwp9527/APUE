#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int glob = 6; 

int main(void)
{
	int var;
	pid_t pid;

	var = 88;
	printf("before vfork\n");
	if((pid = fork()) < 0)
		err_sys("vfork error");
	else if(pid == 0) {
		glob++;
		var++;
		//子进程中显式地关闭stdout
		//标准输出FILE对象的相关存储区将被清零
		//这里我们改用fork函数来观察结果
		fclose(stdout);
		_exit(0);
	}

	int i = printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    char buf[10];
	sprintf(buf, "%d\n", i);
	write(STDOUT_FILENO, buf, strlen(buf));

	exit(0);
}
