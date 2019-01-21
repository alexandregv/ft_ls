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

NAME			= ft_ls
CC				= gcc

# Compiler & Preprocessor flags
CFLAGS		+= -Wall -Werror -Wextra
CPPFLAGS	+= -I include/ -I libft/

# Recompile on headers/Makefile changes
DEPS			= libft/libft.h include/ft_ls.h Makefile

# Source files
SRC_PATH	= src/
#SRC_NAME	= ft_list_dir ft_inspect_file
SRC_NAME	= main
SRC				= $(addsuffix .c, $(SRC_NAME))

# Object files
OBJ_PATH	= obj/
OBJ_NAME	= $(addsuffix .o, $(SRC_NAME))
OBJ				= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

# Library
LIB_PATH	= libft
LIB_NAME	= ft
LIB				= -L $(LIB_PATH) -l $(LIB_NAME)

# Colors
C_RESET		= \033[0m
C_PENDING	= \033[0;36m
C_SUCCESS	= \033[0;32m

# Escape Sequences (ANSI/VT100)
ES_ERASE	= "\033[A\033[K\033[A"

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
#	@$(ECHO) "$(LIB_PATH)\t[$(C_PENDING)⏳ $(C_RESET)]"
	@$(MAKE) -C $(LIB_PATH)
	@$(ECHO) $(ES_ERASE)
#	@$(ECHO) "$(LIB_PATH)\t[$(C_SUCCESS)✅ $(C_RESET)]"
	@$(ECHO) "$(NAME)\t[$(C_PENDING)⏳ $(C_RESET)]"
	@$(CC) $(OBJ) $(LIB) -o $(NAME)
	@$(ECHO) $(ES_ERASE)
	@$(ECHO) "$(NAME)\t[$(C_SUCCESS)✅ $(C_RESET)]"
	@$(ECHO) "$(C_SUCCESS)All done, compilation successful! 👌 $(C_RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEPS)
	@mkdir $(OBJ_PATH) $(HIDE_ERR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	@$(RM) -r $(OBJ_PATH) $(HIDE_ERR)
	@$(RM) -r $(NAME).dSYM $(HIDE_ERR)
	@$(MAKE) -C $(LIB_PATH) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIB_PATH) fclean

re: fclean all

.PHONY: clean fclean all re