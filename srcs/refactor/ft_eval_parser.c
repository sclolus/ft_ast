#include "ast.h"

bool	ft_eval_onechar(t_parser *parser, char **string) {
	if (parser->parser.onechar.c == **string) {
		(*string)++;
		return (true):
	}
	return (false);
}

bool	ft_eval_parser_or(t_parser *parser, char **string) {
	uint32_t    i = 0;

	while (i < parser->n) {
		if (!ft_eval_parser(parser->parsers[i], string)) {
			return false
		}
		i++;
	}
	true
}

bool	ft_eval_parser_ref(t_parser *parser, char **string) {

}

bool	ft_eval_parser(t_parser *parser, char **string) {
	char						*base;
	uint32_t					ret;

	static const t_eval_parser	eval_parsers[18] = {
		{NULL}, {NULL},
		{NULL}, {NULL},
		{NULL}, {NULL},
		{NULL}, {NULL},
		{NULL}, {NULL},
		{NULL}, {NULL},
		{NULL}, {NULL},
		{NULL}, {NULL},
		{NULL}, {NULL}};

	base = *string;
	ret = eval_parsers[parser->id].f(parser, string);
	*string = base;
	return (ret);
}
