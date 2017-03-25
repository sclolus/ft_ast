/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:05:23 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/25 08:46:27 by sclolus          ###   ########.fr       */
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

//	ft_putstr("salut");
	parser = ft_get_parser_grammar();
	CHECK(DAFUQ);

/*	parser = ft_get_parser_and_n(3, (t_parser*[]){ft_get_parser_and_n(2, (t_parser*[]){ft_get_parser_whitespace(), ft_get_parser_onechar('g')})
	s, ft_get_parser_str("loli"), ft_get_parser_str("#tor")});*/
//	ft_dup_parser(parser);
	// ft_put_parser_tree(ft_dup_parser(parser));
# if 1
	char		*base;
	char		*string;
	t_parser	*new_parser;


	// string = ft_strdup("<expression> ::= \"loli\" \"is for seb\" | \"fbi is coming\" '1' \n");
	// string = ft_strdup("<expr> ::= <num><sp>\"toto\"<sp><loli>\n\
	// <num> ::= ('1' | '2' | '3' | '4' |'5' |'6' |'7' |'8' |'9' |'0' | <hexa>)+ \n\
	// <hexa> ::= 'a' | 'b' | 'c' | 'd'| 'e'| 'f'\n\
	// <loli> ::= \"loli\"\n\
	// <sp> ::= (' ' | '\t')*\n");
	string = ft_strdup("<expression> ::= (<spe> <subexpr> <spe> <op> <spe>)+ | <number> \n\
						<op>	     ::= \'+\' | \'-\' | \'/\' | \'*\' \n\
						<number>     ::= (\'1\' | \'2\' | \'3\' | \'4\' |\'5\' |\'6\' |\'7\' |\'8\' |\'9\' |\'0\')+ \n\
						<subexpr>    ::=  <number> <spe> <op> <spe> <number> \n\
		   <spe>          ::= (\' \' | \'\t\')* \n");
	char	*input = ft_strdup("111111111111111111111111111111111111111111111111111111111111111111112 + 1");
	base = string;
	if (ft_eval_input(parser, &string))
	{
		CHECK(eval terminated);
		new_parser = ft_get_grammar_syntax(parser);
		ft_put_parser_tree(new_parser);
		CHECK(test);
		CHECK(get_grammar_syntax terminated);
		// ft_put_parser_tree(new_parser);
		if (!ft_eval_input(new_parser, &input))
		{
			ft_putstr("omg bad input retard : ");
			ft_putstr(input);
			exit(EXIT_FAILURE);
		}
		while (1)
			;
		CHECK(EVAL_INPUT TERMINATED);
		printf("str = <%s>\n", input);

		ft_put_parser_tree(new_parser);
		ft_put_ast_tokens(new_parser);
/*		 for (size_t k = 0; k < new_parser->parser.plus.n; k++) {
		 	ft_put_parser_tree(new_parser->parser.plus.parsers[k]);
		 	printf("-_-_-_-\n");
			}*/
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
