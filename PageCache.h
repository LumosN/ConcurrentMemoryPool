#pragma once
#include "Common.h"
#include "PageMap.h"

class PageCache
{
public:
	static PageCache* GetInstance()
	{
		return &_sInst;
	}

	// 向系统申请k页内存挂到自由链表
	void* SystemAllocPage(size_t k);

	Span* NewSpan(size_t k);

	// 获取从对象到span的映射
	Span* MapObjectToSpan(void* obj);

	// 释放空闲span回到Pagecache，并合并相邻的span
	void ReleaseSpanToPageCache(Span* span);
private:
	SpanList _spanList[NPAGES];	// 按页数映射

	//std::mutex _map_mtx;
	//std::unordered_map<PageID, Span*> _idSpanMap;
	TCMalloc_PageMap2<32 - PAGE_SHIFT> _idSpanMap;
	//TCMalloc_PageMap1 _idSizeMap;

	// tcmalloc 基数树  效率更高

	std::recursive_mutex _mtx;


private:
	PageCache()
	{}

	// 拷贝构造：只声明不定义+声明成私有
	// 如果只声明不定义，是公有的话，可以在类外面定义
	// 只声明不定义，保证在类的里面也拷贝不了
	PageCache(const PageCache&) = delete;

	// 单例
	static PageCache _sInst;
};
