#Makefile

CXX = clang++
CPPFLAGS = -DP0 -I../Tests-auto -I.
CXXFLAGS = -std=c++11 -Wall -g 
VPATH = ../Tests-auto:.
CHECK_SRC = fecha_check.cpp cadena_check.cpp
CHECK_EXE = ${CHECK_SRC:.cpp=}
MAIN_EXE = test-P0-consola
TEST_EXE = test-P0-auto

all: test-P0-auto test-P0-consola

test-P0-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o \
	test-auto.o cadena.o fecha.o
	$(CXX) -o $@ $(LDFLAGS) $^

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

test-P0-consola: test-P0-consola.o fecha.o cadena.o
	$(CXX) -o $@ $(LDFLAGS) $^

test-P0-consola.o: fecha.hpp cadena.hpp

valgrind: ${MAIN_EXE} ${TEST_EXE}
	valgrind --leak-check=full ./${TEST_EXE} --logger=minimal
	valgrind --leak-check=full ./${MAIN_EXE}

check: $(CHECK_EXE)
	@./cadena_check cadena.cpp -- -std=${STD}
	@./fecha_check fecha.cpp -- -std=${STD}

fecha_check: 
	make -f Make_check.mk $@

cadena_check:
	make -f Make_check.mk $@

check_Fecha:
	make -f Make_check.mk $@

check_Cadena:
	make -f Make_check.mk $@

fecha.o: fecha.cpp fecha.hpp
cadena.o: cadena.cpp cadena.hpp

clean:
	$(RM) *.o test-P0-consola test-P0-auto
