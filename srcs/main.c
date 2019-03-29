/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 19:27:47 by aalves            #+#    #+#             */
/*   Updated: 2019/03/04 19:37:03 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ast.h"
#include <errno.h>
#include <assert.h>
#include <readline/readline.h>
#include <stdarg.h>

/* #define ERR(format, ...) do {\ */
/* 		dprintf(STDERR_FILENO, "%s:%d " format "\n", __FILE__, __LINE__, __VA_OPT__, __VA_ARGS__); \ */
/* }while(0); */

int main(int argc, char **argv) {
	t_parser	*parser;
	/* t_parser	*bnf_parser = ft_get_parser_grammar(); */
	t_string	grammar_string = ft_get_file_content("grammar.txt");
	char		*grammar = grammar_string.string;

	if (!grammar) {
        printf("broken\n");
		exit(EXIT_FAILURE);
	}

	/* if (ft_eval_input(bnf_parser, &grammar)) { */
	/* 	parser = ft_get_grammar_syntax(bnf_parser); */
	/* } else { */
	/* 	ERR("Failed to evaluted grammar"); */
	/* 	exit(EXIT_FAILURE); */
	/* } */


	/* ft_put_parser(parser); */
	/* ft_optimizer(parser); */
	t_parser   *onechar = ft_get_parser_onechar('1');

	t_parser   *ref_onechar = ft_get_parser_ref(onechar);

	parser = ft_get_parser_or_n(2, (t_parser *[]){ft_get_parser_and_n(2, (t_parser*[]){
					ref_onechar,
						ft_get_undefined_parser(),
						}),
				ref_onechar}
		);

	parser->parser.or.parsers[0]->parser.and.parsers[1] = ft_get_parser_ref(parser);

	ft_put_parser(parser);
	printf("==========END_PARSER==============\n");
	while (42) {
		char *line = readline("Input regexp");

		if (!line)
			break ;

		printf("matched %d: \n", ft_eval(parser, &line));
	}

	return (0);
}