/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzerad <mzerad@student.42.fr>       	    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:46:03 by mzerad            #+#    #+#             */
/*   Updated: 2025/06/30 16:45:21 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include "../libft/libft.h"
# include <stdio.h>

typedef struct s_env	t_env;

typedef struct s_gc_node
{
	void				*tracked_ptr;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_gc
{
	t_gc_node	*head;
	t_env		*env;
	char		*result;
	int			last_status;
	int			flag;
	int			in_quotes_eof;
}	t_gc;

// GC_INIT_AND_TRACK_MALLOC

void	ft_gc_init(t_gc *gc);
void	ft_gc_add(t_gc *gc, void *ptr);
void	*ft_gc_malloc(t_gc *gc, size_t size);

// GC_ALLOC_FUNCTIONS

char	*ft_gc_strdup(t_gc *gc, const char *s);
char	*ft_gc_substr(t_gc *gc, const char *s, unsigned int start, size_t len);
char	*ft_gc_strjoin(t_gc *gc, const char *s1, const char *s2);
char	*ft_gc_strjoin_cmd(t_gc *gc, const char *s1, const char *s2);
char	*ft_gc_itoa(t_gc *gc, int nbr);

// GC_SPLIT

char	**ft_gc_split(t_gc *gc, const char *s, char c);

// GC_FREE

void	ft_gc_free_one(t_gc *gc, void *ptr);
char	*ft_gc_free_tab(t_gc *gc, char **tab);
void	ft_gc_free_all(t_gc *gc);
void	ft_gc_free_all_and_env(t_gc *gc, t_gc *gc_env);
void	ft_print_gc_alloc_ptr_for_debug(t_gc *gc);//voir si utile

// UTILS

int		ft_count_char_in_nbr(long n);

#endif
