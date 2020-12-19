exce.o : main.cpp pml_hash.cpp pml_hash.h
	g++ -Wall main.cpp pml_hash.cpp -o exce.o -lpmem

.PHONY : clean
	
clean:
	rm exce.o