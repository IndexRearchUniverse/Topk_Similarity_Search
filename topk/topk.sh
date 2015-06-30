#!/bin/bash

#(1)标准topk，相似度函数：jaccard；数据集：dblp；测试范围：500 - 100000 ，后缀深度：2； 程序：topk-standard
echo -e "<<============== dblp(standard 500 - 10000)  jaccard   maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "10000" ] ; do
        let maxk+=500
	./topk-standard j $maxk ../dblp.bin 2 >> result.txt
done

#(2)哈希位置优化(第一步);相似度函数：jaccard；数据集：dblp；测试范围：500 - 100000 ，后缀深度：2； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== dblp(opt-hash 500 - 10000)  jaccard   maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "10000" ] ; do
        let maxk+=500
	./topk-hash j $maxk ../dblp.bin 2 >> result.txt
done

#(3)深度优化(第二步);相似度函数：jaccard；数据集：dblp；测试范围：500 - 100000 ，后缀深度：6； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== dblp(opt-hash 500 - 10000)  jaccard   maxdepth = 6 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "10000" ] ; do
        let maxk+=500
	./topk-hash j $maxk ../dblp.bin 6 >> result.txt
done

#(4)提前结束优化(第三步);相似度函数：jaccard；数据集：dblp；测试范围：500 - 100000 ，后缀深度：6；分块：4； 程序：topk-earlyterm
echo -e >> result.txt
echo -e "<<======== dblp(earlyterm 500 - 10000)  jaccard   maxdepth = 6   segpart = 4 ========>>" >> result.txt
maxk=0
while [ "$maxk" -ne "10000" ] ; do
        let maxk+=500
	./topk-earlyterm j $maxk ../dblp.bin 6  4 >> result.txt
done

#****************************************************************************************************************

#(1)标准topk，相似度函数：consine；数据集：dblp；测试范围：500 - 100000 ，后缀深度：2； 程序：topk-standard
echo -e >> result.txt
echo -e "<<============== dblp(standard 500 - 10000)  consine   maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "10000" ] ; do
        let maxk+=500
	./topk-standard c $maxk ../dblp.bin 2 >> result.txt
done

#(2)哈希位置优化(第一步);相似度函数：consine；数据集：dblp；测试范围：500 - 100000 ，后缀深度：2； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== dblp(opt-hash 500 - 10000)  consine   maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "10000" ] ; do
        let maxk+=500
	./topk-hash c $maxk ../dblp.bin 2 >> result.txt
done

#(3)深度优化(第二步);相似度函数：consine；数据集：dblp；测试范围：500 - 100000 ，后缀深度：6； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== dblp(opt-hash 500 - 10000)  consine   maxdepth = 6 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "10000" ] ; do
        let maxk+=500
	./topk-hash c $maxk ../dblp.bin 6 >> result.txt
done


#(4)提前结束优化(第三步);相似度函数：consine；数据集：dblp；测试范围：500 - 100000 ，后缀深度：6；分块：4； 程序：topk-earlyterm
echo -e >> result.txt
echo -e "<<======== dblp(earlyterm 500 - 10000)  consine   maxdepth = 6   segpart = 4 ========>>" >> result.txt
maxk=0
while [ "$maxk" -ne "10000" ] ; do
        let maxk+=500
	./topk-earlyterm c $maxk ../dblp.bin 6  4 >> result.txt
done

#***************************************************************************************************************

#(1)标准topk，相似度函数：jaccard；数据集：dblp；测试范围：5000 - 100000 ，后缀深度：2； 程序：topk-standard
echo -e "<<============== dblp(standard 5000 - 100000)  jaccard   maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "100000" ] ; do
	let maxk+=5000
	./topk-standard j $maxk ../dblp.bin 2 >> result.txt
done

#(2)哈希位置优化(第一步);相似度函数：jaccard；数据集：dblp；测试范围：5000 - 100000 ，后缀深度：2； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== dblp(opt-hash 5000 - 100000)  jaccard   maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "100000" ] ; do
        let maxk+=5000
	./topk-hash j $maxk ../dblp.bin 2 >> result.txt
done

#(3)深度优化(第二步);相似度函数：jaccard；数据集：dblp；测试范围：5000 - 100000 ，后缀深度：6； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== dblp(opt-hash 5000 - 100000)  jaccard   maxdepth = 6 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "100000" ] ; do
        let maxk+=5000
	./topk-hash j $maxk ../dblp.bin 6 >> result.txt
done

