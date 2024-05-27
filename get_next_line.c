/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:12:35 by jteissie          #+#    #+#             */
/*   Updated: 2024/05/27 18:36:05 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Get start line
//Get line to print 
//Set start line to the line we just printed

#include "get_next_line.h"

void    ft_bzero(void *s, size_t n)
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

void    *ft_calloc(size_t nmemb, size_t size)
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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] = '\0')
		return (0);
	while (str[i])
		i++;
	return (i);
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		parse_index;

	i = 0;
	parse_index = 0;
	joined = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
	{
		free(s2);
		return (NULL);
	}
	while (s1 && s1[parse_index])
	{
		joined[i] = s1[parse_index];
		i++;
		parse_index++;
	}
	parse_index = 0;
	while (s2 && s2[parse_index])
	{
		joined[i] = s2[parse_index];
		i++;
		parse_index++;
	}
	joined[i] = '\0';
	free(s1);
	return (joined);
}

char	*fetch_line(int fd, int buffer_size)
{
	int	status;
	char	*read_buffer;
	char	*temp_buffer;
	
	status = 0;
	temp_buffer = ft_calloc(buffer_size, sizeof(char));
	if (!temp_buffer)
		return (NULL);
	read_buffer = ft_calloc(buffer_size, sizeof(char));
	if (!read_buffer)
	{
		free(temp_buffer);
		return (NULL);
	}
	read_buffer[0] = '\0';
	while(!find_eol(temp_buffer))
	{
		status = read(fd, temp_buffer, buffer_size);
		if (status == -1)
		{
			free(read_buffer);
			free(temp_buffer);
			return (NULL);
		}
		read_buffer = ft_strjoin(read_buffer, temp_buffer);
		if (status == 0)
			break;
		ft_bzero(temp_buffer, buffer_size);
	}
	free(temp_buffer);
	return (read_buffer);
}

//add read permissions safety (if (read(fd) < 0))

char	*trim_buff(char *read_buff)
{
	int	i;
	char	*trimmed_buff;

	i = 0;
	while (read_buff[i])
	{
		if (read_buff[i] == '\n')
		{
			i++;
			break;
		}
		i++;
	}
	trimmed_buff = ft_calloc(i, sizeof(char));
	if (!trimmed_buff)
		return (NULL);
	i = 0;
	while (read_buff[i])
	{
		
		trimmed_buff[i] = read_buff[i];
		i++;
		if (read_buff[i] == '\n')
		{
			trimmed_buff[i] = read_buff[i];
			i++;
			break;
		}
	}
	trimmed_buff[i] = '\0';
	free(read_buff);
	return (trimmed_buff);
}

char	*get_leftovers(char *read_buff)
{
	int	i;
	int	left_i;
	char	*leftovers;

	i = 0;
	left_i = 0;
	while (read_buff[i])
	{
		if (read_buff[i] == '\n')
		{
			i++;
			break;
		}
		i++;
	}
	leftovers = ft_calloc(ft_strlen(read_buff) - i, sizeof(char));
	if (!leftovers)
		return (NULL);
	while (read_buff[i])
	{
		leftovers[left_i] = read_buff[i];
		left_i++;
		i++;
	}
	leftovers[left_i] = '\0';
	return (leftovers);
}

int	check_last_line(char *str)
{
	int	i;
	int	n_count;

	i = 0;
	n_count = 0;
	while (str[i])
	{
		if(str[i] == '\n')
			n_count++;
		i++;
	}
	if(str[i - 1] == '\n' && n_count == 1)
		return (1);
	return (0);
}

char	*last_line_dup(char *str)
{
	int	i;
	int	len;
	char	*last;

	i = 0;
	len = ft_strlen(str);
	last = ft_calloc(len, sizeof(char));
	if (!last)
		return (NULL);
	while (str[i])
	{
		last[i] = str[i];
		i++;
	}
	last[i] = '\0';
	free(str);
	return (last);
}

char	*get_next_line(int fd)
{
	char		*new_line;
	char		*read_buff;
	static char	*leftovers;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	/*if(leftovers && check_last_line(leftovers))
		return(last_line_dup(leftovers));*/
	read_buff = fetch_line(fd, BUFFER_SIZE);
	if (!read_buff)
	{
		if (leftovers)
			free(leftovers);
		return (NULL);
	}
	if (leftovers)
	{
		read_buff = ft_strjoin(leftovers, read_buff);
		if (!read_buff)
		{
			free(leftovers);
			return (NULL);
		}
	}
	leftovers = get_leftovers(read_buff);
	if (!leftovers)
	{
		free(read_buff);
		return (NULL);
	}
	new_line = trim_buff(read_buff);
	if (!new_line)
	{
		free(read_buff);
		free(leftovers);
		return (NULL);
	}
	return (new_line);	
}

#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	(void)argc;
	int	fd;

	fd = open(argv[1], O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return 0;
}
