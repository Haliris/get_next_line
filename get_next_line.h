/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:11:27 by jteissie          #+#    #+#             */
/*   Updated: 2024/05/27 14:49:26 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
char	*get_next_line(int fd);
char	*fetch_line(int fd, int buffer_size);
char	*trim_buff(char *read_buff);
char	*get_leftovers(char *read_buff);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
int		find_eol(char *str);
int	get_buff_len(char *buff);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
#endif
