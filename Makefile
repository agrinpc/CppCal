NAME		= calgen

CC			= c++
FLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

OBJDIR 		= obj
OUTDIR		= output

FILES		=	main \
				CppCal

SRC			= $(FILES:=.cpp)
OBJ			= $(addprefix $(OBJDIR)/, $(FILES:=.o))


all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(OPTS) -o $(NAME)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@mkdir -p $(OUTDIR)
	@$(CC) $(FLAGS) $(OPTS) -c $< -o $@

clean:
	@$(RM) $(OBJ) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME) $(OUTDIR)

re: fclean all

.PHONY: all clean fclean re