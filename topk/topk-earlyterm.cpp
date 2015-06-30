/**
* The Topk earlytermation Optimization, the execute command is:
*    ./topk-earlyterm [sim_fun] [k] [the binary files] [maxDepth] [segpart]> [output file]
**/
#include "topk.h"
#include <cmath>
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

int calk;
unsigned int  indexCount = 0;
unsigned int sizeCount = 0, totalNum = 0,postionCount = 0, stuffixCount = 0, verficationCount = 0 ;
unsigned int hashNumEqualOne = 0, hashNumGreaterOne = 0, hashCount = 0;

int part , segments, partFilterNum = 0;

void topk::PerformTopk()
{
	int x_line, i, x_prefixLength, x_len, x_pos;	//记录x的各种参数，x由前缀事件堆顶取出
	int y_line,  y_len, y_pos;						//y记录位于索引列表中
	int token;
	int overlap, hammingDistanceThreshold;
	double sim_probe, s_probe, sim = 1, sim_count;				//前缀时间堆顶的探测相似度值
	double spx= 0 , sk = 0, spy =0 ;				//sk为零时结果(最小堆)堆顶的相似度值
	double sim_access = 0;					//存取相似读值，减小索引表的大小
	double si = 0;
	prefixEvent prefix_list;
	result result_list;
	maxK = inputk +1;
	calk = maxK ;

	bool flag = false;
	part = recordNum / segPart;
	segments = segPart;

	while(!prefixEventInstance.empty())
	{
		//前缀事件的处理，首先取出堆顶元素，找到要执行的记录x和前缀的长度
		pop_heap(prefixEventInstance.begin(), prefixEventInstance.end());    //调用pop_heap()
		prefix_list = prefixEventInstance.back();							 //取出堆顶元素
		prefixEventInstance.pop_back();										//删除堆顶的一条记录
		sim_probe = prefix_list.getProbeBound();							//取出探测相似度的值
		x_line = prefix_list.getLine();										//记录x所在的行号
		x_prefixLength = prefix_list.getPrefixLength();						//取出x记录前缀的长度
		x_pos = x_prefixLength -1;											//记录x中token的位置，为前缀长度-1
		x_len = joinRecord[x_line].len;

		joinRecord[x_line].bound = sim_probe;

		//处理零时结果，其目地是取出堆顶的相似度值sk，这样我们就可以利用该值进行一些操作，如位置过滤和后缀过滤
		//同时将堆顶的元素删除，防止对后续结果的影响，calk是一个标志位
		if(calk == maxK)
		{
			pop_heap(resultInstance.begin(), resultInstance.end());
			result_list = resultInstance.back();	//取出零时结果堆中的堆顶的元素
			resultInstance.pop_back();
			sk = result_list.getSim();				//取出堆顶的相似度值
			calk--;
		}

		//用于计数
		countNum++;
		if(countNum % 1000000 == 0)
		{
			cerr << "TERM => ";
			cerr << setw(8) << countNum << "   ";
			cerr << setiosflags(ios::fixed) << setprecision(3)<< sk << "   ";
			cerr << setiosflags(ios::fixed) << setprecision(3) << sim_probe << "   ";
			cerr << setiosflags(ios::fixed) << setprecision(3) << sim << endl;
		}

		if(((segments - 1) * part < x_line))
		{
			if(segments != 1)
			{
				flag = EealyTermianlOpt(x_line, (segments - 1) * part, sk);
				if(flag == true)
					segments = segments - 1;
			}
			else
				sim = SimilarityUpperBoundAccess(joinRecord[x_line].bound, joinRecord[0].bound);
		}

		//结束标志
		if((sim_probe <= sk) || (sk >= sim))
			break;

		token = joinRecord[x_line].tokenArray[x_prefixLength - 1];		//取出对应记录的token的具体值
		for( i = 0; i < invertedList[token].endingPostion; i++)
		{
			y_line = invertedList[token].list[i].line;			//y的行号
			y_pos = invertedList[token].list[i].pos;			//索引表中token的位置
			y_len = joinRecord[y_line].len;						//记录y的长度

			if((segments * part < y_line) && (segments * part < x_line))
			{
				partFilterNum++;
				continue;
			}

			overlap = RequiredOverlap(x_len, y_len, sk);		//计算sk对应的两个记录overlap的最大值
			hammingDistanceThreshold = x_len + y_len - 2 * overlap - (x_pos + y_pos);	//最大hamming值

			spx = 1.0 - double(x_pos) / double(x_len);
			spy = 1.0 - double(y_pos) / double(y_len);
			sim_access = SimilarityUpperBoundAccess(spx, spy);	//存取最大值
			if(sim_access < sk)
				invertedList[token].endingPostion = i;			//删除endingPostion的后的索引

			totalNum ++;		//用于记录总的候选对
			if(sk < MINSK)
			{
				sizeCount++;
				if(((x_len - x_pos) < overlap) || ((y_len - y_pos) < overlap))
				{
					postionCount++;
					continue;	//位置过滤
				}
				//后缀过滤
				if(maxDepth > 0 && SuffixFilter(joinRecord[x_line].tokenArray, joinRecord[y_line].tokenArray, x_pos + 1, x_len, y_pos + 1, y_len, hammingDistanceThreshold, 1) > hammingDistanceThreshold)
				{
					stuffixCount++;
					continue;
				}
				VerficationOptimization(x_line, y_line, x_pos, y_pos, sk);
			} //end if sk
			else
			{
				if(jaccard)
				{
					if(y_len >= x_len * sk && y_len <= x_len/sk)
					{
						sizeCount++;
						if(((x_len - x_pos) < overlap) || ((y_len - y_pos) < overlap))
						{
							postionCount++;
							continue;	//位置过滤
						}
						//后缀过滤
						if(maxDepth > 0 && SuffixFilter(joinRecord[x_line].tokenArray, joinRecord[y_line].tokenArray, x_pos + 1, x_len, y_pos + 1, y_len, hammingDistanceThreshold, 1) > hammingDistanceThreshold)
						{
							stuffixCount++;
							continue;
						}
						VerficationOptimization(x_line, y_line, x_pos, y_pos, sk);
					}
				}//end jaccard size filting
				else if(consine)
				{
					if(y_len >= x_len * (sk * sk)  && y_len <= x_len/(sk * sk))
					{
						sizeCount++;
						if(((x_len - x_pos) < overlap) || ((y_len - y_pos) < overlap))
						{
							postionCount++;
							continue;	//位置过滤
						}
						//后缀过滤
						if(maxDepth > 0 && SuffixFilter(joinRecord[x_line].tokenArray, joinRecord[y_line].tokenArray, x_pos + 1, x_len, y_pos + 1, y_len, hammingDistanceThreshold, 1) > hammingDistanceThreshold)
						{
							stuffixCount++;
							continue;
						}
						VerficationOptimization(x_line, y_line, x_pos, y_pos, sk);
					}
				} //end cinsine
			} //end else
		} //end for

		si = SimilarityUpperBoundIndex(x_line, x_prefixLength);	//索引相似读，sk大于该值才能插入到索引表中
		if(si >= sk)
			InsertIndex(x_line, x_pos, token);

		//前缀事件
		s_probe = SimilarityUpperBoundProbe(x_line, x_prefixLength + 1);
		prefix_list = prefixEvent(x_line, x_prefixLength+1, s_probe);
		prefixEventInstance.push_back(prefix_list);
		push_heap(prefixEventInstance.begin(), prefixEventInstance.end());

	} // end whlile
	endsk = sk;
}

