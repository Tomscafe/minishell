#include <sys/stat.h>
#include <stdio.h>

int	main(void)
{
	struct stat permission;
	mode_t mode;

	printf("stat ret : %d\n", stat("/bin/ls", &permission));
	mode = permission.st_mode & 0777;
	printf("all permission : 0%o\n", mode);
	printf("otehr permission : 0%o\n", mode & 07);
	printf("group permission : 0%o\n", mode & 0070);
	printf("user permission : 0%o\n", mode &0700);
	printf("executable : %d %d %d\n", ((mode & 0700) >> 6) & 1, ((mode &070) >> 3) & 1, mode & 1);
	return (0);
}