COMPILER = g++

ALLOBJECTS = gtokenizer.o

gtokenizer: $(ALLOBJECTS)
	${COMPILER}  -o gtokenizer $(ALLOBJECTS)

gtokenizer.o: gtokenizer.cpp
	${COMPILER}  -c gtokenizer.cpp


clean:
	rm -f gtokenizer.o gtokenizer
