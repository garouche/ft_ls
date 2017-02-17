# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: garouche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/24 16:32:09 by garouche          #+#    #+#              #
#    Updated: 2017/02/06 14:01:45 by garouche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	libftprintf.a
SRC		=	arg.c ft_printf.c is_type.c is_int.c parsing.c unicode.c flags.c
OBJ		=	$(SRC:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror
LIBDIR  =   libft/
LIBC    =   $(LIBDIR)libft.a
.PHONY	: 	all clean re fclean

all		:	$(NAME)

$(NAME)	:	$(LIBC) $(PRINTF) $(OBJ)
			ar r $(LIBC) $(OBJ)
			cp $(LIBC) $(NAME)

$(LIBC) :   $(LIBDIR)
			make -C $(LIBDIR)
			
clean	:
			rm -f $(OBJ)
			make -C $(LIBDIR) fclean

re		: 	fclean	all

fclean	:	clean
			rm -f $(NAME)


