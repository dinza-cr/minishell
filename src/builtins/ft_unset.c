/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinza-cr <dinza-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:43:46 by dinza-cr          #+#    #+#             */
/*   Updated: 2025/11/23 19:44:18 by dinza-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_list_one_node(t_list_env *env)
{
	if (env)
	{
		free(env->key);
		free(env->value);
		free(env);
	}
}

int	ft_remove_from_env(t_list_env **env, t_list_env *the_rm_env)
{
	t_list_env	*pos;
	t_list_env	*prev;

	prev = NULL;
	if (!env || !the_rm_env)
		return (ft_error(NULL, 0, 1));
	if (*env == the_rm_env)
	{
		*env = the_rm_env->next;
		return (ft_free_list_one_node(the_rm_env), 0);
	}
	pos = *env;
	while (pos != NULL && pos != the_rm_env)
	{
		prev = pos;
		pos = pos->next;
	}
	if (pos == the_rm_env)
	{
		prev->next = the_rm_env->next;
		ft_free_list_one_node(the_rm_env);
		return (0);
	}
	return (ft_error(NULL, 0, 1));
}

int	ft_unset_is_valid(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_err("minishell: unset: `");
		ft_putstr_err(str);
		ft_putstr_err("\': not a valid identifier\n");
		return (0);
	}
	i = 1;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_putstr_err("minishell: unset: `");
			ft_putstr_err(str);
			write(2, "\': not a valid identifier\n", 26);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_wrong_option(char *cmd)
{
	ft_putstr_err("minishell: unset: ");
	ft_putstr_err(cmd);
	ft_putstr_err(": invalid option\n");
}

int	ft_unset(t_group *group, t_list_env **env)
{
	int			i;
	t_list_env	*the_env;

	i = 1;
	while (group->cmd[i])
	{
		if (group->cmd[i][0] == '-' && group->cmd[i][1] != '\0')
			return (ft_wrong_option(group->cmd[i]), 2);
		if (!ft_unset_is_valid(group->cmd[i]))
		{
			i++;
			continue ;
		}
		the_env = ft_find_in_env(*env, group->cmd[i]);
		if (the_env)
		{
			if (ft_remove_from_env(env, the_env))
				return (1);
		}
		i++;
	}
	return (0);
}
