/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:04:51 by jteissie          #+#    #+#             */
/*   Updated: 2024/05/27 16:04:52 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	unsigned int	i;
	unsigned char	*str;

	i = 0;
	str = s;
	while (i < n)
		str[i++] = '\0';
}

void	copy_and_cat(char *out, char *cpy_src, char *cat_src)
{
	int	i;
	int	src_i;

	i = 0;
	src_i = 0;
	while (cpy_src[src_i])
	{
		out[i] = cpy_src[src_i];
		i++;
		src_i++;
	}
	src_i = 0;
	while (cat_src[src_i])
		out[i++] = cat_src[src_i++];
	out[i] = '\0';
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

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
	if (i)
		ft_bzero(str, i);
	return (0);
}
