all: .cmake

build:
	@echo creating build directory
	mkdir build

.cmake: build
	@cd build && cmake .. && make

clean:
	@echo removing build directory
	rm -r build

test: .cmake
	build/src/test/test_all

check: test