void topk::VerficationOptimization( int xline,  int yline, int xpos, int ypos, double& sk)
{
	verficationCount++;
	int xrec, yrec;
	int xlen, ylen;
	int lx, ly;
	int temp;
	double sim;
	result resultList;
	unsigned long long  key;

	//最小的放于x，最大值放于y中
	if(joinRecord[xline].rid > joinRecord[yline].rid)
	{
		temp = xline, xline = yline, yline = temp;
		temp = xpos, xpos = ypos, ypos = temp;
	}
	//取出记录行号对应的record id号

	if(joinRecord[xline].moveRid == 0)
		joinRecord[xline].moveRid = joinRecord[xline].rid << 16;

	key = joinRecord[xline].moveRid + joinRecord[yline].rid;
	it = pairs.find(key);		//查找key是否存在
	if(it != pairs.end())		//对应的hash表存在，则计数加1
	{
		hashNumGreaterOne++;
		it->second.increment();
	}
	else						//如果不存在，则计算具体的相似读值
	{
		hashNumEqualOne++;
		xlen = joinRecord[xline].len;
		ylen = joinRecord[yline].len;
		lx = xlen - (int)(sk * xlen) + 1;
		ly = ylen - (int)(sk * ylen) + 1;
		sim = CalcSimilarity(xline, yline, xpos, ypos);		//计算具体相似读值

		if(xpos <= lx && ypos <= ly)		//建立hash表
		{
			hashCount++;
			pairs[key].increment();
		}

		resultList = result(joinRecord[xline].rid, joinRecord[yline].rid, sim);

		if((calk < maxK) && (sim >= sk))
		{
			resultInstance.push_back(resultList);
			push_heap(resultInstance.begin(), resultInstance.end());
			calk++;
		}
		//取出堆顶元素，重置sk
		if(calk == maxK)
		{
			pop_heap(resultInstance.begin(), resultInstance.end());
			sk = resultInstance.back().getSim();
			resultInstance.pop_back();
			calk--;
		}
	} //end else

}



