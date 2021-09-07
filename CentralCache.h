#pragma once
#include "Common.h"

class CentralCache
{
public:
	static CentralCache* GetInstance()
	{
		return &_sInst;
	}

	// 从中心缓存获取一定数量的对象给thread cache
	size_t FetchRangeObj(void*& start, void*& end, size_t n, size_t byte_size);

	// 从SpanList或者page cache获取一个span
	Span* GetOneSpan(SpanList& list, size_t byte_size);

	// 将一定数量的对象释放到span跨度
	void ReleaseListToSpans(void* start, size_t byte_size);
private:
	SpanList _spanLists[NFREELISTS]; // 按对齐方式映射

private:
	CentralCache()
	{}

	CentralCache(const CentralCache&) = delete;

	// 单例
	// 整个进程（全局）只有一个唯一对象, 并且无法创建出它的第二个对象
	// 1、自己类里面定义一个静态对象
	// 2、构造是私有的
	// 3、拷贝构造封死：
	// C++98: 只声明不定义+声明成私有
	// C++11： 拷贝构造函数 = delete
	static CentralCache _sInst;
};

