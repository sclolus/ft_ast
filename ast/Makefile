# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalves <aalves@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/11 02:24:19 by aalves            #+#    #+#              #
#    Updated: 2017/03/18 04:44:50 by sclolus          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS=		ast.c \
			ft_put_parser.c \
			ft_eval_parser.c \
			ft_get_grammar_literal.c

OBJS= $(SRCS:.c=.o)

ifeq ($(VERBOSE), 1)
.c.o:
	@$(ECHO) "$(GREEN)Creating $@ $(NC)"
	@$(CC) $(FLAGS) -I ../includes -o $@ -c $<
else
.c.o:
	@$(CC) $(FLAGS) -I ../includes -o $@ -c $<
endif

all: $(OBJS)
	@$(ECHO) "$(CYAN)Parsing module done $(NC)"
	@ar r ../$(NAME) $^

clean:
	@$(RM) $(OBJS)
	@$(ECHO) "$(CYAN)Parsing module cleaned $(NC)"

re: clean all
