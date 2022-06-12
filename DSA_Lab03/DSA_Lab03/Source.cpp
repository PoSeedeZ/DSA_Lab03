#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <sstream>
#include <string>
using namespace std;
using namespace std::chrono;
template <class T>
void HoanVi(T& a, T& b)
{
	T x = a;
	a = b;
	b = x;
}
void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % n;
	}
}
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}
void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int r1 = rand() % n;
		int r2 = rand() % n;
		HoanVi(a[r1], a[r2]);
	}
}
void GenerateData(int a[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// ngẫu nhiên
		GenerateRandomData(a, n);
		break;
	case 1:	// có thứ tự
		GenerateSortedData(a, n);
		break;
	case 2:	// có thứ tự ngược
		GenerateReverseData(a, n);
		break;
	case 3:	// gần như có thứ tự
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}
void heapifyCmp(int*& a, int n, int i, long long& countcompare) {
	int root = i;
	int child = i * 2 + 1;

	if (++countcompare && child < n - 1 && ++countcompare && a[child] < a[child + 1])
		child += 1;

	if (++countcompare && child < n && ++countcompare && a[root] < a[child])
		root = child;

	if (++countcompare && root != i) {
		swap(a[i], a[root]);
		heapifyCmp(a, n, root, countcompare);
	}
}
void heapSortCmp(int*& a, int n, long long& countcompare) {
	countcompare = 0;
	for (int i = n / 2 - 1; ++countcompare && i >= 0; i--)  heapifyCmp(a, n, i, countcompare);
	for (int i = n - 1; ++countcompare && i >= 0; i--) {
		swap(a[0], a[i]);
		heapifyCmp(a, i, 0, countcompare);
	}
}
void heapify(int*& a, int n, int i) {
	int root = i;
	int child = i * 2 + 1;

	if (child < n - 1 && a[child] < a[child + 1])
		child += 1;

	if (child < n && a[root] < a[child])
		root = child;

	if (root != i) {
		swap(a[i], a[root]);
		heapify(a, n, root);
	}
}
void heapSort(int*& a, int n) {
	for (int i = n / 2 - 1; i >= 0; i--)  heapify(a, n, i);
	for (int i = n - 1; i >= 0; i--) {
		swap(a[0], a[i]);
		heapify(a, i, 0);
	}
}
void insertionSortCmp(int*& a, int n, long long& countcompare) {
	countcompare = 0;
	for (int i = 1; ++countcompare && i < n; i++) {
		int flag = a[i];
		int j = i - 1;
		for (; ++countcompare && j >= 0 && ++countcompare && flag < a[j]; --j) {
			a[j + 1] = a[j];
		}
		a[j + 1] = flag;
	}
}
void insertionSort(int*& a, int n) {
	for (int i = 1; i < n; i++) {
		int flag = a[i];
		int j = i - 1;
		for (; j >= 0 && flag < a[j]; --j) {
			a[j + 1] = a[j];
		}
		a[j + 1] = flag;
	}
}
void countingSortCmp(int*& a, int n, long long& countcompare) {
	int max = a[0];
	int* temp = new int[n];
	countcompare = 0;
	//findMax
	for (int i = 0; ++countcompare && i < n; i++) {
		if (a[i] > max)
			max = a[i];
	}
	//assign 0 to b
	int* b = new int[max + 1];
	for (int i = 0; ++countcompare && i <= max; i++) {
		b[i] = 0;
	}
	//count appearance of each element
	for (int i = 0; ++countcompare && i < n; i++) {
		b[a[i]]++;
	}
	//cumulative count
	for (int i = 1; ++countcompare && i <= max; i++) {
		b[i] += b[i - 1];
	}
	//place element to temp by index hold by b
	for (int i = n - 1; ++countcompare && i >= 0; i--) {
		temp[b[a[i]] - 1] = a[i];
		b[a[i]]--;
	}
	//coppy temp to a
	for (int i = 0; ++countcompare && i < n; i++) {
		a[i] = temp[i];
	}
	delete[]b;
	delete[]temp;
}
void countingSort(int*& a, int n) {
	int max = a[0];
	int* temp = new int[n];
	//findMax
	for (int i = 0; i < n; i++) {
		if (a[i] > max)
			max = a[i];
	}
	//assign 0 to b
	int* b = new int[max + 1];
	for (int i = 0; i <= max; i++) {
		b[i] = 0;
	}
	//count appearance of each element
	for (int i = 0; i < n; i++) {
		b[a[i]]++;
	}
	//cumulative count
	for (int i = 1; i <= max; i++) {
		b[i] += b[i - 1];
	}
	//place element to temp by index hold by b
	for (int i = n - 1; i >= 0; i--) {
		temp[b[a[i]] - 1] = a[i];
		b[a[i]]--;
	}
	//coppy temp to a
	for (int i = 0; i < n; i++) {
		a[i] = temp[i];
	}
	delete[]b;
	delete[]temp;
}
int getMaxCmp(int*& arr, int n, long long& count_compare)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
	{
		++count_compare;
		if (arr[i] > mx)
		{
			mx = arr[i];
		}
	}
	return mx;
}
int getMax(int*& arr, int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
	{
		if (arr[i] > mx)
		{
			mx = arr[i];
		}
	}
	return mx;
}
void countSort(int*& arr, int n, int exp)
{
	int* output = new int[n]; //final output
	int i, count[10] = { 0 };
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];
	for (i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	for (i = 0; i < n; i++)
		arr[i] = output[i];
}
void countSortCmp(int*& arr, int n, int exp, long long& count_compare)
{
	int* output = new int[n]; //final output
	int i, count[10] = { 0 };
	for (i = 0; ++count_compare, i < n; i++)
		count[(arr[i] / exp) % 10]++;
	for (i = 1; ++count_compare, i < 10; i++)
		count[i] += count[i - 1];
	for (i = n - 1; ++count_compare, i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	for (i = 0; ++count_compare, i < n; i++)
		arr[i] = output[i];
}
void radixSortCmp(int*& arr, int n, long long& count_compare)
{

	int m = getMaxCmp(arr, n, count_compare);
	for (int exp = 1; ++count_compare, m / exp > 0; exp *= 10)
		countSortCmp(arr, n, exp, count_compare);
}
void radixSort(int*& arr, int n)
{

	int m = getMax(arr, n);
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}
void shakerSort(int*& a, int n)
{
	int left = 0;
	int right = n - 1;
	int k = n;
	do
	{
		for (int j = right; j >= left; j--)
		{
			if (a[j - 1] > a[j])
			{
				swap(a[j - 1], a[j]);
				k = j;
			}
		}
		left = k + 1;
		for (int j = left; j <= right; j++)
		{
			if (a[j - 1] > a[j])
			{
				swap(a[j - 1], a[j]);
				k = j;
			}
		}
		right = k - 1;
	} while (left <= right);
}
void shakerSortCmp(int*& a, int n, long long& count_compare)
{
	int left = 0;
	int right = n - 1;
	int k = n;
	do
	{
		for (int j = right; j >= left; j--)
		{
			++count_compare;
			if (a[j - 1] > a[j])
			{
				swap(a[j - 1], a[j]);
				k = j;
			}
		}
		left = k + 1;
		for (int j = left; j <= right; j++)
		{
			++count_compare;
			if (a[j - 1] > a[j])
			{
				swap(a[j - 1], a[j]);
				k = j;
			}
		}
		right = k - 1;
	} while (left <= right);
}
void mergeCmp(int*& a, int l, int m, int r, long long& count_Compare) {
	int i, j, k;
	count_Compare = 0;
	int n1 = m - l + 1;
	int n2 = r - m;
	int* L, * R;
	L = new int[n1];
	R = new int[n2];
	for (i = 0; ++count_Compare, i < n1; i++) {
		L[i] = a[l + i];
	}
	for (j = 0; ++count_Compare, j < n2; j++) {
		R[j] = a[m + j + 1];
	}
	i = 0;
	j = 0;
	k = l;
	while (++count_Compare && i < n1 && ++count_Compare && j < n2) {
		if (++count_Compare && L[i] <= R[j]) {

			a[k] = L[i];
			i++;
		}
		else {
			count_Compare++;
			a[k] = R[j];
			j++;
		}
		k++;
	}
	while (++count_Compare && i < n1) {
		a[k] = L[i];
		i++;
		k++;
	}
	while (++count_Compare && j < n2) {
		a[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortCmp(int*& a, int l, int r, long long& count_Compare) {
	if (++count_Compare && l < r) {
		int m = l + (r - l) / 2;
		mergeSortCmp(a, l, m, count_Compare);
		mergeSortCmp(a, m + 1, r, count_Compare);
		mergeCmp(a, l, m, r, count_Compare);
	}
}
void selectionSortCmp(int*& a, int n, long long& count_Compare) {
	int indexMin;
	count_Compare = 0;
	for (int i = 0; ++count_Compare, i < n; i++) {
		indexMin = i;
		for (int j = i + 1; ++count_Compare, j < n; j++) {
			if (++count_Compare && a[indexMin] > a[j]) {
				indexMin = j;
			}
		}
		if (++count_Compare && i != indexMin) {
			HoanVi(a[i], a[indexMin]);
		}
	}
}
void insertionSortForFlashCmp(int*& a, int n, long long& count_Compare) {
	int j, valua;
	for (int i = 1; ++count_Compare, i < n; i++) {
		j = i;
		int valua = a[i];
		while (++count_Compare && j > 0 && ++count_Compare && a[j - 1] > valua) {
			a[j] = a[j - 1];
			j--;
		}
		a[j] = valua;
	}
}
int Class(int number, int class_number, int min, int max) {
	return ((double)number - min) / ((double)max - min) * ((double)class_number - 1);
}
void classifyByCountingSortCmp(int*& a, int n, long long& count_Compare) {
	int const class_number = 0.1 * n;

	if (++count_Compare && class_number == 0) {
		return;
	}

	int min = *std::min(a, a + n);
	int max = *std::max(a, a + n);

	if (++count_Compare && min == max) {
		return;
	}

	long long* fre = new long long[class_number]();
	for (int i = 0; ++count_Compare, i < n; ++i) {
		fre[Class(a[i], class_number, min, max)] = 1 + fre[Class(a[i], class_number, min, max)];
	}

	for (int i = 1; ++count_Compare, i < class_number; ++i) {
		fre[i] += fre[i - 1];
	}

	long long* b = new long long[n];
	for (int i = n - 1; ++count_Compare, i >= 0; --i) {
		b[--fre[Class(a[i], class_number, min, max)]] = a[i];
	}

	for (int i = 0; ++count_Compare, i < n; ++i) {
		a[i] = b[i];
	}

	delete[] b;
	delete[] fre;
}
void flashSortCmp(int*& a, int n, long long& count_Compare) {
	count_Compare = 0;
	classifyByCountingSortCmp(a, n, count_Compare);
	insertionSortForFlashCmp(a, n, count_Compare);

	//Tham khảo https://github.com
}
void merge(int*& a, int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	int* L, * R;
	L = new int[n1];
	R = new int[n2];
	for (i = 0; i < n1; i++) {
		L[i] = a[l + i];
	}
	for (j = 0; j < n2; j++) {
		R[j] = a[m + j + 1];
	}
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {

			a[k] = L[i];
			i++;
		}
		else {

			a[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		a[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		a[k] = R[j];
		j++;
		k++;
	}
}
void mergeSort(int*& a, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		mergeSort(a, l, m);
		mergeSort(a, m + 1, r);
		merge(a, l, m, r);
	}
}
void selectionSort(int*& a, int n) {
	int indexMin;
	for (int i = 0; i < n; i++) {
		indexMin = i;
		for (int j = i + 1; j < n; j++) {
			if (a[indexMin] > a[j]) {
				indexMin = j;
			}
		}
		if (i != indexMin) {
			HoanVi(a[i], a[indexMin]);
		}
	}
}
void insertionSortForFlash(int*& a, int n) {
	int j, valua;
	for (int i = 1; i < n; i++) {
		j = i;
		int valua = a[i];
		while (j > 0 && a[j - 1] > valua) {
			a[j] = a[j - 1];
			j--;
		}
		a[j] = valua;
	}
}
void classifyByCountingSort(int*& a, int n) {
	int const class_number = 0.1 * n;

	if (class_number == 0) {
		return;
	}

	int min = *std::min(a, a + n);
	int max = *std::max(a, a + n);

	if (min == max) {
		return;
	}

	long long* fre = new long long[class_number]();
	for (int i = 0; i < n; ++i) {
		fre[Class(a[i], class_number, min, max)] = 1 + fre[Class(a[i], class_number, min, max)];
	}

	for (int i = 1; i < class_number; ++i) {
		fre[i] += fre[i - 1];
	}

	long long* b = new long long[n];
	for (int i = n - 1; i >= 0; --i) {
		b[--fre[Class(a[i], class_number, min, max)]] = a[i];
	}

	for (int i = 0; i < n; ++i) {
		a[i] = b[i];
	}

	delete[] b;
	delete[] fre;
}
void flashSort(int*& a, int n) {
	classifyByCountingSort(a, n);
	insertionSortForFlash(a, n);

	//Tham khảo https://github.com
}
void bubbleSortCmp(int*& a, int n, long long& countCompare)
{
	++countCompare;
	for (int i = 1; i < n; i = i + 1)
	{
		++countCompare;
		for (int j = n - 1; j >= i; j = j - 1)
		{
			if (++countCompare && a[j] < a[j - 1])
			{
				swap(a[j], a[j - 1]);
			}
		}
	}
}
void bubbleSort(int*& a, int n)
{
	for (int i = 1; i < n; i = i + 1)
	{
		for (int j = n - 1; j >= i; j = j - 1)
		{
			if (a[j] < a[j - 1])
			{
				swap(a[j], a[j - 1]);
			}
		}
	}
}
int partitionCmp(int*& a, int left, int right, long long& countCompare) {
	swap(a[left + (right - left) / 2], a[left]);
	int pivot = a[left];
	int i = left + 1;
	int j = right;
	do {
		while (++countCompare && i <= right && a[i] < pivot)
		{
			++i;
		}

		while (++countCompare && j > left && a[j] >= pivot)
		{
			--j;
		}
		if (++countCompare && i < j)
		{
			swap(a[i], a[j]);
		}
	} while (++countCompare && i < j);
	swap(a[j], a[left]);
	return j;
}
int partition(int*& a, int left, int right) {
	swap(a[left + (right - left) / 2], a[left]);
	int pivot = a[left];
	int i = left + 1;
	int j = right;
	do {
		while (i <= right && a[i] < pivot)
		{
			++i;
		}

		while (j > left && a[j] >= pivot)
		{
			--j;
		}
		if (i < j)
		{
			swap(a[i], a[j]);
		}
	} while (i < j);
	swap(a[j], a[left]);
	return j;
}
void quickSortCmp(int*& a, int left, int right, long long& countCompare) {
	if (++countCompare && left < right) {
		int p = partitionCmp(a, left, right, countCompare);
		quickSortCmp(a, left, p - 1, countCompare);
		quickSortCmp(a, p + 1, right, countCompare);
	}
}
void quickSortCmp(int*& a, int n, long long& countCompare) {
	if (++countCompare && n > 1) {
		quickSortCmp(a, 0, n - 1, countCompare);
	}
}
void quickSort(int*& a, int left, int right) {
	if (left < right) {
		int p = partition(a, left, right);
		quickSort(a, left, p - 1);
		quickSort(a, p + 1, right);
	}
}
void quickSort(int*& a, int n) {
	if (n > 1) {
		quickSort(a, 0, n - 1);
	}
}
void shellSortCmp(int*& a, int n, long long& countCompare) {
	for (int gap = n / 2; gap >= 1; gap /= 2) {
		++countCompare;
		for (int k = gap; k < n; ++k) {
			++countCompare;
			int temp = a[k];
			int p;

			for (p = k - gap; p >= 0; p -= gap) {
				++countCompare;
				if (++countCompare && a[p] > temp) {
					a[p + gap] = a[p];
				}
				else {
					break;
				}
				++countCompare;
			}

			a[p + gap] = temp;
		}
		++countCompare;
	}
	++countCompare;
}
void shellSort(int*& a, int n) {
	for (int gap = n / 2; gap >= 1; gap /= 2) {
		for (int k = gap; k < n; ++k) {
			int temp = a[k];
			int p;
			for (p = k - gap; p >= 0; p -= gap) {
				if (a[p] > temp) {
					a[p + gap] = a[p];
				}
				else {
					break;
				}
			}
			a[p + gap] = temp;
		}
	}
}
void coppyToDynamicArray(int a[], int*& b, int n) {
	for (int i = 0; i < n; i++) {
		b[i] = a[i];
	}
}
bool checkCmd1(char* a) {
	string s = a;
	stringstream f(s);
	string temp;
	getline(f, temp, '.');
	getline(f, temp, '.');
	if (temp == "txt") return 1;
	return 0;
}
void cmd1(char* argv[]) {
	ifstream fi(argv[3]);
	int n;
	long long cmp = 0;
	string temp;
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point stop;
	getline(fi, temp);
	n = stoi(temp);
	int* a = new int[n];
	int* b = new int[n];
	getline(fi, temp);
	stringstream s(temp);
	for (int i = 0; i < n; i++) {
		string j;
		getline(s, j, ' ');
		b[i] = stoi(j);
		a[i] = b[i];
	}
	fi.close();
	if (argv[2] == std::string("bubble-sort")) {
		if (argv[4] == std::string("-time")) {
			start = high_resolution_clock::now();
			bubbleSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				bubbleSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				bubbleSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				bubbleSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("selection-sort")) {
		if (argv[4] == std::string("-time")) {
			start = high_resolution_clock::now();
			selectionSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				selectionSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				selectionSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				selectionSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("insertion-sort")) {
		if (argv[4] == std::string("-time")) {
			start = high_resolution_clock::now();
			insertionSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				insertionSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				insertionSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				insertionSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("heap-sort")) {
		if (argv[4] == std::string("-time")) {
			start = high_resolution_clock::now();
			heapSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				heapSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				heapSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				heapSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("shaker-sort")) {
		if (argv[4] == std::string("-time")) {
			start = high_resolution_clock::now();
			shakerSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				shakerSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				shakerSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				shakerSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("shell-sort")) {
		if (argv[4] == std::string("-time")) {
			start = high_resolution_clock::now();
			shellSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				shellSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				shellSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				shellSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("merge-sort")) {
		if (argv[4] == std::string("-time")) {
			start = high_resolution_clock::now();
			mergeSort(b, 0, n - 1);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				mergeSortCmp(b, 0, n - 1, cmp);
			}
			else {
				start = high_resolution_clock::now();
				mergeSort(b, 0, n - 1);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				mergeSortCmp(b, 0, n - 1, cmp);
			}
		}
	}
	if (argv[2] == std::string("quick-sort")) {
		if (argv[4] == std::string("-time")) {
			start = high_resolution_clock::now();
			quickSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				quickSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				quickSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				quickSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("counting-sort")) {
		if (argv[4] == std::string("-time")) {
			start = high_resolution_clock::now();
			countingSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				countingSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				countingSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				countingSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("radix-sort")) {
		if (argv[4] == std::string("-time")) {
			start = high_resolution_clock::now();
			radixSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				radixSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				radixSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				radixSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("flash-sort")) {
		if (argv[4] == std::string("-time")) {
			start = high_resolution_clock::now();
			flashSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				flashSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				flashSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				flashSortCmp(b, n, cmp);
			}
		}
	}
	cout << "ALGORTHM MODE: " << "\n";
	cout << "Algorithm: " << argv[2] << "\n";
	cout << "Input file: " << argv[3] << "\n";
	cout << "Input size: " << n << "\n";
	cout << "-----------------------" << "\n";
	if (argv[4] == std::string("-time")) {
		auto timing = duration_cast<milliseconds>(stop - start);
		cout << "running time: " << timing.count() << " ms\n";
	}
	else {
		if (argv[4] == std::string("-comp")) {
			cout << "Comparisions: " << cmp << "\n";
		}
		else {
			auto timing = duration_cast<milliseconds>(stop - start);
			cout << "Running time: " << timing.count() << " ms\n";
			cout << "Comparisions: " << cmp << "\n";
		}

	}
	ofstream fo("output.txt");
	fo << n << "\n";
	for (int i = 0; i < n; i++) {
		fo << b[i] << " ";
	}
	fo.close();
	delete[]b;
}
void cmd2(char* argv[]) {
	int n = stoi(argv[3]);
	int* a = new int[n];
	int* b = new int[n];
	if (argv[4] == std::string("-rand")) {
		GenerateData(a, n, 0);
		coppyToDynamicArray(a, b, n);
	}
	if (argv[4] == std::string("-sorted")) {
		GenerateData(a, n, 1);
		coppyToDynamicArray(a, b, n);
	}
	if (argv[4] == std::string("-rev")) {
		GenerateData(a, n, 2);
		coppyToDynamicArray(a, b, n);
	}
	if (argv[4] == std::string("-nsorted")) {
		GenerateData(a, n, 3);
		coppyToDynamicArray(a, b, n);
	}
	ofstream fo1("input.txt");
	fo1 << n << "\n";
	for (int i = 0; i < n; i++) {
		fo1 << b[i] << " ";
	}
	fo1.close();
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point stop;
	long long cmp = 0;
	if (argv[2] == std::string("bubble-sort")) {
		if (argv[5] == std::string("-time")) {
			start = high_resolution_clock::now();
			bubbleSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[5] == std::string("-comp")) {
				bubbleSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				bubbleSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				bubbleSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("selection-sort")) {
		if (argv[5] == std::string("-time")) {
			start = high_resolution_clock::now();
			selectionSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[5] == std::string("-comp")) {
				selectionSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				selectionSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				selectionSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("insertion-sort")) {
		if (argv[5] == std::string("-time")) {
			start = high_resolution_clock::now();
			insertionSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[5] == std::string("-comp")) {
				insertionSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				insertionSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				insertionSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("heap-sort")) {
		if (argv[5] == std::string("-time")) {
			start = high_resolution_clock::now();
			heapSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[5] == std::string("-comp")) {
				heapSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				heapSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				heapSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("shaker-sort")) {
		if (argv[5] == std::string("-time")) {
			start = high_resolution_clock::now();
			shakerSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[5] == std::string("-comp")) {
				shakerSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				shakerSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				shakerSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("shell-sort")) {
		if (argv[5] == std::string("-time")) {
			start = high_resolution_clock::now();
			shellSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[5] == std::string("-comp")) {
				shellSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				shellSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				shellSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("merge-sort")) {
		if (argv[5] == std::string("-time")) {
			start = high_resolution_clock::now();
			mergeSort(b, 0, n - 1);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[5] == std::string("-comp")) {
				mergeSortCmp(b, 0, n - 1, cmp);
			}
			else {
				start = high_resolution_clock::now();
				mergeSort(b, 0, n - 1);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				mergeSortCmp(b, 0, n - 1, cmp);
			}
		}
	}
	if (argv[2] == std::string("quick-sort")) {
		if (argv[5] == std::string("-time")) {
			start = high_resolution_clock::now();
			quickSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[5] == std::string("-comp")) {
				quickSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				quickSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				quickSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("counting-sort")) {
		if (argv[5] == std::string("-time")) {
			start = high_resolution_clock::now();
			countingSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[5] == std::string("-comp")) {
				countingSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				countingSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				countingSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("radix-sort")) {
		if (argv[5] == std::string("-time")) {
			start = high_resolution_clock::now();
			radixSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[5] == std::string("-comp")) {
				radixSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				radixSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				radixSortCmp(b, n, cmp);
			}
		}
	}
	if (argv[2] == std::string("flash-sort")) {
		if (argv[5] == std::string("-time")) {
			start = high_resolution_clock::now();
			flashSort(b, n);
			stop = high_resolution_clock::now();
		}
		else {
			if (argv[5] == std::string("-comp")) {
				flashSortCmp(b, n, cmp);
			}
			else {
				start = high_resolution_clock::now();
				flashSort(b, n);
				stop = high_resolution_clock::now();
				coppyToDynamicArray(a, b, n);
				flashSortCmp(b, n, cmp);
			}
		}
	}
	cout << "ALGORTHM MODE: " << "\n";
	cout << "Algorithm: " << argv[2] << "\n";
	cout << "Input size: " << n << "\n";
	cout << "Input order: " << argv[4] << "\n";
	cout << "-----------------------" << "\n";
	if (argv[5] == std::string("-time")) {
		auto timing = duration_cast<milliseconds>(stop - start);
		cout << "running time: " << timing.count() << " ms\n";
	}
	else {
		if (argv[5] == std::string("-comp")) {
			cout << "Comparisions: " << cmp << "\n";
		}
		else {
			auto timing = duration_cast<milliseconds>(stop - start);
			cout << "running time: " << timing.count() << " ms\n";
			cout << "Comparisions: " << cmp << "\n";
		}
	}
	ofstream fo2("output.txt");
	fo2 << n << "\n";
	for (int i = 0; i < n; i++) {
		fo2 << b[i] << " ";
	}
	fo2.close();
	delete[]b;
}
void cmd3(char* argv[]) {
	int n = stoi(argv[3]);
	int* a0 = new int[n];
	int* a1 = new int[n];
	int* a2 = new int[n];
	int* a3 = new int[n];
	long long cmp0 = 0;
	long long cmp1 = 0;
	long long cmp2 = 0;
	long long cmp3 = 0;
	high_resolution_clock::time_point start0;
	high_resolution_clock::time_point start1;
	high_resolution_clock::time_point start2;
	high_resolution_clock::time_point start3;
	high_resolution_clock::time_point stop0;
	high_resolution_clock::time_point stop1;
	high_resolution_clock::time_point stop2;
	high_resolution_clock::time_point stop3;
	int* random = new int[n];
	int* nsorted = new int[n];
	int* sorted = new int[n];
	int* reversed = new int[n];
	GenerateData(a0, n, 0);
	coppyToDynamicArray(a0, random, n);
	ofstream fo1("input_1.txt");
	fo1 << n << "\n";
	for (int i = 0; i < n; i++) {
		fo1 << random[i] << " ";
	}
	fo1.close();
	GenerateData(a1, n, 1);
	coppyToDynamicArray(a1, sorted, n);
	ofstream fo3("input_3.txt");
	fo3 << n << "\n";
	for (int i = 0; i < n; i++) {
		fo3 << sorted[i] << " ";
	}
	fo3.close();
	GenerateData(a2, n, 2);
	coppyToDynamicArray(a2, reversed, n);
	ofstream fo4("input_4.txt");
	fo4 << n << "\n";
	for (int i = 0; i < n; i++) {
		fo4 << reversed[i] << " ";
	}
	fo4.close();
	GenerateData(a3, n, 3);
	coppyToDynamicArray(a3, nsorted, n);
	ofstream fo2("input_2.txt");
	fo2 << n << "\n";
	for (int i = 0; i < n; i++) {
		fo2 << nsorted[i] << " ";
	}
	fo2.close();
	cout << "ALGORTHM MODE: " << "\n";
	cout << "Algorithm: " << argv[2] << "\n";
	cout << "Input size: " << n << "\n\n";
	if (argv[2] == std::string("bubble-sort")) {
		if (argv[4] == std::string("-time")) {
			start0 = high_resolution_clock::now();
			bubbleSort(random, n);
			stop0 = high_resolution_clock::now();
			start1 = high_resolution_clock::now();
			bubbleSort(sorted, n);
			stop1 = high_resolution_clock::now();
			start2 = high_resolution_clock::now();
			bubbleSort(reversed, n);
			stop2 = high_resolution_clock::now();
			start3 = high_resolution_clock::now();
			bubbleSort(nsorted, n);
			stop3 = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				bubbleSortCmp(random, n, cmp0);
				bubbleSortCmp(sorted, n, cmp1);
				bubbleSortCmp(reversed, n, cmp2);
				bubbleSortCmp(nsorted, n, cmp3);
			}
			else {
				start0 = high_resolution_clock::now();
				bubbleSort(random, n);
				stop0 = high_resolution_clock::now();
				start1 = high_resolution_clock::now();
				bubbleSort(sorted, n);
				stop1 = high_resolution_clock::now();
				start2 = high_resolution_clock::now();
				bubbleSort(reversed, n);
				stop2 = high_resolution_clock::now();
				start3 = high_resolution_clock::now();
				bubbleSort(nsorted, n);
				stop3 = high_resolution_clock::now();
				coppyToDynamicArray(a0, random, n);
				coppyToDynamicArray(a1, sorted, n);
				coppyToDynamicArray(a2, reversed, n);
				coppyToDynamicArray(a3, nsorted, n);
				bubbleSortCmp(random, n, cmp0);
				bubbleSortCmp(sorted, n, cmp1);
				bubbleSortCmp(reversed, n, cmp2);
				bubbleSortCmp(nsorted, n, cmp3);
			}
		}
	}
	if (argv[2] == std::string("selection-sort")) {
		if (argv[4] == std::string("-time")) {
			start0 = high_resolution_clock::now();
			selectionSort(random, n);
			stop0 = high_resolution_clock::now();
			start1 = high_resolution_clock::now();
			selectionSort(sorted, n);
			stop1 = high_resolution_clock::now();
			start2 = high_resolution_clock::now();
			selectionSort(reversed, n);
			stop2 = high_resolution_clock::now();
			start3 = high_resolution_clock::now();
			selectionSort(nsorted, n);
			stop3 = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				selectionSortCmp(random, n, cmp0);
				selectionSortCmp(sorted, n, cmp1);
				selectionSortCmp(reversed, n, cmp2);
				selectionSortCmp(nsorted, n, cmp3);
			}
			else {
				start0 = high_resolution_clock::now();
				selectionSort(random, n);
				stop0 = high_resolution_clock::now();
				start1 = high_resolution_clock::now();
				selectionSort(sorted, n);
				stop1 = high_resolution_clock::now();
				start2 = high_resolution_clock::now();
				selectionSort(reversed, n);
				stop2 = high_resolution_clock::now();
				start3 = high_resolution_clock::now();
				selectionSort(nsorted, n);
				stop3 = high_resolution_clock::now();
				coppyToDynamicArray(a0, random, n);
				coppyToDynamicArray(a1, sorted, n);
				coppyToDynamicArray(a2, reversed, n);
				coppyToDynamicArray(a3, nsorted, n);
				selectionSortCmp(random, n, cmp0);
				selectionSortCmp(sorted, n, cmp1);
				selectionSortCmp(reversed, n, cmp2);
				selectionSortCmp(nsorted, n, cmp3);
			}
		}
	}
	if (argv[2] == std::string("insertion-sort")) {
		if (argv[4] == std::string("-time")) {
			start0 = high_resolution_clock::now();
			insertionSort(random, n);
			stop0 = high_resolution_clock::now();
			start1 = high_resolution_clock::now();
			insertionSort(sorted, n);
			stop1 = high_resolution_clock::now();
			start2 = high_resolution_clock::now();
			insertionSort(reversed, n);
			stop2 = high_resolution_clock::now();
			start3 = high_resolution_clock::now();
			insertionSort(nsorted, n);
			stop3 = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				insertionSortCmp(random, n, cmp0);
				insertionSortCmp(sorted, n, cmp1);
				insertionSortCmp(reversed, n, cmp2);
				insertionSortCmp(nsorted, n, cmp3);
			}
			else {
				start0 = high_resolution_clock::now();
				insertionSort(random, n);
				stop0 = high_resolution_clock::now();
				start1 = high_resolution_clock::now();
				insertionSort(sorted, n);
				stop1 = high_resolution_clock::now();
				start2 = high_resolution_clock::now();
				insertionSort(reversed, n);
				stop2 = high_resolution_clock::now();
				start3 = high_resolution_clock::now();
				insertionSort(nsorted, n);
				stop3 = high_resolution_clock::now();
				coppyToDynamicArray(a0, random, n);
				coppyToDynamicArray(a1, sorted, n);
				coppyToDynamicArray(a2, reversed, n);
				coppyToDynamicArray(a3, nsorted, n);
				insertionSortCmp(random, n, cmp0);
				insertionSortCmp(sorted, n, cmp1);
				insertionSortCmp(reversed, n, cmp2);
				insertionSortCmp(nsorted, n, cmp3);
			}
		}
	}
	if (argv[2] == std::string("heap-sort")) {
		if (argv[4] == std::string("-time")) {
			start0 = high_resolution_clock::now();
			heapSort(random, n);
			stop0 = high_resolution_clock::now();
			start1 = high_resolution_clock::now();
			heapSort(sorted, n);
			stop1 = high_resolution_clock::now();
			start2 = high_resolution_clock::now();
			heapSort(reversed, n);
			stop2 = high_resolution_clock::now();
			start3 = high_resolution_clock::now();
			heapSort(nsorted, n);
			stop3 = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				heapSortCmp(random, n, cmp0);
				heapSortCmp(sorted, n, cmp1);
				heapSortCmp(reversed, n, cmp2);
				heapSortCmp(nsorted, n, cmp3);
			}
			else {
				start0 = high_resolution_clock::now();
				heapSort(random, n);
				stop0 = high_resolution_clock::now();
				start1 = high_resolution_clock::now();
				heapSort(sorted, n);
				stop1 = high_resolution_clock::now();
				start2 = high_resolution_clock::now();
				heapSort(reversed, n);
				stop2 = high_resolution_clock::now();
				start3 = high_resolution_clock::now();
				heapSort(nsorted, n);
				stop3 = high_resolution_clock::now();
				coppyToDynamicArray(a0, random, n);
				coppyToDynamicArray(a1, sorted, n);
				coppyToDynamicArray(a2, reversed, n);
				coppyToDynamicArray(a3, nsorted, n);
				heapSortCmp(random, n, cmp0);
				heapSortCmp(sorted, n, cmp1);
				heapSortCmp(reversed, n, cmp2);
				heapSortCmp(nsorted, n, cmp3);
			}
		}
	}
	if (argv[2] == std::string("shaker-sort")) {
		if (argv[4] == std::string("-time")) {
			start0 = high_resolution_clock::now();
			shakerSort(random, n);
			stop0 = high_resolution_clock::now();
			start1 = high_resolution_clock::now();
			shakerSort(sorted, n);
			stop1 = high_resolution_clock::now();
			start2 = high_resolution_clock::now();
			shakerSort(reversed, n);
			stop2 = high_resolution_clock::now();
			start3 = high_resolution_clock::now();
			shakerSort(nsorted, n);
			stop3 = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				shakerSortCmp(random, n, cmp0);
				shakerSortCmp(sorted, n, cmp1);
				shakerSortCmp(reversed, n, cmp2);
				shakerSortCmp(nsorted, n, cmp3);
			}
			else {
				start0 = high_resolution_clock::now();
				shakerSort(random, n);
				stop0 = high_resolution_clock::now();
				start1 = high_resolution_clock::now();
				shakerSort(sorted, n);
				stop1 = high_resolution_clock::now();
				start2 = high_resolution_clock::now();
				shakerSort(reversed, n);
				stop2 = high_resolution_clock::now();
				start3 = high_resolution_clock::now();
				shakerSort(nsorted, n);
				stop3 = high_resolution_clock::now();
				coppyToDynamicArray(a0, random, n);
				coppyToDynamicArray(a1, sorted, n);
				coppyToDynamicArray(a2, reversed, n);
				coppyToDynamicArray(a3, nsorted, n);
				shakerSortCmp(random, n, cmp0);
				shakerSortCmp(sorted, n, cmp1);
				shakerSortCmp(reversed, n, cmp2);
				shakerSortCmp(nsorted, n, cmp3);
			}
		}
	}
	if (argv[2] == std::string("shell-sort")) {
		if (argv[4] == std::string("-time")) {
			start0 = high_resolution_clock::now();
			shellSort(random, n);
			stop0 = high_resolution_clock::now();
			start1 = high_resolution_clock::now();
			shellSort(sorted, n);
			stop1 = high_resolution_clock::now();
			start2 = high_resolution_clock::now();
			shellSort(reversed, n);
			stop2 = high_resolution_clock::now();
			start3 = high_resolution_clock::now();
			shellSort(nsorted, n);
			stop3 = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				shellSortCmp(random, n, cmp0);
				shellSortCmp(sorted, n, cmp1);
				shellSortCmp(reversed, n, cmp2);
				shellSortCmp(nsorted, n, cmp3);
			}
			else {
				start0 = high_resolution_clock::now();
				shellSort(random, n);
				stop0 = high_resolution_clock::now();
				start1 = high_resolution_clock::now();
				shellSort(sorted, n);
				stop1 = high_resolution_clock::now();
				start2 = high_resolution_clock::now();
				shellSort(reversed, n);
				stop2 = high_resolution_clock::now();
				start3 = high_resolution_clock::now();
				shellSort(nsorted, n);
				stop3 = high_resolution_clock::now();
				coppyToDynamicArray(a0, random, n);
				coppyToDynamicArray(a1, sorted, n);
				coppyToDynamicArray(a2, reversed, n);
				coppyToDynamicArray(a3, nsorted, n);
				shellSortCmp(random, n, cmp0);
				shellSortCmp(sorted, n, cmp1);
				shellSortCmp(reversed, n, cmp2);
				shellSortCmp(nsorted, n, cmp3);
			}
		}
	}
	if (argv[2] == std::string("merge-sort")) {
		if (argv[4] == std::string("-time")) {
			start0 = high_resolution_clock::now();
			mergeSort(random, 0, n - 1);
			stop0 = high_resolution_clock::now();
			start1 = high_resolution_clock::now();
			mergeSort(sorted, 0, n - 1);
			stop1 = high_resolution_clock::now();
			start2 = high_resolution_clock::now();
			mergeSort(reversed, 0, n - 1);
			stop2 = high_resolution_clock::now();
			start3 = high_resolution_clock::now();
			mergeSort(nsorted, 0, n - 1);
			stop3 = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				mergeSortCmp(random, 0, n - 1, cmp0);
				mergeSortCmp(sorted, 0, n - 1, cmp1);
				mergeSortCmp(reversed, 0, n - 1, cmp2);
				mergeSortCmp(nsorted, 0, n - 1, cmp3);
			}
			else {
				start0 = high_resolution_clock::now();
				mergeSort(random, 0, n - 1);
				stop0 = high_resolution_clock::now();
				start1 = high_resolution_clock::now();
				mergeSort(sorted, 0, n - 1);
				stop1 = high_resolution_clock::now();
				start2 = high_resolution_clock::now();
				mergeSort(reversed, 0, n - 1);
				stop2 = high_resolution_clock::now();
				start3 = high_resolution_clock::now();
				mergeSort(nsorted, 0, n - 1);
				stop3 = high_resolution_clock::now();
				coppyToDynamicArray(a0, random, n);
				coppyToDynamicArray(a1, sorted, n);
				coppyToDynamicArray(a2, reversed, n);
				coppyToDynamicArray(a3, nsorted, n);
				mergeSortCmp(random, 0, n - 1, cmp0);
				mergeSortCmp(sorted, 0, n - 1, cmp1);
				mergeSortCmp(reversed, 0, n - 1, cmp2);
				mergeSortCmp(nsorted, 0, n - 1, cmp3);
			}
		}
	}
	if (argv[2] == std::string("quick-sort")) {
		if (argv[4] == std::string("-time")) {
			start0 = high_resolution_clock::now();
			quickSort(random, n);
			stop0 = high_resolution_clock::now();
			start1 = high_resolution_clock::now();
			quickSort(sorted, n);
			stop1 = high_resolution_clock::now();
			start2 = high_resolution_clock::now();
			quickSort(reversed, n);
			stop2 = high_resolution_clock::now();
			start3 = high_resolution_clock::now();
			quickSort(nsorted, n);
			stop3 = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				quickSortCmp(random, n, cmp0);
				quickSortCmp(sorted, n, cmp1);
				quickSortCmp(reversed, n, cmp2);
				quickSortCmp(nsorted, n, cmp3);
			}
			else {
				start0 = high_resolution_clock::now();
				quickSort(random, n);
				stop0 = high_resolution_clock::now();
				start1 = high_resolution_clock::now();
				quickSort(sorted, n);
				stop1 = high_resolution_clock::now();
				start2 = high_resolution_clock::now();
				quickSort(reversed, n);
				stop2 = high_resolution_clock::now();
				start3 = high_resolution_clock::now();
				quickSort(nsorted, n);
				stop3 = high_resolution_clock::now();
				coppyToDynamicArray(a0, random, n);
				coppyToDynamicArray(a1, sorted, n);
				coppyToDynamicArray(a2, reversed, n);
				coppyToDynamicArray(a3, nsorted, n);
				quickSortCmp(random, n, cmp0);
				quickSortCmp(sorted, n, cmp1);
				quickSortCmp(reversed, n, cmp2);
				quickSortCmp(nsorted, n, cmp3);
			}
		}
	}
	if (argv[2] == std::string("counting-sort")) {
		if (argv[4] == std::string("-time")) {
			start0 = high_resolution_clock::now();
			countingSort(random, n);
			stop0 = high_resolution_clock::now();
			start1 = high_resolution_clock::now();
			countingSort(sorted, n);
			stop1 = high_resolution_clock::now();
			start2 = high_resolution_clock::now();
			countingSort(reversed, n);
			stop2 = high_resolution_clock::now();
			start3 = high_resolution_clock::now();
			countingSort(nsorted, n);
			stop3 = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				countingSortCmp(random, n, cmp0);
				countingSortCmp(sorted, n, cmp1);
				countingSortCmp(reversed, n, cmp2);
				countingSortCmp(nsorted, n, cmp3);
			}
			else {
				start0 = high_resolution_clock::now();
				countingSort(random, n);
				stop0 = high_resolution_clock::now();
				start1 = high_resolution_clock::now();
				countingSort(sorted, n);
				stop1 = high_resolution_clock::now();
				start2 = high_resolution_clock::now();
				countingSort(reversed, n);
				stop2 = high_resolution_clock::now();
				start3 = high_resolution_clock::now();
				countingSort(nsorted, n);
				stop3 = high_resolution_clock::now();
				coppyToDynamicArray(a0, random, n);
				coppyToDynamicArray(a1, sorted, n);
				coppyToDynamicArray(a2, reversed, n);
				coppyToDynamicArray(a3, nsorted, n);
				countingSortCmp(random, n, cmp0);
				countingSortCmp(sorted, n, cmp1);
				countingSortCmp(reversed, n, cmp2);
				countingSortCmp(nsorted, n, cmp3);
			}
		}
	}
	if (argv[2] == std::string("radix-sort")) {
		if (argv[4] == std::string("-time")) {
			start0 = high_resolution_clock::now();
			radixSort(random, n);
			stop0 = high_resolution_clock::now();
			start1 = high_resolution_clock::now();
			radixSort(sorted, n);
			stop1 = high_resolution_clock::now();
			start2 = high_resolution_clock::now();
			radixSort(reversed, n);
			stop2 = high_resolution_clock::now();
			start3 = high_resolution_clock::now();
			radixSort(nsorted, n);
			stop3 = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				radixSortCmp(random, n, cmp0);
				radixSortCmp(sorted, n, cmp1);
				radixSortCmp(reversed, n, cmp2);
				radixSortCmp(nsorted, n, cmp3);
			}
			else {
				start0 = high_resolution_clock::now();
				radixSort(random, n);
				stop0 = high_resolution_clock::now();
				start1 = high_resolution_clock::now();
				radixSort(sorted, n);
				stop1 = high_resolution_clock::now();
				start2 = high_resolution_clock::now();
				radixSort(reversed, n);
				stop2 = high_resolution_clock::now();
				start3 = high_resolution_clock::now();
				radixSort(nsorted, n);
				stop3 = high_resolution_clock::now();
				coppyToDynamicArray(a0, random, n);
				coppyToDynamicArray(a1, sorted, n);
				coppyToDynamicArray(a2, reversed, n);
				coppyToDynamicArray(a3, nsorted, n);
				radixSortCmp(random, n, cmp0);
				radixSortCmp(sorted, n, cmp1);
				radixSortCmp(reversed, n, cmp2);
				radixSortCmp(nsorted, n, cmp3);
			}
		}
	}
	if (argv[2] == std::string("flash-sort")) {
		if (argv[4] == std::string("-time")) {
			start0 = high_resolution_clock::now();
			flashSort(random, n);
			stop0 = high_resolution_clock::now();
			start1 = high_resolution_clock::now();
			flashSort(sorted, n);
			stop1 = high_resolution_clock::now();
			start2 = high_resolution_clock::now();
			flashSort(reversed, n);
			stop2 = high_resolution_clock::now();
			start3 = high_resolution_clock::now();
			flashSort(nsorted, n);
			stop3 = high_resolution_clock::now();
		}
		else {
			if (argv[4] == std::string("-comp")) {
				flashSortCmp(random, n, cmp0);
				flashSortCmp(sorted, n, cmp1);
				flashSortCmp(reversed, n, cmp2);
				flashSortCmp(nsorted, n, cmp3);
			}
			else {
				start0 = high_resolution_clock::now();
				flashSort(random, n);
				stop0 = high_resolution_clock::now();
				start1 = high_resolution_clock::now();
				flashSort(sorted, n);
				stop1 = high_resolution_clock::now();
				start2 = high_resolution_clock::now();
				flashSort(reversed, n);
				stop2 = high_resolution_clock::now();
				start3 = high_resolution_clock::now();
				flashSort(nsorted, n);
				stop3 = high_resolution_clock::now();
				coppyToDynamicArray(a0, random, n);
				coppyToDynamicArray(a1, sorted, n);
				coppyToDynamicArray(a2, reversed, n);
				coppyToDynamicArray(a3, nsorted, n);
				flashSortCmp(random, n, cmp0);
				flashSortCmp(sorted, n, cmp1);
				flashSortCmp(reversed, n, cmp2);
				flashSortCmp(nsorted, n, cmp3);
			}
		}
	}
	if (argv[4] == std::string("-both")) {
		auto timing0 = duration_cast<milliseconds>(stop0 - start0);
		auto timing1 = duration_cast<milliseconds>(stop1 - start1);
		auto timing2 = duration_cast<milliseconds>(stop2 - start2);
		auto timing3 = duration_cast<milliseconds>(stop3 - start3);
		cout << "Input order: Randonmize" << "\n";
		cout << "-----------------------" << "\n";
		cout << "running time: " << timing0.count() << " ms\n";
		cout << "Comparisions: " << cmp0 << "\n\n";
		cout << "Input order: Sorted" << "\n";
		cout << "-----------------------" << "\n";
		cout << "running time: " << timing1.count() << " ms\n";
		cout << "Comparisions: " << cmp1 << "\n\n";
		cout << "Input order: Reversed" << "\n";
		cout << "-----------------------" << "\n";
		cout << "running time: " << timing2.count() << " ms\n";
		cout << "Comparisions: " << cmp2 << "\n\n";
		cout << "Input order: Nearly Sorted" << "\n";
		cout << "-----------------------" << "\n";
		cout << "running time: " << timing3.count() << " ms\n";
		cout << "Comparisions: " << cmp3 << "\n\n";
	}
	else {
		if (argv[4] == std::string("-time")) {
			auto timing0 = duration_cast<milliseconds>(stop0 - start0);
			auto timing1 = duration_cast<milliseconds>(stop1 - start1);
			auto timing2 = duration_cast<milliseconds>(stop2 - start2);
			auto timing3 = duration_cast<milliseconds>(stop3 - start3);
			cout << "Input order: Randonmize" << "\n";
			cout << "-----------------------" << "\n";
			cout << "running time: " << timing0.count() << " ms\n\n";
			cout << "Input order: Sorted" << "\n";
			cout << "-----------------------" << "\n";
			cout << "running time: " << timing1.count() << " ms\n\n";
			cout << "Input order: Reversed" << "\n";
			cout << "-----------------------" << "\n";
			cout << "running time: " << timing2.count() << " ms\n\n";
			cout << "Input order: Nearly Sorted" << "\n";
			cout << "-----------------------" << "\n";
			cout << "running time: " << timing3.count() << " ms\n\n";
		}
		else {
			cout << "Input order: Randonmize" << "\n";
			cout << "-----------------------" << "\n";
			cout << "Comparisions: " << cmp0 << "\n\n";
			cout << "Input order: Sorted" << "\n";
			cout << "-----------------------" << "\n";
			cout << "Comparisions: " << cmp1 << "\n\n";
			cout << "Input order: Reversed" << "\n";
			cout << "-----------------------" << "\n";
			cout << "Comparisions: " << cmp2 << "\n\n";
			cout << "Input order: Nearly Sorted" << "\n";
			cout << "-----------------------" << "\n";
			cout << "Comparisions: " << cmp3 << "\n\n";
		}
	}
	delete[]random;
	delete[]nsorted;
	delete[]sorted;
	delete[]reversed;
}
void cmd4(char* argv[]) {
	ifstream fi(argv[4]);
	int n;
	long long cmp1 = 0;
	long long cmp2 = 0;
	high_resolution_clock::time_point start1;
	high_resolution_clock::time_point stop1;
	high_resolution_clock::time_point start2;
	high_resolution_clock::time_point stop2;
	string s;
	getline(fi, s);
	n = stoi(s);
	int* a = new int[n];
	int* b = new int[n];
	int* c = new int[n];
	getline(fi, s);
	stringstream f(s);
	for (int i = 0; i < n; i++) {
		string temp;
		getline(f, temp, ' ');
		a[i] = stoi(temp);
	}
	fi.close();
	coppyToDynamicArray(a, b, n);
	coppyToDynamicArray(a, c, n);
	//first algorithm
	if (argv[2] == std::string("bubble-sort")) {
		start1 = high_resolution_clock::now();
		bubbleSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		bubbleSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("selection-sort")) {
		start1 = high_resolution_clock::now();
		selectionSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		selectionSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("insertion-sort")) {
		start1 = high_resolution_clock::now();
		insertionSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		insertionSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("heap-sort")) {
		start1 = high_resolution_clock::now();
		heapSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		heapSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("shaker-sort")) {
		start1 = high_resolution_clock::now();
		shakerSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		shakerSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("shell-sort")) {
		start1 = high_resolution_clock::now();
		shellSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		shellSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("merge-sort")) {
		start1 = high_resolution_clock::now();
		mergeSort(b, 0, n - 1);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		mergeSortCmp(b, 0, n - 1, cmp1);
	}
	if (argv[2] == std::string("quick-sort")) {
		start1 = high_resolution_clock::now();
		quickSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		quickSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("counting-sort")) {
		start1 = high_resolution_clock::now();
		countingSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		countingSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("radix-sort")) {
		start1 = high_resolution_clock::now();
		radixSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		radixSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("flash-sort")) {
		start1 = high_resolution_clock::now();
		flashSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		flashSortCmp(b, n, cmp1);
	}
	//second algorithm	
	if (argv[3] == std::string("bubble-sort")) {
		start2 = high_resolution_clock::now();
		bubbleSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		bubbleSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("selection-sort")) {
		start2 = high_resolution_clock::now();
		selectionSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		selectionSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("insertion-sort")) {
		start2 = high_resolution_clock::now();
		insertionSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		insertionSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("heap-sort")) {
		start2 = high_resolution_clock::now();
		heapSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		heapSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("shaker-sort")) {
		start2 = high_resolution_clock::now();
		shakerSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		shakerSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("shell-sort")) {
		start2 = high_resolution_clock::now();
		shellSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		shellSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("merge-sort")) {
		start2 = high_resolution_clock::now();
		mergeSort(b, 0, n - 1);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		mergeSortCmp(c, 0, n - 1, cmp2);
	}
	if (argv[3] == std::string("quick-sort")) {
		start2 = high_resolution_clock::now();
		quickSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		quickSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("counting-sort")) {
		start2 = high_resolution_clock::now();
		countingSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		countingSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("radix-sort")) {
		start2 = high_resolution_clock::now();
		radixSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(c, b, n);
		radixSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("flash-sort")) {
		start2 = high_resolution_clock::now();
		flashSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		flashSortCmp(c, n, cmp2);
	}
	auto timing1 = duration_cast<milliseconds>(stop1 - start1);
	auto timing2 = duration_cast<milliseconds>(stop2 - start2);
	cout << "COMPARE MODE: " << "\n";
	cout << "Algorithm: " << argv[2] << " | " << argv[3] << "\n";
	cout << "Input file: " << argv[4] << "\n";
	cout << "Input size: " << n << "\n";
	cout << "-----------------------" << "\n";
	cout << "running time: " << timing1.count() << " ms | " << timing2.count() << " ms\n";
	cout << "Comparisions: " << cmp1 << " | " << cmp2 << "\n";
	delete[]b;
	delete[]c;
}
void cmd5(char* argv[]) {
	int n = stoi(argv[4]);
	long long cmp1 = 0;
	long long cmp2 = 0;
	high_resolution_clock::time_point start1;
	high_resolution_clock::time_point stop1;
	high_resolution_clock::time_point start2;
	high_resolution_clock::time_point stop2;
	int* a = new int[n];
	int* b = new int[n];
	int* c = new int[n];
	if (argv[5] == std::string("-rand")) {
		GenerateData(a, n, 0);
		coppyToDynamicArray(a, b, n);
		coppyToDynamicArray(a, c, n);
	}
	if (argv[5] == std::string("-sorted")) {
		GenerateData(a, n, 1);
		coppyToDynamicArray(a, b, n);
		coppyToDynamicArray(a, c, n);
	}
	if (argv[5] == std::string("-rev")) {
		GenerateData(a, n, 2);
		coppyToDynamicArray(a, b, n);
		coppyToDynamicArray(a, c, n);
	}
	if (argv[5] == std::string("-nsorted")) {
		GenerateData(a, n, 3);
		coppyToDynamicArray(a, b, n);
		coppyToDynamicArray(a, c, n);
	}
	ofstream fo1("input.txt");
	fo1 << n << "\n";
	for (int i = 0; i < n; i++) {
		fo1 << a[i] << " ";
	}
	fo1.close();
	//first algorithm
	if (argv[2] == std::string("bubble-sort")) {
		start1 = high_resolution_clock::now();
		bubbleSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		bubbleSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("selection-sort")) {
		start1 = high_resolution_clock::now();
		selectionSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		selectionSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("insertion-sort")) {
		start1 = high_resolution_clock::now();
		insertionSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		insertionSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("heap-sort")) {
		start1 = high_resolution_clock::now();
		heapSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		heapSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("shaker-sort")) {
		start1 = high_resolution_clock::now();
		shakerSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		shakerSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("shell-sort")) {
		start1 = high_resolution_clock::now();
		shellSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		shellSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("merge-sort")) {
		start1 = high_resolution_clock::now();
		mergeSort(b, 0, n - 1);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		mergeSortCmp(b, 0, n - 1, cmp1);
	}
	if (argv[2] == std::string("quick-sort")) {
		start1 = high_resolution_clock::now();
		quickSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		quickSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("counting-sort")) {
		start1 = high_resolution_clock::now();
		countingSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		countingSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("radix-sort")) {
		start1 = high_resolution_clock::now();
		radixSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		radixSortCmp(b, n, cmp1);
	}
	if (argv[2] == std::string("flash-sort")) {
		start1 = high_resolution_clock::now();
		flashSort(b, n);
		stop1 = high_resolution_clock::now();
		coppyToDynamicArray(a, b, n);
		flashSortCmp(b, n, cmp1);
	}
	//second algorithm	
	if (argv[3] == std::string("bubble-sort")) {
		start2 = high_resolution_clock::now();
		bubbleSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		bubbleSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("selection-sort")) {
		start2 = high_resolution_clock::now();
		selectionSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		selectionSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("insertion-sort")) {
		start2 = high_resolution_clock::now();
		insertionSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		insertionSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("heap-sort")) {
		start2 = high_resolution_clock::now();
		heapSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		heapSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("shaker-sort")) {
		start2 = high_resolution_clock::now();
		shakerSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		shakerSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("shell-sort")) {
		start2 = high_resolution_clock::now();
		shellSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		shellSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("merge-sort")) {
		start2 = high_resolution_clock::now();
		mergeSort(b, 0, n - 1);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		mergeSortCmp(c, 0, n - 1, cmp2);
	}
	if (argv[3] == std::string("quick-sort")) {
		start2 = high_resolution_clock::now();
		quickSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		quickSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("counting-sort")) {
		start2 = high_resolution_clock::now();
		countingSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		countingSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("radix-sort")) {
		start2 = high_resolution_clock::now();
		radixSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(c, b, n);
		radixSortCmp(c, n, cmp2);
	}
	if (argv[3] == std::string("flash-sort")) {
		start2 = high_resolution_clock::now();
		flashSort(c, n);
		stop2 = high_resolution_clock::now();
		coppyToDynamicArray(a, c, n);
		flashSortCmp(c, n, cmp2);
	}
	auto timing1 = duration_cast<milliseconds>(stop1 - start1);
	auto timing2 = duration_cast<milliseconds>(stop2 - start2);
	cout << "COMPARE MODE: " << "\n";
	cout << "Algorithm: " << argv[2] << " | " << argv[3] << "\n";
	cout << "Input size: " << n << "\n";
	cout << "Input order: " << argv[5] << "\n";
	cout << "-----------------------" << "\n";
	cout << "running time: " << timing1.count() << " ms | " << timing2.count() << " ms\n";
	cout << "Comparisions: " << cmp1 << " | " << cmp2 << "\n";
	delete[]b;
	delete[]c;
}
int main(int argc, char* argv[]) {
	//Command 1: Run a sorting algorithm on the given input data.
	argc = 5;
	argv[0] = (char*)"DSA_Lab03.exe";
	argv[1] = (char*)"-a";
	argv[2] = (char*)"bubble-sort";
	argv[3] = (char*)"input.txt";
	argv[4] = (char*)"-both";
	
	////Command 2: Run a sorting algorithm on the data generated automatically with specified size and order.
	//argc = 6;
	//argv[0] = (char*)"DSA_Lab03.exe";
	//argv[1] = (char*)"-a";
	//argv[2] = (char*)"bubble-sort";
	//argv[3] = (char*)"10000";
	//argv[4] = (char*)"-rand";
	//argv[5] = (char*)"-time";
	
	////Command 3: Run a sorting algorithm on ALL data arrangements of a specified size.
	//argc = 5;
	//argv[0] = (char*)"DSA_Lab03.exe";
	//argv[1] = (char*)"-a";
	//argv[2] = (char*)"bubble-sort";
	//argv[3] = (char*)"10000";
	//argv[4] = (char*)"-comp";

	////Command 4: Run two sorting algorithms on the given input.
	//argc = 5;
	//argv[0] = (char*)"DSA_Lab03.exe";
	//argv[1] = (char*)"-c";
	//argv[2] = (char*)"heap-sort";
	//argv[3] = (char*)"merge-sort";
	//argv[4] = (char*)"input.txt";

	////Command 5: Run two sorting algorithms on the data generated automatically.
	//argc = 6;
	//argv[0] = (char*)"DSA_Lab03.exe";
	//argv[1] = (char*)"-c";
	//argv[2] = (char*)"quick-sort";
	//argv[3] = (char*)"merge-sort";
	//argv[4] = (char*)"100000";
	//argv[5] = (char*)"-nsorted";

	if (argv[1] == std::string("-a")) {
		if (argc == 6) {
			cmd2(argv);
		}
		else {
			if (checkCmd1(argv[3]) == 1) {
				cmd1(argv);
			}
			else {
				cmd3(argv);
			}
		}
	}
	else {
		if (argc == 5) {
			cmd4(argv);
		}
		else {
			cmd5(argv);
		}
	}
	return 0;
}
