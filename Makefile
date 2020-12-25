# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 08:47:29 by dnakano           #+#    #+#              #
#    Updated: 2020/12/25 17:14:36 by dnakano          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				:=	gcc
CFLAGS			:=	-Wall -Werror -Wextra
NAME			:=	minishell
OUTPUTDIR		:=	.
OUTPUTS			:=	$(addprefix $(OUTPUTDIR)/,$(NAME))
SRCNAME			:=	main.c \
					msh_mshinfo_init.c \
					msh_mshinfo_free.c \
					msh_parse_envp.c \
					msh_signalhandler.c \
					msh_puterr.c \
					msh_loop.c \
					msh_read_and_exec_cmd.c \
					msh_syntaxcheck.c \
					msh_put_syntaxerr.c \
					msh_parse_and_exec_cmd.c \
					msh_get_value_from_envlst.c \
					msh_strdup_skip_bslash.c \
					msh_handle_dollars.c \
					msh_parse_to_arglst.c \
					msh_handle_redirect.c \
					msh_create_redirect.c \
					msh_handle_pipe.c \
					msh_create_pipe.c \
					msh_handle_quote.c \
					msh_exec_cmd.c \
					msh_cd.c \
					msh_pwd.c \
					msh_echo.c \
					msh_env.c \
					msh_unset.c \
					msh_env_isvalid.c \
					msh_putenverr.c \
					msh_env_cmpkey.c \
					msh_executable.c \
					msh_find_and_copy_path.c \
					msh_wait.c \
					msh_exit.c \
					msh_export.c \
					msh_export_new_env.c \
					msh_keyval_free.c \
					msh_keyval_dup.c \
					msh_make_envp.c \
					msh_content_arglst.c \
					msh_get_argv.c \
					msh_msg_return_val.c \
					msh_isescaped.c \
					msh_check_operator.c \
					msh_isspace.c \
					msh_store_argv.c \
					msh_resetfd.c \
					msh_free_setnull.c \
					msh_free_funcs.c
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

$(NAME):		$(LIBFT) $(HEADERS) $(OBJS)
				$(CC) $(CFLAGS) $(OBJS) \
				-L$(LIBFTDIR) $(patsubst lib%,-l%,$(basename $(LIBFTNAME))) \
				-o $(OUTPUTDIR)/$(NAME)

$(LIBFT):
				make -C $(LIBFTDIR) $(LIBFTNAME)

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
