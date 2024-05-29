/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:12:35 by jteissie          #+#    #+#             */
/*   Updated: 2024/05/29 13:08:46 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Get start line
//Get line to print 
//Set start line to the line we just printed

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned int    i;
	unsigned char   *str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}


void	*ft_calloc(size_t nmemb, size_t size)
{
	void    *ptr;
	size_t  total_size;

	total_size = size * nmemb;
	if (total_size < size && total_size != 0)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb);
	return (ptr);
}

int	find_eol(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_str_rejoin(char *stash, char *append)
{
	char	*joined;
	int		i;
	int		parse_index;

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

	status = 1;
	read_buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_buff)
	{
		free(stash);
		return (NULL);
	}
	while (status > 0)
	{
		status = read(fd, read_buff, BUFFER_SIZE);
		if (status == 0)
		{
			free(read_buff);
			if (ft_strlen(stash) != 0)
				return(stash);
			free(stash);
			return (NULL);
		}
		if (status == -1)
		{
			free(read_buff);
			free(stash);
			return (NULL);
		}
		stash = ft_str_rejoin(stash, read_buff);
		if (!stash)
		{
			free(read_buff);
			return (NULL);
		}
		if (find_eol(read_buff))
			break;
		ft_bzero(read_buff, BUFFER_SIZE + 1);
	}
	free(read_buff);
	return (stash);
}

char	*get_leftovers(char *line)
{
	int	i;
	int	left_i;
	char	*leftovers;

	i = 0;
	left_i = 0;
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
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line)
	{
		if (leftovers)
			free(leftovers);
		return (NULL);
	}
	if (leftovers)
	{
		line = ft_str_rejoin(line, leftovers);
		if (!line)
		{
			free(leftovers);
			free(line);
			return (NULL);
		}
		free(leftovers);
	}
	line = fetch_line(line, fd);
	if (!line)
		return (NULL);
	leftovers = get_leftovers(line);
	line = trim_line(line);
	if (!line)
	{
		if (leftovers)
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
