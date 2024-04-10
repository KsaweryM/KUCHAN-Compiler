.PHONY: all clean run

all: build/KUCHAN

build/KUCHAN: build/parser_y.c build/scanner_l.c $(wildcard src/*.cpp)
	mkdir -p build
	g++ -g -I . $^ `llvm-config --cxxflags --ldflags --system-libs --libs core` -lfl -o $@

build/parser_y.c: src/parser.y
	mkdir -p build
	bison -o $@ -d $<

build/scanner_l.c: src/scanner.l
	mkdir -p build
	flex -o $@ $<

clean:
	rm -rf build

run: build/KUCHAN
	./build/KUCHAN

compile:
	llc build/main.ll -o build/main.s
	gcc -no-pie build/main.s -o build/main.out