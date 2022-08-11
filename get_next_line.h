/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:51:51 by mmardi            #+#    #+#             */
/*   Updated: 2022/08/05 18:40:34 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H


# define BUFFER_SIZE 2
# include<stdlib.h>
# include<unistd.h>
#include <fcntl.h>

size_t		ft_strlen(const char *str);
char		*ft_strchr(char *str, char c);
char		*get_next_line(int fd);
char		*ft_strjoin(char *s1, char *s2);

#endif