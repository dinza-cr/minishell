/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinza-cr <dinza-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 19:03:10 by dinza-cr          #+#    #+#             */
/*   Updated: 2025/11/20 18:51:32 by dinza-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_pipe(t_group *group, t_exec *exec)
{
	if (group != exec->start)
	{
		dup2(exec->prev_fd, STDIN_FILENO);
		close(exec->prev_fd);
	}
	if (group->next)
	{
		close(exec->pipefd[0]);
		dup2(exec->pipefd[1], STDOUT_FILENO);
		close(exec->pipefd[1]);
	}
}

int	ft_redir_in(t_group *group)
{
	int	fd;

	fd = open(group->redir_in, O_RDONLY);
	if (fd == -1)
	{
		perror(group->redir_in);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	ft_redir_out(t_group *group)
{
	int	fd;

	fd = open(group->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(group->redir_out);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	ft_app_out(t_group *group)
{
	int	fd;

	fd = open(group->app_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(group->app_out);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	ft_redir(t_group *group)
{
	if (group->redir_in && ft_redir_in(group))
		return (1);
	if (group->redir_out && ft_redir_out(group))
		return (1);
	else if (group->app_out && ft_app_out(group))
		return (1);
	return (0);
}
