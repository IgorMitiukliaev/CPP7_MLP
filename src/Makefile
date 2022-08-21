files_for_test = test/test.cpp MLP/graphneuralnetwork.cpp MLP/matrix_neural_network.cpp MLP/matrix.cpp
files_for_cppcheck = MLP/controller.h \
					 MLP/controller.cpp \
					 MLP/model.h \
					 MLP/model.cpp \
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

clean:
	@rm -rf Documentation

linter:
	@cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg 
	@python3 ../materials/linters/cpplint.py --extensions=cpp $(SRC_DIR)*.cpp 
	@python3 ../materials/linters/cpplint.py --extensions=cpp $(SRC_DIR)*.h

cppcheck1:
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

cpplint:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --filter=-runtime/references --extension=cpp *.cpp ./*/*.cpp
	python3 ../materials/linters/cpplint.py --filter=-runtime/references --extension=h ./*/*.h
	rm CPPLINT.cfg

cppcheck2:
	cppcheck --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction $(files_for_cppcheck)

clean:
	rm -rf tests report *.gcda *.gcno testresult *.info