/*  Programa:Exercício 7
    Autora: Isabela Cristina Silva Pedro
    Versão 4.0 - 30/11/2021
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//programa em C para ordenar vetor de strings com radix sort
void countingSort(int d, int n, char A[n][21], char B[n][21])
{
  int i, j, l, k, m, z, x;
  char aux;
  int c[27];

  //inicializando c[]
  for (i = 0; i < 27; i++)
  {
    c[i] = 0;
  }

  //incrementando c[]
  for (j = 0; j < n; j++)
  {
    //se char = ' '
    if (A[j][d] == 32 || A[j][d] == '\0')
    {
      c[0]++;
    }
    //se a > char > z
    else
    {
      c[A[j][d] - 96]++;
    }
  }

  //fazendo o cumulativo e printando c[]
  for (l = 0; l < 27; l++)
  {
    if (l != 0)
    {
      c[l] = c[l] + c[l - 1];
    }
    printf("%d ", c[l]);
  }
  printf("\n");

  // fazendo a ordenacao estavel em B
  for (k = n - 1; k > -1; k--)
  {
    if (96 < A[k][d] && A[k][d] < 123)
    {
      strcpy(B[c[(A[k][d] - 96)] - 1], A[k]);
      c[(A[k][d] - 96)]--;
    }
    else
    {
      strcpy(B[c[0] - 1], A[k]);
      c[0]--;
    }
  }
  //fazendo A receber B
  for (x = 0; x < n; x++)
  {
    strcpy(A[x], B[x]);
  }
}

void radixSort(int d, int n, char A[n][21], int p, int m)
{
  int i, j;
  char B[n][21];
  for (i = d - 1; i > -1; i--)
  {
    countingSort(i, n, A, B);
  }
  //printando a partir da pos p, m vezes
  for (int z = 0; z < m; z++)
  {
    printf("%s", B[p - 1]);
    if (z < m - 1)
      printf("\n");
    p++;
  }
}

int main()
{
  int n, i, j, k, d = 0, sizef, l, p, m, z;
  scanf("%d", &n);
  char temp[21];
  char arr[n][21];

  //lendo string em temp e copiando em arr
  //d recebe tam da maior string
  for (i = 0; i < n; i++)
  {
    scanf("%s", temp);
    strcpy(arr[i], temp);
    if (strlen(temp) > d)
      d = strlen(temp);
  }
  //lendo pos do primeiro elemento do printf
  //e qntde de prints
  scanf("%d %d", &p, &m);

  //transformando em strings minusculas
  for (j = 0; j < n; j++)
  {
    for (k = 0; k < d; k++)
    {
      if (islower(arr[j][k]) == 0)
      {
        strcpy(temp, arr[j]);
        arr[j][k] = tolower(temp[k]);
      }
    }
    printf("%s.\n", arr[j]);
  }
  //printando tam da maior string
  printf("%d\n", d);

  //transformando em strings de mesmo tamanho
  for (j = 0; j < n; j++)
  {
    for (k = 0; k < d; k++)
    {
      if (arr[j][k] == '\0')
      {
        arr[j][k] = ' ';
        arr[j][k + 1] = '\0';
      }
    }
  }
  radixSort(d, n, arr, p, m);
}