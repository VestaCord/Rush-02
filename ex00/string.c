/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:21:15 by vtian             #+#    #+#             */
/*   Updated: 2025/04/06 22:48:20 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

double	ft_atof(char *str)
{
    double sum_integer = 0.0;
    double sum_fractional = 0.0;
    long fractional_power = 1;
    int i = 0;
    int sign = 1;
    int decimal_point_found = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) {
        i++;
    }

    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
    }

    while (str[i] >= '0' && str[i] <= '9') {
        sum_integer = (sum_integer * 10.0) + (str[i] - '0');
        i++;
    }

    if (str[i] == '.') {
        decimal_point_found = 1;
        i++;
        while (str[i] >= '0' && str[i] <= '9') {
            sum_fractional = (sum_fractional * 10.0) + (str[i] - '0');
            fractional_power *= 10;
            i++;
        }
    }
    if (decimal_point_found) {
        return sign * (sum_integer + (sum_fractional / fractional_power));
    } else {
        return sign * sum_integer;
    }
}

// convert a string to integer based on isspace(3)
int	ft_atoi(char *str)
{
	int	sum;
	int	i;
	int	sign;

	i = 0;
	sum = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		++i;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = (sum * 10) + (str[i] - '0');
		i++;
	}
	return (sign * sum);
}

// returns a pointer to a new string which is a duplicate of the string src
char	*ft_strdup(char *src)
{
	char	*dest;
	int		src_len;
	int		i;

	src_len = 0;
	while (src[src_len])
		src_len++;
	dest = (char *) malloc(sizeof(char) * (src_len + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// like printf("%s", str)
void	ft_putstr(int stream, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(stream, &str[i], 1);
		i++;
	}
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0')
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
