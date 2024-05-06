NAME			:= ../lib_list.a

SRC				:= ./src/init_list.c\
				./src/init_node.c\
				./src/create_node_add_back_lst.c\
				./src/create_node_add_front_lst.c\
				./src/remove_node_front.c\
				./src/remove_node_back.c\
				./src/remove_specific_node.c\
				./src/remove_specific_content.c\
				./src/delete_list.c\
				./src/add_node_back.c\
				./src/add_node_front.c\
				./src/create_string_list.c\
				./src/remove_and_return_node.c\
				./src/insert_nodes_between.c\
				./src/cpy_lst_to_array.c\
				./src/find_str_in_list.c\
				./src/create_lst_add_str.c\
				./src/put_lst_fd.c\
				./src/ft_duplst.c\
				./src/ft_cpynode.c

NUM_FILES		:= $(words $(SRC))
OBJS			:= ./objs_circular_linked_list
INCLUDES		:= -I ./include
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
	@printf "linked_list progress [%s]\r" $(shell echo 	"$$(($(COUNT) * 100 / $(NUM_FILES)))%")
	@sleep 0.1

clean:
	@$(CMD_CLEAN) $(OBJS)

fclean: clean
	@$(CMD_CLEAN) $(NAME)

re: fclean all

.PHONI: all clean fclean re
