# --------------------------------- Makefile Main ---------------------------------- #

MAIN		=	$(SRCDIR)fdf.c		\

SRC			=	$(SRCDIR)camera.c	\
				$(SRCDIR)draw.c		\
				$(SRCDIR)hooks.c	\
				$(SRCDIR)start.c	\
				$(SRCDIR)utils.c	\

BSRC		=	$(SRCDIR)#- *_bonus.c													-#

SRCDIR		=	src/
OBJDIR		=	obj/
MAKENM		=	src/libft

LIBFT		=	libft.a
LIBEXE		=	fdf.a

NAME		=	fdf
BONUS		=	#- The name of the bonus final program.									-#

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g

# --------------------------- Makefile MLX42 Compilation --------------------------- #

MLX42		=	libmlx42
MLX42_FLAG	=	-lglfw
MLX42_PDIR	=	MLX42
MLX42_PLIB	=	$(MLX42_PDIR)/build/libmlx42.a
CMLX42_LIB	=	Libmlx42

# --------------------------- Makefile Object Compilation -------------------------- #

OBJ			=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
MOBJ		=	$(MAIN:$(SRCDIR)%.c=$(OBJDIR)%.o)
# BOBJ		=	$(BSRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

# ------------------------------- Makefile Cosmetics ------------------------------- #

CLIBFT			=	Libft
CNAME			=	Fdf
CBONUS			=	#-Name of the final bonus program with first letter in caps.	-#
COLOUR_GREEN	=	\033[0;32m
COLOUR_RED		=	\033[0;31m
COLOUR_CIAN		=	\033[0;35m
COLOUR_BLUE		=	\033[0;34m
COLOUR_END		=	\033[0m

# --------------------------------- Makefile Body ---------------------------------- #
.PHONY: all msg clear clean fclean re

all: $(MLX42) $(NAME)

#- Creates the libmlx42.a library.													-#
$(MLX42):
	@echo "$(COLOUR_GREEN)$(MLX42_PDIR) - $(CMLX42_LIB) compilation.\n$(COLOUR_END)"
	@echo "$(COLOUR_BLUE)#--------------------------------------------------#\n"
	@cmake $(MLX42_PDIR) -B $(MLX42_PDIR)/build && make -s -C $(MLX42_PDIR)/build -j4
	@echo "$(COLOUR_BLUE)\n#--------------------------------------------------#\n"
	@echo "$(COLOUR_GREEN)$(MLX42_PDIR) - $(CMLX42_LIB) initialized.$(COLOUR_END)"

#- Creates the libft.a library.														-#
$(LIBFT):
	@echo "$(COLOUR_GREEN)$(CNAME) - $(CLIBFT) compilation.\n$(COLOUR_END)"
	@echo "$(COLOUR_BLUE)#--------------------------------------------------#\n"
	@make -s -C $(MAKENM)
	@echo "$(COLOUR_BLUE)\n#--------------------------------------------------#\n"
	@echo "$(COLOUR_GREEN)$(CNAME) - $(CLIBFT) initialized.$(COLOUR_END)"

#- Creates the program library with all the objects minus the main object			-# 
$(LIBEXE): $(LIBFT) $(OBJDIR) $(OBJ) $(MOBJ)
	@echo -n "$(COLOUR_GREEN)"
	@cp $(MAKENM)/$(LIBFT) $(LIBEXE)
	@ar rcs $(LIBEXE) $(OBJ)

#- Creates a directory named $(OBJDIR).												-#
$(OBJDIR):
	@echo "\n$(COLOUR_GREEN)$(CNAME) - Object compilation:\n$(COLOUR_END)"
	@mkdir -p $@
#
#- Compiles each %(generic).c source into its respective %(generic).o				-#
$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(COLOUR_CIAN)\t-$@ created.$(COLOUR_END)"
#
#- Compiles the main object with the program library into the final executable.		-#
$(NAME): $(LIBEXE)
	@$(CC) $(CFLAGS) $(MLX42_FLAG) -o $(NAME) $(MOBJ) $(LIBEXE) $(MLX42_PLIB) -lm
	@echo "\n$(COLOUR_GREEN)$(CNAME) - Program ready.$(COLOUR_END)"
#
msg:
	@echo "$(COLOUR_GREEN)\n$(CBONUS) - Bonus program compilation.\n$(COLOUR_END)"
	@echo "$(COLOUR_BLUE)#--------------------------------------------------#\n"
#
clear:
	@clear
#
#- Compiles the bonus objects and the program library into the bonus executable.	-#
bonus: $(NAME) msg $(BOBJ)
	@$(CC) $(CFLAGS) -o $(BONUS) $(BOBJ) $(LIBEXE)
	@echo "$(COLOUR_BLUE)\n#--------------------------------------------------#\n"
	@echo "$(COLOUR_GREEN)$(CBONUS) - Bonus program ready.$(COLOUR_END)"
#
#- Removes every object inside $(OBJDIR) and the directory itself.					-#
clean:
	@make clean -s -C $(MAKENM)
	@make -s -C $(MLX42_PDIR)/build clean
	@echo "$(COLOUR_RED)$(MLX42_PDIR) - Object cleaning complete.\n$(COLOUR_END)"
	@rm -rf $(OBJDIR)
	@echo "$(COLOUR_RED)$(CNAME) - Object cleaning complete.\n$(COLOUR_END)"
#
#- Removes the final files made with this makefile, executing clean as well.		-#
fclean:
	@make fclean -s -C $(MAKENM)
	@rm -rf $(MLX42_PDIR)/build
	@echo "$(COLOUR_RED)$(MLX42_PDIR) - Object cleaning complete.\n$(COLOUR_END)"
	@rm -rf $(OBJDIR)
	@echo "$(COLOUR_RED)$(CNAME) - Object cleaning complete.\n$(COLOUR_END)"
	@rm -f $(NAME)
	@rm -f $(BONUS)
	@rm -f $(LIBEXE)
	@echo "$(COLOUR_RED)$(CNAME) - Files removed.\n$(COLOUR_END)"
#
#- Restarts the Makefile. Erases everything to default, and executes again.			-#
re: clear fclean all