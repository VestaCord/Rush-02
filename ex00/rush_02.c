/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush_02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:43:12 by vtian             #+#    #+#             */
/*   Updated: 2025/04/06 23:01:00 by vtian            ###   ########.fr       */
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

// shortcut dict search and print for 3 digit only
int	ft_put_short(char *filename, int nb)
{
	int		status;
	t_dict	tmp;

	tmp.nb = ft_itoa(nb);
	status = ft_validate_dict(filename, &tmp);
	ft_putstr(1, tmp.str);
	free(tmp.nb);
	free(tmp.str);
	return (status);
}

// shd implement error checking for putshort.
int ft_print_triple(char *filename, char *str)
{
	int		tmp;
	int		hundreds;
	int		tens;
	int		ones;

	tmp = ft_atoi(str);
	if (tmp > 999)
	{
		ft_putstr(2, "invalid triple\n");
		return (E_FAILURE);
	}
	if (tmp > 99)
	{
		hundreds = tmp / 100;
		tens = (tmp % 100) / 10; //  store tens digit
	}
	else
		tens = tmp / 10;
	ones = (tmp % 10); // store ones digit
	tmp %= 100; // store ten and one 
	if (hundreds)
	{
		ft_put_short(filename, hundreds);
		ft_putstr(1, " ");
		ft_put_short(filename, 100);
	}
	if (tens)
	{
		if (hundreds)
			ft_putstr(1, " and ");
		if (tmp < 20 || ones == 0) // 11 12 13 14 .. 19 20 30 .. 90
			ft_put_short(filename, tmp);
		else
		{
			ft_put_short(filename, (tens * 10)); // 21 22 .. 29 31 .. 91 91 .. 98 99
			ft_putstr(1, "-");
			ft_put_short(filename, ones);
		}
	}
	return (E_SUCCESS);
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
	t_dict dict;
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
	// if (ft_validate_number(nb_temp) == E_FAILURE || ft_validate_dict(filename, &dict) == E_FAILURE)
	if (ft_validate_number(nb_temp) == E_FAILURE)
		return (1);
	ft_print_triple(filename, dict.nb);
	// ft_putstr(1, (dict.str));
	ft_putstr(1, "\n");
}