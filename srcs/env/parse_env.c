//
// Created by joachim on 22/11/2021.
//

#include "minishell.h"

t_env	*parse_env(char **envp)
{
	t_env	*env;
	char	*equal;

	env = NULL;
	while (*envp)
	{
		equal = *envp;
		while (*equal && *equal != '=')
			equal++;
		*equal = 0;
		++equal;
		if (equal)
		{
			add_env(&env, *envp, equal, true);
		}
	}
	return (env);
}