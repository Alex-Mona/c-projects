CC= gcc -std=c11 -D_GNU_SOURCE
WWW= -Wall -Wextra -Werror
GREP= s21_grep.c

all: s21_grep

s21_grep:
	$(CC) $(WWW) $(GREP) -o s21_grep

test:
	chmod 777 test.sh
	./test.sh

autotest:
	chmod 777 t_grep.sh
	./t_grep.sh

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extension=c *.c
	python3 ../../materials/linters/cpplint.py --extension=c *.h
	rm -rf *.cfg

leaks:
	CK_FORK=no leaks --atExit -- ./s21_grep -e on4fdase -e twogsdfgsdf s21_grep.c -f pattern.txt

valgrind:
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./s21_grep -e while -e void s21_grep.c Makefile -o -h -n -f pattern.txt

install_valgrind:
	brew install --HEAD LouisBrunner/valgrind/valgrind

install_cppcheck:
	brew install cppcheck

clean:
	rm -rf s21_grep
	rm -rf *.a *.out *.o log.txt RESULT_VALGRIND.txt

rebuild:
	make clean
	make all
	rm -rf  *.o *.a