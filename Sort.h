#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



void InsertSort(int* arr, size_t size);//��������
void ShellSort(int* arr, size_t size);//ϣ������
void SelectSort(int* arr, size_t size);//ѡ������
void BubbleSort(int* arr, size_t size);//ð������
void QuickSort(int* arr, int left, int right);//��������
static int PartSort1(int* arr, int left, int right);//����ָ�뷨
static int PartSort2(int* arr, int left, int right);//�ڿӷ�
static int PartSort3(int* arr, int left, int right);//��ָ�뷨

void MergeSort(int* arr, int size);//�鲢����
static void PartMergeSort(int* arr, int left, int right, int* tmp);//���ֹ鲢

static void Swap(int* x1, int* x2);
static void ResetArr(int* arr);
static void PrintArr(int* arr, size_t size);

void TestSort();//��������

void InsertSort(int* arr, size_t size)
{
	assert(arr);
	for (int i = 0; i < size - 1; i++)
	{
		int end = i;//�����������������
		int tmp = *(arr + i + 1);//��Ҫ�������
		while (end >= 0 && *(arr + end) > tmp)
		{
			*(arr + end + 1) = *(arr + end);
			end--;
		}
		*(arr + end + 1) = tmp;//1.�±�Ϊ-1  2.�ҵ������±�
	}
}

void ShellSort(int* arr, size_t size)
{
	assert(arr);
	size_t gap = size;
	while (gap > 1)
	{
		//��gap > 1ʱ��ΪԤ���������б�ýӽ�����
		//gap == 1ʱ����Ϊֱ�Ӳ�������
		gap /= 3;
		if (gap == 0)
		{
			gap = 1;
		}
		for (size_t i = 0; i < size - gap; i++)
		{
			int end = i;
			int tmp = *(arr + i + gap);
			while (end >= 0 && *(arr + end) > tmp)
			{
				*(arr + end + gap) = *(arr + end);
				end -= gap;
			}
			*(arr + end + gap) = tmp;
		}
	}
}

void SelectSort(int* arr, size_t size)
{
	assert(arr);
	int index = 0;
	for (size_t i = 0; i < size - 1; i++)
	{
		int min = *(arr + i);
		index = i;
		//�ҳ���С�����±�
		for (size_t j = i + 1; j < size; j++)
		{
			if (min > *(arr + j))
			{
				min = *(arr + j);
				index = j;
			}
		}
		Swap(arr + i, arr + index);
	}
}

void BubbleSort(int* arr, size_t size)
{
	assert(arr);
	while (size--)
	{
		int flag = 0;
		for (int i = 0; i < size; i++)
		{
			if (*(arr + i) > *(arr + i + 1))
			{
				flag = 1;
				Swap(arr + i, arr + i + 1);
			}
		}
		if (flag == 0)
		{
			return;
		}
	}
}

static int PartSort1(int* arr, int left, int right)
{
	assert(arr && left < right);
	int key = arr[right];
	int head = left;
	int tail = right;
	while (head < tail)
	{
		//����ұ�Key��������ұ��ұ�KeyС����������
		while (head < tail && *(arr + head) <= key)
		{
			head++;
		}
		while (head < tail && *(arr + tail) >= key)
		{
			tail--;
		}
		Swap(arr + head, arr + tail);
	}
	Swap(arr + head, arr + right);
	return head;
}

static int PartSort2(int* arr, int left, int right)
{
	assert(arr && left < right);
	int key = arr[right];
	int head = left;
	int tail = right;
	while (head < tail)
	{
		//�ڿӣ���Keyֵ��λ�õ����ӣ����������ң�����ҵ�������Ͱ����ŵ�������ߵ�����λ�ó�Ϊ�µĿ�
		//�ұ߿�ʼ��С�������ҵ������ұߵĿ����������λ�ó�Ϊ�µĿӣ�ѭ��ֱ������ָ������
		while (head < tail && arr[head] <= key)
		{
			head++;
		}
		arr[tail] = arr[head];
		while (head < tail && arr[tail] >= key)
		{
			tail--;
		}
		arr[head] = arr[tail];
	}
	arr[head] = key;
	return head;
}

