SRC_DIR = MLP/
TEXI2DVI = makeinfo --html

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