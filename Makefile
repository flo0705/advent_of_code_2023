all: build run

build:
	g++ $(AOC_DAY).cpp -O3 -o bin/$(AOC_DAY)

run:
	bin/$(AOC_DAY) inputs/$(AOC_DAY).txt
