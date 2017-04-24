/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_tokens_chars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 10:51:51 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/24 14:27:00 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

uint32_t		ft_eval_tokens_oneof(t_parser *parser, t_tokens *tokens)
{
	if (tokens->lens[index] == 1
		&& ft_strchr(parser->parser.oneof.charset, tokens->tokens[index][0]))
	{
		parser->parser.oneof.c = tokens->tokens[index][0];
		tokens->index++;
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_tokens_onechar(t_parser *parser, t_tokens *tokens)
{
	if (tokens->lens[index] == 1
		&& parser->parser.onechar.c == tokens->tokens[index][0])
	{
		tokens->index++;
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_tokens_any(t_parser *parser, t_tokens *tokens)
{
	if (tokens->lens[index] == 1)
	{
		parser->parser.any.matched = tokens->tokens[index][0];
		tokens->index++;
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_tokens_char_range(t_parser *parser, t_tokens *tokens)
{
	if (tokens->lens[index] == 1
		&& tokens->tokens[index][0] <= parser->parser.range.end
		&& tokens->tokens[index][0] >= parser->parser.range.start)
	{
		parser->parser.range.matched = tokens->tokens[index][0];
		tokens->index++;
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_tokens_satisfy(t_parser *parser, t_tokens *tokens)
{
	if (tokens->lens[index] == 1
		&& parser->parser.satisfy.f(tokens->tokens[index][0]))
	{
		parser->parser.satisfy.c = tokens->tokens[index][0];
		tokens->index++;
		return (1);
	}
	else
		return (0);
}
