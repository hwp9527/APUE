#include<unistd.h>
#include<signal.h>
#include<setjmp.h>
#include<stdlib.h>

#define MAXLINE 4096

extern void err_sys(const char *, ...);
extern void err_quit(const char *, ...);
static void sig_alrm(int);
static jmp_buf env_alrm;

int main(void)
{
	int n;
	char line[MAXLINE];

	if(signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal(SIGALRM) error");
	if(setjmp(env_alrm) != 0)
		err_quit("read timeout");

	alarm(10);
	if((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
		err_sys("read error");
	alarm(0);

	write(STDOUT_FILENO, line, n);
	return 0;
}

static void sig_alrm(int signo)
{
	longjmp(env_alrm, 1);
}


