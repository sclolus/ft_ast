/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_grammar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 04:43:56 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/18 05:58:13 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_parser	*ft_get_grammar_literal(t_parser *literal)
{
	t_parser	*parser;
	t_parser	*tmp;

	// dup str_any.str
	if (literal->parser.or.parsers[0]->retained)
	{
		tmp = literal->parser.or.parsers[0]->parser.and.parsers[1];
		parser = ft_get_parser_str(tmp->parser.str_any.str);
	}
	else if (literal->parser.or.parsers[1]->retained)
	{
		tmp = literal->parser.or.parsers[1]->parser.and.parsers[1];
		parser = ft_get_parser_onechar(tmp->parser.any.matched);
	}
	else
	{
		ft_putstr_fd("Error\n", 2);
		return (NULL);
	}
	return (parser);
}
/*
t_parser	*ft_get_grammar_rule_name(t_parser *rule_name)
{
	t_parser	*parser;
	t_parser	*tmp;

	// dup str_any.str
	if (literal->parser.or.parsers[0]->retained)
	{
		tmp = literal->parser.or.parsers[0]->parser.and.parsers[1];
		parser = ft_get_parser_str(tmp->parser.str_any.str);
	}
	else if (literal->parser.or.parsers[1]->retained)
	{
		tmp = literal->parser.or.parsers[1]->parser.and.parsers[1];
		parser = ft_get_parser_onechar(tmp->parser.any.matched);
	}
	else
	{
		ft_putstr_fd("Error\n", 2);
		return (NULL);
	}
	return (parser);
}
*/

t_parser	*ft_get_grammar_term(t_parser *term)
{
	t_parser	*parser;

	if (term->parser.or.parsers[0]->retained)
		parser = ft_get_grammar_literal(term->parser.or.parsers[0]);
	else if (term->parser.or.parsers[1]->retained)
	{
//		parser = ft_get_grammar_rule_name(term->parser.or.parsers[1]);
		ft_putstr_fd("rule_name not implemented", 2);
	}
	else
		ft_putstr_fd("Error\n", 2);
}

t_parser	*ft_get_grammar_list(t_parser *list)
{
	t_parser	*parser;
	t_parser	**parsers;
	uint32_t	i;

	i = 0;
	if (!(parsers = (t_parser**)malloc(sizeof(t_parser*) 
									   * list->parser.plus.n)))
		exit(EXIT_FAILURE);
	while (i < list->parser.plus.n)
	{
		parsers[i] = list->parser.plus.parsers[i]->parser.and.parsers[0];
		i++;
	}
	parser = ft_get_parser_and_n(list->parser.plus.n, parsers);
	free(parsers);
	return (parser);
}

t_parser	*ft_get_grammar_expression(t_parser *expression)
{
	t_parser	*parser;
	t_parser	**parsers;
	uint32_t	total;
	uint32_t	i;

	i = 0;
	if (expression->parser.and.parsers[1]->parser.multiply.n)
	{
		total = expression->parser.and.parsers[1]->parser.multiply.n + 1;
		if (!(parsers = (t_parser**)malloc(total))))
			exit(EXIT_FAILURE);
		parsers[0] = expression->parser.and.parsers[0];
		while (i < total - 1)
		{
			parsers[i + 1] = expression->parser.and.parsers[1]->parser.multiply.parsers[i];
			i++;
		}
		parser = ft_get_parser_or_n(total, parsers);
		free(parsers);
		return (parser);
	}
	else
		return (ft_get_grammar_list(expression->parser.and.parsers[0]));
}

t_parser	*ft_get_grammar_rule(t_parser *rule)
{
	t_parser	*parser;

	parser = ft_get_grammar_expression(rule->parser.and.parsers[5]);
	parser->name = ft_strndup(rule->parser.and.parsers[1]->parser.and.parsers[1]->parser.str_any.str
							  , rule->parser.and.parsers[1]->parser.and.parsers[1]->parser.str_any.len);
	return (parser);
}

t_parser	*ft_get_grammar_syntax(t_parser *syntax)
{
	t_parser	*parser;
	t_parser	**parsers;
	uint32_t	i;

	i = 0;
	if (!(parsers = (t_parser**)malloc(syntax->parser.plus.n)))
		exit(EXIT_FAILURE);
	while (i < syntax->parser.plus.n)
	{
		parsers[i] = syntax->parser.plus.parsers[i];
		i++;
	}
	parser = ft_get_parser_plus(ft_get_parser_or_n(syntax->parser.plus.n, parsers));
	free(parsers);
	return (parser);
}
