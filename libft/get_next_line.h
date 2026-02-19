/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:29:31 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/13 12:30:08 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen_next(char *str);
char	*ft_strchr_next(char *s, int c);
char	*ft_strjoin_next(char *s1, char *s2);
char	*ft_strdup_next(char *s);
char	*ft_substr_next(char *s, unsigned int start, size_t len);

char	*get_next_line(int fd);

#endif
