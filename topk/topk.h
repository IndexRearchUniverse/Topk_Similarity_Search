/*
 * topk.h

 *
 *  Created on: 2014年10月14日
 *      Author: ylh
 */
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include <algorithm>
using namespace std;

struct record
{
	int line;
	int rid ; 					//保存记录对应的id号
	int len  ;					//每一个record中的token的个数
//	int pos;
	int count;
	int prefix;
	double bound;
	unsigned long long moveRid;
	vector<int> tokenArray ;  	//记录每个具体的token
};


struct index_entry
{
	int line;		//record id
    int pos;        //token的位置
};

struct index_list
{
	vector<index_entry> list;
	int endingPostion;
};

struct Counter
{
	Counter() : count(0){}
	void increment() {
		++count;
	}
	int count;
};


class prefixEvent{
private:
	int line;
	int prefixLength;
	double probeBound;
public:
    prefixEvent(int line,  int prefixLength, double probeBound)
    {
    	this->line  = line;
    	this->prefixLength = prefixLength;
    	this->probeBound = probeBound;
    }
	prefixEvent():line(-1),prefixLength(0),probeBound(0){};
	int getLine()
	{
		return this->line;
	}

	int getPrefixLength()
	{
		return this->prefixLength;
	}
	double getProbeBound()
	{
		return this->probeBound;
	}
	void put()
	{
		cout<<line <<  "\t" <<"\t"<<prefixLength << "\t" << probeBound<<endl;
	}
	friend bool operator <(const prefixEvent& lhs, const prefixEvent& rhs);
	prefixEvent& operator =(prefixEvent pre)
	{
		line = pre.line;
		prefixLength = pre.prefixLength;
		probeBound = pre.probeBound;
		return *this;
	}
};


class result
{
public:
    int xrid;
    int yrid;
    double sim;

	result(int xrid, int yrid, double sim)
	{
		this->xrid = xrid;
		this->yrid = yrid;
		this->sim = sim;
	}
	result(): xrid(-1), yrid(-1), sim(0){};
	int getXrid()
	{
		return this->xrid;
	}
	int getYrid()
	{
		return this->yrid;
	}
	double getSim()
	{
		return this->sim;
	}
	result& operator =(result temp)
	{
		xrid = temp.xrid;
		yrid = temp.yrid;
		sim = temp.sim;
		return *this;
	}
	void put()
	{
		cout<< xrid << "\t" << yrid << "\t" << setiosflags(ios::fixed) << setprecision(3) << sim <<endl;
	}
    friend bool operator <(const result& lhs, const result& rhs);
};


class topk
{
	static const int INF = 1 << 24;
	static const double EPS = 1e-8;
	static const double MINSK = 0.0001;
	bool jaccard,consine;
	double failtime;
	double endsk;
	int maxK;
	int inputk;
	int maxDepth;
	int segPart;
	int tokenNum;
	int recordNum;
	int countNum;
	vector<record> joinRecord;
	vector<prefixEvent> prefixEventInstance;
	vector<result> resultInstance;
	vector<index_list> invertedList;


public:
	topk(){
		jaccard = consine = 0;
		endsk = 0;
		failtime = 0;
		tokenNum = -1;
		maxDepth = 2;
		segPart = 1;
		recordNum = 0;
		countNum = 0;

	}
	int getK();
	int getMaxK();
	int getMaxDepth();
	int getSegpart();
	void setFailtime(double);
	void ReadDate(char* );
	int ReadParameters(char*, char*);
	int ReadParameters(char*,char*,char*);
	int ReadParameters(char*,char*,char*, char*);
	void InitializeEvent();
	void InitializeTempResults(const int);
	void InitializeTempResultsOpt(const int);
	void BuildIndex();
	void InsertIndex(const int line, const int postion, const int token);
	void PerformTopk();
	void VerficationOptimization(int,  int, int, int, double&);
	void VerficationOptimization(int,  int, int, int, unsigned long long, double&);
	double CalcSimilarity(const int, const int ,int& , int&);
	void CalSecondPostion(vector<int>&, vector<int>&, int, int, int&, int&);
	double SimilarityUpperBoundProbe(const int rec, const int prefixLength);
	double SimilarityUpperBoundIndex(const int rec, const int prefixLength);
	double SimilarityUpperBoundAccess(const double spx, const double spy);
	int RequiredOverlap(const int,const int, const double);
	int SuffixFilter(vector<int>&, vector<int>&, int, int, int, int, int, int);
	int BinarySearch(vector<int>&, int, int, int);
	int CountOverlap(vector<int>& , vector<int>&, int , int , int& , int& , int );
	bool EealyTermianlOpt(const int line, const int segment, const double sk);
	bool HashChecked(unsigned long long );
	void WriteResults();
	void CoutHashIndex();

};



