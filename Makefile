OBJ = constructor.o create.o create_file.o esh_main.o get_status.o handle_input.o list_dir_contents.o read_file.o read_block.o split.o update_status.o write_block.o create_directory.o change_directory.o print_working_directory.o find_blocks.o

DEP = esh_deps.h
CC  = g++
CFLAGS = -std=c++11 #-static-libstdc++

all: $(OBJ) $(DEP)
	$(CC) $(CFLAGS) -o ESH $(OBJ)

%.o: %.cpp $(DEP)

	g++ $(CFLAGS) -g -c -o $@ $<


clean:write_block
	@rm -f *.o
	@rm -f *.gch
	@rm -f *.bin
	@rm ESH