#(4)提前结束优化(第三步);相似度函数：jaccard；数据集：dblp；测试范围：5000 - 100000 ，后缀深度：6；分块：4； 程序：topk-earlyterm
echo -e >> result.txt
echo -e "<<======== dblp(earlyterm 5000 - 100000)  jaccard   maxdepth = 6   segpart = 4 ========>>" >> result.txt
maxk=0
while [ "$maxk" -ne "100000" ] ; do
        let maxk+=5000
	./topk-earlyterm j $maxk ../dblp.bin 6  4 >> result.txt
done

#*********************************************************************************************************************

#(1)标准topk，相似度函数：consine；数据集：dblp；测试范围：5000 - 100000 ，后缀深度：2； 程序：topk-standard
echo -e >> result.txt
echo -e "<<============== dblp(standard 5000 - 100000)  consine   maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "100000" ] ; do
        let maxk+=5000
	./topk-standard c $maxk ../dblp.bin 2 >> result.txt
done

#(2)哈希位置优化(第一步);相似度函数：consine；数据集：dblp；测试范围：5000 - 100000 ，后缀深度：2； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== dblp(opt-hash 5000 - 100000)  consine   maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "100000" ] ; do
        let maxk+=5000
	./topk-hash c $maxk ../dblp.bin 2 >> result.txt
done

#(3)深度优化(第二步);相似度函数：consine；数据集：dblp；测试范围：5000 - 100000 ，后缀深度：6； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== dblp(opt-hash 5000 - 100000)  consine   maxdepth = 6 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "100000" ] ; do
        let maxk+=5000
	./topk-hash c $maxk ../dblp.bin 6 >> result.txt
done


#(4)提前结束优化(第三步);相似度函数：consine；数据集：dblp；测试范围：5000 - 100000 ，后缀深度：6；分块：4； 程序：topk-earlyterm
echo -e >> result.txt
echo -e "<<======== dblp(earlyterm 5000 - 100000)  consine   maxdepth = 6   segpart = 4 ========>>" >> result.txt
maxk=0
while [ "$maxk" -ne "100000" ] ; do
        let maxk+=5000
	./topk-earlyterm c $maxk ../dblp.bin 6  4 >> result.txt
done

#**********************************************************************************************************************
#===========================================trec 数据集=================================================================


#(1)标准topk，相似度函数：jaccard；数据集：trec；测试范围：0 - 5000 ，后缀深度：2； 程序：topk-standard
echo -e "<<============== trec(standard 0 - 5000)  jaccard   maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "5000" ] ; do
	let maxk+=500
	./topk-standard j $maxk ../ohsumed.93.bin 2 >> result.txt
done

#(2)哈希位置优化(第一步);相似度函数：jaccard；数据集：trec；测试范围：0 - 5000 ，后缀深度：2； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== trec(opt-hash 0 - 5000)  jaccard   maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "5000" ] ; do
	let maxk+=500
	./topk-hash j $maxk ../ohsumed.93.bin 2 >> result.txt
done

#(3)深度优化(第二步);相似度函数：jaccard；数据集：trec；测试范围：0 - 5000 ，后缀深度：6； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== trec(opt-hash 0 - 5000)  jaccard   maxdepth = 6 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "5000" ] ; do
	let maxk+=500
	./topk-hash j $maxk ../ohsumed.93.bin 6 >> result.txt
done

#(4)提前结束优化(第三步);相似度函数：jaccard；数据集：trec；测试范围：0 - 5000，后缀深度：6；分块：4； 程序：topk-earlyterm
echo -e >> result.txt
echo -e "<<======== trec(earlyterm 0 - 5000)  jaccard   maxdepth = 6   segpart = 4 ========>>" >> result.txt
maxk=0
while [ "$maxk" -ne "5000" ] ; do
	let maxk+=500
	./topk-earlyterm j $maxk ../ohsumed.93.bin 6  4 >> result.txt
done

#**********************************************************************************************************************


#(1)标准topk，相似度函数：consine；数据集：trec；测试范围：0 - 5000 ，后缀深度：2； 程序：topk-standard
echo -e "<<============== trec(standard 0 - 5000)  consine  maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "5000" ] ; do
	let maxk+=500
	./topk-standard c $maxk ../ohsumed.93.bin 2 >> result.txt
done

#(2)哈希位置优化(第一步);相似度函数：consine；数据集：trec；测试范围：0 - 5000 ，后缀深度：2； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== trec(opt-hash 0 - 5000)  consine  maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "5000" ] ; do
	let maxk+=500
	./topk-hash c $maxk ../ohsumed.93.bin 2 >> result.txt
done

