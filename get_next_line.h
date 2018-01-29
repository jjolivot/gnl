/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 18:06:42 by jjolivot          #+#    #+#             */
/*   Updated: 2018/01/29 22:29:36 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
 #define GET_NEXT_LINE_H
 #define BUFF_SIZE 32

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"

typedef struct	var
{
	char		buff[BUFF_SIZE + 1];
	int			ret;
	int			i;
	char		*tmp;
}				var;

int		get_next_line(const int fd, char **line);

#endif
