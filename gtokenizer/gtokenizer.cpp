#include<iostream>
#include<fstream>
#include <cstring>
#include<vector>
#include <cstdio>
#include <cstdlib>
#include <tr1/unordered_map>

using namespace std::tr1;
using namespace std;

struct record
{
	int rid;
	int len;
	vector<int> tokenArray;
};
struct recordSort
{
	int rid;
	int len;
	recordSort& operator = (recordSort record)
	{
		this->rid = record.rid;
		this->len = record.len;
		return *this;
	}
};
vector<record> joinRecord;
vector<record> newJoinRecord;
int recordNum = 0, newRecordNum = 0;

void ReadData(char* filename)
{
	FILE *fp;
	int rid, len, inputToken;
	record inputRecord;
	fp = fopen(filename, "rb");
	joinRecord.clear();
	cerr << "Data Reading ... " << endl;
	while(fread(&rid, sizeof(int), 1, fp) == 1)
	{
		recordNum++;
		fread(&len, sizeof(int), 1, fp);
		inputRecord.rid = rid;
		inputRecord.len = len;
		inputRecord.tokenArray.clear();
		for(int i = 0; i < len; i++)
		{
			fread(&inputToken, sizeof(int), 1, fp);
			inputRecord.tokenArray.push_back(inputToken);
		}
		joinRecord.push_back(inputRecord);
	}
}

void ReadNewData()
{
	int token, len;
	record inputRecord;
	newJoinRecord.clear();
	cerr << "Data building ..." << endl;
	for(int i = 0; i < recordNum; i++)
	{
		if(joinRecord[i].len == 0)
			continue;
		inputRecord.tokenArray.clear();
		inputRecord.rid = joinRecord[i].rid;

		int k = 0;
		inputRecord.tokenArray.push_back(joinRecord[i].tokenArray[0]);
		for(int j = 1; j < joinRecord[i].len; j++)
		{
			if(joinRecord[i].tokenArray[j] != inputRecord.tokenArray[k])
			{
				inputRecord.tokenArray.push_back(joinRecord[i].tokenArray[j]);
				k++;
			}
		}
		inputRecord.len = k + 1;
		newJoinRecord.push_back(inputRecord);
		newRecordNum++;
	}
}

int compare(const void *a, const void *b)
{
	return (*(recordSort *)a).len > (*(recordSort *)b).len ? 1 : -1;
}

void SortAndWirte(char* filename)
{
	int rid = 0;
	FILE *fp;
	recordSort recSort[newJoinRecord.size()];

	cerr << "Data sorting ..." << endl;
	for(int i = 0; i < newJoinRecord.size(); i++)
	{
		recSort[i].rid = rid++;
		recSort[i].len = newJoinRecord[i].len;
	}
	qsort(recSort, newJoinRecord.size(), sizeof(int) * 2, compare);

	cerr << "Data writing ... " << endl;
	fp = fopen(filename, "wb");
	for(int i = 0; i < newJoinRecord.size(); i++)
	{
		fwrite(&newJoinRecord[recSort[i].rid].rid, sizeof(int), 1, fp);
		fwrite(&newJoinRecord[recSort[i].rid].len, sizeof(int), 1, fp);
		for(int j = 0; j < newJoinRecord[recSort[i].rid].len; j++)
			fwrite(&newJoinRecord[recSort[i].rid].tokenArray[j], sizeof(int), 1, fp);
	}
/*
	for(int i = 0; i < newJoinRecord.size(); i++)
	{
		cout << newJoinRecord[recSort[i].rid].rid << " " << newJoinRecord[recSort[i].rid].len << " ";
		for(int j = 0; j < newJoinRecord[recSort[i].rid].len; j++)
			cout << newJoinRecord[recSort[i].rid].tokenArray[j] << " ";
		cout << endl;
	}
*/
}

int main(int argc, char* argv[])
{
	cerr << "========BEGIN========" << endl;
	ReadData(argv[1]);
	ReadNewData();
	SortAndWirte(argv[2]);
	cerr << "=========END=========" << endl;
/*
	for(int i = 0; i < recordNum; i++)
	{
		cout << joinRecord[i].rid << " " << joinRecord[i].len << " ";
		for(int j = 0; j < joinRecord[i].len; j++)
			cout << joinRecord[i].tokenArray[j] << " ";
		cout << endl;
	}
	cout << endl;
	cout << "******************************************************************" << endl;
	for(int i = 0; i < newJoinRecord.size(); i++ )
	{
		cout << newJoinRecord[i].rid << " " << newJoinRecord[i].len << " ";
		for(int j = 0; j < newJoinRecord[i].len; j++)
		{
			cout << newJoinRecord[i].tokenArray[j] << " ";
		}
		cout << endl;
	}
	*/

	return 0;
}







