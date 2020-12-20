NAME := turing
CC := g++
OBJS := turing.cpp tm.cpp tm.h 

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

.PHONY: debug clean

debug: $(OBJS)
	$(CC) -o $(NAME) -DDEBUG $(OBJS)

clean:
	-rm $(NAME)
