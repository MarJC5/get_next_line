#include "get_next_line.h"

int	main(int argc, char *argv[])
{
	int		i;
	int		fd;
	char	*path;
	char	*result;

	i = 0;
	if (argc != 2)
		printf("Please enter the file descriptor path after the program name.\n");
	else
		path = argv[argc - 1];
	if ((fd = open(path, O_RDONLY)) == -1)
		printf("Cannot open the file.\n");
	result = get_next_line(fd);
	while (i++ < 12)
	{
		//printf("\033[1;32mRESULT -> \033[0;37m\033[1;37mline N°%d\033[0;37m\n", i);
		printf("%s", result);
		result = get_next_line(fd);
	}
	if (close(fd) == -1)
		printf("Error, cannot close the file.\n");
	return (0);

	//printf("\n\n\033[1;33mREAD IN LOOP ->\033[0;37m\n%d", file);

	//printf("\n\n\033[1;37mTEMP ->\033[0;37m\n%s", temp);

	//printf("\n\n\033[1;33mSAVE NL POSITION ->\033[0;37m\n%d", ft_strchr_pos(*save, '\n'));

	//printf("\n\n\033[1;34mSAVE BEFORE LOOP ->\033[0;37m\n%s", *save);
	//printf("\n\n\033[1;36mSAVE IN LOOP ->\033[0;37m\n%s", *save);

	//printf("\n\n\033[1;31mBUF IN LOOP ->\033[0;37m\n%s", buf);
	//printf("\n\n\033[1;33mBUF AFTER LOOP ->\033[0;37m\n%s", result);
}
