# Manual for Makefile
# https://www.gnu.org/software/make/manual/html_node/index.html
SERVER = server
CLIENT = client

SRC_SERV = server.c
SRC_CLNT = client.c
HEADER = minitalk.h
SRCDIR = ./
OBJDIR = ./obj/
OBJ_SERV = $(addprefix $(OBJDIR), $(notdir $(SRC_SERV:.c=.o)))
OBJ_CLNT = $(addprefix $(OBJDIR), $(notdir $(SRC_CLNT:.c=.o)))
OBJ_UTIL = $(addprefix $(OBJDIR), $(notdir $(SRC_UTIL:.c=.o)))
D_FILES += $(addprefix $(OBJDIR), $(notdir $(SRC_SERV:.c=.d)))
D_FILES += $(addprefix $(OBJDIR), $(notdir $(SRC_CLNT:.c=.d)))
D_FILES += $(addprefix $(OBJDIR), $(notdir $(SRC_UTIL:.c=.d)))
CC = gcc -Wall -Werror -Wextra
DEBUG = -g
OPTIMIZATION = -O2
LIB += -lft
LIBPATH += -L./libraries/libft/
LIBINC += -I./libraries/libft/

all: $(SERVER) $(CLIENT)

# translation of assembly language code into machine code
# -c, stops after assembly stage
# -MD lists both system header files and user header files, dependencies
# -MMD lists only user header files, dependencies
# $< the first prerequisite (usually a source file) main.c (dependency %.c)
# $@ is the name of the target being generated main.o (target %.o)
$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER) | obj
	$(CC) $(DEBUG) $(LIBINC) -c $< -o $@ -MMD

# linking stage
$(SERVER): $(OBJ_SERV)
	make -C ./libraries/libft/
	$(CC) $(OBJ_SERV) $(LIBPATH) $(LIB) $(LIBINC) -o $(SERVER)

$(CLIENT): $(OBJ_CLNT)
	make -C ./libraries/libft/
	$(CC) $(OBJ_CLNT) $(LIBPATH) $(LIB) $(LIBINC) -o $(CLIENT)

obj:
	mkdir -p $(OBJDIR)

include $(wildcard $(D_FILES))

bonus: all

norm:
	norminette $(SRC)

# rule for the cleaning
clean:
	make clean -C ./libraries/libft/
	rm -rf $(OBJDIR)

fclean:
	make fclean -C ./libraries/libft/
	rm -rf $(OBJDIR)
	rm -f $(SERVER)
	rm -f $(CLIENT)

# rule for rebuild a project
re: fclean all

# directory exceptions
.PHONY: all clean fclean norm re bonus
