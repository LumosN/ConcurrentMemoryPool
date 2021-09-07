#pragma once
#include "Common.h"

class CentralCache
{
public:
	static CentralCache* GetInstance()
	{
		return &_sInst;
	}

	// �����Ļ����ȡһ�������Ķ����thread cache
	size_t FetchRangeObj(void*& start, void*& end, size_t n, size_t byte_size);

	// ��SpanList����page cache��ȡһ��span
	Span* GetOneSpan(SpanList& list, size_t byte_size);

	// ��һ�������Ķ����ͷŵ�span���
	void ReleaseListToSpans(void* start, size_t byte_size);
private:
	SpanList _spanLists[NFREELISTS]; // �����뷽ʽӳ��

private:
	CentralCache()
	{}

	CentralCache(const CentralCache&) = delete;

	// ����
	// �������̣�ȫ�֣�ֻ��һ��Ψһ����, �����޷����������ĵڶ�������
	// 1���Լ������涨��һ����̬����
	// 2��������˽�е�
	// 3���������������
	// C++98: ֻ����������+������˽��
	// C++11�� �������캯�� = delete
	static CentralCache _sInst;
};