static int PartSort3(int* arr, int left, int right)
{
	assert(arr && left < right);
	int key = arr[right];
	int fast = left;
	int slow = left - 1;
	//һ����ָ��һ����ָ�룬��ָ��ʼ��ǰ������ָ��ֻ���ڵ�ǰ��С��Key����
	//����ָ��++�󲻵��ڿ�ָ�룬�򽻻�������λ��
	while (fast < right)
	{
		if (arr[fast] <= key && ++slow != fast)
		{
				Swap(arr + fast, arr + slow);
		}
		fast++;
	}
	slow++;
	Swap(arr + slow, arr + right);
	return slow;
}

void QuickSort(int* arr, int left, int right)
{
	assert(arr);
	int div = PartSort3(arr, left, right);
	if (left < div - 1)
	{
		//�ݹ�������仮��
		QuickSort(arr, left, div - 1);
	}
	if (right > div + 1)
	{
		QuickSort(arr, div + 1, right);
	}
}

void MergeSort(int* arr, int size)
{
	//�鲢��Ҫ��ʱ�ռ�
	int* tmp = (int*)malloc(sizeof(int) * size);
	PartMergeSort(arr, 0, size - 1, tmp);
	free(tmp);
}

static void PartMergeSort(int* arr, int left, int right, int* tmp)
{
	if (left >= right)
	{
		return;
	}
	int mid = (left + right) / 2;//ȡ�м����ֳ������ֵݹ���й鲢
	PartMergeSort(arr, left, mid, tmp);
	PartMergeSort(arr, mid + 1, right, tmp);

	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int index = left;
	while (begin1 <= end1 && begin2 <= end2)
	{
		//��ԭ������ȡ���ݣ�����鲢����ʱ�ռ���
		if (arr[begin1] <= arr[begin2])
		{
			tmp[index++] = arr[begin1++];
		}
		else
		{
			tmp[index++] = arr[begin2++];
		}
	}
	//���������ֱض���һ���ֻ�û���꣬���԰�ʣ�²��ּ���������ʱ�������
	if (begin1 <= end1)
	{
		memcpy(tmp + index, arr + begin1, sizeof(int) * (end1 - begin1 + 1));
	}
	else
	{
		memcpy(tmp + index, arr + begin2, sizeof(int) * (end2 - begin2 + 1));
	}
	//����ʱ�ռ�����ݷŻ�ԭ����
	memcpy(arr + left, tmp + left, sizeof(int) * (right - left + 1));
}

static void Swap(int* x1, int* x2)
{
	if (x1 == x2)
	{
		return;
	}
	*x1 ^= *x2;
	*x2 ^= *x1;
	*x1 ^= *x2;
}

static void ResetArr(int* arr)
{
	*(arr + 0) = 6;
	*(arr + 1) = 4;
	*(arr + 2) = 3;
	*(arr + 3) = 7;
	*(arr + 4) = 9;
	*(arr + 5) = 1;
	*(arr + 6) = 5;
	*(arr + 7) = 2;
	*(arr + 8) = 8;
	*(arr + 9) = 5;
}

static void PrintArr(int* arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		printf("%d ", *(arr + i));
	}
	printf("\n");
}

void TestSort()
{
	int arr[10] = { 6,4,3,7,9,1,5,2,8,5 };
	PrintArr(arr, 10);
	
	SelectSort(arr, 10);
	PrintArr(arr, 10);
	ResetArr(arr);

	ShellSort(arr, 10);
	PrintArr(arr, 10);
	ResetArr(arr);

	InsertSort(arr, 10);
	PrintArr(arr, 10);
	ResetArr(arr);

	BubbleSort(arr, 10);
	PrintArr(arr, 10);
	ResetArr(arr);

	QuickSort(arr, 0, 9);
	PrintArr(arr, 10);
	ResetArr(arr);

	MergeSort(arr, 10);
	PrintArr(arr, 10);
}