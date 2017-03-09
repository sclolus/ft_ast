/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:05:18 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/09 15:11:05 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_parser	*ft_get_undefined_parser(void)
{
	t_parser	*parser;

	if (!(parser = (t_parser*)malloc(sizeof(t_parser))))
		exit (EXIT_FAILURE);
	parser->id = UNDEFINED;
	parser->retained = UNRETAINED;
	return (parser);
}

t_parser	*ft_set_parser_onechar(char c)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->parser.onechar.c = c;
	parser->id = ONECHAR;
	return (parser);
}

t_parser	*ft_get_parser_str(char *str)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	if (!(parser->parser.string.str = ft_strdup(str)))
		exit(EXIT_FAILURE);
	parser->id = STRING;
	return (parser);
}

t_parser	*ft_get_parser_range(char start, char end)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->id = RANGE;
	parser->parser.range.start = start;
	parser->parser.range.end = end;
	return (parser);
}

t_parser	*ft_get_parser_and_n(uint32_t n, t_parser **parsers)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->parser.and.n = n;
	parser->parser.and.parsers = parsers;
	parser->id = AND;
	return (parser);
}

t_parser	*ft_get_parser_or_n(uint32_t n, t_parser **parsers)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->parser.and.n = n;
	parser->parser.and.parsers = parsers;
	parser->id = OR;
	return (parser);
}

t_parser	*ft_get_parser_any(void)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->id = ANY;
	return (parser);
}

t_parser	*ft_get_parser_satisfy(int32_t (*f)(char))
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->id = SATISFY;
	parser->parser.satisfy.f = f;
	return (parser);
}

t_parser	*ft_get_parser_satisfy_str(int32_t (*f)(char*))
{
		t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->id = SATISFY_STR;
	parser->parser.satisfy_str.f = f;
	return (parser);
}

t_parser	*ft_get_parser_not(t_parser *parser)
{
	t_parser	*new_parser;

	new_parser = ft_get_undefined_parser();
	new_parser->id = NOT;
	new_parser->parser.not.parser = parser;
	return (parser);
}
