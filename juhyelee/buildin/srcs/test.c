#include "../includes/buildin.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	**envs;

	envs = dup_envs((const char **)envp);
	envs = export_cmd(argc, (const char **)argv, (const char **)envs);
	export_cmd(1, (const char **)argv, (const char **)envs);
	unset_cmd(argc, (const char **)argv, envs);
	printf("\n\n");
	export_cmd(1, (const char **)argv, (const char **)envs);
	return (0);
}
