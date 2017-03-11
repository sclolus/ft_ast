/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 05:09:17 by aalves            #+#    #+#             */
/*   Updated: 2017/03/08 06:13:20 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_error(char *msg, char *file, const char *func)
{
	ft_putstr("error : ");
	ft_putstr(msg);
	ft_putstr("\nfunction ");
	ft_putstr(func);
	ft_putstr(" in ");
	ft_putendl(file);
	exit(EXIT_FAILURE);
}
