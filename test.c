/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:05:23 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/19 10:38:37 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

int main(int argc, char **argv)
{

	if (argc || argv)
	{};
/*
	if (ft_grammar("number \"number\" : /[0-9]+/ ;\
expression      : <product> ((\'+\' | \'-\') <product>)* ;\
product         : <value> ((\'*\' | \'/\') <value>)* ;\
value           : <number> | \'(\' <expression> \')\' ;\
maths           : /^/ <expression> /$/ ;"))
		ft_putstr("\n");
	else
	ft_putstr("lol");*/
//	ft_parser(argv[1]);
//	ft_get_parser_grammar();
	t_parser	*parser;

//	parser = ft_get_parser_grammar();

	parser = ft_get_parser_and_n(3, (t_parser*[]){ft_get_parser_and_n(2, (t_parser*[]){ft_get_parser_whitespace(), ft_get_parser_onechar('g')})
	, ft_get_parser_str("loli"), ft_get_parser_str("#tor")});
//	ft_dup_parser(parser);
	ft_put_parser_tree(	ft_dup_parser(parser));
# if 0
	char		*base;
	char		*string;


	string = ft_strdup("<expression> ::= \"test\" \'+\' <value> \n"
					   "<value> ::= (<digit>)* \n"
					   "<digit> ::= \'1\' | \'2\' | \'3\' | \'4\' \n");
	base = string;
	parser = ft_get_parser_grammar();
	if (ft_eval_parser(parser, &string))
	{
		ft_putstr(" current string:-");
		ft_putstr(string);
		ft_putchar('\n');
	}
	else
	{
		//string = base;
		ft_putstr("nope : \n");
		ft_putstr(string);
	}
#endif 
	return (0);
}
