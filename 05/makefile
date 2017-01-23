all: 
	g++ -c Memory.cpp CPU.cpp CPUProgram.cpp Computer.cpp _mainTester.cpp 
	g++ CPUProgram.o Memory.o CPU.o Computer.o _mainTester.o -o myCpu
	./myCpu add.txt 1
clean:
	rm *.o myCpu
