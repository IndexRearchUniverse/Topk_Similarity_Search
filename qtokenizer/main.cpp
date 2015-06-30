#include "qtokenizer.h"

int main(int argc, char* argv[])
{
	int gram;
	const char *out;
	string output;
	qtokenizer tokenInstance;

	gram = atoi(argv[1]);
	output = argv[2];
	output.append(".").append(argv[1]).append("gram.bin");
	out = output.c_str();

	cerr << "=================<< BEGIN EXECUTE >>=================" << endl;

	tokenInstance.ReadData(argv[2], gram);
	tokenInstance.AddDF();
	tokenInstance.SortEachRecord();
	tokenInstance.SortAndWrite(out);
	cerr << "*********< 信息统计 >***********" << endl;
	cerr << "Record Number: " << tokenInstance.recordNum << endl;
	cerr << "Token Number:  " << tokenInstance.tokenNum << endl;
	cerr << "maxinum Length: " << tokenInstance.maxLength << endl;
	cerr << "mininum Length: " << tokenInstance.minLength << endl;
	cerr << "*******************************" << endl;
	cerr << "=================<< END EXECUTE >>==================" << endl;
	return 0;
}



