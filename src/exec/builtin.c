/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinza-cr <dinza-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:04 by abelosev          #+#    #+#             */
/*   Updated: 2025/11/10 19:05:18 by dinza-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built(char *str)
{
	int		i;
	char	*tab[7];

	i = 0;
	if (!str)
		return (0);
	tab[0] = "echo";
	tab[1] = "cd";
	tab[2] = "pwd";
	tab[3] = "export";
	tab[4] = "unset";
	tab[5] = "env";
	tab[6] = "exit";
	while (i <= 6)
	{
		if (ft_strlen(tab[i]) == ft_strlen(str) && ft_strcmp(str, tab[i]) == 0)
			return (i + 1);
		i++;
	}
	return (0);
}
