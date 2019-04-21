##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## makefile
##

SRC		=	src/main.cpp				\
			src/ModuleManager.cpp		\
			src/ncurse/MonitorNcurse.cpp\
			src/MonitorSfml.cpp		    \
			src/launch.cpp				\
			src/modules/DateModule.cpp	\
			src/modules/OSModule.cpp	\
			src/modules/CPUModule.cpp	\
			src/modules/NamesModule.cpp \
			src/modules/RAMModule.cpp   \
			src/components/Graph.cpp

NAME    =   MyGKrellm

CXXFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system -lncurses -lmenu -I include -std=c++14 -W -Wall -Wextra -g3

OBJ		=	$(SRC:%.cpp=%.o)

all:	$(NAME)

%.o: %.cpp
	g++ -c $^ -o $@ $(CXXFLAGS)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf */*.gcda
	rm -rf */*.gcno
	rm -rf $(OBJ)

re: fclean $(NAME)
