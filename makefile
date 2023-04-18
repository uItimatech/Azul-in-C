OBJS	= main.o console_handler.o game_handler.o tile_handler.o input_handler.o
SOURCE	= main.c console_handler.c game_handler.c tile_handler.c input_handler.c
HEADER	= console_handler.h game_handler.h tile_handler.h input_handler.h
OUT	= main
CC	 = gcc
FLAGS	 = -g -Wall -Wextra

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

console_handler.o: console_handler.c
	$(CC) $(FLAGS) console_handler.c 

game_handler.o: game_handler.c
	$(CC) $(FLAGS) game_handler.c 

tile_handler.o: tile_handler.c
	$(CC) $(FLAGS) tile_handler.c 

input_handler.o: input_handler.c
	$(CC) $(FLAGS) input_handler.c 


clean:
	rm -f $(OBJS) $(OUT)