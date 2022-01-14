NAME = vector
SRCS_DIR = ./
SRCS = test-vector.cpp
FLAGS = -std=c++98 -Wall -Wextra -Werror
OBJS_DIR 	= 	objects/
OBJ 		= 	$(SRCS:.cpp=.o)
OBJS 		= 	$(addprefix $(OBJS_DIR), $(OBJ))

$(OBJS_DIR)%.o :	$(SRCS_DIR)%.cpp
	@mkdir -p $(OBJS_DIR)
	@echo "\033[0;33mCompiling: $<"
	@clang++ $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@clang++ $(FLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	@echo "\033[0;31mCleaning: $(OBJS_DIR)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "\033[0;31mCleaning: $(NAME)"
	@rm -f $(NAME)

re: fclean all