/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush_02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:43:12 by vtian             #+#    #+#             */
/*   Updated: 2025/04/06 16:45:28 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "rush_02.h"
#include <stdio.h>

// NOTES
// allowed func: write, read, close (unistd), malloc, free (stdlib), open (fcntl)
// A program that takes a number as an argument and converts it to its written
// letter value.
// Malloc must be freed

// If the argument representing the number is not a valid and positive integer,
// program must output "Error" followed by a newline.
int	ft_validate_number(double nb_temp)
{
	long	nb_int_temp;

	nb_int_temp = (long)nb_temp;
	if (nb_temp < 0 || (nb_temp - nb_int_temp) != 0.0)
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
		printf("File failed to open\n");
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

// Your program can take 1 or 2 arguments
// Program must handle beyond unsigned int
// Must parse numbers.dict, the values in it can be modified freely
// CURRENTLY THESE CASES ARE FAILING BC THEY HAVENT BEEN IMPLEMETNED:
// ./rush-02 10.4 SHOULD OUTPUT "Error\n" NOT "ten"
// to do this, just use atof instead of atoi (need to make it urself),
// then check if the float has non zero dp before casting to long
// remove all printf obviously
// now all u need to do is to write code to combine keys
// ie 10 and 1000 become ten thousand
// how i wld do this is, if nb is >= 1000, find log1000(nb)
// then u get the xxillion.
// then u find xxillion n - 1
// then u find hundreds
// then u find tens (iterate thru twenty to ninety
// then u do the ones :)
int	main(int argc, char **argv)
{
	char	*filename;
	double	nb_temp;
	t_dict	dict;
	const char	*filename_default = "numbers.dict";

	if (argc == 2)
	{
		nb_temp = ft_atof(argv[1]);
		dict.nb = argv[1];
		filename = (char *)filename_default;
	}
	else if (argc == 3)
	{
		nb_temp = ft_atof(argv[2]);
		dict.nb = argv[2];
		filename = argv[1];
	}
	else
		return (1);
	if (ft_validate_number(nb_temp) == E_FAILURE || ft_validate_dict(filename, &dict) == E_FAILURE)
		return (1);
	ft_putstr(1, (dict.str));
	ft_putstr(1, "\n");
}