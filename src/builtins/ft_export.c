/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinza-cr <dinza-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:43:40 by dinza-cr          #+#    #+#             */
/*   Updated: 2025/11/23 19:44:13 by dinza-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write_export(t_list_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key, "_", ft_strlen(env->key)) == 0)
		{
			env = env->next;
			continue ;
		}
		if (env->key)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(env->key, STDOUT_FILENO);
			if (!env->value && ft_strchr(env->key, '='))
				ft_putstr_fd("\"\"", STDOUT_FILENO);
			else if (env->value)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(env->value, STDOUT_FILENO);
				ft_putstr_fd("\"", STDOUT_FILENO);
			}
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		env = env->next;
	}
}

int	ft_export_is_valid(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_err("minishell: export: `");
		ft_putstr_err(str);
		ft_putstr_err("\': not a valid identifier\n");
		return (0);
	}
	i = 1;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_putstr_err("minishell: export: `");
			ft_putstr_err(str);
			ft_putstr_err("\': not a valid identifier\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export_replace_or_add(t_list_env **env, char *str)
{
	t_list_env	*the_env;
	char		*new_key;
	char		*new_value;

	new_key = get_key(str);
	if (!new_key)
		return (ft_error(NULL, 0, 1));
	the_env = ft_find_in_env(*env, new_key);
	if (!the_env)
	{
		free(new_key);
		return (ft_add_to_msh_env(env, str));
	}
	free(the_env->key);
	the_env->key = new_key;
	new_value = get_value(str);
	if (!new_value)
		return (0);
	if (the_env->value)
		free(the_env->value);
	the_env->value = new_value;
	return (0);
}

int	ft_export(t_group *group, t_list_env *env)
{
	int		i;
	int		error_flag;
	int		valid;

	if (group->cmd[1] == NULL)
		return (ft_write_export(env), 0);
	i = 1;
	error_flag = 0;
	while (group->cmd[i] != NULL)
	{
		valid = ft_export_is_valid(group->cmd[i]);
		if (valid == -1)
			return (2);
		else if (valid == 0)
			error_flag = 1;
		else if (valid == 1)
		{
			if (ft_export_replace_or_add(&env, group->cmd[i]))
				return (1);
		}
		i++;
	}
	return (error_flag);
}
