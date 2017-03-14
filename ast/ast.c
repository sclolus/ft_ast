/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:05:18 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/14 05:44:56 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int32_t		ft_is_metachar(char c)
{
	if (ft_strchr(MPC_PARSING_METACHAR, c))
		return (1);
	else
		return (0);
}

t_parser	*ft_get_parser_literal(void)
{
	return (ft_get_parser_or_n(2, {
				ft_get_parser_and_n(3, {ft_get_parser_onechar('\"')
							, ft_get_parser_str_any(), ft_get_parser_onechar('\"')})
					, ft_get_parser_and_n(3, {ft_get_parser_onechar('\'')
								, ft_get_parser_any(), ft_get_parser_onechar('\'')})}));
}

t_parser	*ft_get_parser_rule_name(void)
{
	return (ft_get_parser_or_n(3, {ft_get_parser_onechar('<')
					, ft_get_parser_str_any()
					, ft_get_parser_onechar('>')}));
}

t_parser	*ft_get_parser_list(t_parser *term, t_parser *whitespace)
{

	return (ft_get_parser_or_n(2, {term, 
					ft_get_parser_multiply(
						ft_get_parser_and_n(2, {term, whitespace}))}));
}

t_parser	*ft_get_parser_expression(t_parser *list, t_parser *whitespace)
{
	return (ft_get_parser_or_n(2, {list
					, ft_get_parser_multiply(ft_get_parser_and_n(4, {list, whitespace
									, ft_get_parser_onechar('|'), whitespace}))}));
}

t_parser	*ft_get_parser_line_end(t_parser *whitespace)
{
	t_parser	*eol;

	eol = ft_get_parser_and_n(2, {whitespace, ft_get_parser_onechar('\n')});
	return (ft_get_parser_plus(eol));
}

t_parser	*ft_get_parser_rule(t_parser *expression, t_parser *rule_name
								, t_parser *whitespace, t_parser *eol)
{
	return (ft_parser_and_n(7, {whitespace, rule_name
					, whitespace, ft_get_parser_str("::=")
					, whitespace, expression, eol}));
}

t_parser	*ft_get_parser_syntax(t_parser *rule)
{
	return (ft_get_parser_plus(rule));
}

t_parser	*ft_get_parser_grammar(void)
{
	t_parser	*symbol;
	t_parser	*letter;
	t_parser	*character;
	t_parser	*whitespace;
	t_parser	*literal;
	t_parser	*term;
	t_parser	*rule_name;
	t_parser	*list;
	t_parser	*expression;
	t_parser	*eol;
	t_parser	*rule;
	t_parser	*syntax;

	letter = ft_get_parser_satisfy(&ft_isalpha);
	symbol = ft_get_parser_satisfy(&ft_is_metachar);
	character = ft_get_parser_or_n(2, {&letter, &symbol});
	whitespace = ft_get_parser_multiply(ft_get_parser_onechar(' '));
	literal = ft_get_parser_literal();
	rule_name = ft_get_parser_rule_name();
	term = ft_get_parser_or_n(2, {literal, rule_name});
	list = ft_get_parser_list(term, whitespace);
	expression = ft_get_parser_expression(list, whitespace);
	eol = ft_get_parser_line_end(whitespace);
	rule = ft_get_parser_rule(expression, rule_name, whitespace, eol);
	syntax = ft_get_parser_syntax(rule);
	return (syntax);
}

t_parser	*ft_get_undefined_parser(void)
{
	t_parser	*parser;

	if (!(parser = (t_parser*)malloc(sizeof(t_parser))))
		exit (EXIT_FAILURE);
	parser->id = UNDEFINED;
	parser->retained = UNRETAINED;
	return (parser);
}
					
					t_parser	*ft_get_parser_str_any(void)
					{
						t_parser	*parser;
						
						parser = ft_get_undefined_parser();
						parser->id = STR_ANY;
						return (parser);	
					}

t_parser	*ft_get_multiply_parser(t_parser *parser)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->parser.multiply.parser = parser;
	parser->id = MULTIPLY;
	return (parser);
}

t_parser	*ft_get_plus_parser(t_parser *parser)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->parser.plus.parser = parser;
	parser->id = PLUS;
	return (parser);
}

t_parser	*ft_get_parser_onechar(char c)
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
	parser->parser.satisfy.c = c;
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
