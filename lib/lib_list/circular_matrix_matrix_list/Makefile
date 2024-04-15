NAME			:= ../lib_list.a

SRC				:= ./src/ft_add_node_m_back.c\
				./src/ft_add_node_m_front.c\
				./src/init_matrix_matrix_lst.c\
				./src/init_node_m_mtrx_lst.c\
				./src/remove_mlst_front.c\
				./src/remove_mlst_back.c\
				./src/remove_especific_matrix.c\
				./src/ft_delete_mtrx_mtrx_lst.c

NUM_FILES		:= $(words $(SRC))
OBJS			:= ./objs_matrix_matrix_list
INCLUDES		:= -I ./include -I ../circular_matrix_list/include -I ../circular_linked_list/include
O_FILE			:= $(SRC:%.c=$(OBJS)/%.o)
CC				:= cc
CFLAGS 			:= -Wall -Werror -Wextra
O_FLAGS 		:= -c
CMD_CLEAN		:= rm -Rf

all : $(NAME)

$(NAME): $(O_FILE)
	@ar -rc $(NAME) $(O_FILE)
	@echo ""

$(OBJS)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(INCLUDES) $(O_FLAGS) $(CFLAGS) $< -o $@
	@$(eval COUNT := $(shell echo $$(($(COUNT)+1))))
	@printf "matrix_matrix_list   [%s]\r" $(shell echo 	"$$(($(COUNT) * 100 / $(NUM_FILES)))%")
	@sleep 0.1

clean:
	@$(CMD_CLEAN) $(OBJS)

fclean: clean
	@$(CMD_CLEAN) $(NAME)

re: fclean all

.PHONI: all clean fclean re
