INC= minilibx-linux/libmlx.a libft/libft.a

NAME = cub3D
SRC = ${wildcard src/*.c}
OBJ = $(SRC:.c=.o)
CC = cc

LFLAGS = -lX11 -lXext -lm
FLAGS = -Wall -Werror -Wextra

# ------------------------------ Colors ------------------------------

BOLD_PURPLE     =       \033[1;35m

BOLD_CYAN       =       \033[1;36m

BOLD_YELLOW     =       \033[1;33m

NO_COLOR        =       \033[0m

# ------------------------------ Messages ------------------------------

HEADER_NAME		=		$(HEADER_TOP) $(HEADER_TOP_MID) $(HEADER_MID)$(HEADER_BOT)

HEADER_COMP     =       echo "\n🌐 $(BOLD_YELLOW)Cub3D $(NO_COLOR)by jcasades & ltressen\n\n"

COMP_START      =       printf "\n🚧 $(BOLD_YELLOW)Make: $(NO_COLOR)Debut de compilation...\r"

EXE_READY       =       echo "\n\n📟 Compilation de $(BOLD_YELLOW)Cub3D$(NO_COLOR) reussie !\n"

CLEANED         =       echo "\n💧 $(BOLD_YELLOW)Clean: $(NO_COLOR)Suppression des fichiers .o et de l'executable \n"

FCLEANED        =       echo "\n🧼 $(BOLD_YELLOW)Fclean: $(NO_COLOR)Suppression des fichiers .o et de l'executable \n"

NORM			= 		echo "\n📢 $(BOLD_CYAN)NORMINETTE: $(BOLD_YELLOW)Verification de la norme de tous les fichiers en .c !\n$(BOLD_PURPLE)"

NORM_H			=		echo "\n📣 $(BOLD_CYAN)NORMINETTE: $(BOLD_YELLOW)Verification de la norme du .h\n$(BOLD_PURPLE)"

# ------------------------------ Rules ------------------------------
MAKEFLAGS += --silent

$(NAME): comp_start $(OBJ)
	make -C libft/
	make -C minilibx-linux/
	rm -f libft/*.o
	@$(CC) $(FLAGS) $(OBJ) $(INC) $(LFLAGS) -o $(NAME)
	echo "\n"
	@$(EXE_READY)

all: $(NAME) norminette

norminette:
	$(NORM)
	norminette *.c
	$(NORM_H)
	norminette -R checkDefine cub3d.h
	echo "\n"

comp_start:
	@$(HEADER_COMP)
	@$(COMP_START)

clean:
	make clean -C libft/
	make clean -C minilibx-linux/
	$(CLEANED)
	rm -f $(NAME) $(OBJ) *~ core *.core

fclean: clean
	make fclean -C libft/
	rm -f $(NAME) $(OBJ) *~ core *.core
	$(FCLEANED)

re: clean all

bonus: re

%.o: %.c
	@printf "🚧 $(BOLD_YELLOW)Make: $(NO_COLOR)Compilation des fichiers : %-33.33s\r$(NO_COLOR)" $@
	@${CC} ${FLAGS} -c $< -o $@
