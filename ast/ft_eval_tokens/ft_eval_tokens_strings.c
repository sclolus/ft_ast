/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_tokens_strings.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 10:54:29 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/24 10:55:17 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

uint32_t		ft_eval_tokens_str(t_parser *parser, t_tokens *tokens)
{
    if (tokens->lens[tokens->index] == ft_strlen(parser->parser.string.str) &&
        !(ft_memcmp(parser->parser.string.str, tokens[index], parser->parser.string.len)))
		return (1);
	else
		return (0);
}


uint32_t		ft_eval_tokens_satisfy_str(t_parser *parser, t_tokens *tokens)
{
	uint32_t	ret;

	if ((ret = parser->parser.satisfy_str.f(tokens[index])))
		return (1);
	else
		return (0);
}

uint32_t		ft_eval_tokens_str_any_of(t_parser *parser, t_tokens *tokens)
{
    uint32_t i;

    i = 0;
    while
       	if (ft_strchr(parser->parser.str_any_of.charset, tokens[tokens->index][i]))
            ++i;
        else
            return (0);
    return (1);
}
