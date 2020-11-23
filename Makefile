# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 08:47:29 by dnakano           #+#    #+#              #
#    Updated: 2020/11/23 18:08:33 by dnakano          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				:=	gcc
CFLAGS			:=	-Wall -Werror -Wextra
NAME			:=	miniRT
OUTPUTDIR		:=	.
OUTPUTS			:=	$(addprefix $(OUTPUTDIR)/,$(NAME))
SRCNAME			:=	minirt.c
SRCDIR			:=	./srcs
SRCS			:=	$(addprefix $(SRCDIR)/,$(SRCNAME))
OBJNAME			:=	$(SRCNAME:%.c=%.o)
OBJS			:=	$(addprefix $(SRCDIR)/,$(OBJNAME))
LIBFTDIR		:=	libft
LIBFTNAME		:=	libft.a
LIBFT			:=	$(addprefix $(LIBFTDIR)/,$(LIBFTNAME))
HEADERNAME		:=	minishell.h
HEADERDIR		:=	./includes
HEADERS			:=	$(addprefix $(HEADERDIR)/,$(HEADERNAME))

.SUFFIXES:		.o .c

.PHONY:			all
all:			$(NAME)

$(NAME):		$(LIBFT) $(HEADERS)
				$(CC) $(CFLAGS) $(OBJS) \
				-L$(LIBFTDIR) $(patsubst lib%,-l%,$(basename $(LIBFTNAME))) \
				-o $(OUTPUTDIR)/$(NAME)

$(LIBFT):
				cd $(LIBFTDIR) && make $(LIBFTNAME)

.c.o:
				$(CC) $(CFLAGS) -I$(HEADERDIR) \
				-c $< -o $(patsubst %.c,%.o,$<)

.PHONY:			clean
clean:
				cd $(LIBFTDIR)/ && make fclean
				rm -f $(OBJS)

.PHONY:			fclean
fclean:			clean
				rm -f $(OUTPUTDIR)/$(OUTPUTS)

.PHONY:			re
re:				fclean all
