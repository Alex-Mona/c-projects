CC= gcc -std=c11 -D_GNU_SOURCE
WWW= -Wall -Wextra -Werror
CAT= s21_cat.c

all: s21_cat

s21_cat:
	$(CC) $(WWW) $(CAT) -o s21_cat

autotest:
	chmod 777 t_cat.sh
	./t_cat.sh

test:
	chmod 777 tests.sh
	./tests.sh

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extensions=c *.c
	rm -rf *.cfg

leaks:
	CK_FORK=no leaks --atExit -- ./s21_cat

valgrind:
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./s21_cat

install_valgrind:
	brew install --HEAD LouisBrunner/valgrind/valgrind

install_cppcheck:
	brew install cppcheck

rebuild:
	make clean
	make all
	rm -rf  *.o *.a

clean:
	rm -rf s21_cat
	rm -rf *.a *.out *.o log.txt RESULT_VALGRIND.txt