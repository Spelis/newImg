windows:
	mkdir -p o
	windres nimg.rc -O coff -o ./o/nimg.res
	g++ -c -o ./o/nimg.o main.cpp -Wall
	g++ ./o/nimg.o -o ./o/nimg ./o/nimg.res

linux:
	mkdir -p o
	g++ -o ./o/nimg main.cpp -Wall

clean:
	rm -rf ./o
