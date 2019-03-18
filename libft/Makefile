# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/18 16:51:51 by aguiot--          #+#    #+#              #
#    Updated: 2019/03/18 14:51:36 by sboulaao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
CC			= gcc

# Compiler & Preprocessor flags
CFLAGS		+= -Wall -Werror -Wextra
CPPFLAGS    += -I include/

# Take care of headers/Makefile changes
DEPS		= include/libft.h include/get_next_line.h Makefile

# Source files
SRC_PATH	= src/
SRC_NAME	= \
			ft_putchar_fd		ft_strclr			ft_strtrim			\
			ft_putchar			ft_strequ			ft_striter			\
			ft_putstr_fd		ft_strnequ			ft_striteri			\
			ft_putstr			ft_strstr			ft_strmap			\
			ft_putendl_fd		ft_strnstr			ft_strmapi			\
			ft_putendl			ft_memset			ft_atoi				\
			ft_putnbr_fd		ft_bzero			ft_memcpy			\
			ft_putnbr			ft_memalloc			ft_memchr			\
			ft_strlen			ft_memdel			ft_memcmp			\
			ft_strcpy			ft_strnew			ft_memmove			\
			ft_strncpy			ft_strdel			ft_memccpy			\
			ft_strdup			ft_strsub			ft_strsplit			\
			ft_strcat			ft_strjoin			ft_itoa				\
			ft_strncat			ft_isspace			ft_lstnew			\
			ft_strlcat			ft_isblank			ft_lstadd			\
			ft_strchr			ft_iscntrl			ft_lstdelone		\
			ft_strrchr			ft_isgraph			ft_lstdel			\
			ft_strcmp			ft_isxdigit			ft_lstiter			\
			ft_strncmp			ft_str_is_alpha		ft_lstmap			\
			ft_isupper			ft_str_is_lowercase ft_str_skip_to		\
			ft_islower			ft_str_is_uppercase ft_str_skip_while	\
			ft_isalpha			ft_str_is_numeric	ft_str_skip_charset \
			ft_isdigit			ft_str_is_printable ft_str_copy_to		\
			ft_isalnum			ft_strupcase		ft_strnjoin			\
			ft_isprint			ft_strlowcase		ft_die				\
			ft_isascii			ft_strcasestr		ft_sort_table		\
			ft_tolower			ft_strcasecmp		get_next_line		\
			ft_toupper			ft_strndup			ft_list_rev			\
			ft_list_del			ft_list_del_at		ft_list_del_node	\
			ft_list_get_at		ft_list_get_index	ft_list_iter		\
			ft_list_map			ft_list_new			ft_list_size		\
			ft_list_push_at		ft_list_push_back	ft_list_push_front	\
			ft_list_pop_at		ft_list_pop_back	ft_list_pop_front	\
			ft_list_sort		ft_list_last		ft_dlist_msort		\
			ft_dlist_rev		ft_int_tab			ft_sizet_tab		

# Object files
OBJ_PATH	= obj/
OBJ_NAME	= $(addsuffix .o, $(SRC_NAME))
OBJ			= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

# Colors
C_RESET		= \033[0m
C_PENDING	= \033[0;36m
C_SUCCESS	= \033[0;32m

# Escape Sequences (ANSI/VT100)
ES_ERASE	= "\033[A\033[K\033[A"
ERASE		= $(ECHO) $(ES_ERASE)

# Hide STD/ERR and prevent Make from returning non-zero code
HIDE_STD	= > /dev/null
HIDE_ERR	= 2> /dev/null || true

# Multi platforms 
ECHO 		= echo
ifeq ($(shell uname),Linux)
	ECHO	+= -e
endif

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rcs $(NAME) $(OBJ) $(HIDE_STD)
	@$(ERASE)
	@$(ECHO) "$(NAME)\t[$(C_SUCCESS)✅ $(C_RESET)]"
	@$(ECHO) "$(C_SUCCESS)All done, compilation successful! 👌 $(C_RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEPS)
	@mkdir $(OBJ_PATH) $(HIDE_ERR)
	@$(ERASE)
	@$(ECHO) "$(NAME)\t[$(C_PENDING)⏳ $(C_RESET)]"
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@$(ERASE)

clean:
	@$(RM) -r $(OBJ_PATH) $(HIDE_ERR)
	@$(RM) -r $(NAME).dSYM $(HIDE_ERR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
