COMPILER = g++
CCINCLUDES = -I.
ALLOBJECTS = main.o google_hash_test.o 

google_hash_test: $(ALLOBJECTS)
	${COMPILER}  -o google_hash_test $(ALLOBJECTS)

main.o: main.cpp
	${COMPILER} ${CCINCLUDES} -c main.cpp


google_hash_test.o: google_hash_test.cpp
	${COMPILER} ${CCINCLUDES} -c google_hash_test.cpp


clean:
	rm -f main.o google_hash_test.o
