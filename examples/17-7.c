#include<sys/socket.h>
#include<sys/un.h>
#include<stddef.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	int fd, size;
	struct sockaddr_un un;

	un.sun_family = AF_UNIX;
    strcpy(un.sun_path, "foo.socket");

	fd = socket(AF_UNIX, SOCK_STREAM,0);
	size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);

	if(bind(fd, (struct sockaddr *)&un, size) < 0)
		err_sys("bind failed");
	printf("UNIX domain socket bound\n");
	exit(0);
}
