CC=g++ -std=c++17
SOURCE= circle.cpp glad.c constants.h
OPENGLFLAGS=-ldl -lglfw
PROJECT=circle



$(PROJECT):$(SOURCE)
	$(CC)  $(SOURCE) $(OPENGLFLAGS) -o $(PROJECT)
