#include "listadeprodutos.h"

PLISTA criarLista(){
  PLISTA res = (PLISTA) malloc(sizeof(LISTADEPRODUTOS));
  res->cabeca = (PONT) malloc(sizeof(REGISTRO));
  res->cabeca->id=-1;
  res->cabeca->tipo=-1;
  res->cabeca->quantidade=0;
  res->cabeca->valorUnitario=0;
  res->cabeca->proxProd=NULL;
  return res;
}


int tamanho(PLISTA l){
  PONT atual = l->cabeca->proxProd;
  int tam = 0;
  while (atual) {
    atual = atual->proxProd;
    tam++;
  }
  return tam;
}

PONT buscarID(PLISTA l, int id){
  PONT atual = l->cabeca->proxProd;
   while (atual) {
    if (atual->id == id) return atual;
    atual = atual->proxProd;
  }
  return NULL;
}

void exibirLog(PLISTA f){
  int numElementos = tamanho(f);
  printf("Log lista [elementos: %i]\n    ", numElementos);
  PONT atual = f->cabeca->proxProd;
  while (atual){
    printf(" [%i;%i;%i;%i;$%i]", atual->id, atual->tipo, atual->quantidade, atual->valorUnitario, atual->quantidade*atual->valorUnitario);
    atual = atual->proxProd;
  }
  printf("\n\n");
}

int consultarValorUnitario(PLISTA l, int id){
  PONT atual = l->cabeca->proxProd;
   while (atual) {
    if (atual->id == id) return atual->valorUnitario;
    atual = atual->proxProd;
  }
  return 0;
}

PONT buscarValorTotal(PLISTA l, int valorTotal, PONT* ant){
  PONT atual = l -> cabeca -> proxProd;
  while (atual) {
    if((atual -> quantidade * atual -> valorUnitario) < valorTotal) return atual;
    *ant = atual;
    atual = atual -> proxProd;
  }
  return NULL;
}


bool inserirNovoProduto(PLISTA l, int id, int tipo, int quantidade, int valor){
  PONT i, x, ant;
  /* Teste de validade dos valores recebidos */
  //if(id <= 0 || tipo <= 0 || quantidade <= 0 || valor <= 0) return false;

  /* Busca do produto pelo ID */
  i = buscarID(l, id);
  //if(i != NULL) return false; // Retorna false caso ja exista um produto com o mesmo ID.

  /* Busca da posição certa do REGISTRO */
  x = buscarValorTotal(l, quantidade*valor, &ant);
  //if(!x) return false;

  /* Posicionando os valores e ajustando os ponteiros envolvidos */
  x = (PONT) malloc(sizeof(REGISTRO));
  x -> id = id;
  x -> tipo = tipo;
  x -> quantidade = quantidade;
  x -> valorUnitario = valor;
  x -> proxProd = ant -> proxProd;
  ant -> proxProd = x;

  return true;
}



bool removerItensDeUmProduto(PLISTA l, int id, int quantidade){

  /* COMPLETAR */

  return false;
}


bool atualizarValorDoProduto(PLISTA l, int id, int valor){

  /* COMPLETAR */

  return false;
}
