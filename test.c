/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:05:23 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/26 19:10:54 by sclolus          ###   ########.fr       */
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
	int32_t	fd;

	if ((fd = open("grammar.txt", O_RDONLY)) < 0)
	{
		ft_putnbr(fd);
		exit (EXIT_FAILURE);
	}
	parser = ft_get_parser_grammar();

/*	parser = ft_get_parser_and_n(3, (t_parser*[]){ft_get_parser_and_n(2, (t_parser*[]){ft_get_parser_whitespace(), ft_get_parser_onechar('g')})
	s, ft_get_parser_str("loli"), ft_get_parser_str("#tor")});*/
//	ft_dup_parser(parser);
	// ft_put_parser_tree(ft_dup_parser(parser));
	ft_eval_input_file(fd, parser);
# if 0
	char		*base;
	char		*string;
	char		*shell_syntax;
	t_parser	*new_parser;


	// string = ft_strdup("<expression> ::= \"loli\" \"is for seb\" | \"fbi is coming\" '1' \n");
	// string = ft_strdup("<expr> ::= <num><sp>\"toto\"<sp><loli>\n\
	// <num> ::= ('1' | '2' | '3' | '4' |'5' |'6' |'7' |'8' |'9' |'0' | <hexa>)+ \n\
	// <hexa> ::= 'a' | 'b' | 'c' | 'd'| 'e'| 'f'\n\
	// <loli> ::= \"loli\"\n\
	// <sp> ::= (' ' | '\t')*\n");
	shell_syntax = ft_strdup("<complete_command> ::= <list> <separator> | list \n\
						<list>             ::= <list> <separator_op> <and_or> |  and_or \n\
						<and_or>           ::= <pipeline> | <and_or> <AND_IF> <linebreak> <pipeline> \n\ | <and_or> <OR_IF> <linebreak> <pipeline> \n\
						<pipeline>         ::= <pipe_sequence> | <Bang> <pipe_sequence> \n\
						<pipe_sequence>    ::= <command> | <pipe_sequence> '|' <linebreak> <command> \n\
						<command>          ::= <simple_command> | <compound_command> | <compound_command> <redirect_list> | <function_definition> \n\
						<compound_command> ::= <brace_group> | <subshell> | <for_clause> | <case_clause> | <if_clause> | <while_clause> | <until_clause> \n\
						<subshell>         ::= '(' <compound_list> ')' \n\
						<compound_list>    ::= <term> | <newline_list> <term> | <term> <separator> | <newline_list> <term> <separator> \n\
						<term>             ::= <term> <separator> <and_or> | <and_or> \n\
						<for_clause>       ::= <For> <name> <linebreak> <do_group> | <For> <name> <linebreak> <in> <sequential_sep> <do_group> | <For> <name> <linebreak> <in> <wordlist> <sequential_sep> <do_group> \n\
						<name>             ::= <NAME>                     /* Apply rule 5 */ \n\
						<in>               ::= <In>                       /* Apply rule 6 */ \n\
						<wordlist>         ::= <wordlist> WORD | WORD \n\
						<case_clause>      ::= <Case> WORD <linebreak> <in> <linebreak> <case_list> \"Esac\" | <Case> WORD <linebreak> <in> <linebreak> <case_list_ns> <Esac> | <Case> WORD <linebreak> <in> <linebreak> \"Esac\" \n\
						<case_list_ns>     ::= <case_list> <case_item_ns> | <case_item_ns> \n\
						<case_list>        ::= <case_list> <case_item> | <case_item> \n\
						<case_item_ns>     ::= <pattern> ')' <linebreak> | <pattern> ')' <compound_list> <linebreak> | '(' <pattern> ')' <linebreak> | '(' <pattern> ')' <compound_list> <linebreak> \n\
						<case_item>        ::= <pattern> ')' <linebreak> ';' <linebreak> |     <pattern> ')' <compound_list> ';' <linebreak> | '(' <pattern> ')' <linebreak> ';' <linebreak> | '(' <pattern> ')' <compound_list> ';' <linebreak> \n\
						<pattern>          ::=             WORD         /* Apply rule 4 */ | <pattern> '|' WORD         /* Do not apply rule 4 */ \n\
						<if_clause>        ::= \"if\" <compound_list> \"then\" <compound_list> else_part \"fi\" | \"if\" <compound_list> \"then\" <compound_list> \"fi\" \n\
						<else_part>        ::= \"elif\" <compound_list> \"then\" <else_part> | \"else\" <compound_list> \n\
						<while_clause>     ::= \"while\" <compound_list> <do_group> \n\
						<until_clause>     ::= \"until\" <compound_list> <do_group> \n\
						<function_definition> ::= <fname> '(' ')' <linebreak> <function_body> \n\
						<function_body>    ::= <compound_command>                /* Apply rule 9 */ | <compound_command> <redirect_list>  /* Apply rule 9 */ \n\
						<fname>            ::= NAME                            /* Apply rule 8 */ \n\
						<brace_group>      ::= \'{\' <compound_list> \'}\' \n\
						<do_group>         ::= \"do\" <compound_list> \"done\"           /* Apply rule 6 */ \n\
						<simple_command>   ::= <cmd_prefix> <cmd_word> <cmd_suffix> | <cmd_prefix> <cmd_word> | <cmd_prefix> | <cmd_name> <cmd_suffix> | <cmd_name> \n\
						<cmd_name>         ::= WORD                   /* Apply rule 7a */ \n\
						<cmd_word>         ::= WORD                   /* Apply rule 7b */ \n\ 
						<cmd_prefix>       ::= <io_redirect> | <cmd_prefix> <io_redirect> |            ASSIGNMENT_WORD | <cmd_prefix> ASSIGNMENT_WORD \n\
						<cmd_suffix>       ::= <io_redirect> | <cmd_suffix> <io_redirect> |            WORD | <cmd_suffix> WORD \n\
						<redirect_list>    ::= <io_redirect> | <redirect_list> <io_redirect> \n\
						<io_redirect>      ::= <io_file> | IO_NUMBER <io_file> | <io_here> | IO_NUMBER <io_here> \n\
						<io_file>          ::= '<' <filename> | LESSAND <filename> | '>' <filename> | GREATAND  <filename> | DGREAT <filename> | LESSGREAT <filename> | CLOBBER   <filename> \n\
						<filename>         ::= WORD                      /* Apply rule 2 */ \n\
						<io_here>          ::= DLESS     <here_end> | DLESSDASH <here_end> \n\
						<here_end>         ::= WORD                      /* Apply rule 3 */ \n\
						<newline_list>     ::=              NEWLINE | <newline_list> NEWLINE \n\
						<linebreak>        ::= <newline_list> | /* empty */ \n\
						<separator_op>     ::= '&' | ';' \n\
						<separator>        ::= <separator_op> <linebreak> | <newline_list> \n\
						<sequential_sep>   ::= ';' <linebreak>\n");

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
			ft_putstr("omg bad input retard ::= ");
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
		ft_putstr("nope ::= \n");
		ft_putstr(string);
	}
#endif
	return (0);
}
