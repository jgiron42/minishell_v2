/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:06:37 by jgiron            #+#    #+#             */
/*   Updated: 2022/03/04 11:06:38 by jgiron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	ft_shell(t_env *env, char *line)
{
	t_token_list	*tokens;
	t_command		tree;
	int				ret;

	ret = tokenise(line, &tokens, env);
	if (ret != OK)
	{
		if (env->is_interactive)
			return (ret);
		else
			return (FATAL);
	}
	if (tokens->type == END)
		return (free_token_list(tokens), OK);
	ret = parse_tree(tokens, &tree, env);
	if (ret == OK)
		ret = exec_command(tree, env);
	else if (!env->is_interactive)
		ret = FATAL;
	destroy_tree(tree);
	free_token_list(tokens);
	return (ret);
}

t_status	loop(t_env *env)
{
	char	*line;
	int		ret;

	ret = 0;
	while (1)
	{
		ret = readnline(&line, env);
		if (ret == FATAL)
			return (FATAL);
		if (ret == OK && ft_shell(env, line) == FATAL)
		{
			free(line);
			return (FATAL);
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		env;

	(void)argc;
	(void)argv;
	if (parse_env(envp, &env) != FATAL && init_env(&env) != FATAL)
		loop(&env);
	if (errno)
		perror(NAME);
	free_env(&env);
	return (1);
}

/* ( ls | cat && pwd || ls ) | { pwd | echo } && ls
 *
 *
 *
 * 		ls		  cat
 * 		|		  |
 * 		pipeline--pl     pwd	   ls	   pwd		   echo
 * 		|				 |		   |	   |		   |
 * 		list&&-----------list||----list;   pipeline----pl
 * 		|								   |
 * 		grouping(						   grouping{
 * 		|								   |
 * 		pipeline---------------------------pl				 ls
 * 	   	|				   									 |
 * 		list&&-----------------------------------------------list;
 * 		|
 * 		root
 */
//
//t_command	*parse_grouping(t_token *list)
//{
//	 t_command *ret = new_command;
//
//	 if (list->type == '(')
//		 new_command->is_in_subshell = true;
//	 else
//		 new_command->is_in_subshell = false;
//	 ret->command = parse(list->next, {')'});
//	 return (ret);
//}
//	pipeline: {"|", "&&", "||", ")"};
//	list:	  {"&&", "||", ")"};
//	simple:	  {"|", "&&", "||", ")"};
//	grouping: {")"};
//
//root = parse(token_list);
