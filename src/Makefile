SRC_DIR = MLP/
TEXI2DVI = makeinfo --html
SUP = --suppress=

CC=g++ -std=c++17
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	CC += -D OS_MAC
else
	CC += -D OS_LINUX
endif

all: install

uninstall:
	@rm -rf build

install: uninstall
	@mkdir build
	@cmake $(SRC_DIR)CMakeLists.txt 
	@make -C $(SRC_DIR) 
	@cp -r $(SRC_DIR)MLP build/MLP
	@make clean -C $(SRC_DIR)

dvi:
	$(TEXI2DVI) Documentation.texi

linter:
	@cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg 
	@python3 ../materials/linters/cpplint.py --filter=-runtime/references --extensions=cpp $(SRC_DIR)*.cpp 
	@python3 ../materials/linters/cpplint.py  --extensions=cpp $(SRC_DIR)*.h

cppcheck:
	cppcheck --enable=all $(SUP)useStlAlgorithm $(SUP)unusedFunction $(SUP)missingInclude $(SRC_DIR)*.cpp

dist: 
	@cmake $(SRC_DIR)CMakeLists.txt 
	@make -C $(SRC_DIR) 
	@tar -zcf MLP.tar $(SRC_DIR)MLP 
	@make clean -C $(SRC_DIR)

gcov_report:
	$(CC) --coverage -o testresult $(files_for_test) -lm -lgtest -lpthread
	./testresult
	lcov -t "testresult" -o testresult.info -c -d .
	genhtml -o report testresult.info
	open ./report/index.html

tests:
ifeq ($(OS), Darwin)
	$(CC) -o tests $(files_for_test) -lm -lgtest -lpthread
else
	$(CC) -o tests $(files_for_test) -lm -lgtest -lpthread
endif
	./tests
	rm -rf tests
test: tests

clean:
	@rm -rf Documentation
	rm -rf tests report *.gcda *.gcno testresult *.info