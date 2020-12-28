# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 08:47:29 by dnakano           #+#    #+#              #
#    Updated: 2020/12/25 13:25:25 by dnakano          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				:=	gcc
CFLAGS			:=	-Wall -Werror -Wextra
SRCNAME			:=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c\
					ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c \
					ft_strlcat.c ft_strncmp.c ft_strchr.c ft_strrchr.c \
					ft_strnstr.c ft_strdup.c ft_isalpha.c ft_isdigit.c \
					ft_isupper.c ft_islower.c \
					ft_isalnum.c ft_isascii.c ft_isprint.c ft_isspace.c \
					ft_toupper.c ft_tolower.c ft_atoi.c ft_calloc.c ft_substr.c \
					ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
					ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUSSRCNAME	:=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
					ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
					ft_lstmap.c ft_lstsort.c ft_lstrm_if.c ft_lstpop.c \
					ft_lstdup.c \
					ft_putstrn_fd.c \
					get_next_line.c \
					ft_printf.c ft_printf_util.c ft_printf_putnbr.c \
					ft_printf_findflags.c \
					ft_printf_putbyte.c ft_printf_putstr.c \
					ft_printf_putpadding.c \
					ft_printf_putpercent.c ft_printf_putpointer.c \
					ft_printf_putint.c \
					ft_printf_putint_signed.c ft_printf_putint_unsigned.c \
					ft_printf_putarg_bonus.c \
					ft_printf_putfloat_bonus.c ft_store_iflt.c \
					ft_printf_floatutil_bonus.c ft_printf_floatutil2_bonus.c \
					ft_printf_putfloat_f_bonus.c \
					ft_printf_putfloat_e_bonus.c \
					ft_printf_putfloat_g_bonus.c \
					ft_printf_store_n_bonus.c \
					ft_atof.c ft_atof_dectobin_exp.c \
					ft_atof_bintof.c ft_atof_dectobin_frac.c \
					ft_atof_atobin.c ft_atof_atodec.c \
					ft_atof_uint128_2.c ft_atof_uint128.c
SRCDIR			:=	.
SRCS			:=	$(addprefix $(SRCDIR)/,$(SRCNAME))
OBJNAME			:=	$(SRCNAME:%.c=%.o)
BONUSOBJNAME	:=	$(BONUSSRCNAME:%.c=%.o)
OBJDIR			:=	$(SRCDIR)
OBJS			:=	$(addprefix $(OBJDIR)/,$(OBJNAME))
BONUSOBJS		:=	$(addprefix $(OBJDIR)/,$(BONUSOBJNAME))
HEADERNAME		:=	libft.h ft_printf.h
HEADERDIR		:=	.
HEADERS			:=	$(addprefix $(HEADERDIR)/,$(HEADERNAME))
NAME			:=	libft.a
OUTPUTDIR		:=	.
OUTPUTS			:=	$(addprefix $(OUTPUTDIR)/,$(NAME))
TESTDIR			:=	.
TESTNAME		:=	test.out
TESTSRCNAME		:=	test.c
TESTINCLUDENAME	:=	test_memset.c test_bzero.c test_memcpy.c test_memccpy.c\
					test_memmove.c test_memchr.c test_memcmp.c test_strnstr.c\
					test_strlen.c test_strlcpy.c test_strlcat.c test_strncmp.c\
					test_strxchr.c test_strdup.c test_isxxx.c test_toxxx.c\
					test_atoi.c test_calloc.c test_substr.c test_strjoin.c\
					test_split.c test_strtrim.c test_itoa.c test_strmapi.c\
					test_putxxx_fd.c test_lstxxx.c
TESTS			:=	$(addprefix $(TESTDIR)/,$(TESTNAME))
TESTSRCS		:= 	$(addprefix $(TESTDIR)/,$(TESTSRCNAME))
TESTINCLUDES	:=	$(addprefix $(TESTDIR)/,$(TESTINCLUDENAME))

.SUFFIXES:		.o .c

.PHONY:			all
all:			$(NAME)

$(NAME):		$(OBJS) $(BONUSOBJS) $(HEADERS)
				ar cr $(OUTPUTS) $(OBJS) $(BONUSOBJS)

.PHONY:			bonus
bonus:			$(OBJS) $(BONUSOBJS) $(HEADERS)
				ar cr $(OUTPUTS) $(OBJS) $(BONUSOBJS)

.c.o:
				$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $(patsubst %.c,%.o,$<)

.PHONY:			clean
clean:
				rm -f $(OBJS) $(BONUSOBJS)

.PHONY:			fclean
fclean:			clean
				rm -f $(OUTPUTS)

.PHONY:			re
re:				fclean all

$(TESTNAME):	$(OUTPUTS) $(TESTSRCS) $(TESTINCLUDES) $(NAME)
				rm -f $(TESTS)
				$(CC) $(CFLAGS) $(TESTSRCS) $(addprefix -include ,$(TESTINCLUDES)) -L. -lft -o $(TESTS)

.PHONY:			debug
debug:
				$(warning OBJS = $(OBJS))
				$(warning SRCS = $(SRCS))
				$(warning OUTPUTS = $(OUTPUTS))
