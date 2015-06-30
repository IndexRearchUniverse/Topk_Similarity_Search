#include<iostream>
#include <cstring>
#include<vector>
#include <cstdio>
#include <cstdlib>
#include <tr1/unordered_map>

using namespace std;
using namespace std::tr1;

struct token
{
	int tokenId;
	int df;
	token(): tokenId(-1), df(0){}
	token& operator =(token tok)
	{
		this->tokenId = tok.tokenId;
		this->df = tok.df;
		return *this;
	}
};

struct record
{
	int rid;
	int len;
	vector<token> tokenArray;
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

class qtokenizer
{
public:
	int recordNum;
	int tokenNum;
	int maxLength;
	int minLength;

	unordered_map<string, vector<int> > dictionIndex;
	unordered_map<string, vector<int> >::iterator iter;

	unordered_map<string, int > pairs;
	unordered_map<string, int > ::iterator it;

	vector<int> dictionaries;
	vector<record> joinRecord;

	qtokenizer(){
		recordNum = 0;
		tokenNum = 0;
		maxLength = 0;
		minLength = 0xfffffff;
		dictionIndex.clear();
		dictionaries.clear();
		joinRecord.clear();
	}

	void ReadData(char* filemane, int gram);
	void AddDF();
	void SortEachRecord();
	void SortAndWrite(const char*);
};







