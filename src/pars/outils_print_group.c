/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_print_group.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:35:34 by anbelose          #+#    #+#             */
/*   Updated: 2025/11/23 19:35:38 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

void	print_group(t_group *group)
{
	if (group == NULL)
		return ;
	ft_putstr_fd("\nGroup : \n", 0);
	if (group->cmd)
	{
		ft_putstr_fd("\ncmd: \n", STDOUT_FILENO);
		print_tab(group->cmd, STDOUT_FILENO);
	}
	if (group->redir_in)
		printf("fichier redir_in: %s\n", group->redir_in);
	if (group->redir_out)
		printf("fichier redir_out: %s\n", group->redir_out);
	if (group->app_out)
		printf("fichier app_out: %s\n", group->app_out);
	printf("flag_fail: %d\n", group->flag_fail);
}

void	print_group_list(t_group *group)
{
	if (!group)
		return ;
	while (group)
	{
		print_group(group);
		group = group->next;
	}
}
