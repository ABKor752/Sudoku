PATH := /usr/um/gcc-6.2.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-6.2.0/lib64
LD_RUN_PATH := /usr/um/gcc-6.2.0/lib64

# This Makefile comes courtesy of the University of Michigan EECS 281 Makefile template

EXECUTABLE  = solver

CXX         = g++

CXXFLAGS = -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic 

SOURCES     = $(wildcard *.cpp)
SOURCES     := $(filter-out $(TESTSOURCES), $(SOURCES))

OBJECTS     = $(SOURCES:%.cpp=%.o)


$(EXECUTABLE): $(OBJECTS)
ifeq ($(EXECUTABLE), executable)
	@echo Edit EXECUTABLE variable in Makefile.
	@echo Using default a.out.
	$(CXX) $(CXXFLAGS) $(OBJECTS)
else
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)
endif

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(DEBUG) $(TESTS) \
	rm -Rf *.dSYM

sudoku.o: sudoku.cpp sudoku.h
main.o: main.cpp sudoku.h
