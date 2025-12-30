/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinza-cr <dinza-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 19:04:10 by dinza-cr          #+#    #+#             */
/*   Updated: 2025/11/20 18:37:54 by dinza-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_exec(t_main *parsed, t_exec *exec, t_list_env *env)
{
	if (g_status)
		return (1);
	exec->env = env;
	exec->main = parsed;
	exec->start = parsed->group;
	exec->group_count = ft_count_groups(parsed);
	exec->prev_fd = -1;
	exec->pipefd[0] = -1;
	exec->pipefd[1] = -1;
	exec->cpid_index = 0;
	exec->cpid = malloc(exec->group_count * sizeof(pid_t));
	if (!exec->cpid)
		return (1);
	exec->envp = ft_convert_env(env);
	if (!exec->envp)
		return (free(exec->cpid), 1);
	return (0);
}

int	ft_exec(t_main *parsed, t_list_env *env, int *code)
{
	t_exec	exec;

	if (ft_init_exec(parsed, &exec, env))
		return (free_main(parsed), 1);
	while (parsed->group)
	{
		if (parsed->group->next)
			if (pipe(exec.pipefd) == -1)
				return (perror("pipe failed"), 1);
		if (parsed->group->cmd && parsed->group->cmd[0]
			&& is_built(parsed->group->cmd[0]))
			exec_builtin(parsed->group, env, &exec, code);
		else
			exec_execve(parsed->group, &exec);
		parsed->group = parsed->group->next;
	}
	if (exec.cpid_index > 0)
		*code = ft_wait(&exec, code);
	parsed->group = exec.start;
	free_main(parsed);
	free_exec(&exec);
	return (*code);
}
