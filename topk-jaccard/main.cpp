#include <sys/time.h>
#include "topk.h"
/**
* Program running command
* @param {int}
*   The topk function,inlcude topk-stardard,topk-hash,topk-earlyterm,topk-multilen
* @param {char}
*   Simalarity function type. 
*   'j' or 'J' stand for Jaccrad similarity 
*   'c' or 'C' stand for Cosine similarity
* @param {int}
*   The k value, this is return most former k similarity candidate pairs.
* @param {char*}
*   The binary input file
* @param {int}
*   The maxdapth for suffix filtering,default value is 2.
* @param {int}
*   The block parameter when the function is topk-earlyterm.
* e.x.  ./topk-hash j 500 dblp.bin 2
**/
int main(int argc , char* argv[])
{
	if(argc < 4)
	{
		cerr << "Usage: topk [sim_func] [k] [binary_input_file] [maxdepth (optional)]" << endl;
		return 1;
	}

	topk topkInstance;
	if(argc >= 4 && argc < 5)
	{
		if(topkInstance.ReadParameters(argv[1], argv[2]))
		{
			cerr << "Similarity Function Missing!" << endl;
			return 1;
		}
	}
	else if(argc >= 5 && argc < 6)
	{
		if(topkInstance.ReadParameters(argv[1], argv[2], argv[4]))
		{
			cerr << "Similarity Function Missing!" << endl;
			return 1;
		}
	}
	else
	{
		if(topkInstance.ReadParameters(argv[1], argv[2], argv[4], argv[5]))
		{
			cerr << "Similarity Function Missing!" << endl;
			return 1;
		}
	}
	timeval timeStart, timeEnd;
	if(topkInstance.getConsine())
	{
		cerr << "###error: need jaccard, please input 'j' or 'J' " << endl;
		exit(1);
	}
	topkInstance.ReadDate(argv[3]);
	topkInstance.InitializeEvent();
	topkInstance.InitializeTempResults(topkInstance.getK() +1);
	topkInstance.BuildIndex();
	gettimeofday(&timeStart, NULL);
	cerr << "========= BEGIN JOIN (TIMER STARTED) ========" << endl;
	topkInstance.PerformTopk();
	cerr << "========== END JOIN (TIMER STOPPED) =========" << endl;
	gettimeofday(&timeEnd, NULL);
//	topkInstance.WriteResults();
	topkInstance.setFailtime(double(timeEnd.tv_sec - timeStart.tv_sec) + double(timeEnd.tv_usec - timeStart.tv_usec) / 1e6);
	topkInstance.CoutHashIndex();
//	cout << setiosflags(ios::fixed) << setprecision(3) << double(timeEnd.tv_sec - timeStart.tv_sec) + double(timeEnd.tv_usec - timeStart.tv_usec) / 1e6 << endl;
//	cerr << "#总共用时为:  " << setiosflags(ios::fixed) << setprecision(3) << double(timeEnd.tv_sec - timeStart.tv_sec) + double(timeEnd.tv_usec - timeStart.tv_usec) / 1e6 << endl;
	return 0;
}

