#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


typedef struct tree_node_s
{
  int A;
  int B;
  struct tree_node_s *left;
  struct tree_node_s *right;
}
tree_node_t;

int compare_tree_nodes(tree_node_t *node1,tree_node_t *node2){
    int c = 0;
    if (node1->A > node2->A)
        c = -1;
    else if (node1->A < node2->A)
        c = 1;
    return c;
}
void tree_insert(tree_node_t **link, tree_node_t *tuple, int ncases){
  if(*link == NULL){ 
    (*link) = tuple;
    printf("%10d %10d\n",(*link)->A,(*link)->B);
  } else {
    int compare = compare_tree_nodes(*link, tuple);
    if( compare > 0){  
        tree_insert(&((*link)->left), tuple, ncases); 
    } else if( compare < 0){
        tree_insert(&((*link)->right), tuple, ncases);
    } else {
        printf ("ERROR: A is repeated! \n");
        executor(ncases);
        exit(1);
    }
  } 
}
int tree_depth(tree_node_t *link, int main_index) {
  if (link == NULL){return 0;}
  int ld = tree_depth(link->left[main_index], main_index);
  int rd = tree_depth(link->right[main_index], main_index);
  if (ld > rd) {return ld + 1;}
  else {return rd + 1;}
}

int executor(int ncases) {
    // 2) Gere N pares de números (A,B), em que A é um número inteiro (um int) uniformemente distribuído no intervalo
    //    [0,1000000000] e onde B (um int) é um número inteiro uniformemente distribuído no intervalo [1,10]. Os valores de A
    //    têm de ser todos distintos (isso pode ter testado ao gerar a árvore binária da próxima alínea.
    tree_node_t *tuples = (tree_node_t *)calloc((size_t)ncases,sizeof(tree_node_t));
    if(tuples == NULL){
        fprintf(stderr,"Output memory!\n");
        return 1;
    }
    for(int i = 0; i < ncases; i++){
        tuples[i].A = rand()%1000000001;
        tuples[i].B = rand()%10+1;
        tuples[i].left = NULL; tuples[i].right = NULL;
    }
    // 3) Crie uma estrutura de dados especial, parecida com uma árvore binária ordenada, que guarda em cada nó os valores A
    //    e B. A árvore tem de estar ordenada pelo campo A. Um valor repetido de A faz com que se tenha de voltar a repetir
    //    a alínea 2). O campo B representa o custo de seguir a aresta que liga esse nó ao nó do seu progenitor (pense que é
    tree_node_t *root = NULL;
    for(int i = 0;i < ncases;i++){
      tree_insert(&(root),&(tuples[i]), ncases); // place your code here to insert &(persons[i]) in the tree with number main_index
    }
    // 4) Ao percorrer a árvore para efetuar uma determinada tarefa, os custos somam-se. Assim, para a árvore em baixo,
    //    para ir da raiz (4,1) para o nó (1,7) o custo é 3+7=11 --- (1,4)->(2,3) + (2,3)->(1,7).
    //    Para ir, por exemplo, de (1,7) para (3,2), o custo é 7+2 --- (1,7)->(2,3) + (2,3)->(3,2)
    // 5) Começando na raiz, e andando sempre para baixo, qual é a folha cujo caminho para lá chegar tem maior custo?


    return EXIT_SUCCESS;
}

int main(int argc,char **argv){
    // srand(time(NULL));
    // 1) Leia do terminal ou da linha de comandos o número N. Este número não poderá ser inferior a 10 nem superior a 10000.
    if(argc < 2) {
        printf("Program Usage: ./main arg1\n");
        return EXIT_FAILURE;
    }
    int ncases = atoi(argv[1]);
    if(ncases < 10 || ncases > 10000) {
        printf("Program Error: Arg1 must be a number between 10 and 10000!\n");
        return EXIT_FAILURE;
    }
    return executor(ncases);
}

