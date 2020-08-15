CXX = clang++
STD = c++17
CXXFLAGS = -std = c++11 -g -Wall -Wextra -pedantic
CPPFLAGS = -DP0 -I../Tests-auto -I.
VPATH = ../Tests-autoo:.
SRC = fecha.cpp test-auto.cpp test-caso0-fecha-auto.cpp test-P0-consola.cpp cadena.cpp


RMV = rm -f
OBJ = $(SRC:.cpp=.o)
EXE = test-P0-consola
AUTO = test-auto

all: ${EXE} ${AUTO}

run-auto: ${AUTO}
	./$<

test-consola: ${EXE}
	@./$<

run-dsl: fecha_check cadena_check 
		 ./fecha_check fecha.cpp -- -std=${STD}
		 ./cadena_check cadena.cpp -- -std=${STD}

fecha_check: fecha_check.cpp
	$(MAKE) -f Make_check.mk

${EXE}: fecha.o test-P0-consola.o
	$(CXX) $(CXXFLAGS) $^ -o $@

${AUTO}: test-caso0-fecha-auto.o test-auto.o fecha.o cadena.o test-caso0-cadena-auto.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

$(OBJ): $(SRC)

cadena_check: cadena_check.cpp
	${MAKE} -f Make_check.mk

limpia: 
	$(RMV) *.o
	$(MAKE) -f Make_check.mk clean