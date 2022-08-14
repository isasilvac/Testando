/*  Programa:Exercício 3.2
    Autora: Isabela Cristina Silva Pedro
    Versão 1.0 - 03/11/2021
*/
#include <stdio.h>
#include <stdlib.h>

void recursiveInsertionSort(int array[], int count, int pos)
{
    if (count <= 1)
    {
        return;
    }
    recursiveInsertionSort(array, count - 1, pos);
    printf("%d", pos - count); //printa a posição da chave
    int last = array[count - 1];
    int aux = count - 2;
    printf(" %d ", array[count - 1]); //printa o valor da chave
    while (aux >= 0 && array[aux] > last)
    {
        array[aux + 1] = array[aux];
        aux--;
    }
    printf("%d\n", aux + 1); //printa a localização da chave do vetor
    array[aux + 1] = last;
}

int main()
{
    int n, i;
    scanf("%d", &n);
    int array[n];

    for (i = 0; i < n; i++)
    {
        scanf("%d", &array[i]); //preenchendo vetor com sequencia de numeros digitada
    }
    if (n <= 1)
    {
        printf("1 1 0\n1");
        return 0;
    }
    recursiveInsertionSort(array, n, n + 1);
    for (i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    return 0;
}