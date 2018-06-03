OBJ  = ./obj
SRC  = ./src
INC  = ./include
BIN  = gc
OBJS = $(addprefix $(OBJ), $(subst .c,.o,$(subst $(SRC),,$(wildcard $(SRC)/*.c))))

all:
	mkdir -p $(OBJ)
	make gc

$(BIN): $(OBJS)
	gcc -o $@ $^ -I$(INC)

$(OBJ)/%.o: $(SRC)/%.c
	gcc -o $@ -c $< -I$(INC)

check:
	make $(BIN)
	valgrind --leak-check=yes --track-origins=yes ./$(BIN)

.PHONY: clean
clean:
	rm -f gc $(OBJ)/*.o
