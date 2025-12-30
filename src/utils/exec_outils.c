/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:39:31 by anbelose          #+#    #+#             */
/*   Updated: 2025/11/23 19:39:34 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *name, int type, int code)
{
	if (type == 0)
	{
		if (name == NULL)
			perror("minishell");
		else
		{
			ft_putstr_err("minishell: ");
			perror(name);
		}
	}
	if (type == 1 && name)
	{
		ft_putstr_err("minishell: ");
		ft_putstr_err(name);
		ft_putstr_err(": command not found\n");
	}
	return (code);
}

int	ft_count_env(t_list_env *env)
{
	int			count;
	t_list_env	*start;

	count = 0;
	start = env;
	while (start)
	{
		count++;
		start = start->next;
	}
	return (count);
}

char	**ft_convert_env(t_list_env *env)
{
	char		**new_env;
	char		*tmp;
	int			count;
	int			i;

	i = 0;
	count = ft_count_env(env);
	new_env = ft_calloc(count + 1, sizeof(char *));
	while (env)
	{
		if (env->value)
		{
			tmp = ft_strjoin(env->key, "=");
			new_env[i] = ft_strjoin(tmp, env->value);
			free(tmp);
		}
		else
			new_env[i] = ft_strdup(env->key);
		i++;
		env = env->next;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	ft_count_groups(t_main *parsed)
{
	int		count;
	t_group	*tmp;

	count = 0;
	tmp = parsed->group;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int	ft_wait(t_exec *exec, int *code)
{
	int	status;
	int	i;
	int	sig;

	status = 0;
	i = 0;
	sig = 0;
	while (i < exec->cpid_index)
	{
		waitpid(exec->cpid[i], &status, 0);
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
			else if (sig == SIGINT && exec->group_count > 1)
				write(1, "\n", 1);
			*code = 128 + sig;
		}
		else if (WIFEXITED(status))
			*code = WEXITSTATUS(status);
		i++;
	}
	return (*code);
}
