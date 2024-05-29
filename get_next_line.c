/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:12:35 by jteissie          #+#    #+#             */
/*   Updated: 2024/05/29 13:16:26 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_str_rejoin(char *stash, char *add)
{
	char	*joined;

	if (!stash)
		return (NULL);
	joined = ft_calloc((ft_strlen(stash) + ft_strlen(add) + 1), sizeof(char));
	if (!joined)
	{
		free(stash);
		return (NULL);
	}
	copy_and_cat(joined, stash, add);
	free(stash);
	return (joined);
}

char	*fetch_line(char *stash, int fd, int *status)
{
	char	*read_buff;

	if (!stash)
		return (NULL);
	read_buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_buff)
	{
		free(stash);
		return (NULL);
	}
	while (!find_eol(read_buff))
	{
		*status = read(fd, read_buff, BUFFER_SIZE);
		if (*status <= 0)
		{
			free(read_buff);
			if (ft_strlen(stash) != 0)
				return (stash);
			free(stash);
			return (NULL);
		}
		stash = ft_str_rejoin(stash, read_buff);
	}
	free(read_buff);
	return (stash);
}

void	get_leftovers(char *leftovers, char *line)
{
	int	i;
	int	left_i;

	i = 0;
	left_i = 0;
	if (!line)
		return ;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	while (line[i])
	{
		leftovers[left_i] = line[i];
		line[i] = '\0';
		left_i++;
		i++;
	}
	leftovers[left_i] = '\0';
}

char	*trim_line(char	*untrimmed)
{
	int		i;
	char	*trimmed;

	i = 0;
	if (!untrimmed)
		return (NULL);
	while (untrimmed[i])
		i++;
	trimmed = ft_calloc(i + 1, sizeof(char));
	if (!trimmed)
	{
		free(untrimmed);
		return (NULL);
	}
	i = 0;
	while (untrimmed[i])
	{
		trimmed[i] = untrimmed[i];
		i++;
	}
	trimmed[i] = '\0';
	free(untrimmed);
	return (trimmed);
}

char	*get_next_line(int fd)
{
	static char	leftovers[BUFFER_SIZE + 1];
	char		*line;
	int			status;

	status = 0;
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_calloc(1, sizeof(char));
	if (ft_strlen(leftovers))
		line = ft_str_rejoin(line, leftovers);
	line = fetch_line(line, fd, &status);
	if (status == -1)
	{
		ft_bzero(leftovers, BUFFER_SIZE + 1);
		free(line);
		return (NULL);
	}
	get_leftovers(leftovers, line);
	line = trim_line(line);
	if (!line)
		return (NULL);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(int main, char *argv[])
{
	int	fd;
	char	*line;
	char	*line2;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	line2 = get_next_line(fd);
	printf("%s", line);
	printf("%s", line2);
	free(line);
	free(line2);
	return (0);
}*/
