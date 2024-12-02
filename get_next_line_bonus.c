/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 08:54:04 by etorun            #+#    #+#             */
/*   Updated: 2024/12/02 09:00:44 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	char	*src;

	src = (char *)s;
	if (!src)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		str = (char *)malloc(sizeof(char));
		if (!str)
			return (NULL);
		*str = '\0';
	}
	else
	{
		if ((ft_strlen(s) - start) < len)
			len = ft_strlen(s) - start;
		str = (char *)malloc((sizeof(char) * len) + 1);
		if (!str)
			return (NULL);
		ft_strlcpy(str, (char *)(s + start), len + 1);
	}
	return (str);
}

char	*read_line(int fd, char *forever)
{
	char	*buf;
	int		rd;
	char	*temp;

	rd = 1;
	buf = malloc(BUFFER_SIZE + 1);
	ft_memset(buf, '\0', BUFFER_SIZE + 1);
	while (!(ft_strchr(buf, '\n')) && rd != 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == 0 && forever == NULL)
			return (free(buf), NULL);
		if (rd < 0)
			return (free(buf), free(forever), NULL);
		buf[rd] = '\0';
		if (!forever)
		{
			forever = malloc(1);
			forever[0] = '\0';
		}
		temp = forever;
		forever = ft_strjoin(forever, buf);
		free(temp);
	}
	return (free(buf), forever);
}

char	*keep_remain(char *forever)
{
	int		i;
	char	*temp;

	i = 0;
	while (forever[i] != '\0')
	{
		if (forever[i] == '\n')
		{
			temp = forever;
			forever = ft_substr(forever, i + 1, ft_strlen(forever) - i);
			free (temp);
			if (forever[0] == '\0')
				return (free (forever), NULL);
			return (forever);
		}
		i++;
	}
	return (free(forever), NULL);
}

char	*line_whr_iam(char *forever)
{
	char	*done;

	if (ft_strchr(forever, '\n'))
	{
		done = ft_substr(forever, 0, ft_strchr(forever, '\n') - forever + 1);
		return (done);
	}
	else
	{
		done = ft_substr(forever, 0, ft_strlen(forever));
		return (done);
	}
}

char	*get_next_line(int fd)
{
	static char	*forever[MAXI];
	char		*done;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	forever[fd] = read_line(fd, forever[fd]);
	if (!forever[fd])
		return (NULL);
	done = line_whr_iam(forever[fd]);
	forever[fd] = keep_remain(forever[fd]);
	return (done);
}
