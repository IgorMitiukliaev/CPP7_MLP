SRC_DIR = MLP/

all: install

uninstall:
	@rm -rf build

install: uninstall
	@mkdir build
	@cmake $(SRC_DIR)CMakeLists.txt 
	@make -C $(SRC_DIR) 
	@cp -r $(SRC_DIR)MLP build/MLP
	@make clean -C $(SRC_DIR)
