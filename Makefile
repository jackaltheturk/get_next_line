main: main.c get_next_line_utils.c get_next_line.c
	cc -Wall -Werror -Wextra -D BUFFER_SIZE=8000000 -o main main.c get_next_line.c get_next_line_utils.c 