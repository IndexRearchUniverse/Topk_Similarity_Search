COMPILER = g++
CCINCLUDES = -I.
ALLOBJECTS = main.o index.o heap.o io.o topk-standard.o topk-hash.o
TOPKSTANDARDJECTS = main.o index.o heap.o io.o topk-standard.o
TOPKHASHJECTS = main.o index.o heap.o io.o topk-hash.o
TOPKEARLYTERMJECTS = main.o index.o heap.o io.o topk-earlyterm.o
TOPKMULTILENJECTS = main.o index.o heap.o io.o topk-multilen.o

all: $(TOPKSTANDARDJECTS) $(TOPKHASHJECTS) $(TOPKEARLYTERMJECTS) $(TOPKMULTILENJECTS)
	${COMPILER}  -o topk-standard $(TOPKSTANDARDJECTS)
	${COMPILER}  -o topk-hash $(TOPKHASHJECTS)
	${COMPILER}  -o topk-earlyterm $(TOPKEARLYTERMJECTS)
	${COMPILER}  -o topk-multilen $(TOPKMULTILENJECTS)

topk-standard: $(TOPKSTANDARDJECTS)
	${COMPILER}  -o topk-standard $(TOPKSTANDARDJECTS)

topk-hash: $(TOPKHASHJECTS)
	${COMPILER}  -o topk-hash $(TOPKHASHJECTS)

topk-earlyterm: $(TOPKEARLYTERMJECTS)
	${COMPILER}  -o topk-earlyterm $(TOPKEARLYTERMJECTS)

topk-multilen: $(TOPKMULTILENJECTS)
	${COMPILER}  -o topk-multilen $(TOPKMULTILENJECTS)

main.o: main.cpp
	${COMPILER} ${CCINCLUDES} -c main.cpp

io.o: io.cpp
	${COMPILER} ${CCINCLUDES} -c io.cpp

index.o: index.cpp
	${COMPILER} ${CCINCLUDES} -c index.cpp

heap.o: heap.cpp
	${COMPILER} ${CCINCLUDES} -c heap.cpp

topk-standard.o: topk-standard.cpp
	${COMPILER} ${CCINCLUDES} -c topk-standard.cpp

topk-hash.o: topk-hash.cpp
	${COMPILER} ${CCINCLUDES} -c topk-hash.cpp

topk-earlyterm.o: topk-earlyterm.cpp
	${COMPILER} ${CCINCLUDES} -c topk-earlyterm.cpp

topk-multilen.o: topk-multilen.cpp
	${COMPILER} ${CCINCLUDES} -c topk-multilen.cpp

clean:
	rm -f main.o io.o index.o heap.o topk-standard.o topk-hash.o topk-earlyterm.o topk-multilen.o












