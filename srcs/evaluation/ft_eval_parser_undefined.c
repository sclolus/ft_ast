/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_parser_undefined.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 21:03:34 by aalves            #+#    #+#             */
/*   Updated: 2019/03/06 21:33:03 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

bool	ft_eval_parser_undefined(t_parser *parser, char **string)
{
	(void)parser;
	(void)string;
	ft_putstr_fd("Tried to eval undefined parser\n", STDERR_FILENO);
#if ASSERT
	assert(false);
#endif
    return (false); //Maybe call exit in non assert mode ?
}
