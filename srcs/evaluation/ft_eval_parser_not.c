/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_parser_not.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:37:44 by aalves            #+#    #+#             */
/*   Updated: 2019/03/06 20:40:35 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static inline t_mpc_not	*get_p_not(t_parser *parser)
{
#if ASSERT
	assert(parser->id == NOT);
#endif
	return (&parser->parser.not);
}

bool	ft_eval_parser_not(t_parser *parser, char **string)
{
    t_mpc_not	*inner;

	inner = get_p_not(parser);
	return (!ft_eval_parser(inner->parser, string));
}
