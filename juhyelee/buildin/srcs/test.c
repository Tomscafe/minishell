#include "../includes/buildin.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*envs;

	convert_env_list(&envs, (const char **)envp);
	export_cmd(&envs, argc, (const char **)argv);
	t_list *p = envs;
	while (p)
	{
		t_env *env = p->content;
		printf("%s\n", env->env);
		p = p->next;
	}
	return (0);
}
