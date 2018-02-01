/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 18:54:48 by jjolivot          #+#    #+#             */
/*   Updated: 2018/02/01 18:18:47 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		ft_get_reste(char **reste, char **line)
{
	char		*endline;
	char		*tmp;

	if ((endline = ft_strchr(*reste, '\n')))
	{
		if (!((*line = ft_strsub(*reste, 0, endline - *reste)) &&
		(tmp = ft_strsub(*reste, endline - *reste + 1, ft_strlen(*reste)))))
			return (-1);
		ft_strdel(reste);
		*reste = tmp;
		return (1);
	}
	else
	{
		if (!(*line = ft_strdup(*reste)))
			return (-1);
		ft_strdel(reste);
	}
	return (0);
}

int		ft_gnl_start(int fd, char **line, char **endline, char **reste)
{
	int ret;

	if (fd < 0 || line == NULL)
		return (-1);
	if (!(*line = ft_strnew(0)))
		return (-1);
	*endline = NULL;
	if (*reste)
	{
		if ((ret = ft_get_reste(reste, &(*line))) == -1)
			return (-1);
		if (ret == 1)
			return (1);
	}
	return (2);
}

int		get_next_line(const int fd, char **line)
{
	static char	*reste;
	int			ret;
	char		buff[BUFF_SIZE + 1];
	char		*endline;
	char		*tmp;

	if ((ret = ft_gnl_start(fd, line, &endline, &reste)) != 2)
		return (ret);
	while (!endline)
	{
		ret = read(fd, buff, BUFF_SIZE);
		if (ret == -1)
			return (ret);
		if (ret == 0)
		{
			if ((*line)[0])
				return (1);
			return (0);
		}
		buff[ret] = '\0';
		if (!(endline = ft_strchr(buff, '\n')))
		{
			if (!(*line = ft_f_strjoin(*line, buff)))
				return (-1);
		}
		else
		{
			if (!((*line = ft_f_strjoin(*line,
				(tmp = ft_strsub(buff, 0, endline - buff)))) &&
				(reste = ft_strsub(buff, endline - buff + 1, ft_strlen(buff)))))
				return (-1);
			free(tmp);
		}
	}
	return (1);
}
/*
int main ()
{
	char *line;
	int i;
	int fd = open("gnl7_3.txt", O_RDONLY);
	i = 0;
//	ft_putnbr(get_next_line(1, &line));
	while (get_next_line(fd, &line))
	{
		printf("%s      %p\n", line, line);
		free(line);
	}
	while (1);
	return (1);
}*/
