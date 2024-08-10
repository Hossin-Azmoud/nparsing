CC=gcc
PRE=./src/
SRC=util.c np_float.c np_atoi_base.c np_itoa_base.c np_itoa.c np_atoi.c 
SRCS=$(addprefix $(PRE), $(SRC))
OBJ=$(SRCS:.c=.o)
CFLAG=-Wall -Wextra -Werror
LIB=-lm
INCLUDE=-I ./include/
MAIN=main.c
BIN=main

all: $(BIN)

.c.o:
	$(CC) $(CFLAG) $(INCLUDE) -c $< -o $@ $(LIB) 

$(BIN): $(OBJ) $(MAIN) 
	$(CC) $(CFLAG) $(INCLUDE) $^ $(LIB) -o $@

clean:
	rm $(OBJ)

fclean: clean
	rm $(BIN)
