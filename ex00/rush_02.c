/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush_02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:43:12 by vtian             #+#    #+#             */
/*   Updated: 2025/04/05 20:02:49 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "rush_02.h"

// NOTES
// allowed func: write, read, close (unistd), malloc, free (stdlib), open (fcntl)
// A program that takes a number as an argument and converts it to its written
// letter value.
// Malloc must be freed
// • Example:
// $> ./rus	open()
// h-02 42 | cat -e
// forty two$
// $> ./rush-02 0 | cat -e
// zero$
// $> ./rush-02 10.4 | cat -e
// Error$
// $> ./rush-02 100000 | cat -e
// one hundred thousand$
// $> grep "20" numbers.dict | cat -e
// 20 : hey everybody ! $
// $> ./rush-02 20 | cat -e
// hey everybody !$
// 5

// If the argument representing the number is not a valid and positive integer,
// program must output "Error" followed by a newline.
int	ft_validate_number(long	nb)
{
	if (nb < 0)
	{
		write(2, "Error\n", 7);
		return (-1);
	}
	return (0);
}

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
	while (read_i > 0)
	{
		read_i = read(file, buffer + line_len, 1);
		if (buffer[line_len] == '\n')
		{
			buffer[line_len] = '\0';
			*line = ft_strdup(buffer);
			return (E_SUCCESS);
		}
	}
	if (read_i < 0)
		write(2, "Unknown read error in ft_read_line\n", 36);
	*line_n = -1;
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
	int		nb;
	int		rule;
	// if EOF, return error
	if (ft_read_line(file, line_n, &line) == E_FAILURE)
		return (E_FAILURE);
	i = 0;
	nb = 0;
	rule = 0;
	while (line[i] >= '0' && line[i] <= '9')
	{
		nb = (nb * 10) + (line[i] - '0');
		rule = 1;
		i++;
	}
	if (nb != (*dict).nb)
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
		(*dict).str = ft_strdup(line);
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
		write(2, "Dict Error\n", 12);
		close(file);
		return (-1);
	}
	line_n = 0;
	validity = E_RUNNING;
	while (validity == E_RUNNING)
		validity = ft_validate_line(file, &line_n, dict);
	if (validity == E_FAILURE)
		write(2, "Dict Error\n", 12);
	return (validity);
	close (file);
}

// Your program can take 1 or 2 arguments
// Program must handle beyond unsigned int
// Must parse numbers.dict, the values in it can be modified freely
int	main(int argc, char **argv)
{
	char	*filename;
	t_dict	dict;
	const char	*filename_default = "numbers.dict";

	if (argc == 2)
	{
		dict.nb = ft_atoi(argv[1]);
		filename = (char *)filename_default;
	}
	else if (argc == 3)
	{
		dict.nb = ft_atoi(argv[2]);
		filename = argv[1];
	}
	else
		return (1);
	if (ft_validate_number(dict.nb) == E_FAILURE || ft_validate_dict(filename, &dict) == E_FAILURE)
		return (1);
	ft_putstr((dict.str));
}