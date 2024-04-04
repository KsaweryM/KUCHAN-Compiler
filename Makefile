make:
	mkdir -p build
	bison -o build/parser_y.c -d src/parser.y
	flex -o build/scanner_l.c src/scanner.l
	g++ -I . src/*.cpp build/parser_y.c build/scanner_l.c -o build/KUCHAN -lfl

clean:
	rm -rf build

run:
	./build/KUCHAN