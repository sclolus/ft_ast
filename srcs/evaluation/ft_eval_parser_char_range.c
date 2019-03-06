/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_parser_char_range.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:19:21 by aalves            #+#    #+#             */
/*   Updated: 2019/03/06 20:23:03 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static t_mpc_char_range	*get_p_char_range(t_parser *parser)
{
#if ASSERT
	assert(parser->id == RANGE);
#endif
	return (&parser->parser.range);
}

bool		ft_eval_parser_char_range(t_parser *parser, char **string)
{
	t_mpc_char_range	*inner;

	inner = get_p_char_range(parser);
	if (**string >= inner->start && **string <= inner->end)
	{
		(*string)++;
		return (true);
	}
	return (false);
}
