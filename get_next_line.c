/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:43:01 by mstawski          #+#    #+#             */
/*   Updated: 2025/03/20 22:11:41 by agiedroi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *stash)
{
	char	*line;
	char	*new_position;

	new_position = ft_strchr(stash, '\n');
	if (new_position)
		line = ft_substr(stash, 0, (new_position - stash + 1));
	else
		line = ft_strdup(stash);
	return (line);
}

char	*stash_update(char *stash)
{
	char	*new_addr;
	char	*tmp;

	new_addr = ft_strchr(stash, '\n');
	if (new_addr)
	{
		tmp = ft_strdup(new_addr + 1);
		free(stash);
		new_addr = tmp;
	}
	else
	{
		free(stash);
		stash = NULL;
		return (stash);
	}
	return (new_addr);
}

char	*read_file(int fd, char *stash, char *buffer)
{
	char	*tmp;
	int		r_bytes;

	while (1)
	{
		r_bytes = read(fd, buffer, BUFFER_SIZE);
		if (r_bytes <= 0)
			break ;
		buffer[r_bytes] = '\0';
		if (!stash)
			stash = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(stash, buffer);
			free(stash);
			stash = tmp;
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	stash = read_file(fd, stash, buffer);
	line = extract_line(stash);
	stash = stash_update(stash);
	return (line);
}
