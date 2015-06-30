#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include <algorithm>
using namespace std;

struct Counter
{
	Counter() : count(0){}
	void increment() {
		++count;
	}
	int count;
};

struct hashKey
{
	unsigned long long key;
	int flag;
/*
	hashKey(unsigned long long key, int flag)
	{
		this->key = key;
		this->flag = flag;
	}
	hashKey& operator =(hashKey keys)
	{
		this->key = keys.key;
		this->flag = keys.flag;
		return *this;
	}
*/
};


class test
{

public:
	int totalNum;
	vector<hashKey> keys;
	test(){
		totalNum = 0;
		keys.clear();
	}
	void DataReader(char*);
	void TimeCount();
};



