/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinza-cr <dinza-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:43:44 by dinza-cr          #+#    #+#             */
/*   Updated: 2025/11/23 19:44:15 by dinza-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_group *group)
{
	char	*current_dir;

	if (group->cmd[1])
		return (ft_putstr_err("minishell: pwd: too many arguments\n"), 1);
	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (ft_error("pwd", 0, 1));
	write(STDOUT_FILENO, current_dir, ft_strlen(current_dir));
	write(STDOUT_FILENO, "\n", 1);
	free(current_dir);
	return (0);
}