#(3)深度优化(第二步);相似度函数：consine；数据集：trec；测试范围：0 - 5000 ，后缀深度：6； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== trec(opt-hash 0 - 5000)  consine  maxdepth = 6 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "5000" ] ; do
	let maxk+=500
	./topk-hash c $maxk ../ohsumed.93.bin 6 >> result.txt
done

#(4)提前结束优化(第三步);相似度函数：consine；数据集：trec；测试范围：0 - 5000，后缀深度：6；分块：4； 程序：topk-earlyterm
echo -e >> result.txt
echo -e "<<======== trec(earlyterm 0 - 5000)  consine   maxdepth = 6   segpart = 4 ========>>" >> result.txt
maxk=0
while [ "$maxk" -ne "5000" ] ; do
	let maxk+=500
	./topk-earlyterm c $maxk ../ohsumed.93.bin 6  4 >> result.txt
done

#**********************************************************************************************************************
#======================================================================================================================
#****************************************************trec-3GRAM********************************************************


#(1)标准topk，相似度函数：jaccard；数据集：trec-3gram；测试范围：0 - 300 ，后缀深度：2； 程序：topk-standard
echo -e "<<============== trec-3gram(standard 0 - 300)  jaccard   maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "300" ] ; do
	let maxk+=10
	./topk-standard j $maxk ../ohsumed.93.3gram.up.bin 2 >> result.txt
done

#(2)哈希位置优化(第一步);相似度函数：jaccard；数据集：trec-3gram；测试范围：0 - 300 ，后缀深度：2； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== trec-3gram(opt-hash 0 - 300)  jaccard   maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "300" ] ; do
	let maxk+=10
	./topk-hash j $maxk ../ohsumed.93.3gram.up.bin 2 >> result.txt
done

#(3)深度优化(第二步);相似度函数：jaccard；数据集：trec-3gram；测试范围：0 - 300 ，后缀深度：6； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== trec-3gram(opt-hash 0 - 300)  jaccard   maxdepth = 6 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "300" ] ; do
	let maxk+=10
	./topk-hash j $maxk ../ohsumed.93.3gram.up.bin 6 >> result.txt
done

#(4)提前结束优化(第三步);相似度函数：jaccard；数据集：trec-3gram；测试范围：0 - 300，后缀深度：6；分块：4； 程序：topk-earlyterm
echo -e >> result.txt
echo -e "<<======== trec-3gram(earlyterm 0 - 300)  jaccard   maxdepth = 6   segpart = 4 ========>>" >> result.txt
maxk=0
while [ "$maxk" -ne "300" ] ; do
	let maxk+=10
	./topk-earlyterm j $maxk ../ohsumed.93.3gram.up.bin 6  4 >> result.txt
done

#********************************************************************************************************************

#(1)标准topk，相似度函数：consine；数据集：trec-3gram；测试范围：0 - 300 ，后缀深度：2； 程序：topk-standard
echo -e "<<============== trec-3gram(standard 0 - 300)  consine   maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "300" ] ; do
	let maxk+=10
	./topk-standard c $maxk ../ohsumed.93.3gram.up.bin 2 >> result.txt
done

#(2)哈希位置优化(第一步);相似度函数：consine；数据集：trec-3gram；测试范围：0 - 300 ，后缀深度：2； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== trec-3gram(opt-hash 0 - 300)  consine   maxdepth = 2 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "300" ] ; do
	let maxk+=10
	./topk-hash c $maxk ../ohsumed.93.3gram.up.bin 2 >> result.txt
done

#(3)深度优化(第二步);相似度函数：consine；数据集：trec-3gram；测试范围：0 - 300 ，后缀深度：6； 程序：topk-hash
echo -e >> result.txt
echo -e "<<============== trec-3gram(opt-hash 0 - 300)  consine   maxdepth = 6 ==============>>" >> result.txt
maxk=0
while [ "$maxk" -ne "300" ] ; do
	let maxk+=10
	./topk-hash c $maxk ../ohsumed.93.3gram.up.bin 6 >> result.txt
done

#(4)提前结束优化(第三步);相似度函数：consine；数据集：trec-3gram；测试范围：0 - 300，后缀深度：6；分块：4； 程序：topk-earlyterm
echo -e >> result.txt
echo -e "<<======== trec-3gram(earlyterm 0 - 300)  consine   maxdepth = 6   segpart = 4 ========>>" >> result.txt
maxk=0
while [ "$maxk" -ne "300" ] ; do
	let maxk+=10
	./topk-earlyterm c $maxk ../ohsumed.93.3gram.up.bin 6  4 >> result.txt
done

#********************************************************************************************************************
#====================================================================================================================
#********************************************************************************************************************


















