
all: compile run

compile: tower.cpp
	g++ -std=c++11 tower.cpp -o tower

run: compile
	./tower