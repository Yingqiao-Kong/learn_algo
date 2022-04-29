#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

void _merge(int *a, int p, int q, int r) {
	int n = r - p + 1;
	int *tmp = (int *)malloc(sizeof(int) * n);
	assert(tmp != NULL);
	int k = 0;
	int i = p, j = q + 1;
	while (i <= q && j <= r) {
		if (a[i] <= a[j])
			tmp[k++] = a[i++];
		else
			tmp[k++] = a[j++];
	}
	//判断哪个数组有剩余数据，将剩余数据拷贝到tmp数组
	int start = i, end = q;
	if (i == q + 1) {
		start = j;
		end = r;
	}
	while (start <= end) {
		tmp[k++] = a[start++];
	}
	//注意此处copy到a + p,并且拷贝大小是n * sizeof(int)
	memcpy(a + p, tmp, n * sizeof(int));
	free(tmp);

	return;
}

void _merge_guard(int *a, int p, int q, int r) {
	//构建左右临时数组，然后将左右数组合并到原数组
	int *tmp_left = (int *)malloc(sizeof(int) * (q - p + 2));
	int *tmp_right = (int *)malloc(sizeof(int) * (r - q + 2));
	int i, j, left, right;
	//[p, q] [q + 1, r]
	//tmp_left tmp_right的末位都加哨兵值INT_MAX
	for (i = p, left = 0; i <= q; i++, left++)
	       tmp_left[left] = a[i];
	tmp_left[left++] = INT_MAX;

	for (j = q + 1, right = 0; j <= r; j++, right++)
		tmp_right[right] = a[j];
	tmp_right[right++] = INT_MAX;

	for (int k = p, i = 0, j = 0; k <= r; k++) {
		if (tmp_left[i] <= tmp_right[j])
			a[k] = tmp_left[i++];
		else
			a[k] = tmp_right[j++];
	}

	free(tmp_left);
	free(tmp_right);
	return;
}

void _merge_sort(int *a, int p, int r) {
	//取中间点q，对前后部分分别排序，再将排好序的两部分合并在一起
	//递归终止条件，p >= r
	if (p >= r)
		return;
	int q = (p + r) / 2;
	_merge_sort(a, p, q);
	_merge_sort(a, q + 1, r);
	//_merge(a, p, q, r);
	_merge_guard(a, p, q, r);
}

void merge_sort(int *a, int n) {
	_merge_sort(a, 0, n - 1);
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
	merge_sort(test, size);
	dump(test, size);

	return 0;
}
