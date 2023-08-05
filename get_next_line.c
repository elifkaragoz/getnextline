/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaragoz <ekaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 22:35:22 by elif              #+#    #+#             */
/*   Updated: 2023/07/29 17:25:05 by ekaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_remain_str(char *str, int nl_index, int i)
{
	char	*remain_str;

	if (nl_index == -1)
	{
		free(str);
		return (NULL);
	}
	nl_index++;
	remain_str = malloc(ft_strlen(str) - nl_index + 1);
	if (!remain_str)
		return (NULL);
	while (str[nl_index + i])
	{
		remain_str[i] = str[nl_index + i];
		i++;
	}
	remain_str[i] = '\0';
	free(str);
	return (remain_str);
}

char	*get_fline(char *str)
{
	char	*line;
	int		i;

	if (!str || str[0] == '\0')
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*str_join(char *str, char *buffer, int i, int j)
{
	char	*join_str;

	if (str == NULL)
	{
		str = malloc(sizeof(char) * 1);
		str[0] = '\0';
	}
	if (buffer == NULL)
		return (NULL);
	join_str = malloc(ft_strlen(str) + ft_strlen(buffer) + 1);
	if (!join_str)
		return (NULL);
	while (str[i])
	{
		join_str[i] = str[i];
		i++;
	}
	while (buffer[j])
		join_str[i++] = buffer[j++];
	join_str[i] = '\0';
	free(str);
	return (join_str);
}

char	*gnl_helper(char **str)
{
	int		nl_index;
	char	*line;

	nl_index = find_newline_index(*str);
	line = get_fline(*str);
	*str = get_remain_str(*str, nl_index, 0);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*buffer;
	int			read_counter;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_counter = read(fd, buffer, BUFFER_SIZE);
	if (read_counter == -1)
	{
		free(str);
		str = NULL;
		free(buffer);
		return (NULL);
	}
	buffer[read_counter] = '\0';
	str = str_join(str, buffer, 0, 0);
	free(buffer);
	if (find_newline_index(str) != -1 || read_counter == 0)
		return (gnl_helper(&str));
	else
		return (get_next_line(fd));
}
