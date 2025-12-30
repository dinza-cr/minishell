/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinza-cr <dinza-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:57:56 by dinza-cr          #+#    #+#             */
/*   Updated: 2025/11/23 14:58:00 by dinza-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

char	*get_hd_delimiter(t_tokens *list)
{
	char	*del;

	del = NULL;
	while (list && list->next)
	{
		if (list->type == APP_IN && list->next->type == WORD)
		{
			free(del);
			del = ft_strdup(list->next->value);
			if (!del)
				return (NULL);
		}
		list = list->next;
	}
	return (del);
}

void	hd_loop(t_exec *exec, char *line, char *expanded, int pipefd[2])
{
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, exec->main->hd_del) == 0)
			break ;
		expanded = ft_expand(line, exec->env, &g_status);
		free(line);
		line = expanded;
		if (line)
		{
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
	}
}

void	ft_heredoc(t_exec *exec)
{
	int		pipefd[2];
	char	*line;
	char	*expanded;

	line = NULL;
	expanded = NULL;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	heredoc_signals();
	hd_loop(exec, line, expanded, pipefd);
	free(line);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}
