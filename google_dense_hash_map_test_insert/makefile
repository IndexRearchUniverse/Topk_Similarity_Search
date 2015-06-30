COMPILER = g++
CCINCLUDES = -I.
ALLOBJECTS = main.o dense_hash_test.o 

dense_hash_test: $(ALLOBJECTS)
	${COMPILER}  -o dense_hash_test $(ALLOBJECTS)

main.o: main.cpp
	${COMPILER} ${CCINCLUDES} -c main.cpp


dense_hash_test.o: dense_hash_test.cpp
	${COMPILER} ${CCINCLUDES} -c dense_hash_test.cpp


clean:
	rm -f main.o dense_hash_test.o dense_hash_test