//计算存取相似度值
double topk::SimilarityUpperBoundAccess(const double spx, const double spy)
{
	double ubound;
	if(jaccard)
		ubound = (spx * spy) / (spx + spy - spx * spy);
	else if(consine)
		ubound = (spx * spx * spy * spy) / (spx * spx + spy * spy - spx * spx * spy * spy);
	return ubound;
}

//计算索引相似度值
double topk::SimilarityUpperBoundIndex(const int line, const int prefixLength)
{
	int len;
	double ubound;
	len = joinRecord[line].len;
	if(jaccard)
		ubound = double(len - prefixLength +1)/ double(len + prefixLength - 1);
	else if(consine)
		ubound = 1 - double(prefixLength - 1) / double(len);
	return ubound;

}

//计算探测相似度值
double topk::SimilarityUpperBoundProbe(const int xline, const int prefixLength)
{
	int len;
	double probe;
	len = joinRecord[xline].len;
	if(jaccard)
		probe = 1 - (double)(prefixLength - 1)/ (double)len;
	else if(consine)
		probe = sqrt(1 - double(prefixLength - 1) / double(len));
	return probe;
}

//计算sk对应的最大相似度值
int topk::RequiredOverlap(const int lenx, const int leny, const double sk)
{
	int ubound;
	if(jaccard)
		ubound = int((sk * (lenx + leny)) / (1.0 + sk) -EPS) + 1;
	else if(consine)
		ubound = int(sqrt(double(lenx)) * sqrt(double(leny)) * sk - EPS) + 1;
	return ubound;
}


//计算overlap值
int topk::CountOverlap(vector<int>& xArray, vector<int>& yArray, int xLen, int yLen, int& xStart, int& yStart, int requiredOverlap)
{
	int i = xStart, j = yStart, ans = 0;
	while (i < xLen && j < yLen) {
		if (xArray[i] == yArray[j])
		{
			++ans;
			if(ans == 2)
				xStart = i, yStart = j;
			++i, ++j;
		}
		else {
			if (xArray[i] < yArray[j]) ++i;
			else ++j;
		}
	}
	if (ans < requiredOverlap) return -INF;
	else return ans;
}

double topk::CalcSimilarity(const int xline, const int yline ,int& xpos, int& ypos)
{
	int count;
	int xlen, ylen;
	double sim;

	xlen = joinRecord[xline].len;
	ylen = joinRecord[yline].len;
	count = CountOverlap(joinRecord[xline].tokenArray, joinRecord[yline].tokenArray, joinRecord[xline].len, joinRecord[yline].len, xpos, ypos, -1);
	if(jaccard)
		sim = double(count) /double(xlen + ylen -count);
	else if(consine)
		sim = double(count) / (sqrt(double(xlen)) * sqrt(double(ylen)));
	return sim;
}

