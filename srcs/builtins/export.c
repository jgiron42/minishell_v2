#include "minishell.h"

unsigned char	sh_export(char **argv, t_env *env)
{
	int ret;
	int	i;

	ret = 0;
	argv++;
	while (argv && *argv)
	{
		i = 0;
		while ((*argv)[i] && !ft_isdigit((*argv)[0]) && isvalid_name_letter((*argv)[i]))
			i++;
		if (i > 0 && (*argv)[i] == '=')
		{
			(*argv)[i] = '\0';
			if(set_var(env, *argv,*argv + i + 1, 1) == FATAL)
				return (-1);
			(*argv)[i] = '=';
		}
		else
		{
			ret = 1;
			ft_putstr_fd("export :bad variable name\n", 2);
		}
		argv++;
	}
	return (ret);
}
