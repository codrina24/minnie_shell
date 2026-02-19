/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:40:46 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/24 16:19:35 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

char	*ft_get_home(t_cmd *cmd, t_gc *gc, t_env *env)
{
	char	*path;

	if (!cmd || !gc || !env)
		return (NULL);
	if (!cmd->args[1])
	{
		path = ft_get_path_value(env, "HOME", gc);
		if (!path)
			return (NULL);
	}
	else
	{
		path = ft_gc_strdup(gc, cmd->args[1]);
		if (!path)
			return (NULL);
	}
	return (path);
}

char	*ft_get_right_path(t_cmd *cmd, t_env *env, t_gc *gc)
{
	char	*path;

	if (!cmd || !env || !gc)
		return (NULL);
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-") == 0)
	{
		path = ft_implement_dash(env, gc);
		if (!path)
			return (NULL);
	}
	else
	{
		path = ft_get_home(cmd, gc, env);
		if (!path)
			return (NULL);
	}
	return (path);
}

char	*ft_implement_dash(t_env *env, t_gc *gc)
{
	char	*path;

	if (!env || !gc)
		return (NULL);
	path = ft_get_path_value(env, "OLDPWD", gc);
	if (!path)
		return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), NULL);
	ft_putendl_fd(path, 2);
	return (path);
}

int	ft_change_dir(char *path)
{
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	return (0);
}

int	ft_cd_execute(t_cmd *cmd, t_gc *gc, t_env *env)
{
	char	*oldcwd;
	char	*new_path;
	char	*path;

	oldcwd = getcwd(NULL, 0);
	if (!oldcwd || ft_supp_protect(oldcwd) == 1)
	{
		ft_putstr_fd("minishell: cd: error: no such file or directory\n", 2);
		return (1);
	}
	path = ft_get_right_path(cmd, env, gc);
	if (!path)
		return (free(oldcwd), 1);
	if (ft_change_dir(path) != 0)
		return (free(oldcwd), 1);
	new_path = getcwd(NULL, 0);
	if (!new_path || ft_supp_protect(new_path) == 1)
	{
		ft_putstr_fd("minishell: cd: error getting path\n", 2);
		return (free(oldcwd), ft_gc_free_one(gc, path), 1);
	}
	if (ft_up_pwd(env, oldcwd, new_path, gc) != 0)
		return (ft_putstr_fd("err up pwd", 2), free(oldcwd), free(new_path), 1);
	return (free(oldcwd), free(new_path), 0);
}
