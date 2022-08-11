/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:40:16 by mmardi            #+#    #+#             */
/*   Updated: 2022/08/05 19:04:27 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(char *res, int fd)
{
	char	*buff;
	int		n;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	n = 1;
	while (ft_strchr(res, '\n') == NULL && n != 0)
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[n] = '\0';
		res = ft_strjoin(res, buff);
	}
	free(buff);
	return (res);
}

char	*ft_ch_res(char	*res)
{
	size_t	i;
	size_t	j;
	char	*s;

	i = 0;
	j = 0;
	while (res[i] != '\n' && res[i] != '\0')
		i++;
	if (i == ft_strlen(res))
	{
		free(res);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(res) - i + 1));
	if (s == NULL)
		return (NULL);
	i++;
	while (res[i])
	{
		s[j++] = res[i++];
	}
	s[j] = '\0';
	free (res);
	return (s);
}

char	*ft_line(char *res)
{
	size_t	i;
	char	*line;
	size_t	j;

	i = 0;
	if (res[0] == '\0')
		return (NULL);
	while (res[i] != '\n' && res[i] != '\0')
		i++;
	// if (res[i] == '\n')
	// 	i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (line == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = res[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	res = ft_read(res, fd);
	if (res == NULL)
		return (NULL);
	line = ft_line(res);
	res = ft_ch_res(res);
	return (line);
}

/*int	main()
{
	int	fd;
	int fc;

	fd = open("get_next_line.c", O_RDONLY);
	fc = open("get_next_line_utils.c", O_RDONLY);
	char *b = "j";
	while(b != NULL)
	{
		b = get_next_line(fd);
		b = get_next_line(fc);
		printf("%s", b);
	}
}*/