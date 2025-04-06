/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dict.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 21:27:57 by vtian             #+#    #+#             */
/*   Updated: 2025/04/06 22:31:48 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_02.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// returns ptr to line by allocating mem, moves seekptr to next line
// sets line to -1 if EOF
// read() returns 0 on reaching file end, and <0 if unknown error.
// Skips empty lines in the dictionary.
int	ft_read_line(int file, int *line_n, char **line)
{
	int		line_len;
	int		read_i;
	char	buffer[BUFFER_SIZE];

	line_len = 0;
	read_i = 1;
	while (read_i > 0)
	{
		read_i = read(file, buffer + line_len, 1);
		if (buffer[line_len] == '\n')
		{
			buffer[line_len] = '\0';
			*line = ft_strdup(buffer);
			*line_n += 1;
			return (E_SUCCESS);
		}
		line_len++;
	}
	if (read_i < 0)
	{
		ft_putstr(2, "Unknown read error in ft_read_line\n");
		*line_n = -1;
	}
	return (E_FAILURE);
}

// DICTIONARY RULES
// ◦ The dictionary will always have at least the keys contained in the reference
// dictionary. Their values can be modified, more entries can be added, but the
// initial keys can’t be remove// 
// also checks if every step of the rule is obeyed:
// checks for number, then colon, then printable
// [a number][0 to n spaces]:[0 to n spaces][any printable characters]\n
// Returns -1 if invalid, 0 nb not in valid line, 1 if found 
int	ft_validate_line(int file, int *line_n, t_dict *dict)
{
	int		i;
	char	*line;
	int		dec_places;
	int		rule;
	// if EOF, return error
	if (ft_read_line(file, line_n, &line) == E_FAILURE)
		return (E_FAILURE);
	i = 0;
	dec_places = 0;
	rule = 0;
	while ((line[i] >= '0' && line[i] <= '9') || ((*dict).nb[i] >= '0' && (*dict).nb[i] <= '9'))
	{
		dec_places++;
		rule = 1;
		i++;
	}
	if (ft_strncmp((*dict).nb, line, dec_places) != 0)
	{
		free(line);
		return (E_RUNNING);
	}
	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		i++;
	if (line[i] == ':' && rule++ == 1) // check dict line for colon, else fails
		i++;
	else
	{
		free(line);
		return (E_FAILURE);
	}
	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		i++;
	if (line[i])
		(*dict).str = ft_strdup(line + i);
	free(line);
	return(E_SUCCESS);
}

// Outputs "Dict Error\n" if invalid dictionary syntax or no conversion
// for provided number. Returns -1 if error and 1 if string found
// essentially propagates ft_validate_line
// basically, it crawls the dict line by line, until it finds a valid match
// according to dictionary rule:
// [a number][0 to n spaces]:[0 to n spaces][any printable characters]\n
int	ft_validate_dict(char *filename, t_dict *dict)
{
	int	file;
	int	line_n;
	int	validity;

	file = open(filename, 0);
	if (file < 0)
	{
		// printf("File failed to open\n");
		write(2, "Dict Error\n", 12);
		close(file);
		return (-1);
	}
	line_n = 0;
	validity = E_RUNNING;
	while (validity == E_RUNNING)
	{
		// printf("Checking line %d for key %ld\n", line_n, (*dict).nb);
		validity = ft_validate_line(file, &line_n, dict);
	}
	if (validity == E_FAILURE)
		write(2, "Dict Error\n", 12);
	return (validity);
	close (file);
}