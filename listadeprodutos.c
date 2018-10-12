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
  *ant = l->cabeca;
  PONT atual = l->cabeca->proxProd;

  while(atual && atual->quantidade * atual->valorUnitario < valorTotal){
    if(atual && atual->quantidade * atual->valorUnitario == valorTotal) return atual;
    *ant = atual;
    atual = atual->proxProd;
  }
  return NULL;
}

PONT buscarReg(PLISTA l, int id, PONT* ant){
  *ant = l->cabeca;
  PONT atual = l->cabeca->proxProd;
   while (atual) {
    if (atual->id == id) return atual;
    *ant = atual;
    atual = atual->proxProd;
  }
  return NULL;
}


bool inserirNovoProduto(PLISTA l, int id, int tipo, int quantidade, int valor){
  PONT x, ant;

  /* Teste de validade dos valores recebidos */
  if(id <= 0 || tipo <= 0 || quantidade <= 0 || valor <= 0) return false;

  /* Busca do produto pelo ID */
  x = buscarID(l, id);
  if(x != NULL) return false; // Retorna o PONT caso ja exista um produto com o mesmo ID.
  /* Busca da posição certa do REGISTRO */
  x = buscarValorTotal(l, quantidade*valor, &ant);
  if(x != NULL) return false;
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
  PONT x, ant;
  int valor, tipo, quant;

  /* Retorna false caso o valor de quantidade recebido seja menor ou igual a zero*/
  if(quantidade <= 0) return false;

  /* Retorna false caso não exista produto com o id recebido */
  x = buscarReg(l, id, &ant);
  if(x == NULL) return false;

  valor = x->valorUnitario;
  tipo = x->tipo;
  quant = x->quantidade - quantidade;

  /* Testar se a quantidade recebida é maior que a quantidade real do registro */
  if(quantidade > x->quantidade) return false;

  /* Se a quantidade for igual a quantidade do REGISTRO, apagar todo */
  ant->proxProd = x->proxProd;
  free(x);

  inserirNovoProduto(l, id, tipo, quant, valor);

  return true;
}


bool atualizarValorDoProduto(PLISTA l, int id, int valor){
  PONT x, ant;
  int quant, tipo;

  if(valor <= 0) return false;

  x = buscarReg(l, id, &ant);
  if(x == NULL) return false;

  quant = x->quantidade;
  tipo = x->tipo;

  ant->proxProd = x->proxProd;
  free(x);

  inserirNovoProduto(l, id, tipo, quant, valor);
  return true;
}
