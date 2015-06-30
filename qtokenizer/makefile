COMPILER = g++

ALLOBJECTS = qtokenizer.o main.o

qtokenizer: $(ALLOBJECTS)
	${COMPILER}  -o qtokenizer $(ALLOBJECTS)

qtokenizer.o: qtokenizer.cpp
	${COMPILER}  -c qtokenizer.cpp
main.o: main.cpp
	${COMPILER}  -c main.cpp

clean:
	rm -f qtokenizer.o main.o qtokenizer
