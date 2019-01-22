# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/18 16:51:51 by aguiot--          #+#    #+#              #
#    Updated: 2019/01/18 16:51:52 by aguiot--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a
CC				= gcc

# Compiler & Preprocessor flags
CFLAGS		+= -Wall -Werror -Wextra

# Take care of headers/Makefile changes
DEPS			= libft.h

# Source files
SRC_NAME	= ft_putchar_fd ft_putchar ft_putstr_fd ft_putstr ft_putnbr_fd \
	  				ft_putnbr ft_strlen ft_strcpy  ft_strncpy ft_strdup \
	  				ft_strcat ft_strncat ft_strlcat ft_strchr ft_strrchr \
	  				ft_strcmp ft_strncmp ft_isupper ft_islower ft_isalpha \
	  				ft_isdigit ft_isalnum ft_isprint ft_isascii ft_toupper \
	  				ft_tolower ft_strclr ft_putendl_fd ft_putendl ft_strequ \
	  				ft_strnequ ft_strstr ft_strnstr ft_memset ft_bzero \
	  				ft_memalloc ft_memdel ft_strnew ft_strdel ft_strsub \
	  				ft_strjoin ft_isspace ft_isblank ft_iscntrl ft_isgraph \
	  				ft_isxdigit ft_str_is_alpha ft_str_is_lowercase \
	  				ft_str_is_uppercase ft_str_is_numeric ft_str_is_printable \
	  				ft_strupcase ft_strlowcase ft_strcasestr ft_strcasecmp \
	  				ft_strndup ft_strtrim ft_striter ft_striteri ft_strmap \
	  				ft_strmapi ft_atoi ft_memcpy ft_memchr ft_memcmp ft_memmove \
	  				ft_memccpy ft_strsplit ft_itoa ft_lstnew ft_lstadd \
	  				ft_lstdelone ft_lstdel ft_lstiter ft_lstmap ft_str_skip_to \
	  				ft_str_skip_while ft_str_skip_charset get_next_line ft_str_copy_to \
						ft_strnjoin ft_die
SRC				= $(addsuffix .c, $(SRC_NAME))

# Object files
OBJ_PATH	= obj/
OBJ_NAME	= $(addsuffix .o, $(SRC_NAME))
OBJ				= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

# Colors
C_RESET		= \033[0m
C_PENDING	= \033[0;36m
C_SUCCESS	= \033[0;32m

# Escape Sequences (ANSI/VT100)
ES_ERASE	= "\033[A\033[K\033[A"
ERASE			= $(ECHO) $(ES_ERASE)

# Hide STD/ERR and prevent Make from returning non-zero code
HIDE_STD	= > /dev/null
HIDE_ERR	= 2> /dev/null || true

# Multi platforms 
ECHO 			= echo
ifeq ($(shell uname),Linux)
	ECHO		+= -e
endif

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rcs $(NAME) $(OBJ) $(HIDE_STD)
	@$(ERASE)
	@$(ECHO) "$(NAME)\t[$(C_SUCCESS)✅ $(C_RESET)]"
	@$(ECHO) "$(C_SUCCESS)All done, compilation successful! 👌 $(C_RESET)"

$(OBJ_PATH)%.o: %.c $(DEPS)
	@mkdir $(OBJ_PATH) $(HIDE_ERR)
	@$(ERASE)
	@$(ECHO) "$(NAME)\t[$(C_PENDING)⏳ $(C_RESET)]"
	$(CC) $(CFLAGS) -o $@ -c $<
	@$(ERASE)

clean:
	@$(RM) -r $(OBJ_PATH) $(HIDE_ERR)
	@$(RM) -r $(NAME).dSYM $(HIDE_ERR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
