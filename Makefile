CC=gcc
PRE=./src/
SRC=read_file.c util.c np_ftoa.c split.c np_atof.c np_atoi_base.c np_itoa_base.c np_itoa.c np_atoi.c 
SRCS=$(addprefix $(PRE), $(SRC))
OBJ=$(SRCS:.c=.o)
CFLAG=-ggdb -Wall -Wextra -Werror
LIB=-lm
INCLUDE=-I ./include/
MAIN=main.c
BIN=./bin/main
CSV_BIN=./bin/csvmain
all: setup $(BIN) tests clean

.c.o:
	$(CC) $(CFLAG) $(INCLUDE) -c $< -o $@ $(LIB) 

setup:
	mkdir ./bin/ -p

$(BIN): $(OBJ) $(MAIN) 
	$(CC) $(CFLAG) $(INCLUDE) $^ $(LIB) -o $@

tests: $(OBJ)
	$(CC) $(CFLAG) $(INCLUDE) $^ ./tests/csv_parser.c -o $(CSV_BIN) $(LIB) 

clean:
	rm $(OBJ)

fclean: clean
	rm $(BIN)
