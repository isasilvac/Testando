/*  Programa:Exercício 5
    Autora: Isabela Cristina Silva Pedro
    Versão 4.0 - 17/11/2021
*/
#include <stdio.h>
#include <stdlib.h>

void partition(int arr[], int low, int high, int pivot);

void quickSort(int arr[], int low, int high, int pivot)
{
  if (low < high)
  {
    partition(arr, low, high, pivot);
    quickSort(arr, low, high, pivot);
  }
  int aux;
  aux = arr[low];
  arr[low] = arr[pivot];
  arr[pivot] = aux;
}

//checa low > pivo e high < pivo e troca os numeros
void partition(int arr[], int low, int high, int pivot)
{
  if (arr[low] > arr[pivot])
  {
    while (high > low)
    {
      if (arr[high] <= arr[pivot])
      {
        int aux = arr[low];
        arr[low] = arr[high];
        arr[high] = aux;
        low++;
        break;
      }
      else
      {
        high--;
      }
    }
  }
  else
  {
    low++;
  }
}
void printArray(int arr[], int k, int N)
{
  printf("%do menor elemento eh o %d\n", k, arr[k - 1]);
  int j;
  for (j = 0; j < N; j++)
  {
    printf("%d ", arr[j]);
    printf("\n");
  }
}

int main()
{
  int k, N, i;
  int arr[N];
  scanf("%d", &k);
  scanf("%d", &N);
  for (i = 0; i < N; i++)
  {
    scanf("%d", &arr[i]);
  }
  quickSort(arr, 0, N - 2, N - 1);
  printArray(arr, k, N);
}