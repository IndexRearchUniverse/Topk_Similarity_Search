#include <algorithm>
#include "topk.h"

/*
* Initialize Prefix Event
*/
void topk::InitializeEvent()
{
	int line ;
	prefixEvent prefix_list;
	prefixEventInstance.clear();
	make_heap(prefixEventInstance.begin(), prefixEventInstance.end());
	for(int i = 0; i < recordNum; i++)
	{
		line = joinRecord[i].line;
		prefix_list = prefixEvent(line, 1, 1.0);
		prefixEventInstance.push_back(prefix_list);
		push_heap(prefixEventInstance.begin(), prefixEventInstance.end());
	}

	cerr<<"**************<< Prefix event >>************"<<endl;
	cerr << "Initialize prefix event has complete!!" <<endl;
	cerr << "The prefix event max-heap length is : " << recordNum <<endl;
	cerr <<"********************************************\n"<<endl;
}


//最大堆重载
bool operator <(const prefixEvent& lhs, const prefixEvent& rhs)
{
	return lhs.probeBound < rhs.probeBound ? true : false;
}
//最小堆重载
bool operator <(const result& lhs, const result& rhs)
{
	return lhs.sim > rhs.sim ? true : false;
}
