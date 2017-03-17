/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:05:18 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/15 10:37:27 by sclolus          ###   ########.fr       */
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

int32_t		ft_is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z'));
}

t_parser	*ft_get_parser_literal(void)
{
	t_parser	*parser;

	parser = ft_get_parser_or_n(2, (t_parser *[]){
				ft_get_parser_and_n(3, (t_parser *[]){ft_get_parser_onechar('\"')
							, ft_get_parser_str_any(), ft_get_parser_onechar('\"')})
					, ft_get_parser_and_n(3, (t_parser *[]){ft_get_parser_onechar('\'')
								, ft_get_parser_any(), ft_get_parser_onechar('\'')})});
	if (!(parser->name = ft_strdup("<parser_literal>")))
		exit(EXIT_FAILURE);
	return (parser);
}

t_parser	*ft_get_parser_rule_name(void)
{
	t_parser	*parser;

	parser = ft_get_parser_and_n(3, (t_parser *[]){ft_get_parser_onechar('<')
					, ft_get_parser_str_any()
					, ft_get_parser_onechar('>')});
	if (!(parser->name = ft_strdup("<rule_name>")))
		exit(EXIT_FAILURE);
	return (parser);
}

// list optimisable
t_parser	*ft_get_parser_list(t_parser *term, t_parser *whitespace)
{
	t_parser	*parser;

	parser = ft_get_parser_or_n(2, (t_parser *[]){term,
					ft_get_parser_multiply(
						ft_get_parser_and_n(2, (t_parser *[]){term, whitespace}))});
	if (!(parser->name = ft_strdup("<list>")))
		exit(EXIT_FAILURE);
	return (parser);
}

t_parser	*ft_get_parser_expression(t_parser *list, t_parser *whitespace)
{
	t_parser	*parser;

	parser = ft_get_parser_or_n(2, (t_parser *[]){list
					, ft_get_parser_multiply(ft_get_parser_and_n(4, (t_parser *[]){list, whitespace
									, ft_get_parser_onechar('|'), whitespace}))});
	if (!(parser->name = ft_strdup("<expression>")))
		exit(EXIT_FAILURE);
	return (parser);
}

t_parser	*ft_get_parser_line_end(t_parser *whitespace)
{
	t_parser	*eol;

	eol = ft_get_parser_and_n(2, (t_parser *[]){whitespace, ft_get_parser_onechar('\n')});
	if (!(eol->name = ft_strdup("<eol>")))
		exit(EXIT_FAILURE);
	return (ft_get_parser_plus(eol));
}

t_parser	*ft_get_parser_rule(t_parser *expression, t_parser *rule_name
								, t_parser *whitespace, t_parser *eol)
{
	t_parser	*parser;

	parser = ft_get_parser_and_n(7, (t_parser*[]){whitespace, rule_name
					, whitespace, ft_get_parser_str("::=")
					, whitespace, expression, eol}); 
	if (!(parser->name = ft_strdup("<rule>")))
		exit(EXIT_FAILURE);
	return (parser);
}

t_parser	*ft_get_parser_syntax(t_parser *rule)
{
	t_parser	*parser;

	parser = ft_get_parser_plus(rule);
	if (!(parser->name = ft_strdup("<syntax>")))
		exit(EXIT_FAILURE);
	return (parser);
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

	letter = ft_get_parser_satisfy(ft_is_alpha);
	ft_set_name_parser(letter, "letter");
	symbol = ft_get_parser_satisfy(ft_is_metachar);
	ft_set_name_parser(symbol, "symbol");
	character = ft_get_parser_or_n(2, (t_parser *[]){letter, symbol});
	ft_set_name_parser(character, "character");
	whitespace = ft_get_parser_multiply(ft_get_parser_onechar(' '));
	ft_set_name_parser(whitespace, "whitespace");
	literal = ft_get_parser_literal();
	ft_set_name_parser(literal, "literal");
	rule_name = ft_get_parser_rule_name();
	term = ft_get_parser_or_n(2, (t_parser *[]){literal, rule_name});
	list = ft_get_parser_list(term, whitespace);
	expression = ft_get_parser_expression(list, whitespace);
	eol = ft_get_parser_line_end(whitespace);
	rule = ft_get_parser_rule(expression, rule_name, whitespace, eol);
	syntax = ft_get_parser_syntax(rule);
//	ft_put_parser(syntax);
	return (syntax);
}

t_parser	*ft_get_undefined_parser(void)
{
	t_parser	*parser;

	if (!(parser = (t_parser*)malloc(sizeof(t_parser))))
		exit (EXIT_FAILURE);
	parser->id = UNDEFINED;
	parser->retained = UNRETAINED;
	parser->name = NULL;
	return (parser);
}

t_parser	*ft_get_parser_str_any(void)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->parser.str_any.len = 0;
	parser->parser.str_any.str = NULL;
	parser->id = STR_ANY;
	return (parser);
}

t_parser	*ft_get_parser_multiply(t_parser *parser)
{
	t_parser	*new;

	new = ft_get_undefined_parser();
	new->parser.multiply.parser = parser;
	new->id = MULTIPLY;
	return (new);
}

t_parser	*ft_get_parser_plus(t_parser *parser)
{
	t_parser	*new;

	new = ft_get_undefined_parser();
	new->parser.plus.parser = parser;
	new->id = PLUS;
	return (new);
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
	parser->parser.string.len = ft_strlen(str);
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
	uint32_t	i;

	i = 0;
	parser = ft_get_undefined_parser();
	if (!(parser->parser.and.parsers = (t_parser**)malloc(sizeof(t_parser*) * n)))
		exit (EXIT_FAILURE);
	parser->parser.and.n = n;
	while (i < n)
	{
		parser->parser.and.parsers[i] = parsers[i];
		i++;
	}
	parser->id = AND;
	return (parser);
}

t_parser	*ft_get_parser_or_n(uint32_t n, t_parser **parsers)
{
	t_parser	*parser;
	uint32_t	i;

	i = 0;
	parser = ft_get_undefined_parser();
	if (!(parser->parser.or.parsers = (t_parser**)malloc(sizeof(t_parser*) * n)))
		exit (EXIT_FAILURE);
	parser->parser.or.n = n;
	while (i < n)
	{
		parser->parser.or.parsers[i] = parsers[i];
		i++;
	}
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
