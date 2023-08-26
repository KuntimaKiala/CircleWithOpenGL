CC=g++ -std=c++17
SOURCE= circle.cpp glad.c
OPENGLFLAGS=-ldl -lglfw
PROJECT=circle



$(PROJECT):$(SOURCE)
	$(CC)  $(SOURCE) $(OPENGLFLAGS) -o $(PROJECT)
