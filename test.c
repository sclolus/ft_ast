/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:05:23 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/21 04:32:40 by aalves           ###   ########.fr       */
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

	parser = ft_get_parser_grammar();

/*	parser = ft_get_parser_and_n(3, (t_parser*[]){ft_get_parser_and_n(2, (t_parser*[]){ft_get_parser_whitespace(), ft_get_parser_onechar('g')})
	s, ft_get_parser_str("loli"), ft_get_parser_str("#tor")});*/
//	ft_dup_parser(parser);
	ft_put_parser_tree(ft_dup_parser(parser));
# if 1
	char		*base;
	char		*string;
	t_parser	*new_parser;


	// string = ft_strdup("<expression> ::= \"loli\" \"is for seb\" | \"fbi is coming\" '1' \n");
	string = ft_strdup("<expression> ::= ('1' | '2' | '3' | '4' |'5' |'6' |'7' |'8' |'9' |'0' )+ \n");
	// \	<hexa> ::= 'a' | 'b' | 'c' | 'd'| 'e'| 'f'\n");

	char	*input = ft_strdup("6868casacaca46514365146351");
	base = string;
	if (ft_eval_input(parser, &string))
	{
/*		ft_putstr(" current string:-");
		ft_putstr(string);
		ft_putchar('\n');*/
		CHECK(GRAMMAR ENTERED);
		new_parser = ft_get_grammar_syntax(parser);
		ft_link_rule_name(new_parser, &new_parser);
		ft_put_parser_tree(new_parser);
			if (!ft_eval_input(new_parser, &input))
				{
					ft_putstr("omg bad input retard : ");
					ft_putstr(input);
					exit(EXIT_FAILURE);
				}
printf("str = <%s>\n", input);
		// for (size_t k = 0; k < new_parser->parser.plus.n; k++) {
		// 	ft_put_parser_tree(new_parser->parser.plus.parsers[k]);
		// 	printf("-_-_-_-\n");
		// }
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
