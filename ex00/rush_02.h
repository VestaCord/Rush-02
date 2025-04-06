/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush_02.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:21:55 by vtian             #+#    #+#             */
/*   Updated: 2025/04/06 22:12:16 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH_02_H
# define RUSH_02_H
# define BUFFER_SIZE 1024
# define E_SUCCESS 1
# define E_FAILURE -1
# define E_RUNNING 0

typedef struct s_dict
{
	char	*nb;
	char	*str;
}	t_dict;

int		ft_atoi(char *str);
double	ft_atof(char *str);
char	*ft_strdup(char *src);
void	ft_putstr(int stream, char *str);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_validate_dict(char *filename, t_dict *dict);
char* 	ft_itoa(int num);
#endif