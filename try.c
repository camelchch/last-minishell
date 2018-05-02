#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "minishell.h"

size_t		get_key()
{
	unsigned char	buff[11];

	//ft_bzero(buff, 4);
	memset(buff, 0, 11);
	read(0, buff, 11);
	printf("%u %u %u %u %u %u %u %u %u %u\n", buff[0], buff[1], buff[2], \
		buff[3], buff[4], buff[5], buff[6], buff[7], buff[8], buff[9]);
	//return (*buff + (*buff << 8) + (*buff << 16));
	unsigned long a= buff[0];
	unsigned long b=buff[1]<< 8;
	unsigned long c= buff[2] <<  16;
	unsigned long d= buff[3] <<  24;
	unsigned long e= (unsigned long)buff[4] <<  32;
	unsigned long f= (unsigned long) buff[5] <<  40;
//	printf("%lu %lu %lu %lu\n", a, b, c, a+b+c);
	return (a + b + c + d + e + f);
}


int		main()
{
	unsigned long	key;

	key = get_key();
	printf("size of unsigned long log=%d\n", (int)sizeof(unsigned long));
	printf("key=%lu\n", key);
	if (33 <= key && key <= 126)
		printf("key is printable, key =%c\n", (char)key);
}

