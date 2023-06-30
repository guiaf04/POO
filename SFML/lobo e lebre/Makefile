all: compile link

compile:
	g++ -c main.cpp

link:
	g++ main.o -o main.exe -lsfml-graphics -lsfml-window -lsfml-system

run: main.exe
	./main.exe

clean:
	del -rf *.o main.exe