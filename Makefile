all: .cmake


bin:
	echo creating bin directory
	mkdir bin

.cmake: bin
	@cd bin && cmake .. && make


clean:
	echo removing bin directory
	rm -r bin
