/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:25:14 by dnakano           #+#    #+#             */
/*   Updated: 2020/11/02 17:49:33 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static int	gnl_errend(char **s, char **line, char *buf)
{
	free(*s);
	*s = NULL;
	free(buf);
	if (line)
	{
		free(*line);
		*line = NULL;
	}
	return (GNL_EXITERR);
}

static int	gnl_mstrcat(char **s, char *buf, ssize_t len)
{
	size_t			s_len;
	char			*s_new;

	s_len = ft_strlen(*s);
	if (!(s_new = (char *)malloc(sizeof(char) * (s_len + len + 1))))
		return (1);
	ft_strlcpy(s_new, *s, s_len + 1);
	ft_strlcat(s_new, buf, len + s_len + 1);
	free(*s);
	*s = s_new;
	return (0);
}

static int	gnl_lineend(char **s, char **line, char *buf)
{
	char	*s_new;
	size_t	len;
	size_t	s_newlen;

	len = 0;
	while (*((char *)(*s) + len) != '\n')
		len++;
	if (!(*line = (char *)malloc(sizeof(char) * (len + 1))))
		return (gnl_errend(s, NULL, buf));
	ft_strlcpy(*line, *s, len + 1);
	s_newlen = ft_strlen((char *)(*s) + len + 1);
	if (!(s_new = (char *)malloc(sizeof(char) * (s_newlen + 1))))
		return (gnl_errend(s, line, buf));
	ft_strlcpy(s_new, *s + len + 1, s_newlen + 1);
	free(*s);
	*s = s_new;
	free(buf);
	return (GNL_EXITENDL);
}

static int	gnl_fileend(char **s, char **line, char *buf)
{
	size_t		len;

	len = ft_strlen(*s);
	if (!(*line = (char *)malloc(sizeof(char) * (len + 1))))
		return (gnl_errend(s, NULL, buf));
	ft_strlcpy(*line, *s, len + 1);
	free(*s);
	*s = NULL;
	free(buf);
	return (GNL_EXITENDF);
}

int			get_next_line(int fd, char **line)
{
	ssize_t			len;
	static char		*s[N_FDMAX];
	char			*buf;

	if (fd < 0 || fd > N_FDMAX)
		return (GNL_EXITERR);
	if (!line)
		return (gnl_errend(&s[fd], NULL, NULL));
	if (!s[fd])
		if (!(s[fd] = ft_calloc(1, sizeof(char))))
			return (GNL_EXITERR);
	if (!(buf = (char *)malloc(BUFFER_SIZE)))
		return (gnl_errend(&s[fd], NULL, NULL));
	if (ft_memchr(s[fd], '\n', ft_strlen(s[fd])))
		return (gnl_lineend(&s[fd], line, buf));
	while ((len = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		if (gnl_mstrcat(&s[fd], buf, len))
			return (gnl_errend(&s[fd], NULL, buf));
		if (ft_memchr(buf, '\n', len))
			return (gnl_lineend(&s[fd], line, buf));
		if (len < BUFFER_SIZE)
			return (gnl_fileend(&s[fd], line, buf));
	}
	return (gnl_errend(&s[fd], NULL, buf));
}
