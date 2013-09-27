all: .cmake

build:
	@echo creating build directory
	mkdir build

.cmake: build
	@cd build && cmake .. && make

clean:
	@echo removing build directory
	rm -r build
	rm -r Michael_Gerow
	rm -r Michael_Gerow.zip

test: .cmake
	build/src/test/test_all

submission:
	mkdir Michael_Gerow && cp -r lib Michael_Gerow && cp -r src Michael_Gerow && cp CMakeLists.txt Michael_Gerow && cp Makefile Michael_Gerow && cp Readme.txt Michael_Gerow && cp setup.sh Michael_Gerow && zip -r Michael_Gerow.zip Michael_Gerow && rm -rf Michael_Gerow

check: test

