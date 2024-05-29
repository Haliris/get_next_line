/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:11:27 by jteissie          #+#    #+#             */
/*   Updated: 2024/05/29 11:15:30 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*fetch_line(char *stash, int fd, int *status);
char	*trim_buff(char *read_buff);
void	get_leftovers(char *leftovers, char *line);
char	*ft_str_rejoin(char *stash, char *append);
int		ft_strlen(char *str);
int		find_eol(char *str);
int		get_buff_len(char *buff);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
char	*last_line_dup(char *str);
int		check_last_line(char *str);
void	copy_and_cat(char *out, char *cpy_src, char *cat_src);
#endif
