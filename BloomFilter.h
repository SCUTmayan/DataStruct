#pragma once

#include "Bitmap.h"

typedef Bitmap BloomFilter;
typedef char* BloomFilterData;

void BloomFilterInit(BloomFilter* bf, size_t range);//��ʼ��
size_t BloomFilterFunc1(BloomFilterData str);//��ϣ����
size_t BloomFilterFunc2(BloomFilterData str);
size_t BloomFilterFunc3(BloomFilterData str);
void BloomFilterSet(BloomFilter* bf, BloomFilterData str);//����ĳ���ַ����Ĵ�����Ϣ
bool BloomFilterTest(BloomFilter* bf, BloomFilterData str);//���ĳ���ַ����Ƿ����
void BloomFilterDestroy(BloomFilter* bf);//����

void TestBloomFilter();//��������

void BloomFilterInit(BloomFilter* bf, size_t range)
{
	assert(bf);
	BitmapInit(bf, range);
}

size_t BloomFilterFunc1(BloomFilterData str)
{
	size_t seed = 131;
	register size_t hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

size_t BloomFilterFunc2(BloomFilterData str)
{
	register size_t hash = 0;
	size_t seed = 65599;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return hash;
}

size_t BloomFilterFunc3(BloomFilterData str)
{
	register size_t hash = 0;
	size_t seed = 63689;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return hash;
}

void BloomFilterSet(BloomFilter* bf, BloomFilterData str)
{
	assert(bf);
	size_t index1 = BloomFilterFunc1(str);
	size_t index2 = BloomFilterFunc2(str);
	size_t index3 = BloomFilterFunc3(str);
	BitmapSet(bf, index1);
	BitmapSet(bf, index2);
	BitmapSet(bf, index3);
}

bool BloomFilterTest(BloomFilter* bf, BloomFilterData str)
{
	assert(bf);
	size_t index1 = BloomFilterFunc1(str);
	if (BitmapTest(bf, index1) == false)
	{
		return false;
	}
	size_t index2 = BloomFilterFunc2(str);
	if (BitmapTest(bf, index2) == false)
	{
		return false;
	}
	size_t index3 = BloomFilterFunc3(str);
	if (BitmapTest(bf, index3) == false)
	{
		return false;
	}
	return true;
}

void BloomFilterDestroy(BloomFilter* bf)
{
	assert(bf);
	BitmapDestroy(bf);
}

void TestBloomFilter()
{
	BloomFilter bf;
	char str1[] = "hello";
	char str2[] = "nice";
	char str3[] = "perfect";

	BloomFilterInit(&bf, 4200000000);
	BloomFilterSet(&bf, str1);
	BloomFilterSet(&bf, str2);
	BloomFilterSet(&bf, str3);
	printf("%d\n", BloomFilterTest(&bf, "hello"));
	printf("%d\n", BloomFilterTest(&bf, "perfect"));
	printf("%d\n", BloomFilterTest(&bf, "great"));

	BitmapDestroy(&bf);
}