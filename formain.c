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
  } else {
    int compare = compare_tree_nodes(*link, tuple);
    if( compare > 0){  
        tree_insert(&((*link)->left), tuple, ncases); 
    } else if( compare < 0){
        tree_insert(&((*link)->right), tuple, ncases);
    }
  } 
}


int highestCostLeaf(tree_node_t *link) {
  if (link == NULL){return 0;}
  int ld = highestCostLeaf(link->left);
  int rd = highestCostLeaf(link->right);
  if (ld > rd) {return ld + link->B;}
  else {return rd + link->B;}
}

int tree_depth_search(tree_node_t *link, int sum) {
  if (link == NULL){return 0;}
  if ((link->left) != NULL)
    sum = tree_depth_search(link->left, (sum + (link->left)->B));
  if ((link->right) != NULL)
    sum = tree_depth_search(link->right, (sum + (link->right)->B));
  return (sum + link->B);
}

int tree_depth(tree_node_t *link) {
  if (link == NULL){return 0;}
  int ld = tree_depth(link->left);
  int rd = tree_depth(link->right);
  if (ld > rd) {return ld + 1;}
  else {return rd + 1;}
}

int searchLevel(tree_node_t *link, int level, int sum) {
  if (link == NULL)
    return 0;
  if (level == 1)
    return (sum + link->B);
  else if (level > 1) {
    if ((link->left) != NULL)
      sum = searchLevel(link->left, level - 1, (sum + (link->left)->B));
    if ((link->right) != NULL)
      sum = searchLevel(link->right, level - 1, (sum + (link->right)->B));
    return (sum + link->B);
  }
}

int tree_breadth_search(tree_node_t *link) {
  int h = tree_depth(link), sum = 0;
  if (link != NULL) {
    for (int i = 1; i <= h; i++){
      sum = sum + searchLevel(link, i, 0) - link->B;
    }
  }
  return sum;
}

int executor(int ncases) {
    
}

int main(void){
    srand(time(NULL));
    FILE *cinco_10, *cinco_100, *cinco_1000, *cinco_10000;
    FILE *seis_10, *seis_100, *seis_1000, *seis_10000;
    FILE *sete_10, *sete_100, *sete_1000, *sete_10000;
    cinco_10 = fopen("cinco10.txt","a");
    cinco_100 = fopen("cinco100.txt","a");
    cinco_1000 = fopen("cinco1000.txt","a");
    cinco_10000 = fopen("cinco10000.txt","a");
    seis_10 = fopen("seis10.txt","a");
    seis_100 = fopen("seis100.txt","a");
    seis_1000 = fopen("seis1000.txt","a");
    seis_10000 = fopen("seis10000.txt","a");
    sete_10 = fopen("sete10.txt","a");
    sete_100 = fopen("sete100.txt","a");
    sete_1000 = fopen("sete1000.txt","a");
    sete_10000 = fopen("sete10000.txt","a");
    int numeros[4] = {10,100,1000,10000};
    for (int alberto = 0; alberto < 1000; alberto++){
        for (int x = 0; x < 4; x++){
            int ncases = numeros[x];
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
            int rlcost = 0;
            if (root != NULL){
                rlcost = highestCostLeaf(root) - root->B;
            }
            if (ncases == 10) {
                fprintf(cinco_10, "%d\n", rlcost);
            } else if (ncases == 100) {
                fprintf(cinco_100, "%d\n", rlcost);
            } else if (ncases == 1000) {
                fprintf(cinco_1000, "%d\n", rlcost);
            } else {
                fprintf(cinco_10000, "%d\n", rlcost);
            }
            // 6) Começando na raiz, qual é o custo de percorrer a árvore toda usando depth search?
            int dfscost = 0;
            if (root != NULL){
                dfscost = tree_depth_search(root,0) - root->B;
            }
            if (ncases == 10) {
                fprintf(seis_10, "%d\n", dfscost);
            } else if (ncases == 100) {
                fprintf(seis_100, "%d\n", dfscost);
            } else if (ncases == 1000) {
                fprintf(seis_1000, "%d\n", dfscost);
            } else {
                fprintf(seis_10000, "%d\n", dfscost);
            }
            // 7) Começando na raiz, qual é o custo de percorrer a árvore toda usando breadth search?
            int bfscost = tree_breadth_search(root);
            if (ncases == 10) {
                fprintf(sete_10, "%d\n", bfscost);
            } else if (ncases == 100) {
                fprintf(sete_100, "%d\n", bfscost);
            } else if (ncases == 1000) {
                fprintf(sete_1000, "%d\n", bfscost);
            } else {
                fprintf(sete_10000, "%d\n", bfscost);
            }
        }
        printf("Done %d \n", alberto);
    }
    fclose(cinco_10);
    fclose(cinco_100);
    fclose(cinco_1000);
    fclose(cinco_10000);
    fclose(seis_10);
    fclose(seis_100);
    fclose(seis_1000);
    fclose(seis_10000);
    fclose(sete_10);
    fclose(sete_100);
    fclose(sete_1000);
    fclose(sete_10000);
    return EXIT_SUCCESS;

}
