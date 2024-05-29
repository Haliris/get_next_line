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

char	*ft_str_rejoin(char *stash, char *append)
{
	char	*joined;
	int		i;
	int		parse_index;

	if (!stash)
		return (NULL);
	i = 0;
	parse_index = 0;
	joined = ft_calloc((ft_strlen(stash) + ft_strlen(append) + 1), sizeof(char));
	if (!joined)
	{
		free(stash);
		return (NULL);
	}
	while (stash[parse_index])
	{
		joined[i] = stash[parse_index];
		i++;
		parse_index++;
	}
	parse_index = 0;
	while (append[parse_index])
	{
		joined[i] = append[parse_index];
		i++;
		parse_index++;
	}
	joined[i] = '\0';
	free(stash);
	return (joined);
}

char	*fetch_line(char *stash, int fd)
{
	char	*read_buff;
	int	status;

	if (!stash)
		return (NULL);
	status = 1;
	read_buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_buff)
	{
		free(stash);
		return (NULL);
	}
	while (!find_eol(read_buff))
	{
		status = read(fd, read_buff, BUFFER_SIZE);
		if (status <= 0)
		{
			free(read_buff);
			if (ft_strlen(stash) != 0)
				return(stash);
			free(stash);
			return (NULL);
		}
		stash = ft_str_rejoin(stash, read_buff);
	}
	free(read_buff);
	if (!stash)
		return (NULL);
	return (stash);
}

char	*get_leftovers(char *line)
{
	int	i;
	int	left_i;
	char	*leftovers;

	i = 0;
	left_i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\n')
		{
			i++;
			break;
		}
		i++;
	}
	if (ft_strlen(line) - i == 0)
		return (NULL);
	leftovers = ft_calloc((ft_strlen(line) - i + 1), sizeof(char));
	if (!leftovers)
		return (NULL);
	while (line[i])
	{
		leftovers[left_i] = line[i];
		left_i++;
		i++;
	}
	leftovers[left_i] = '\0';
	return (leftovers);
}

char	*trim_line(char	*untrimmed)
{
	int	i;
	char	*trimmed;

	i = 0;
	if (!untrimmed)
		return (NULL);
	while (untrimmed[i])
	{
		if (untrimmed[i] == '\n')
		{
			i++;
			break;
		}
		i++;
	}
	trimmed = ft_calloc(i + 1, sizeof(char));
	if (!trimmed)
	{
		free(untrimmed);
		return (NULL);
	}
	i = 0;
	while (untrimmed[i] != '\n' && untrimmed[i])
	{
		trimmed[i] = untrimmed[i];
		i++;
	}
	if (untrimmed[i] == '\n')
	{
		trimmed[i] = '\n';
		i++;
	}
	trimmed[i] = '\0';
	free(untrimmed);
	return (trimmed);
}

char	*get_next_line(int fd)
{
	static char	*leftovers;
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_calloc(1, sizeof(char));
	if (leftovers)
		line = ft_str_rejoin(line, leftovers);
	free(leftovers);
	line = fetch_line(line, fd);
	leftovers = get_leftovers(line);
	line = trim_line(line);
	if (!line)
	{
		free(leftovers);
		return (NULL);
	}
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
