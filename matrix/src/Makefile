GCC=gcc
CFLAGS= -Wall -Werror -Wextra -std=c11
LIBS= -lcheck
LFLAGS= -fprofile-arcs -ftest-coverage
LINUX = -lrt -lpthread -lm -lsubunit
OS=$(shell uname -s)

all: clean s21_matrix.a test

s21_matrix.o:
	$(GCC) $(CFLAGS) -c s21_matrix.c -o s21_matrix.o

s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o
	cp s21_matrix.a libs21_matrix.a
	cp s21_matrix.a ls21_matrix.a
	ranlib libs21_matrix.a
	ranlib ls21_matrix.a

test: s21_matrix.a
ifeq ($(OS), Darwin)
	$(GCC) $(CFLAGS) test.c s21_matrix.a -o test.out $(LIBS)
	./test.out
else
	$(GCC) $(CFLAGS) test.c s21_matrix.a -o test.out $(LIBS) $(LINUX)
	./test.out
endif

gcov_report: s21_matrix.c
ifeq ($(OS), Darwin)
	$(GCC) $(CFLAGS) $(LFLAGS) test.c s21_matrix.c -o test.out $(LIBS)
else
	$(GCC) $(CFLAGS) $(LFLAGS) test.c s21_matrix.c -o test.out $(LIBS) $(LINUX)
endif
	./test.out
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

open:
ifeq ($(OS), Darwin)
	open report/index.html
else
	xdg-open report/index.html
endif

valg: s21_matrix.a
ifeq ($(OS), Darwin)
	gcc $(WWW) test.c s21_matrix.a -o test $(LIBS)
	CK_FORK=no valgrind --leak-check=full -s ./test.out
else
	gcc $(WWW) test.c s21_matrix.a -o test $(LIBS) $(LINUX)
	K_FORK=no valgrind --leak-check=full -s ./test.out
endif

check:
	cp ../materials/linters/.clang-format .clang-format
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	clang-format -i *.c *.h
	sleep 0.5
	clang-format -i *.c *.h
	rm -rf .clang-format
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test.out
else
	valgrind ./test.out --leak-check=full
endif
	make clean

clean:
	rm -rf  *.a *.o *.gc* *.out *.info test.out test report

rebuild: clean all
