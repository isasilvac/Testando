/*  Programa:Exercício 7
    Autora: Isabela Cristina Silva Pedro
    Versão 1.0 - 22/11/2021
*/
#include <stdio.h>
#include <stdlib.h>

//Programa em C para ordenar vetor de inteiros com Arvore AVL
struct Node
{
  int key;
  struct Node *left;
  struct Node *right;
  int height;
};

//Funcao para achar o maximo entre dois inteiros
int max(int a, int b)
{
  return (a > b) ? a : b;
}

struct Node *minValueNode(struct Node *node)
{
  struct Node *current = node;
  //encontrar a folha mais a esquerda
  while (current->left != NULL)
    current = current->left;
  return current;
}

//Funcao que retorna a altura de um no
int height(struct Node *N)
{
  if (N == NULL)
    return 0;
  return N->height;
}

//Funcao que cria e inicializa um novo no
struct Node *newNode(int key)
{
  struct Node *node = (struct Node *)
      malloc(sizeof(struct Node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1; //no adicionado como folha
  return (node);
}

//Funcao que procura uma chave na arvore
struct Node *search(struct Node *root, int key)
{
  if (root == NULL || root->key == key)
    return root;
  if (root->key < key)
    return search(root->right, key);
  return search(root->left, key);
}

//Funcao para rotacionar para direita a arvore enraizada em y
struct Node *rightRotate(struct Node *y)
{
  struct Node *x = y->left;
  struct Node *T2 = x->right;
  x->right = y;
  y->left = T2;
  //atualizando altura
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  //retornando nova raiz
  return x;
}

//Funcao para rotacionar para esquerda a arvore enraizada em x
struct Node *leftRotate(struct Node *x)
{
  struct Node *y = x->right;
  struct Node *T2 = y->left;
  y->left = x;
  x->right = T2;
  //atualizando altura
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  //retornando nova raiz
  return y;
}

//Funcao que checa a diferenca de altura das subarvores em um no
int getBalance(struct Node *N)
{
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

//Funcao para inserir novo no e retornar nova raiz da arvore
struct Node *insert(struct Node *root, int key)
{
  // insercao direta
  if (root == NULL)
    return (newNode(key));

  if (key < root->key)
    root->left = insert(root->left, key);
  else if (key > root->key)
    root->right = insert(root->right, key);
  else //nao sao consideradas chaves iguais
    return root;

  //atualizando altura do no ancestral
  root->height = 1 + max(height(root->left),
                         height(root->right));

  //checando se o no ancestral se desequilibrou
  int balance = getBalance(root);

  // 4 casos para caso tenha desequilibrado
  // caso LL
  if (balance > 1 && key < root->left->key)
    return rightRotate(root);

  // caso RR
  if (balance < -1 && key > root->right->key)
    return leftRotate(root);

  // caso LR
  if (balance > 1 && key > root->left->key)
  {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  // caso RL
  if (balance < -1 && key < root->right->key)
  {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  //retornando o no nao alterado
  return root;
}

struct Node *deleteNode(struct Node *root, int key)
{
  //checar se arvore esta vazia
  if (root == NULL)
    return root;
  //chave a ser deletada menor que a raiz
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  //chave a ser deletada maior que a raiz
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else
  {
    //no com um ou nenhum filho
    if ((root->left == NULL) || (root->right == NULL))
    {
      struct Node *temp = root->left ? root->left : root->right;
      //no com nenhum filho
      if (temp == NULL)
      {
        temp = root;
        root = NULL;
      }
      else
        // no com um filho
        *root = *temp;
      free(temp);
    }
    else
    {
      // obtendo o menor sucessor da direita num no com 2 filhos
      struct Node *temp = minValueNode(root->right);
      //substituindo no no
      root->key = temp->key;
      //deletando o sucessor
      root->right = deleteNode(root->right, temp->key);
    }
  }
  //retornando se a arvore tinha apenas um no
  if (root == NULL)
    return root;
  //atualizando a altura do no atual
  root->height = 1 + max(height(root->left),
                         height(root->right));

  //obter o equilibrio do no
  int balance = getBalance(root);
  //se o no estiver desequilibrado, considerar os 4 casos
  //caso LL
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  //caso LR
  if (balance > 1 && getBalance(root->left) < 0)
  {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  //caso RR
  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  //caso RL
  if (balance < -1 && getBalance(root->right) > 0)
  {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}

int main()
{
  int a, i = 1, d = 1;
  int nodeHeight, leftHeight, rightHeight;
  struct Node *root = NULL;
  struct Node *keypos;
  //lendo enquanto num inserido for > 0
  while (d > 0)
  {
    scanf("%d", &d);
    if (d < 0)
      break;
    root = insert(root, d);
  }
  nodeHeight = height(root) - 1;
  leftHeight = height(root->left);
  rightHeight = height(root->right);
  /*imprimindo a altura da raiz, subarvore a direita e a esquerda
  de acordo com o requisitado no exercicio*/
  printf("%d, %d, %d\n", nodeHeight, leftHeight, rightHeight);
  //lendo enquanto num inserido for > 0
  while (i > 0)
  {
    scanf("%d", &i);
    if (i < 0)
      break;
    keypos = search(root, i);
    if (keypos == NULL)
      root = insert(root, i);
    else
      root = deleteNode(root, i);
  }
  scanf("%d", &a);
  keypos = search(root, a);
  if (keypos == NULL)
    printf("Valor nao encontrado");
  else
  {
    nodeHeight = height(keypos) - 1;
    leftHeight = height(keypos->left);
    rightHeight = height(keypos->right);
    /*imprimindo a altura da raiz, subarvore a direita e a esquerda
  de acordo com o requisitado no exercicio*/
    printf("%d, %d, %d\n", nodeHeight, leftHeight, rightHeight);
  }
  return 0;
}