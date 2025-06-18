/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarrodri <sarrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:18:56 by sarrodri          #+#    #+#             */
/*   Updated: 2025/06/18 17:42:59 by sarrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_buf(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

static char	*extract_line(char *store)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(*line));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = store[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*update_store(char *store)
{
	size_t	i;
	size_t	len;
	char	*new_store;

	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (!store[i])
		return (free(store), NULL);
	i++;
	len = 0;
	while (store[i + len])
		len++;
	new_store = malloc(len + 1);
	if (!new_store)
		return (free(store), NULL);
	len = 0;
	while (store[i + len])
	{
		new_store[len] = store[i + len];
		len++;
	}
	new_store[len] = '\0';
	free(store);
	return (new_store);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		read_buffer[BUFFER_SIZE + 1];
	char		*returned_line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (store = free_buf(store));
	bytes_read = 1;
	while (!(store && ft_strchr(store, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (store = free_buf(store));
		read_buffer[bytes_read] = '\0';
		store = ft_strjoin(store, read_buffer);
		if (!store)
			return (store = free_buf(store));
	}
	if (!store || !*store)
		return (store = free_buf(store));
	returned_line = extract_line(store);
	store = update_store(store);
	return (returned_line);
}
