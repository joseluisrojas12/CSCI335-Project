OPTS=-O0

CXX       = g++
CPPFLAGS += $(OPTS) -std=c++11

#all:	test
all: demo_operation_sequence_reader

test:	main.o MatrixOperationBatchTester.o Matrix.h MatrixOperator.h Options.o Matrix.o
	$(CXX) $(CPPFLAGS) -o test main.o MatrixOperationBatchTester.o Options.o Matrix.o -pg

main.o:	main.cpp
	$(CXX) $(CPPFLAGS) -c -g -std=c++11 -MMD -MP -MF main.o.d main.cpp -pg

MatrixOperationBatchTester.o:	MatrixOperationBatchTester.cpp
	$(CXX) $(CPPFLAGS) -c -g -std=c++11 -MMD -MP -MF MatrixOperationBatchTester.o.d MatrixOperationBatchTester.cpp -pg

Matrix.o:	Matrix.cpp
	$(CXX) $(CPPFLAGS) -c -g -std=c++11 -MMD -MP -MF Matrix.o.d Matrix.cpp -pg

Options.o:	Options.cpp
	$(CXX) $(CPPFLAGS) -c -g -std=c++11 -MMD -MP -MF Options.o.d Options.cpp -pg

DemoOperationSequenceReader.o: DemoOperationSequenceReader.cpp
	g++ -c -g -std=c++11 -MMD -MP -MF DemoOperationSequenceReader.o.d -o DemoOperationSequenceReader.o DemoOperationSequenceReader.cpp -pg

operation_sequence_reader.o: operation_sequence_reader.c
	gcc -c -g -MMD -MP -MF operation_sequence_reader.o.d -o operation_sequence_reader.o operation_sequence_reader.c -pg

demo_operation_sequence_reader: main.o DemoOperationSequenceReader.o operation_sequence_reader.o
	g++ main.o DemoOperationSequenceReader.o operation_sequence_reader.o -o demo_operation_sequence_reader -pg

clean:
	rm -f *.o test results*