//后缀过滤
int topk::SuffixFilter(vector<int>& xArray, vector<int>& yArray, int xStart, int xEnd, int yStart, int yEnd, int HD, int depth)
{
	if (xEnd <= xStart || yEnd <= yStart) return abs((xEnd - xStart) - (yEnd - yStart));
	int xLen = xEnd - xStart, yLen = yEnd - yStart;
	int left, right, mid, pos, token, offset;
	int HDLeft, HDRight, HDLeftBound, HDRightBound;

	mid = xStart + xLen / 2, token = xArray[mid];

	if (xLen >= yLen) {
		offset = (HD - (xLen - yLen)) / 2 + (xLen - yLen), left = yStart + xLen / 2 - offset;
		offset = (HD - (xLen - yLen)) / 2, right = yStart + xLen / 2 + offset;
	}
	else {
		offset = (HD - (yLen - xLen)) / 2, left = yStart + xLen / 2 - offset;
		offset = (HD - (yLen - xLen)) / 2 + (yLen - xLen), right = yStart + xLen / 2 + offset;
	}

	if ((left >= yStart && yArray[left] > token) || (right < yEnd && yArray[right] < token)) return HD + 1;

	pos = BinarySearch(yArray, token, left >= yStart ? left : yStart, right + 1 < yEnd ? right + 1 : yEnd);
	if (pos < yEnd && yArray[pos] == token) { // x:[Left][mid][Right] y:[Left][pos][Right]
		HDLeft = HDLeftBound = abs((mid - xStart) - (pos - yStart));
		HDRight = HDRightBound = abs((xEnd - mid - 1) - (yEnd - pos - 1));
		if (HDLeftBound + HDRightBound > HD) return HDLeftBound + HDRightBound;
		if (depth < maxDepth) {
			HDLeft = SuffixFilter(xArray, yArray, xStart, mid, yStart, pos, HD - HDRightBound, depth + 1);
			if (HDLeft + HDRightBound > HD) return HDLeft + HDRightBound;
			HDRight = SuffixFilter(xArray, yArray, mid + 1, xEnd, pos + 1, yEnd, HD - HDLeft, depth + 1);
		}
		if (HDLeft + HDRight > HD) return HDLeft + HDRight;
		return HDLeft + HDRight;
	}
	else { // x:[Left][mid][Right] y:[Left][Right]
		HDLeft = HDLeftBound = abs((mid - xStart) - (pos - yStart));
		HDRight = HDRightBound = abs((xEnd - mid - 1) - (yEnd - pos));
		if (HDLeftBound + HDRightBound + 1 > HD) return HDLeftBound + HDRightBound + 1;
		if (depth < maxDepth) {
			HDLeft = SuffixFilter(xArray, yArray, xStart, mid, yStart, pos, HD - HDRightBound - 1, depth + 1);
			if (HDLeft + HDRightBound + 1 > HD) return HDLeft + HDRightBound + 1;
			HDRight = SuffixFilter(xArray, yArray, mid + 1, xEnd, pos, yEnd, HD - HDLeft - 1, depth + 1);
		}
		if (HDLeft + HDRight + 1 > HD) return HDLeft + HDRight + 1;
		return HDLeft + HDRight + 1;
	}

	return 0;
}

int topk::BinarySearch(vector<int>& array, int value, int start, int end)
{
	int mid;
	while (start < end) {
		mid = (start + end) / 2;
		if (array[mid] < value) start = mid + 1;
		else end = mid;
	}
	return start;
}


void topk::InitializeTempResults(const int maxk)
{
	int xlen, ylen;
	int xpos = 0, ypos = 0;
	int count;
	double sim;
	unsigned long long key, xmv;
	result temp;

	pairs.set_empty_key(0xffffffffffffffff);			//哈希表的设置
	pairs.clear_no_resize();

	resultInstance. reserve(maxk);
	resultInstance.clear();
	make_heap(resultInstance.begin(), resultInstance.end());
	for(int i =1; i <= maxk; i++)
	{
		count = CountOverlap(joinRecord[0].tokenArray, joinRecord[i].tokenArray, joinRecord[0].len, joinRecord[i].len, xpos, ypos, -1);
		if(count>=0)
		{
			sim = CalcSimilarity(0, i, xpos, ypos);
		}

		if(joinRecord[0].rid > joinRecord[i].rid)
		{
			if(joinRecord[i].moveRid == 0)
				joinRecord[i].moveRid = joinRecord[i].rid << 16;

			key = joinRecord[0].rid + joinRecord[i].moveRid;
		}
		else
		{
			if(joinRecord[0].moveRid == 0)
				joinRecord[0].moveRid = joinRecord[0].rid << 16;

			key = joinRecord[0].moveRid + joinRecord[i].rid;
		}

		pairs[key].increment();		//加入到hash表中
		if(joinRecord[0].rid > joinRecord[i].rid)
			temp = result(joinRecord[i].rid, joinRecord[0].rid, sim);
		else
			temp = result(joinRecord[0].rid, joinRecord[i].rid, sim);

		resultInstance.push_back(temp);
		push_heap(resultInstance.begin(), resultInstance.end());
	}
	int j = 0;
/*
	while(!resultInstance.empty())
	{
		j++;
		pop_heap(resultInstance.begin(), resultInstance.end());
		temp = resultInstance.back();
		resultInstance.pop_back();
		temp.put();
		cout << "movrid[0]:\t" << joinRecord[0].moveRid <<"  " << joinRecord[0].rid << "\tmovRid[" << j <<"]:\t" << joinRecord[j].moveRid << "   " << joinRecord[j].rid<< endl;
	}
*/
	cerr<<"***************<< temp Record >>*************"<<endl;
	cerr << "Initialize temp result has complete!!" <<endl;
	cerr << "The temp-resultt min-heap length is : " << inputk <<endl;
	cerr <<"********************************************\n"<<endl;
}

