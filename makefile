CC=g++ -g
RM=del
target=main.exe
Outputs=.\\
ofile=$(Outputs)memory.o $(Outputs)process.o $(Outputs)test.o

$(target):$(ofile)
	$(CC) $(ofile) -o $(target)
$(Outputs)memory.o:memory.cpp
	$(CC) memory.cpp -c -o $(Outputs)memory.o
$(Outputs)process.o:process.cpp
	$(CC) process.cpp -c -o $(Outputs)process.o
$(Outputs)test.o:test.cpp
	$(CC) test.cpp -c -o $(Outputs)test.o
clean:
	$(RM) $(ofile) $(target)