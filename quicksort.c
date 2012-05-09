#include <stdio.h>
#define CUTOFF	10

void			QuickSort(int A[], int N);
static void		QSort(int A[], int Left, int Right);
static int		Median3(int A[], int Left, int Right);	//Calculate the pivot
static void		InsertionSort(int A[], int Left, int Right);
static void		Swap(int *a, int *b);

int main(void)
{
	int A[] = {3, 66, 39, 24, 89, 84, 0, 165, 45, 77, 10, 99};
	int i;
	
	QuickSort(A, 12);

	for (i=0; i<12; i++)
		printf("%-4d", A[i]);
	putchar('\n');

	return 0;
}

void QuickSort(int A[], int N)
{
	QSort(A, 0, N-1);
}

static void		QSort(int A[], int Left, int Right)
{
	int i, j, Pivot;

	if (Left+CUTOFF < Right)
		{
			Pivot = Median3(A, Left, Right);
			i	  = Left;
			j	  = Right - 1;

			for (;;)
				{
					while (A[++i] < Pivot)
						;
					while (A[--j] > Pivot)
						;

					if (i < j)
						Swap(&A[i], &A[j]);
					else
						break;
				}
			Swap(&A[i], &A[Right-1]);

			QSort(A, Left, i-1);
			QSort(A, i+1, Right);
		}
	else
		InsertionSort(A, Left, Right);
}

static int		Median3(int A[], int Left, int Right)
{
	int Center = (Left+Right)/2;

	if (A[Center] < A[Left])
		Swap(&A[Center], &A[Left]);
	if (A[Right] < A[Left])
		Swap(&A[Right], &A[Left]);
	if (A[Center] > A[Right])
		Swap(&A[Center],&A[Right]);

	Swap(&A[Center], &A[Right-1]);
   	return A[Right-1];
}

static void		InsertionSort(int A[], int Left, int Right)
{
	int i, j, tmp;

	for (i=Left+1; i<=Right; i++)
		{
			tmp = A[i];
			
			for (j=i; j>Left && tmp<A[j-1]; j--)
					A[j] = A[j-1];
			A[j]		 = tmp;
		}
}

static void Swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a	 = *b;
	*b	 = temp;
}
