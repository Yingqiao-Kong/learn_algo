#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//注意swap与()中间不能加空格
//#define swap(a, b) do {typeof(a) t = (a); (a) = (b); (b) = t;} while(0)
#define swap(x, y) do {x ^= y; y ^= x; x ^= y;} while(0)	//只适用于整型，速度快
//#define swap(a, b) do {a += b; b = a - b; a -= b;} while(0)	//容易溢出

void dump(int *a, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	return;
}

//冒泡排序
void bubble_sort(int *a, int size) {
	if (size <= 1)
		return;
	//标记循环的趟数
	for (int i = 0; i < size - 1; i++) {
		//提前退出冒泡排序的标志位
		bool flag = false;
		//注意j的起始位置
		for (int j = 0; j < size - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
				flag = true;
			}
		}
		if (flag == false)	break;
	}
	return;
}

void insert_sort(int *a, int size) {
	if (size <= 1)
		return;
	//分为已排序列和未排序列
	//未排序列
	for (int i = 1; i < size; i++) {
		//将a[i]插入已经排好的序列[0, i - 1]
		int val = a[i];
		int j;
		for (j = i - 1; j >= 0; j--) {
			if (val < a[j])
				a[j + 1] = a[j];
			else
				break;
		}
		a[j + 1] = val;	//注意此处a[j + 1]而不是a[j]
	}
	return;
}

void select_sort(int *a, int size) {
	if (size <= 1)
		return;
	//已排序列的尾i - 1
	for (int i = 0; i < size - 1; i++) {
		//选取待排序列[i, size - 1]中最小值
		int min = i;
		for (int j = i + 1; j < size; j++) {
			if (a[j] < a[min])
				min = j;
		}
		//将min放到已排序列的尾i - 1后面i
		if (min != i)
			swap(a[i], a[min]);
	}
	return;
}

int main() {
	int a[7] = {4, 5, 6, 1, 3, 2, 3};
	int n = sizeof(a) / sizeof(int);
	//bubble_sort(a, n);
	//printf("bubble sort ");
	insert_sort(a, n);
	printf("insert sort ");
	//select_sort(a, n);
	//printf("select sort ");
	dump(a, n);

	return 0;
}
