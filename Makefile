CXX  = g++-8
EXE = ipl_parser
CXXDEBUG = -g -Wall
CXXSTD = -std=c++11


.PHONY: all clean
all: parser lexer
	$(CXX) $(CXXDEBUG) $(CXXSTD) -o iplC driver.cpp ast.cpp parser.o scanner.o 

parser: parser.yy scanner.hh
	bison -d -v $<
	$(CXX) $(CXXDEBUG) $(CXXSTD)  -c parser.tab.cc -o parser.o 

lexer: scanner.l scanner.hh parser.tab.hh parser.tab.cc	
	flex++ --outfile=scanner.yy.cc  $<
	$(CXX)  $(CXXDEBUG) $(CXXSTD) -c scanner.yy.cc -o scanner.o

clean:
	rm -f parser.tab.cc parser.tab.hh position.hh scanner.o iplC parser.o parser.output scanner.yy.cc stack.hh Fl.h
