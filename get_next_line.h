/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:11:27 by jteissie          #+#    #+#             */
/*   Updated: 2024/05/26 17:13:36 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
char	*get_next_line(int fd);
char	*make_line(int fd, char *new_line, char *next_start);
void	ft_putstr(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
int		find_eol(char *str, int len);
char	*store_next(char *buff);
void	ft_putchar(char c);
#endif
