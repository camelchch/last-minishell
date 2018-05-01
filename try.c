#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

size_t		get_key()
{
	unsigned char	buff[8];

	//ft_bzero(buff, 4);
	memset(buff, 0, 8);
	read(0, buff, 8);
	printf("%u %u %u %u %u %u %u\n", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5], buff[6]);
	//return (*buff + (*buff << 8) + (*buff << 16));
	size_t a= buff[0];
	size_t b=buff[1]<< 8;
	size_t c= buff[2] <<  16;
	printf("%lu %lu %lu %lu\n", a, b, c, a+b+c);
	return (a + b + c);
}


int		main()
{
	size_t	key;

	key = get_key();
	printf("key=%zu\n", key);
	if (33 <= key && key <= 126)
		printf("key is printable, key =%c\n", (char)key);
}

