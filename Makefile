all: build run

build:
	clang++ -Wall -Wno-extra-qualification -I . -o main main.cpp ptsd.cpp

run:
	./main -h -json idk.js