bool topk::EealyTermianlOpt(const int line, const int segment, const double sk)
{
	bool flag = false;
	double segmentsim;
	if(line > segment)
	{
		segmentsim = SimilarityUpperBoundAccess(joinRecord[line].bound, joinRecord[segment].bound);
		if(sk >= segmentsim)
			flag = true;
	}
	return flag;
}

void topk::CoutHashIndex()
{
	int hashNum = 0, indexNum = 0;
	for(int i = 0; i < tokenNum; i++)
	{
		indexNum += invertedList[i].endingPostion;
	}
	for(it = pairs.begin(); it != pairs.end(); it++)
		hashNum++;
	cerr << "\n*******TOPK第三步EARLYTERM优化**********" << endl;
	cerr << "<<<-----------< 结果统计 >------------->>>" << endl;
	if(jaccard)      cerr << "#相似连接算法(Similarity)：  jaccard" << endl;
	else if(consine) cerr << "#相似连接算法(Similarity)：  consine" << endl;
	cerr << "#后缀过滤深度(max-depth)：   " << maxDepth << endl;
	cerr << "#提前结束分块(seg-part)：    " << segPart << endl;
	cerr << "#要查询的记录数(TOP-K):      " << inputk << endl;
	cerr << "#结果最小的相似读值(SK):     " << endsk << endl;
	cerr << "#前缀事件总数(prefixEvent)： " << countNum << endl;
	cerr << "#索引记录总数(Index-count):  " << indexNum << endl;
	cerr << "#生成记录对数(Record-pair):  " << totalNum << endl;
	cerr << "#通过size过滤(Passed-size):  " << sizeCount << endl;
	cerr << "#需要验证对数(Verify-count): " <<  verficationCount << endl;
	cerr << "#哈希表的大小(Hash-count):   " << hashNum << endl;
	cerr << "#程序运行时间(Total-time):   " <<  setiosflags(ios::fixed) << setprecision(3) << failtime << endl;
	cerr << "=================过滤统计=================" << endl;
	cerr << "#size过滤数目(Size-filter)：    " << (totalNum - sizeCount) << endl;
	cerr << "#位置过滤数目(Position-filter): " << postionCount << endl;
	cerr << "#后缀过滤数目(Stuffix-filter):  " << stuffixCount << endl;
	cerr << "--------------------------------------------" << endl;

	if(jaccard) cout << "J\t";
	else if(consine) cout << "C\t";
	cout << inputk << "\t" << maxDepth << "\t" << segPart << "\t";			//output k , maxdepth , segpart
	cout << setiosflags(ios::fixed) << setprecision(3) << endsk << "\t";  // output smallist similarity
	cout << countNum << "\t" << indexNum << "\t" << totalNum << "\t";
	cout << (totalNum - sizeCount) << "\t" << postionCount << "\t" << stuffixCount << "\t";
	cout << verficationCount << "\t" << hashNum << "\t";
	cout << setiosflags(ios::fixed) << setprecision(3) << failtime << endl;

//	cerr << "#记录中有一个以上公共token值的记录对为：  " << hashNumEqualOne << endl;
//	cerr << "#记录中有两个以上的公共token记录对总共的碰撞次数： " << hashNumGreaterOne << endl;
//	cerr << "#通过哈希函数后没有被验证的记录候选对为：" << (verficationCount - hashNumEqualOne - hashNumGreaterOne) << endl;
}




