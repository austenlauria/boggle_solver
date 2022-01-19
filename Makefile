opt:
	g++ -O3 -o boggle_solver finder.cpp main.cpp

dbg:
	g++ -g -O0 -o boggle_solver finder.cpp main.cpp

clean:
	rm -f *.o boggle_solver
