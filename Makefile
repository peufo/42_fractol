NAME			=	fractol
DIR_SRC			=	./src
DIR_BUILD		=	./build
SOURCES			=	events.c image.c main.c math.c render.c view.c zoom.c 
SOURCES_NAME	=	$(basename $(SOURCES))
OBJECTS			=	$(addsuffix .o, $(addprefix $(DIR_BUILD)/, $(SOURCES_NAME)))
FLAGS			=	-Wall -Wextra -Werror

FT_PRINTF		=	./lib/ft_printf
ifeq ($(shell uname),Darwin)
	LIBX			=	./lib/minilibx_opengl
	LIBS_INCLUDE	=	-I$(FT_PRINTF) -I$(LIBX)
	LIBS_LINK_DIR	=	-L$(FT_PRINTF) -L$(LIBX) 
	LIBS_LINK		=	-lftprintf -lmlx -framework OpenGL -framework AppKit
else
	LIBX			=	./lib/minilibx-linux
	LIBS_INCLUDE	=	-I$(FT_PRINTF) -I$(LIBX) -I/usr/include
	LIBS_LINK_DIR	=	-L$(FT_PRINTF) -L$(LIBX) -L/usr/lib  
	LIBS_LINK		=	-lftprintf -lmlx -lXext -lX11 -lm -lz
endif

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(FT_PRINTF)
	@make -C $(LIBX)
	@cc $(OBJECTS) $(FLAGS) $(LIBS_LINK_DIR) $(LIBS_LINK) -o $@

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c | $(DIR_BUILD)
	@cc $(FLAGS) $(LIBS_INCLUDE) -c $^ -o $@

$(DIR_BUILD):
	@mkdir -p $@

clean:
	make clean -C $(FT_PRINTF)
	rm -rf $(DIR_BUILD)

fclean: clean
	make fclean -C $(FT_PRINTF)
	rm -f $(NAME)

re: fclean all
	make re -C $(FT_PRINTF)
