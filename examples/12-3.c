#include<limits.h>
#include<string.h>

extern char **environ;
//静态缓冲区
static char envbuf[ARG_MAX];

char *getenv(const char *name)
{
	int i, len;
	len = strlen(name);
	for(i=0; environ[i] != NULL; i++) {
		if((strncmp(name, environ[i], len) == 0) &&
				(environ[i][len] == '=')) {
			strcpy(envbuf, &environ[i][len+1]);
			return envbuf;
		}
	}
	return NULL;
}

