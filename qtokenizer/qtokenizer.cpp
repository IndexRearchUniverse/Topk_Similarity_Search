#include "qtokenizer.h"
#include <fstream>

void qtokenizer::ReadData(char* filename, int gram)
{
	ifstream input(filename);
	string str;
	record inputRecord;
	int rid = 0;

	cerr <<"Data Reading ..." << endl;
	while(getline(input, str))
	{
		int j = 0, len = 0;
		const char* ch;
		char temp[gram + 1];
		string s1;
		vector<string> eachRecord;

		ch = str.data();
		eachRecord.clear();
		if(str.length() < gram) continue;
		for(int i = 0; i < str.length() - gram + 1; i++)
		{
			for(j = 0; j < gram; j++)
				temp[j] = ch[i + j];
			temp[j] = '\0';
			s1 = temp;
			eachRecord.push_back(s1);
			len++;
		}
		if(minLength > len) minLength = len;
		if(maxLength < len) maxLength = len;
		inputRecord.rid = recordNum, inputRecord.len = len;
		inputRecord.tokenArray.clear(), inputRecord.tokenArray.resize(len);
		recordNum++;

		pairs.clear();
		for(int k = 0; k < len; k++)
		{
			int tokenid = -1;
			it = pairs.find(eachRecord[k]);
			if(it != pairs.end())
				tokenid = it->second;

			iter = dictionIndex.find(eachRecord[k]);
			if(iter != dictionIndex.end())
			{
				int p = 0;
				for(p = 0; p < iter->second.size(); p++)
				{
					if(tokenid >= iter->second[p])
						continue;
					else{
						inputRecord.tokenArray[k].tokenId = iter->second[p];
						pairs[eachRecord[k]] = iter->second[p];
						dictionaries[iter->second[p]]++;
						break;
					}
				}
				if(p == iter->second.size())
				{
					iter->second.push_back(tokenNum);
					inputRecord.tokenArray[k].tokenId = tokenNum;
					pairs[eachRecord[k]] = tokenNum;
					dictionaries.push_back(1);
					tokenNum++;
				}

			} // end if iter
			else{
				vector<int> temp;
				temp.push_back(tokenNum);
				dictionIndex[eachRecord[k]] = temp;
				dictionaries.push_back(1);
				inputRecord.tokenArray[k].tokenId = tokenNum;
				pairs[eachRecord[k]] = tokenNum;
				tokenNum++;
			}
		}  //end for
		joinRecord.push_back(inputRecord);

		if(recordNum % 10000 == 0)
			cerr << recordNum << "\t" << tokenNum << endl;
	} //end while
}

void qtokenizer::AddDF()
{
	int count = 0;
	double pecent;
	cerr << "DFs are writting..." << endl;
	for(int i = 0; i < joinRecord.size(); i++)
	{
		for(int j = 0; j < joinRecord[i].tokenArray.size(); j++)
		{
			int index = joinRecord[i].tokenArray[j].tokenId;
			joinRecord[i].tokenArray[j].df = dictionaries[index];
		}
		count++;
		pecent = (double) count * 100 / (double) recordNum;

		if(((int)pecent) % 10 == 0)
			cerr << (int)pecent << "..";
	}
	cerr << endl;
//	cerr << "DFs have writed !" << endl;
}

int cmp(const void* a, const void* b)
{
	return (*(token *)a).df > (*(token *)b).df ? 1 : -1;
}

void qtokenizer::SortEachRecord()
{
	int count = 0;
	double pecent;
	cerr << "Tokens are sorting ... " << endl;
	for(int i = 0; i < joinRecord.size(); i++)
	{
		token tok[joinRecord[i].len];
		for(int j = 0; j < joinRecord[i].len; j++)
			tok[j] = joinRecord[i].tokenArray[j];
		qsort(tok, joinRecord[i].len, sizeof(int) * 2, cmp);
		for(int j = 0; j < joinRecord[i].len; j++)
			joinRecord[i].tokenArray[j] = tok[j];

		count++;
		pecent = (double) count * 100 / (double) recordNum;

		if(((int)pecent) % 10 == 0)
			cerr << (int)pecent << "..";
	}
	cerr << endl;
//	cerr << "Tokens have sorted !" << endl;
/*
	for(int i = 0; i < joinRecord.size(); i++)
	{
		cout << joinRecord[i].rid << " " << joinRecord[i].len << " ";
		for(int j = 0; j < joinRecord[i].tokenArray.size(); j++)
			cout << "(" << joinRecord[i].tokenArray[j].tokenId << "," << joinRecord[i].tokenArray[j].df << ") ";
		cout << endl;
	}
*/
}

int compare(const void *a, const void *b)
{
	return (*(recordSort *)a).len > (*(recordSort *)b).len ? 1 : -1;
}

void qtokenizer::SortAndWrite(const char* filename)
{
	int count = 0;
	double pecent;
	FILE * fp;
	recordSort record[recordNum];

	cerr << "Records are sorting..." << endl;

	for(int i = 0; i < recordNum; i++)
	{
		record[i].rid = joinRecord[i].rid;
		record[i].len = joinRecord[i].len;
	}
	qsort(record, recordNum, sizeof(int) * 2, compare);

//	cerr << "Records have sorted !" << endl;
	cerr << "Data are writting ..." << endl;

	fp = fopen(filename, "wb");
	for(int i = 0; i < recordNum; i++)
	{
		int rid = record[i].rid;
		fwrite(&joinRecord[rid].rid, sizeof(int), 1, fp);
		fwrite(&joinRecord[rid].len, sizeof(int), 1, fp);
		for(int j = 0; j < joinRecord[rid].len; j++)
			fwrite(&joinRecord[rid].tokenArray[j].tokenId, sizeof(int), 1, fp);

		count++;
		pecent = (double) count * 100 / (double) recordNum;

		if(((int)pecent) % 10 == 0)
			cerr << (int)pecent << "..";
	}
	cerr << endl;
/*
	for(int i = 0; i < recordNum; i++)
	{
		int rid = record[i].rid;
		cout << joinRecord[rid].rid << " " << joinRecord[rid].len << " " ;
		for(int j = 0; j < joinRecord[rid].len; j++)
			cout << "(" << joinRecord[rid].tokenArray[j].tokenId << "," << joinRecord[rid].tokenArray[j].df << ") ";
		cout << endl;
	}
*/
}



















