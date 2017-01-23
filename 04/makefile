all: 
	g++ -c Memory.cpp CPU.cpp CPUProgram.cpp Computer.cpp main.cpp 
	g++ CPUProgram.o Memory.o CPU.o Computer.o main.o -o myCpu
	./myCpu sort.txt 1
clean:
	rm *.o myCpu
