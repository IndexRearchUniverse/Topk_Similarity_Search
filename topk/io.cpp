#include <algorithm>
#include "topk.h"
/**
* Read binary file to struct joinRecord.
* @param {char*}
*  binnary file, The format is [id, word number, word1, word2, ..., wordn] 
**/
void topk::ReadDate(char* filename)
{
	int rid;
	int len;
	int line =0;
	int inputToken;
	int totalLen = 0;
	record inputRecord;
	FILE *fp;
	fp =  fopen(filename,"rb");
	while(fread(&rid, sizeof(int), 1, fp) == 1)
	{
		fread(&len, sizeof(int),1, fp);
		totalLen += len;
		inputRecord.line = line++;
		inputRecord.rid  = rid;
		inputRecord.len = len;
		inputRecord.moveRid = rid << 16;
//		inputRecord.pos = 0;
		inputRecord.prefix = 0;
		inputRecord.count = 0;
		inputRecord.bound = 1;
		inputRecord.tokenArray.clear();
		for(int i = 0; i < inputRecord.len; i++)
		{
			fread(&inputToken, sizeof(int), 1, fp);
			if(inputToken > tokenNum)
				tokenNum = inputToken;
			inputRecord.tokenArray.push_back(inputToken);
		}
		joinRecord.push_back(inputRecord);
		recordNum++;
	}
	fclose(fp);
	tokenNum++;

	//结果输出
	cerr<<"************<< Reading Record >>************"<<endl;
	cerr << "# Records: " << recordNum << endl;
	cerr << "# Average Record Size: " << double(totalLen) / recordNum << endl;
	cerr << "# Maximum Record Size: " << joinRecord[recordNum - 1].len << endl;
	cerr <<"********************************************\n"<<endl;

}
/**
* Read input Parameter.
* @param {char*}
*  The similarity function , 'j' or 'J' stand for 'Jaccard'; 'c' or 'C' represent 'Cosine'.
* @param {char*}
*  The value of k, stand for what we want to output the similarity pairs.  
**/
int topk::ReadParameters(char* sim_fun, char* inputk)
{
	if(sim_fun[0] == 'J' || sim_fun[0] == 'j') jaccard = 1;
	else if(sim_fun[0] == 'C' || sim_fun[0] == 'c') consine =1;
	else return 1;
	topk::inputk = atoi(inputk);
	cerr << "#Similarity Function: ";
	if(jaccard == 1) cerr<< "jaccard" <<endl;
	if(consine == 1) cerr << "consine" <<endl;
	cerr << "#you want top "<< inputk << " similarity pairs" <<endl;
	return 0;
}
/**
* Read input Parameter.
* @param {char*}
*  The similarity function , 'j' or 'J' stand for 'Jaccard'; 'c' or 'C' represent 'Cosine'.
* @param {char*}
*  The value of k, stand for what we want to output the similarity pairs.  
* @param {char*}
*  The max Depth of stuffix filtering.
**/
int topk::ReadParameters(char* sim_fun, char* inputk, char* maxDepth)
{
	if(sim_fun[0] == 'J' || sim_fun[0] == 'j') jaccard = 1;
	else if(sim_fun[0] == 'C'|| sim_fun[0] == 'c') consine = 1;
	else return 1;
	topk::inputk = atoi(inputk);
	topk::maxDepth = atoi(maxDepth);

	cerr << "#Similarity Function: ";
	if(jaccard == 1) cerr << "jaccard" <<endl;
	if(consine == 1) cerr << "consine" <<endl;
	cerr << "#you want top "<< inputk << " similarity pairs" <<endl;
	return 0;
}
/**
* Read input Parameter.
* @param {char*}
*  The similarity function , 'j' or 'J' stand for 'Jaccard'; 'c' or 'C' represent 'Cosine'.
* @param {char*}
*  The value of k, stand for what we want to output the similarity pairs.  
* @param {char*}
*  The max Depth of stuffix filtering.
* @param {char*}
*  The seg part parameter.
**/
int topk::ReadParameters(char* sim_fun, char* inputk, char* maxDepth, char* segPart)
{
	if(sim_fun[0] == 'J' || sim_fun[0] == 'j') jaccard = 1;
	else if(sim_fun[0] == 'C'|| sim_fun[0] == 'c') consine = 1;
	else return 1;
	topk::inputk = atoi(inputk);
	topk::maxDepth = atoi(maxDepth);
	topk::segPart = atoi(segPart);

	cerr << "#Similarity Function: ";
	if(jaccard == 1) cerr << "jaccard" <<endl;
	if(consine == 1) cerr << "consine" <<endl;
	cerr << "#you want top "<< inputk << " similarity pairs" <<endl;
	return 0;
}
/*
void topk::WriteResults()
{
	int i;
	vector<result>::iterator it;
	for (it = resultInstance.begin(); it != resultInstance.end(); ++it)
		cout << it->xrid << "\t" << it->yrid << "\t" << setiosflags(ios::fixed) << setprecision(3) << it->sim << endl;
}
*/
/**
* Output the Topk similarity pairs.
**/
void topk::WriteResults()
{
	result temp;
	while(!resultInstance.empty())
	{
		pop_heap(resultInstance.begin(), resultInstance.end());
		temp = resultInstance.back();
		resultInstance.pop_back();
		temp.put();
	}
}
int topk::getK()
{
	return inputk;
}

int topk::getMaxDepth()
{
	return maxDepth;
}

int topk::getSegpart()
{
	return segPart;
}

void topk::setFailtime(double time)
{
	failtime = time;
}

