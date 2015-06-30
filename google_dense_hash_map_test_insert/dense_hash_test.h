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

class test
{

public:
	int totalNum;
	vector<unsigned long long> keys;
	test(){
		totalNum = 0;
		keys.clear();
	}
	void DataReader(char*);
	void TimeCount();
};



