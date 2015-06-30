#include "dense_hash_test.h"
#include<fstream>
#include <sys/time.h>
#include <google/dense_hash_map>
using google::dense_hash_map;      // namespace where class lives by default
using __gnu_cxx::hash;  // or __gnu_cxx::hash, or maybe tr1::hash, depending on your OS

namespace __gnu_cxx
{
template<>
    struct hash<unsigned long long>
    {
      size_t
      operator()(unsigned long long __x) const
      { return __x; }
    };
}

typedef google::dense_hash_map<unsigned long long, Counter> hashmap_t;
typedef google::dense_hash_map<unsigned long long, Counter>::iterator hashmap_iterator_t;

hashmap_t pairs;
hashmap_iterator_t it;

void test::DataReader(char* filename)
{
	ifstream input(filename);
	pairs.set_empty_key(0xffffffffffffffff);
	pairs.clear_no_resize();
	char a[50], *end;
	unsigned long long temp;

	cerr << "数据读入中..." << endl;
	while(input.getline(a, 50))
	{
		temp = strtoull(a, &end, 10);
		keys.push_back(temp);
		totalNum++;
	}

}

void test::TimeCount()
{
	timeval buildStart, buildEnd;
	timeval findStart, findEnd;
	timeval itStart, itEnd;
	int success = 0, fail = 0 ;
	int hashNum = 0;
	cerr << "开始生成哈希表..." << endl;

	gettimeofday(&buildStart, NULL);
	for(long  i = 0; i < totalNum; i++)
	{
		it = pairs.find(keys[i]);
		if(it != pairs.end())
		{
			it->second.increment();
			success++;
		}
		else
		{
			pairs[keys[i]].increment();
			fail++;
		}
	//	if(i % 1000000 == 0)
          //              cerr << i << endl;
	}
	gettimeofday(&buildEnd, NULL);
	cerr << "<<------数据统计------>>" << endl;
	cerr << "#插入条数为： " << totalNum << endl;
	cerr << "#哈希大小为： " << fail << endl;
	cerr << "#查到条数为： " << success << endl;
	cerr << "#总共用时为:  " << setiosflags(ios::fixed) << setprecision(3) << double(buildEnd.tv_sec - buildStart.tv_sec) + double(buildEnd.tv_usec - buildStart.tv_usec) / 1e6 << endl;
	cerr << endl;

	gettimeofday(&itStart, NULL);
	for(it = pairs.begin(); it != pairs.end(); it++)
		hashNum++;
	gettimeofday(&itEnd, NULL);
	cerr << "<<------遍历统计------>>" << endl;
	cerr << "#遍历条数为： " << hashNum << endl;
	cerr << "#总共用时为:  " << setiosflags(ios::fixed) << setprecision(3) << double(itEnd.tv_sec - itStart.tv_sec) + double(itEnd.tv_usec - itStart.tv_usec) / 1e6 << endl;

}




