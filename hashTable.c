/*  Programa:Exercício 13
    Autora: Isabela Cristina Silva Pedro
    Versão 1.0 - 10/01/2022
*/

/*C program for hashing with chaining*/

#include <stdio.h>
#include <stdlib.h>

//creating a node
struct node
{
  int data;
  struct node *next;
};

//hash function
int hashcode(struct node *hashTable[], int n, int size)
{
  int hash_value = n % size;
  return hash_value;
}

//initializing the hash table with null
void initialize(struct node *hashTable[], int size)
{
  int i;
  for (i = 0; i < size; i++)
  {
    hashTable[i] = NULL;
  }
}

//creating a new node with null pointer
void insert(struct node *hashTable[], int n, int size)
{
  struct node *newNode = malloc(sizeof(struct node));
  newNode->data = n;
  newNode->next = NULL;

  //finding the index of the new node
  int key = hashcode(hashTable, n, size);
  //if the hash table is empty
  if (hashTable[key] == NULL)
  {
    hashTable[key] = newNode;
  }
  //if it's not empty, go to the last node
  else
  {
    //using a temp pointer
    struct node *temp = hashTable[key];
    while (temp->next)
    {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

//function to print the elements of a given key
void printTable(struct node *hashTable[], int size, int key)
{
  struct node *temp = hashTable[key];
  printf("[%d] ", key);

  /*while the node exists, print its data
  then go to the next node*/
  while (temp)
  {
    printf("%d ", temp->data);
    temp = temp->next;
  }
}

//a function to search and delete a given data
void searchDelete(struct node *hashTable[], int data, int size)
{
  int key = hashcode(hashTable, data, size);
  //auxiliar pointer to free the allocated memory
  struct node *dealloc;

  //if the node exists
  if (hashTable[key] != NULL)
  {
    /*if the first element in the key chain
     is equal to data */
    if (hashTable[key]->data == data)
    {
      dealloc = hashTable[key];
      //the first element will be the second
      hashTable[key] = hashTable[key]->next;
      free(dealloc);
      return;
    }
    /*if the given data is not in the first
    element, we need to travel the array */
    else
    {
      struct node *temp = hashTable[key];
      //while the next node exists
      while (temp->next)
      {
        //in case the next node is equal to data
        if (temp->next->data == data)
        {
          dealloc = temp->next;
          /*the actual node receives the next's next
          node as its next */
          temp->next = temp->next->next;
          free(dealloc);
          return;
        }
        temp = temp->next;
      }
    }
  }
  //if the data is not found in the array
  printf("Valor nao encontrado\n");
}

int main()
{
  int size, data = 1, num, key;
  //reading the size of the hash table
  scanf("%d", &size);

  struct node *hashTable[size];
  initialize(hashTable, size);

  /*reading the numbers for the hash table
  until input of negative numbers */
  while (data >= 0)
  {
    scanf("%d", &data);
    if (data < 0)
      break;
    insert(hashTable, data, size);
  }

  //reading a number to be searched
  scanf("%d", &num);
  searchDelete(hashTable, num, size);
  //reading the index to be printed
  scanf("%d", &key);
  printTable(hashTable, size, key);
}