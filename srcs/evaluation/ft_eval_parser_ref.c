/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_parser_ref.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:52:14 by aalves            #+#    #+#             */
/*   Updated: 2019/03/06 21:02:34 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static inline t_mpc_ref	*get_p_ref(t_parser *parser)
{
#if ASSERT
	assert(parser->id == REF);
#endif
	return (&parser->parser.ref);
}

bool	ft_eval_parser_ref(t_parser *parser, char **string)
{
	t_mpc_ref	*inner;

	inner = get_p_ref(parser);
	return (ft_eval_parser(inner->ref, string));
}
