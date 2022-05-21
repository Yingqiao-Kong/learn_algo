/**
 * 堆排序分为两步：建堆+排序
 * 建堆:从后往前处理数组，对每个数据从上往下堆化
 * 自上而下堆化:比较父子节点，对不满足父节点>=子节点的，将父节点和较大的子节点互换位置，重复此过程
 */
void swap(int *nums, int index1, int index2) {
	int tmp = nums[index1];
	nums[index1] = nums[index2];
	nums[index2] = tmp;
}

//自上而下堆化
void heapify(int *nums, int n, int i) {     //当前下沉的节点i
	int max_pos = i;
	while(true) {   //父节点i
	if (i * 2 + 1 < n && nums[max_pos] < nums[i * 2 + 1])    //左子节点i*2+1
		max_pos = i * 2 + 1;
	if (i * 2 + 2 < n && nums[max_pos] < nums[i * 2 + 2])    //右子节点i*2+2
		max_pos = i * 2 + 2;
	if (max_pos == i)           //父节点>=子节点，满足堆的性质，退出
		break;
	swap(nums, max_pos, i);     //将父节点和较大的子节点互换位置
	i = max_pos;        //继续向下堆化
	}
}

//建堆：从最后一个非叶子节点(n-1)/2开始堆化，向前一直到节点0
void build_heap(int *nums, int n) {
	for (int i = (n - 1) / 2; i >= 0; i--)
	heapify(nums, n, i);
}

//建堆结束，nums是一个大顶堆，堆顶元素是当前堆最大的数据，将堆顶元素跟当前最后一个元素交换，最大的数据就放到了数组索引n-1
//将移除了堆顶元素的堆，再次调整堆化，然后将堆顶元素放到索引n-2
//以此类推，知道堆里只剩下最后一个元素
void sort(int *nums, int n) {
	int tail = n - 1;   //nums[0]是堆顶，nums[tail]是待交换的数组索引
	while (tail > 0) {  //当堆只剩下一个元素，退出
		swap(nums, 0, tail);    //将堆顶和数组索引tail交换,堆大小-1,堆化
		heapify(nums, tail, 0);
		tail--;
	}
}

void heap_sort(int *nums, int n) {
	build_heap(nums, n);
	sort(nums, n);
}

