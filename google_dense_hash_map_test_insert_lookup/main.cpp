#include <sys/time.h>

#include "google_hash_test.h"

int main(int argc , char* argv[])
{

	cerr << "========BEFIN TEST========" << endl;
	test hash_test;
	hash_test.DataReader(argv[1]);
	hash_test.TimeCount();
	cerr << "=========END TEST==========" << endl;
	return 0;
}


