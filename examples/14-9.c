#include "apue.h"
#include<stropts.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
	int fd, i, nmods;
	struct str_list list;

	if(argc != 2)
		err_quit("usage: %s <pathname>", argv[0]);
	if((fd = open(argv[1], O_RDONLY)) < 0)
		err_sys("can't open %s", argv[1]);
	if(isastream(fd) == 0)
		err_quit("%s is not a stream", argv[1]);

	if((nmods = ioctl(fd, I_LIST, (void *)0)) < 0)
		err_sys("I_LIST error for nmods");
	printf("#modules = %d\n", nmods);

	list.sl_modlist = calloc(nmods, sizeof(struct str_mlist));
	if(list.sl_modlist == NULL)
		err_sys("calloc error");
	list.sl_nmods = nmods;

	if(ioctl(fd, I_LIST, &list) < 0)
		err_sys("I_LIST error for list");

	for(i=1; i<=nmods; i++)
		printf(" %s: %s\n", (i==nmods)?"driver":"module", list.sl_modlist++->l_name);

	exit(0);
}
