#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

ifstream file;
const char* f_path = "matr.txt";

int** read_matrix(const char* file_path, int& n, int& m)
{
	ifstream in(file_path);

	if (in.is_open())
	{
		//how many numbers in the file (matrix)
		int count = 0;//quantity of numbers
		int temp;

		while (!in.eof())//till the end of the file
		{
			in >> temp;//reading of numbers without saving
			count++;
		}

		//to find out how many numbers in the first row
		in.seekg(0, ios::beg);//to the file beginning
		in.clear();

		int count_space = 0;//number of spaces
		char symbol;
		while (!in.eof())//to be on the save side - no longer than end of the file
		{
			in.get(symbol);//reading each next symbol
			if (symbol == ' ') count_space++;
			if (symbol == '\n') break;//if the row is finished, than stop
		}
		//cout << count_space << endl;

		//beginning of the file
		in.seekg(0, ios::beg);
		in.clear();

		int _n = count / (count_space + 1);//number of rows
		n = _n;
		int _m = count_space + 1;//number of columns
		m = _m;
		int** x;//the matrix
		x = new int* [_n];
		for (int i = 0; i < _n; i++) x[i] = new int[_m];

		//reading the matrix
		for (int i = 0; i < _n; i++)
			for (int j = 0; j < _m; j++)
				in >> x[i][j];

		in.close();
		return x;
	}
	else
	{
		cout << "Error: wrong file path";
	}
}

void insertion_sort(int arr[], int n);
void bubble_sort(int arr[], int n);
void mix_sort(int a[], int n);
void quick_sort(int arr[], int low, int high);
void merge_sort(int arr[], int l, int r);
int shell_sort(int arr[], int n);

void print_array(int arr[], int n)
{
	for (int i = 0;i < n;i++)
		cout << arr[i] << " ";
}

int main()
{
	int n;
	int** adj_mx = read_matrix(f_path, n, n);

	int numb_edges = 0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if (adj_mx[i][j]!=0)
			{
				numb_edges++;
			}
		}
	}
	
	int* edges = new int[numb_edges];
	int ind_edg = 0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(adj_mx[i][j]!=0)
			{
				edges[ind_edg] = adj_mx[i][j];
				ind_edg++;
			}
		}
	}
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Оберіть метод сортування: " << endl;
	cout << "1. Вставками" << endl;
	cout << "2. Бульбашкою" << endl;
	cout << "3. Перемішуванням" << endl;
	cout << "4. Швидке" << endl;
	cout << "5. Злиттям" << endl;
	cout << "6. Шелла" << endl;
	cout << "0. Вихід" << endl << endl;
	cout << "Ваш вибір: ";
	
	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1:
		insertion_sort(edges, numb_edges);
		break;
	case 2:
		bubble_sort(edges, numb_edges);
		break;
	case 3:
		mix_sort(edges, numb_edges);
		break;
	case 4:
		quick_sort(edges, 0, numb_edges - 1);
		break;
	case 5:
		merge_sort(edges, 0, numb_edges - 1);
		break;
	case 6:
		shell_sort(edges, numb_edges);
		break;
	default:
		return 0;
	}

	cout << "Відсортовані ребра по їхнім довжинам: ";
	print_array(edges, numb_edges);
	
	return 0;
}

void insertion_sort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void bubble_sort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
}

void mix_sort(int a[], int n)
{
	bool swapped = true;
	int start = 0;
	int end = n - 1;

	while (swapped)
	{
		swapped = false;

		for (int i = start; i < end; ++i)
		{
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				swapped = true;
			}
		}

		if (!swapped)
			break;

		swapped = false;

		--end;

		for (int i = end - 1; i >= start; --i)
		{
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				swapped = true;
			}
		}
		
		++start;
	}
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quick_sort(int arr[], int low, int high)	// low=0, high=n-1
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

		quick_sort(arr, low, pi - 1);
		quick_sort(arr, pi + 1, high);
	}
}

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;


	int* L = new int[n1];
	int* R = new int[n2];


	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void merge_sort(int arr[], int l, int r)
{
	if (l < r) {
		int m = l + (r - l) / 2;

		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

int shell_sort(int arr[], int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2)
	{

		for (int i = gap; i < n; i += 1)
		{
			int temp = arr[i];

			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];

			arr[j] = temp;
		}
	}
	return 0;
}