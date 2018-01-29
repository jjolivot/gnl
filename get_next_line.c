/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 18:54:48 by jjolivot          #+#    #+#             */
/*   Updated: 2018/01/29 22:34:07 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		ft_get_reste(char **reste, char **line)
{
	char		*endline;

	if ((endline = ft_strchr(*reste, '\n')))
	{
		if (!((*line = ft_strsub(*reste, 0, endline - *reste)) &&
		(*reste = ft_strsub(*reste, endline - *reste + 1, ft_strlen(*reste)))))
			return (-1);
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

int		get_next_line(const int fd, char **line)
{
	static char	*reste;
	int			ret;
	char		buff[BUFF_SIZE + 1];
	char		*endline;

	endline = NULL;
	if (reste)
	{
		if ((ret = ft_get_reste(&reste, &(*line))) == -1)
			return (-1);
		if (ret == 1)
			return (1);
	}

	while(!endline)
	{
		ret = read(fd, buff, BUFF_SIZE);
		if (ret == 0 || ret == -1)
			return(ret);
		buff[ret] = '\0';
		if (!(endline = ft_strchr(buff, '\n')))
		{
			if(!(*line = ft_strjoin(*line, buff)))
				return (-1);
		}
		else
		{
			if (!((*line = ft_strjoin(*line, ft_strsub(buff, 0, endline - buff))) &&
				(reste = ft_strdup(ft_strsub(buff, endline - buff + 1, ft_strlen(buff))))))
			return (-1);
		}
	}
	return (1);
}

int main ()
{
	char *line;
	int i;
	int fd = open("test.txt", O_RDONLY);
	i = 0;
	while ((i = get_next_line(fd, &line)))
	{
		printf("%d  %s\n",i, line);
	}
	return (1);
}
/*int	get_to_line(char **line, char *buff)
{
	char	*endline;
	int		i;
	char	*tmp;
	int		j;

	i = -1;
	if ((endline = ft_strchr(buff, '\n')) || (endline == ft_strchr(buff, '\0')))
		{
		//	printf("endline = %s\n", endline);
			if (!(tmp = (char *)malloc(sizeof(char) * (endline - buff) + (j = ft_strlen(*line)) + 1)))
				return (-1);
			ft_strcpy(tmp, *line);
		//	printf("j = %d  tmp = %s\n buff = %s\n", j, tmp, buff);
			//free(*line);
			*line = tmp;
		//	printf("la ca marche\n");
			while(buff[++i] != *endline)
			{
		//		printf("i = %d  j = %d line[j + i -1] = %c buff[i] = %c\n", i, j, (*line)[j + i -1], buff[i]);
				(*line)[j + i] = buff[i];
			}
		}
	if(*endline == '\n')
		return (1);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	int			ret;
	static char	*reste;
	int			gtl;
	char		*tmp;

	gtl = 0;
	if (reste)
	{
		if ((gtl = get_to_line(&(*line), reste) == -1))
			return (-1);
		if (gtl == 1)
		{
			gtl = (ft_strchr(reste, '\n') - reste);
			tmp = ft_strsub(reste, gtl, ft_strlen(reste) - gtl);
			free(reste);
			reste = tmp;
			return(1);
		}
		if (gtl == 0)
			free(reste);
	}
	while (gtl == 0)
	{
		if ((ret = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		buff[ret] = '\0';
		if ((gtl = get_to_line(&(*line), buff)) == -1)
			return (-1);
		if (gtl == 1)
		{
			gtl = (ft_strchr(buff, '\n') - buff);
			reste = ft_strsub(buff, gtl, ft_strlen(buff) - gtl);
		}
	}
	if (!(ret == 0))
		return (1);
	return (0);
}

*/
