/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:12:35 by jteissie          #+#    #+#             */
/*   Updated: 2024/05/26 18:33:22 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Get start line
//Get line to print 
//Set start line to the line we just printed

#include "get_next_line.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		parse_index;

	i = 0;
	parse_index = 0;
	joined = malloc (sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
		return (NULL);
	while (s1 && s1[parse_index])
	{
		joined[i] = s1[parse_index];
		i++;
		parse_index++;
	}
	parse_index = 0;
	while (s2 && s2[parse_index] && s2[parse_index] != '\n')
	{
		joined[i] = s2[parse_index];
		i++;
		parse_index++;
		if (s2[parse_index] == '\n')
			joined[i++] = '\n';
	}
	joined[i] = '\0';
	free(s1);
	return (joined);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	find_eol(char *str, int len)
{
	int	i;

	i = 0;
	while (i < len || str[i])
	{
		if (str[i] == '\n' || str[i] == '\0')
			return (1);
		i++;
	}
	if (i != len)
		return (1);
	return (0);
}

//WHAT HAPPENS IF END OF FILE
char	*store_next(char *buff)
{
	int		i;
	int		new_i;
	char	*new_start;

	i = 0;
	new_i = 0;
	while (buff[i] != '\n' && buff)
		i++;
	new_start = malloc(sizeof(char) * (ft_strlen(buff) - i) + 1);
	if (!new_start)
		return 0; (NULL);
	while (buff[i])
	{
		new_start[new_i] = buff[i];
		i++;
		new_i++;
	}
	new_start[new_i] = '\0';
	return (new_start);
}

char	*make_line(int fd, char *new_line, char **next_start)
{
	int		status;
	int		buff_len;
	char	*buff;

	status = 0;
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (next_start)
	{
		new_line = ft_strjoin(new_line, *next_start);
		free(*next_start);
	}
	status = read(fd, buff, BUFFER_SIZE); 
	if (status == -1)
	{
		free(buff);
		return (NULL);
	}
	buff_len = ft_strlen(buff);
	while (!find_eol(buff, BUFFER_SIZE))
	{
		new_line = ft_strjoin(new_line, buff);
		status = read(fd, buff, BUFFER_SIZE);
		if (status == -1) //fix safety
		{
			free(buff);
			return (NULL);
		}
	}
	new_line = ft_strjoin(new_line, buff);
	*next_start = store_next(buff);
	free(buff);
	return (new_line);
}

//add read permissions safety (if (read(fd) < 0))

char	*get_next_line(int fd)
{
	char		*new_line;
	static char	*next_start;

	if (!fd || BUFFER_SIZE <= 0)
		return (NULL);
	new_line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!new_line)
		return (NULL);
	new_line = NULL;
	if (next_start != NULL)
		new_line = ft_strjoin(new_line, next_start);
	new_line = make_line(fd, new_line, &next_start); 
	if (!new_line)
		return (NULL);
	ft_putstr(new_line);
	free(new_line);
}

#include <fcntl.h>

int	main(int argc, char *argv[])
{
	(void)argc;
	int	fd;

	fd = open(argv[1], O_RDONLY);
	get_next_line(fd);
	get_next_line(fd);
	return 0;
}
