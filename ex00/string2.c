/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 22:02:59 by vtian             #+#    #+#             */
/*   Updated: 2025/04/06 22:30:32 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
char* ft_itoa(int num) {
    int 	i;
	int		tmp;
	int		size;
	char 	*str;

    if (num == 0) {
		str = malloc(sizeof(char) * 2);
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
	size = 0;
	tmp = num;
	while (tmp > 0)
	{
		tmp /= 10;
		size += 1;
	}
	str = malloc(sizeof(char) * (size + 1));
	i = 1;
    while (num > 0) {
        str[size - i++] = (num % 10) + '0';
        num /= 10;
    }
    str[size] = '\0';
    return str;
}