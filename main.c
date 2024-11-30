#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>

int main()

{
    int fd = open("test.txt",O_RDONLY);
    char *line=get_next_line(fd);
    printf("%s",line);
    free(line);
    line=get_next_line(fd);
    printf("%s",line);
    free(line);
    line=get_next_line(fd);
    printf("%s",line);
    free(line);
    line=get_next_line(fd);
    printf("%s",line);
    free(line);
    close(fd);
    return 0;

}