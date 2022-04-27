#include <stdlib.h>
#include <stdio.h>

//这种方法必须保证x != y
#define swap1(x, y) {x ^= y; y ^= x; x ^= y;}
#define swap2(x, y) {typeof(x) t = x; x = y; y =t;}

//这种分区方法效率很低
int partion(int *a, int p, int r) {
	//[p, r],pivot = r
	int pi_val = a[r];
	//比a[pivot]小的值都放在pivot左侧，比a[pivot]大的值放在pivot右侧
	int i = p, j = p;
	//a[p, i - 1]的值都小于pivot, 已处理区间；
	//a[i, r - 1]的值都大于pivot，未处理区间.
	//从a[i, r - 1]中取出a[j]与pivot比较，如果小于pivot，将其放到已处理区间尾部a[i]的位置，swap(a[i], a[j]),i++
	//a[i]始终是第一个大于pivot的位置
	while (j <= r - 1) {
		if (a[j] < pi_val) {
			//一定要判断i != j
			//if (i != j)
			//	swap1(a[j], a[i]);
			swap2(a[j], a[i]);
			i++;
		}
		j++;
	}
	//小于pivot pivot 大于pivot
	//if (i != r)
	//	swap1(a[i], a[r]);
	swap2(a[i], a[r]);
	return i;
}

int random_partion(int *a, int p, int r) {
	int i = p + rand() % (r - p + 1);
	if (i != r)
		swap1(a[i], a[r]);
	return partion(a, p, r);
}

void _quick_sort(int *a, int p, int r) {
	if (p >= r)
		return;
	//返回pivot在数组中的下标位置,固定下来
	//随机生成pivot避免极端情况
	int pivot = random_partion(a, p, r);
	//int pivot = partion(a, p, r);
	//[p, pivot - 1] [pivot + 1, q]
	_quick_sort(a, p, pivot - 1);
	_quick_sort(a, pivot + 1, r);
}

void quick_sort(int *a, int n) {
	_quick_sort(a, 0, n - 1);
	return;
}
void dump(int *a, int n) {
        for (int i = 0; i < n; i++)
                printf("%d ", a[i]);
        printf("\n");

        return;
}

int main() {
        int test[12] = {11, 8, 3, 8, 9, 7, 1, 1, 2, 5, 16, 15};
        int size = sizeof(test) / sizeof(int);
        quick_sort(test, size);
        dump(test, size);

        return 0;
}
