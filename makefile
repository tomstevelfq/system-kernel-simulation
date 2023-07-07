CC=gcc -g
RM=del
target=project3
Outputs=build\\
ofile=$(Outputs)memory.o $(Outputs)process.o $(Outputs)test.o $(Outputs)kernel.o $(Outputs)cycle.o

$(target):$(ofile)
	$(CC) $(ofile) -lstdc++ -o $(target)
$(Outputs)memory.o:memory.cpp
	$(CC) memory.cpp -c -lstdc++ -o $(Outputs)memory.o
$(Outputs)process.o:process.cpp
	$(CC) process.cpp -c -lstdc++ -o $(Outputs)process.o
$(Outputs)test.o:test.cpp
	$(CC) test.cpp -c -lstdc++ -o $(Outputs)test.o
$(Outputs)kernel.o:kernel.cpp
	$(CC) kernel.cpp -c -lstdc++ -o $(Outputs)kernel.o
$(Outputs)cycle.o:cycle.cpp
	$(CC) cycle.cpp -c -lstdc++ -o $(Outputs)cycle.o
clean:
	$(RM) $(ofile) $(target)