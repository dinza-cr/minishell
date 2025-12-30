/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinza-cr <dinza-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:43:36 by dinza-cr          #+#    #+#             */
/*   Updated: 2025/11/23 19:44:07 by dinza-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_group *group, t_list_env *env)
{
	if (group->cmd[1] && *(group->cmd[1])
		&& (ft_strncmp(group->cmd[1], "env", ft_strlen("env"))))
	{
		ft_putstr_err("env: ");
		ft_putstr_err(group->cmd[1]);
		ft_putstr_err(": No such file or directory\n");
		return (125);
	}
	print_env_list(env, STDOUT_FILENO);
	return (0);
}
