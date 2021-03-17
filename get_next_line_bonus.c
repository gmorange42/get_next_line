/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 09:08:09 by gmorange          #+#    #+#             */
/*   Updated: 2021/02/10 07:41:54 by gmorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		free_null(char **str)
{
	free((*str));
	(*str) = NULL;
	return (0);
}

char	*fillout_line(char *temp)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while ((temp[i] != '\n') && (temp[i] != '\0'))
		i++;
	if (!(line = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	line[i] = '\0';
	i = 0;
	while ((temp[i] != '\n') && (temp[i] != '\0'))
	{
		line[i] = temp[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	readgnl(ssize_t *end, int fd, char *buf, char **temp)
{
	char	*ttemp;

	if (*temp == NULL)
	{
		*end = read(fd, buf, BUFFER_SIZE);
		if (*end == -1)
			return ;
		buf[*end] = '\0';
		*temp = ft_strdup(buf);
	}
	while ((gnl_ft_strchr(*temp, '\n') == NULL) && (*end != 0))
	{
		*end = read(fd, buf, BUFFER_SIZE);
		if (*end == -1)
			return ;
		buf[*end] = '\0';
		ttemp = ft_strjoin(*temp, buf);
		free_null(temp);
		*temp = ft_strdup(ttemp);
		free_null(&ttemp);
	}
}

int		get_next_line(int fd, char **line)
{
	static char		*temp;
	char			*buf;
	ssize_t			end;
	char			*ttemp;

	buf = NULL;
	ttemp = NULL;
	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
		return (-1);
	end = 1;
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	readgnl(&end, fd, buf, &temp);
	if (end == -1)
		return (-1);
	if (!(*line = fillout_line(temp)))
		return (-1);
	free_null(&buf);
	if (end == 0)
		return (free_null(&temp));
	ttemp = ft_strdup(temp);
	free_null(&temp);
	temp = ft_strdup(gnl_ft_strchr(ttemp, '\n'));
	free_null(&ttemp);
	return (1);
}
