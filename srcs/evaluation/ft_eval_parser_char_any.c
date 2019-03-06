/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_parser_char_any.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:33:46 by aalves            #+#    #+#             */
/*   Updated: 2019/03/06 21:36:48 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static inline t_mpc_any	*get_p_any(t_parser *parser)
{
#if ASSERT
	assert(parser->id == ANY);
#endif
	return (&parser->parser.any);
}

bool	ft_eval_parser_char_any(t_parser *parser, char **string)
{
	t_mpc_any	*inner;

	if (!**string)
		return (false);
	inner = get_p_any(parser);
//parser->parser.any.matched = **string;
	(*string)++;
	return (true);
}
