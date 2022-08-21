SRC_DIR = MLP/
TEXI2DVI = makeinfo --html
SUP = --suppress=

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

cppcheck:
	cppcheck --enable=all $(SUP)useStlAlgorithm $(SUP)unusedFunction $(SUP)missingInclude $(SRC_DIR)*.cpp

dist: 
	@cmake $(SRC_DIR)CMakeLists.txt 
	@make -C $(SRC_DIR) 
	@tar -zcf MLP.tar $(SRC_DIR)MLP 
	@make clean -C $(SRC_DIR)


