/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinza-cr <dinza-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:43:32 by dinza-cr          #+#    #+#             */
/*   Updated: 2025/11/23 19:44:05 by dinza-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_echo_is_flag(char *str)
{
	int	i;

	if ((ft_strlen(str) < 2) || (ft_strncmp(str, "-n", 2) != 0))
		return (0);
	i = 2;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_group *group)
{
	int	option_flag;
	int	i;

	if (group->cmd[1] == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	option_flag = 0;
	i = 1;
	while (group->cmd[i] && ft_echo_is_flag(group->cmd[i]))
	{
		option_flag = 1;
		i++;
	}
	while (group->cmd[i])
	{
		write(STDOUT_FILENO, group->cmd[i], ft_strlen(group->cmd[i]));
		i++;
		if (group->cmd[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (option_flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
