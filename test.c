/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:05:23 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/24 15:45:55 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

int main(int argc, char **argv)
{
	t_parser	*bnf;

	bnf = ft_get_grammar();
	char	*grammar = ft_strdup("");
	t_parser	*parser;
	char	*input = ft_strdup("test");
	if (!(ft_eval_parser(bnf, grammar)))
	{
		parser = ft_get_grammar_syntax(parser);
		ft_optimizer(parser);
		if (!(ft_eval_parser(parser, input)))
		{
			ft_put_ast_tokens(parser);
		}
		else
			ft_putendl("syntax error");
	}
	else
		ft_putstr("grammar error");
	return (0);
}
