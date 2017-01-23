all: 
	g++ -c CPU.cpp CPUProgram.cpp main.cpp
	g++ CPUProgram.o CPU.o main.o -o myCpu
	./myCpu deneme.txt 1
clean:
	rm *.o myCpu
