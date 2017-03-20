/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_grammar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 04:43:56 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/20 09:27:49 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_parser	*ft_get_grammar_literal(t_parser *literal)
{
	t_parser	*parser;
	t_parser	*tmp;

	// dup str_any.str
	CHECK(literal);
	if (literal->parser.or.parsers[0]->retained)
	{
		tmp = literal->parser.or.parsers[0]->parser.and.parsers[1];
		parser = ft_get_parser_str(tmp->parser.str_any.str);
		CHECK(STR);
		ft_putstr(parser->parser.string.str);
		CHECK(END);
	}
	else if (literal->parser.or.parsers[1]->retained)
	{
		tmp = literal->parser.or.parsers[1]->parser.and.parsers[1];
		parser = ft_get_parser_onechar(tmp->parser.any.matched);
		CHECK(ONECHAR);
		ft_putchar(parser->parser.onechar.c);
		CHECK(END);
	}
	else
	{
		ft_putstr_fd("Error\n", 2);
		return (NULL);
	}
	CHECK(exited literal);
	return (parser);
}

/*t_parser	*ft_get_grammar_rule_name(t_parser *rule_name)
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
	}*/


t_parser	*ft_get_grammar_term(t_parser *term)
{
	CHECK(entered term);
	if (term->parser.or.parsers[0]->retained)
		return (ft_get_grammar_literal(term->parser.or.parsers[0]));
	else
	{
		return (ft_get_parser_ref(
					term->parser.or.parsers[1]->parser.and.parsers[1]->parser.str_any.str));
//		parser = ft_get_grammar_rule_name(term->parser.or.parsers[1]);
//		ft_putstr_fd("rule_name not implemented", 2);
	}

}

t_parser	*ft_get_grammar_list(t_parser *list)
{
	t_parser	*parser;
	t_parser	**parsers;
	uint32_t	i;

	CHECK(entered list);
	i = 0;
	if (!(parsers = (t_parser**)malloc(sizeof(t_parser*) 
									   * list->parser.plus.n)))
		exit(EXIT_FAILURE);
	while (i < list->parser.plus.n)
	{
		parsers[i] = ft_get_grammar_term(list->parser.plus.parsers[i]->parser.and.parsers[0]);
		CHECK(exited term);
		i++;
	}
	parser = ft_get_parser_and_n(list->parser.plus.n, parsers);
	free(parsers);
	CHECK(exited list);
	return (parser);
}

t_parser	*ft_get_grammar_or_n(uint32_t n, t_parser *first, t_parser **parsers)
{
	t_parser	*parser;
	uint32_t	i;

	CHECK(entered grammar_or_n);
	i = 0;
	parser = ft_get_undefined_parser();
	if (!(parser->parser.or.parsers = (t_parser**)malloc(sizeof(t_parser*) * n)))
		exit (EXIT_FAILURE);
	parser->parser.or.n = n;
	parser->parser.or.parsers[0] = ft_get_grammar_list(first);
	CHECK(exited grammar list first or_n);
	while (i + 1 < n)
	{
		CHECK(entered  grammar list while or_n);
/*		ft_put_id(parsers[0]->parser.and.parsers[3]->parser.plus.parsers[0]);
		while (1)
		;*/
		parser->parser.or.parsers[i + 1] = ft_get_grammar_list(parsers[i]->parser.and.parsers[3]);
		CHECK(exited grammar list while  or_n);
		i++;
	}
	parser->id = OR;
	CHECK(exited grammar_or_n);
	return (parser);
}

t_parser	*ft_get_grammar_sub_expression(t_parser *sub_expression)
{
	t_parser	*tmp;
	uint32_t	size;

	CHECK(ENTERED subexpression);
	if (sub_expression->parser.or.parsers[0]->retained) // factorise plz
	{
		if (sub_expression->parser.or.parsers[0]->parser.func.parser->parser.and.parsers[6]->parser.oneof.c == '+')
			return (ft_get_parser_plus(ft_get_grammar_expression(
													sub_expression->parser.or.parsers[0]->parser.func.parser->parser.and.parsers[3])));
		else
			return (ft_get_parser_multiply(ft_get_grammar_expression(
													sub_expression->parser.or.parsers[0]->parser.func.parser->parser.and.parsers[3])));
	}
	else
	{
		size = sub_expression->parser.or.parsers[1]->parser.and.parsers[1]->parser.multiply.n;
		tmp = sub_expression->parser.or.parsers[1];
		CHECK(PUT_ID);
		ft_put_id(tmp->parser.and.parsers[1]->parser.multiply.parsers[0]);
		CHECK(exited PUT_ID);
		if (size)
			return (ft_get_grammar_or_n(size + 1, tmp->parser.and.parsers[0], tmp->parser.and.parsers[1]->parser.multiply.parsers));
		else
			return (ft_get_grammar_list(tmp->parser.and.parsers[0]));
	}
}

t_parser	*ft_get_grammar_expression(t_parser *expression)
{
	t_parser	*parser;
	t_parser	**parsers;
	uint32_t	i;

	i = 0;
	CHECK(ENTERED expression);
	if (!(parsers = (t_parser**)malloc(sizeof(t_parser*) * expression->parser.plus.n)))
		exit(EXIT_FAILURE);
	while (i < expression->parser.plus.n)
	{
		parsers[i] = ft_get_grammar_sub_expression(expression->parser.plus.parsers[i]);
		CHECK(exited sub_expression);
		i++;
	}
	parser = ft_get_parser_and_n(expression->parser.plus.n, parsers);
	CHECK(exited expression);
	return (parser);
}

t_parser	*ft_get_grammar_rule(t_parser *rule)
{
	t_parser	*parser;

	parser = ft_get_grammar_expression(rule->parser.and.parsers[5]);
	CHECK(EXPRESSION);
	ft_put_parser_tree(parser);
	CHECK(END);
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
		parsers[i] = ft_get_grammar_rule(syntax->parser.plus.parsers[i]);
		i++;
	}
	parser = ft_get_parser_plus(ft_get_parser_or_n(syntax->parser.plus.n, parsers));
	free(parsers);
	return (parser);
}
