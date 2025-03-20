#----------	Makefile Library -- All the following variables can be edited. ----------#

SRC		=	$(SRCDIR)ft_atoi.c					\
			$(SRCDIR)ft_itoa.c					\
			$(SRCDIR)ft_bzero.c					\
			$(SRCDIR)ft_split.c					\
			$(SRCDIR)ft_calloc.c				\
			$(SRCDIR)ft_memchr.c				\
			$(SRCDIR)ft_memcmp.c				\
			$(SRCDIR)ft_memcpy.c				\
			$(SRCDIR)ft_memset.c				\
			$(SRCDIR)ft_strchr.c				\
			$(SRCDIR)ft_strdup.c				\
			$(SRCDIR)ft_strlen.c				\
			$(SRCDIR)ft_substr.c				\
			$(SRCDIR)ft_isalnum.c				\
			$(SRCDIR)ft_isalpha.c				\
			$(SRCDIR)ft_isascii.c				\
			$(SRCDIR)ft_isdigit.c				\
			$(SRCDIR)ft_isprint.c				\
			$(SRCDIR)ft_memmove.c				\
			$(SRCDIR)ft_strjoin.c				\
			$(SRCDIR)ft_strlcat.c				\
			$(SRCDIR)ft_strlcpy.c				\
			$(SRCDIR)ft_strmapi.c				\
			$(SRCDIR)ft_strncmp.c				\
			$(SRCDIR)ft_strnstr.c				\
			$(SRCDIR)ft_strrchr.c				\
			$(SRCDIR)ft_strtrim.c				\
			$(SRCDIR)ft_tolower.c				\
			$(SRCDIR)ft_toupper.c				\
			$(SRCDIR)ft_striteri.c				\
			$(SRCDIR)ft_putchar_fd.c			\
			$(SRCDIR)ft_putstr_fd.c				\
			$(SRCDIR)ft_putendl_fd.c			\
			$(SRCDIR)ft_putnbr_fd.c				\
			$(SRCDIR)ft_argjoin.c				\
			$(SRCDIR)ft_atol.c					\
			$(SRCDIR)ft_utoa_base.c				\
			$(SRCDIR)ft_lstnew_bonus.c			\
			$(SRCDIR)ft_lstadd_front_bonus.c	\
			$(SRCDIR)ft_lstsize_bonus.c			\
			$(SRCDIR)ft_lstlast_bonus.c			\
			$(SRCDIR)ft_lstadd_back_bonus.c		\
			$(SRCDIR)ft_lstdelone_bonus.c		\
			$(SRCDIR)ft_lstclear_bonus.c		\
			$(SRCDIR)ft_lstiter_bonus.c			\
			$(SRCDIR)ft_lstmap_bonus.c			\
			$(SRCDIR)ft_printf_bonus.c			\
			$(SRCDIR)ft_printf_flags_bonus.c	\
			$(SRCDIR)ft_printf_utils_bonus.c	\
			$(SRCDIR)ft_printf_utils.c			\
			$(SRCDIR)ft_printfd.c				\
			$(SRCDIR)get_next_line_bonus.c		\
			$(SRCDIR)get_next_line_utils_bonus.c\

#
SRCDIR	=	./
OBJDIR	=	obj/

NAME	=	libft.a

CC		=	cc
GCC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

#---------- Edit the following if: IGLAGS added or no sub-makefile needed. ----------#

OBJ		=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

.PHONY: all clean fclean re

all: $(NAME)

#- Creates a directory named $(OBJDIR).												  -#
$(OBJDIR):
	@mkdir -p $@
#
#- Compiles each %(generic).c source into its respective %(generic).o				  -#
$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\e[0;35m -$@ created."
#
$(NAME): $(OBJDIR) $(OBJ)
	@echo "\e[0;32m"
	@ar rcs $(NAME) $(OBJ)
	@echo "\e[0;32m $@ linked.\n"
#
#- Removes every object inside $(OBJDIR) and the directory itself.					  -#
clean:
	@rm -rf $(OBJDIR)
	@echo "\e[0;32m Cleaning complete."
#
#- Removes the final files made with this makefile, executing clean as well.		  -#
fclean: clean
	@rm -f $(NAME)
	@echo "\e[0;32m Files removed."
#
#- Restarts the Makefile. Erases everything to default, and executes again.			  -#
re: fclean all