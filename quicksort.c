#include <stdio.h>

void			QuickSort(int A[], int N);
static void		QSort(int A[], int Left, int Right);
static void		Median3(int A[], int Left, int Right);	//Calculate the pivot
static void		InsertSort(int A[], int Left, int Right);

int main(void)
{
	int A[] = {3, 66, 39, 24, 89, 84, 0, 165, 45, 77, 10, 99};
	int i;
	
	QuickSort(A, 12);

	for (i=0; i<12; i++)
		printf("%-4d\n", A[i]);
	putchar('\n');

	return 0;
}

void QuickSort(int A[], int N)
{
	QSort(A, 0, N-1);
}

static void		QSort(int A[], int Left, int Right)
{
	
}

static int		Median3(int A[], int Left, int Right)
{
	int Median = A[(Left+Right)/2];

	if (Median > A[Left])
		Median = A[Left];
	if (Median > A[Right])
		Median = A[Right];

	return Median;
}

static void		InsertSort(int A[], int Left, int Right)
{
	int i, j, tmp;

	for (i=Left+1; i<Right; i++)
		{
			tmp = A[i];
			
			for (j=i; j>Left && tmp<A[j-1]; j--)
					A[j] = A[j-1];
			A[j]		 = tmp;
		}
}

		
