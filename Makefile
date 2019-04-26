OBJECTS = main.cpp useful_functions.cpp mode_add.cpp mode_delete.cpp

main: $(OBJECTS)
	g++ $(OBJECTS) -o main
