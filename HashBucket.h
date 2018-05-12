#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <assert.h>

typedef int HashDataType;

typedef struct HashBucketNode
{
	HashDataType _data;
	struct HashBucketNode* _next;
}HashNode;

typedef struct HashBucket
{
	HashNode** _tables;
	size_t _size;
	size_t _capacity;
}HashBucket;

void HashInit(HashBucket* hb, size_t capacity);//��ʼ����ϣͰ

static size_t HashFunc(HashBucket* hb, HashDataType data);//��ϣ����
static HashNode* BuyNewHashNode(HashDataType data);//���������ڵ�
static void CheckCapacity(HashBucket* hb);//���ռ䣬ȷ��Ч��
static size_t GetPrime(HashBucket* hb);
static void HashPrint(HashBucket* hb);

bool HashInsert(HashBucket* hb, HashDataType data);//����
HashNode* HashFind(HashBucket* hb, HashDataType data);//����ĳ��Ԫ���Ƿ����
bool HashRemove(HashBucket* hb, HashDataType data);//ɾ��
size_t HashSize(HashBucket* hb);

void TestHashTable();//��������


void HashInit(HashBucket* hb, size_t capacity)
{
	assert(hb);
	hb->_capacity = capacity;
	hb->_capacity = GetPrime(hb);
	hb->_tables = (HashNode**)malloc(sizeof(HashNode*) * hb->_capacity);
	hb->_size = 0;
	for (size_t i = 0; i < hb->_capacity; i++)
	{
		*(hb->_tables + i) = NULL;
	}
}

static size_t HashFunc(HashBucket* hb, HashDataType data)
{
	assert(hb);
	return data % hb->_capacity;
}

static HashNode* BuyNewHashNode(HashDataType data)
{
	HashNode* new_node = (HashNode*)malloc(sizeof(struct HashBucketNode));
	new_node->_data = data;
	new_node->_next = NULL;
	return new_node;
}

static void CheckCapacity(HashBucket* hb)
{
	assert(hb);
	if (hb->_size == hb->_capacity)
	{
		HashBucket new_hb;
		HashNode* cur = NULL;
		HashNode* next = NULL;
		HashInit(&new_hb, hb->_capacity);
		for (size_t i = 0; i < hb->_capacity; i++)
		{
			//��ԭ���ݲ����±���
			cur = *(hb->_tables + i);
			while (cur)
			{
				//֮���Կ���ͷ������Ϊ����û���ظ�
				next = cur->_next;
				size_t index = HashFunc(&new_hb, cur->_data);
				cur->_next = *(new_hb._tables + index);
				*(new_hb._tables + index) = cur;
				cur = next;
			}
		}
		hb->_capacity = new_hb._capacity;
		free(hb->_tables);//�ͷžɱ�
		hb->_tables = new_hb._tables;//�����±�
	}
}

static size_t GetPrime(HashBucket* hb)
{
	assert(hb);
	const int _PrimeSize = 28;
	//�����ݶ��Ǿ�������˲��Ե��������ܹ��������󣬳�ͻ��С
	static const unsigned long _PrimeList[_PrimeSize] = {
		53ul,97ul,193ul,389ul,769ul,
		1543ul,3079ul,6151ul,12289ul,
		24593ul,49157ul,98317ul,196613ul,
		393241ul,786433ul,1572869ul,3145739ul,
		6291469ul,12582917ul,25165843ul,50331653ul,
		100663319ul,201326611ul,402653189ul,805306457ul,
		1610612741ul, 3221225473ul, 4294967291ul
	};
	int index = 0;
	while (index < _PrimeSize)
	{
		if (hb->_capacity < _PrimeList[index])
		{
			return _PrimeList[index];
		}
		index++;
	}
	return _PrimeList[_PrimeSize - 1];
}

static void HashPrint(HashBucket* hb)
{
	//������ӡ����
	assert(hb);
	HashNode* cur = NULL;
	for (size_t i = 0; i < hb->_capacity; i++)
	{
		cur = *(hb->_tables + i);
		printf("tables[%d]", i);
		while (cur)
		{
			printf("->%d", cur->_data);
			cur = cur->_next;
		}
		printf("->NULL\n");
	}
}

bool HashInsert(HashBucket* hb, HashDataType data)
{
	assert(hb);
	CheckCapacity(hb);
	size_t index = HashFunc(hb, data);
	HashNode* cur = *(hb->_tables + index);
	HashNode* prev = cur;
	if (cur == NULL)
	{
		//��λ��û���κνڵ㣬ֱ�Ӳ���
		*(hb->_tables + index) = BuyNewHashNode(data);
	}
	else
	{
		//��λ�����нڵ㣬��Ѱ����λ�ò���
		while (cur)
		{
			//������ͷ�壬��Ϊ�����������ظ�
			if (cur->_data == data)
			{
				return false;
			}
			prev = cur;
			cur = cur->_next;
		}
		prev->_next = BuyNewHashNode(data);
	}
	hb->_size++;
	return true;
}

HashNode* HashFind(HashBucket* hb, HashDataType data)
{
	assert(hb);
	size_t index = HashFunc(hb, data);
	HashNode* cur = *(hb->_tables + index);
	while (cur)
	{
		if (cur->_data == data)
		{
			return cur;
		}
		cur = cur->_next;
	}
	return NULL;
}

bool HashRemove(HashBucket* hb, HashDataType data)
{
	assert(hb);
	size_t index = HashFunc(hb, data);
	HashNode* cur = *(hb->_tables + index);
	HashNode* prev = cur;
	while (cur)
	{
		if (cur->_data == data)
		{
			break;
		}
		prev = cur;
		cur = cur->_next;
	}
	if (cur == NULL)
	{
		//cur�Ѿ��鵽�׻��߸�λ�ñ���û�нڵ�Ϊ�գ�δ�ҵ�
		return false;
	}
	else
	{
		//�ҵ�
		if (cur == prev)
		{
			//�ڵ�Ϊ��һ����㣬����ֱ��prev = cur����Ϊprev����ʱ����
			*(hb->_tables + index) = cur->_next;
		}
		else
		{
			//�ڵ㲻�ǵ�һ���ڵ�
			prev->_next = cur->_next;
		}
		free(cur);
		return true;
	}
}

size_t HashSize(HashBucket* hb)
{
	return hb->_size;
}

void TestHashTable()
{
	HashBucket hb;
	HashInit(&hb, 0);

	srand((unsigned)time(0));
	for (int i = 0; i < 50; i++)
	{
		HashInsert(&hb, rand() % 200);
	}
	HashPrint(&hb);
	printf("\n");

	for (int i = 0; i < 50; i++)
	{
		HashInsert(&hb, rand() % 200);
	}
	HashPrint(&hb);
	printf("\n");

	for (int i = 0; i < 200; i++)
	{
		HashRemove(&hb, rand() % 200);
	}
	HashPrint(&hb);
	
}