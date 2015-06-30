#include "topk.h"
/*
* Build the index
*/
void topk::BuildIndex()
{
	invertedList.resize(tokenNum + 1 );
	for(int i = 0; i <= tokenNum; i++)
	{
		invertedList[i].endingPostion = 0;
		invertedList[i].list.clear();
	}
	cerr<<"*****************<< Index >>***************"<<endl;
	cerr << "The inverted index has been builded!!" << endl;
	cerr << "The index length is : " << tokenNum <<endl;
	cerr <<"********************************************\n"<<endl;

}

void topk::InsertIndex(const int line, const int postion, const int token)
{
	index_entry index;
	index.line = line;
	index.pos  = postion;
//	cout << "-----------------------INDES--------------------------" << endl;
//	cout << "line  = \t" << line << "\t postion \t" << postion << "\t token = \t"
//			<< token << "\t invertedList[token].endingPostion \t" << invertedList[token].endingPostion <<endl;
	if(invertedList[token].endingPostion < invertedList[token].list.size())
	{
		invertedList[token].list[invertedList[token].endingPostion].line = line;
		invertedList[token].list[invertedList[token].endingPostion].pos = postion;
		invertedList[token].endingPostion++;
	}
	else
	{
		invertedList[token].list.push_back(index);
		invertedList[token].endingPostion++;
	}

}
