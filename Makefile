# *********************************************************** #
#                                                             #
#           :::      ::::::::                   :::::::       #
#         :+:      :+:    :+:               :+:+:      :+:    #
#       +:+ +:+         +:+              +:+:+:+              #
#     +#+  +:+       +#+       \\//      +#+#+     #+#+#+     #
#   +#+#+#+#+#+   +#+          //\\       +#+#+#   +#  #+     #
#        #+#    #+#                        #+#+#+#+#  +#      #
#       ###   ########.fr                         ####        #
#                                                             #
# *********************************************************** #

NAME	= Cub3D
SRCS	= ft_launcher.c		\
		ft_gnl.c			\
		ft_draw.c			\
		ft_dda.c	 		\
		ft_bmp.c			\
		ft_check_contours.c	\
		ft_draw_sprites.c	\
		ft_game_loop.c		\
		ft_parse_info.c		\
		ft_parse_map.c		\
		ft_parse_textures.c	\
		ft_terminate.c		\

CFLAGS	= -Wall -Wextra -Werror
OBJS	= ${SRCS:.c=.o}

all:		${NAME}

tag:
		@echo "${_CYAN}# *********************************************************** #${_END}"
		@echo "${_CYAN}#                                                             #${_END}"
		@echo "${_CYAN}#           :::      ::::::::                   :::::::       #${_END}"
		@echo "${_CYAN}#         :+:      :+:    :+:               :+:+:      :+:    #${_END}"
		@echo "${_CYAN}#       +:+ +:+         +:+              +:+:+:+              #${_END}"
		@echo "${_CYAN}#     +#+  +:+       +#+                 +#+#+     #+#+#+     #${_END}"
		@echo "${_CYAN}#   +#+#+#+#+#+   +#+             X       +#+#+#   +#  #+     #${_END}"
		@echo "${_CYAN}#        #+#    #+#                        #+#+#+#+#  +#      #${_END}"
		@echo "${_CYAN}#       ###   ########.fr                         ####        #${_END}"
		@echo "${_CYAN}#                                                             #${_END}"
		@echo "${_CYAN}# *********************************************************** #${_END}"
		@echo "${_GREEN}Building objs${_END}"

$(NAME):	tag	${OBJS}
		@echo "${_RED}Compiling cub3d${_END}"
		@gcc ${OBJS} -I mlx libmlx.dylib -framework OpenGL -framework AppKit -o $(NAME)
		@echo "${_YELLOW}Done.${_END}"

%.o:%.c
		@gcc -Wall -Wextra -Werror -Imlx -Iinc -Ilibft -c $< -o $@

clean:	
		@echo "${_PURPLE}Removing objs${_END}"
		@rm -f ${OBJS}

fclean:		clean
		@echo "${_BLUE}Removing ${NAME}${_END}"
		@rm -f ${NAME}

re:		fclean all

.PHONY:		clean fclean

# This is a minimal set of ANSI/VT100 color codes
_END=$'\x1b[0m
_BOLD=$'\x1b[1m
_UNDER=$'\x1b[4m
_REV=$'\x1b[7m

# Colors
_GREY=$'\x1b[30m
_RED=$'\x1b[31m
_GREEN=$'\x1b[32m
_YELLOW=$'\x1b[33m
_BLUE=$'\x1b[34m
_PURPLE=$'\x1b[35m
_CYAN=$'\x1b[36m
_WHITE=$'\x1b[37m

# Inverted, i.e. colored backgrounds
_IGREY=$'\x1b[40m
_IRED=$'\x1b[41m
_IGREEN=$'\x1b[42m
_IYELLOW=$'\x1b[43m
_IBLUE=$'\x1b[44m
_IPURPLE=$'\x1b[45m
_ICYAN=$'\x1b[46m
_IWHITE=$'\x1b[47m
