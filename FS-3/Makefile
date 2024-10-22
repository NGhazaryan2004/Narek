all: program

program: hacker-rm.o
	g++ -o program hacker-rm.o
hacker-rm.o:hacker-rm.cpp
	g++ -c hacker-rm.cpp -o hacker-rm.o
clear:
	rm -f hacker-rm.o program
