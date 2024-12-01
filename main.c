#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd=open("test.txt",O_RDONLY);
	char *yyy=get_next_line(fd);
	
	printf("%s",yyy);
	free(yyy);
	close(fd);
}
