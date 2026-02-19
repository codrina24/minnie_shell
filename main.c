/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzerad <mzerad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:56:50 by mzerad            #+#    #+#             */
/*   Updated: 2025/09/27 19:10:01 by mzerad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./parser/pars_minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	ft_start(void)
{
	ft_putendl_fd("\033[1;36m        __  __ _       _     _          _ _     \
		   														\033[0m", 1);
	ft_putendl_fd("\033[1;35m       |  \\/  (_)_ __ (_)___| |__   ___| | |    \
		   														\033[0m", 1);
	ft_putendl_fd("\033[1;33m       | |\\/| | | '_ \\| / __| '_ \\ / _ \\ | | \
																\033[0m", 1);
	ft_putendl_fd("\033[1;32m       | |  | | | | | | \\__ \\ | | |  __/ | |   \
		  														\033[0m", 1);
	ft_putendl_fd("\033[1;31m       |_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|    \
																\033[0m", 1);
	ft_putendl_fd("\033[1;96m       _    _ _ _   _ _ ___ _   _   ___ _ _ \
																\033[0m\n", 1);
}

int	ft_safe_return(t_gc *gc, t_gc *gc_env, int last_status)
{
	ft_gc_free_all(gc);
	ft_gc_free_all(gc_env);
	return (last_status);
}

int	main(int argc, char **argv, char **envp)
{
	int		last_status;
	t_gc	gc;
	t_gc	gc_env;
	t_env	*env;
	t_ast	*ast;

	(void)argc;
	(void)argv;
	gc.last_status = 0;
	ast = NULL;
	ft_gc_init(&gc_env);
	env = ft_env_init(&gc_env);
	if (!env)
		return (ft_gc_free_all(&gc_env), -1);
	env = ft_create_env_list(envp, env, &gc_env);
	if (!env)
		return (ft_gc_free_all(&gc_env), -1);
	ft_increment_shlvl(&gc_env, env);
	gc_env.env = env;
	if (isatty(0))
		ft_start();
	last_status = ft_mini_world(env, &ast, &gc, &gc_env);
	ft_gc_free_all_and_env(&gc, &gc_env);
	rl_clear_history();
	return (last_status);
}
