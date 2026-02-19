/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:35:11 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/13 12:28:44 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_read(int fd, char *buff, char *cup)
{
	int		count;
	char	*temp;

	count = 1;
	while (count != 0)
	{
		count = read(fd, buff, BUFFER_SIZE);
		if (count == -1)
			return (NULL);
		else if (count == 0)
			break ;
		buff[count] = '\0';
		if (cup == NULL)
			cup = ft_strdup_next("");
		temp = cup;
		cup = ft_strjoin_next(temp, buff);
		free(temp);
		temp = NULL;
		if (ft_strchr_next(buff, '\n'))
			break ;
	}
	return (cup);
}

static char	*ft_obtain(char *line)
{
	size_t		count;
	char		*result;

	count = 0;
	while (line[count] && line[count] != '\n')
		count++;
	if (!line[count] || line[count + 1] == '\0')
		return (NULL);
	result = ft_substr_next(line, count + 1, ft_strlen_next(line) - count);
	if (!result)
		return (NULL);
	if (*line == '\0')
	{
		free(line);
		line = NULL;
	}
	line[count + 1] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*x;
	char		*buffer;
	char		*line;	

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(x);
		x = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = ft_read(fd, buffer, x);
	free(buffer);
	buffer = NULL;
	if (line == NULL)
	{
		free(x);
		x = NULL;
		return (NULL);
	}
	x = ft_obtain(line);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>



int	main(int ac, char **av)
{
	int		fd;
	char	*nextline;

	nextline = NULL;
	(void)ac;
	fd = open(av[1], O_RDONLY);
	while (nextline == get_next_line(fd))
	{
		printf("%s\n", nextline);
		free(nextline);
	}s
	close(fd);
	return (0);
}
*/
/*
int	main(void)
{
	int		fd;
	char	*line;


	fd = open("text.txt", O_RDONLY);
	while ((line = get_next_line(fd)) > 0)
		printf("%s\n", line);
	close(fd);
	return (0);
} */
