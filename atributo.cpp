#include "atributo.h"
#include<stdlib.h>
#include <Arduino.h>



/*
 * 
 * 
 * ALGORITMO GENETICO
 * 
 */
float log2(int number){
    return log(number)/log(2);
  
  }


/*
 * CODIGO RELACIONADO COM ATRIBUTO
 * 
 * 
 */

// CRIAR NOVO ATRIBUTO
T_ATRIBUTO* novo_atributo(int quantidade,int* elementos_discretos){
    T_ATRIBUTO* atributo = (T_ATRIBUTO*) malloc(sizeof(T_ATRIBUTO));
    atributo->quantidade_de_elementos_discreto = quantidade;
    atributo->elementos_discretos = (int*)malloc(sizeof(int)*quantidade);
    for (int i = 0; i < quantidade; i++)
        atributo->elementos_discretos[i] = elementos_discretos[i];
    return atributo;
}



// CRIAR TODOS OS ATRIBUTOS
T_ATRIBUTO** inicializacao_atributos(){
    T_ATRIBUTO** atributos = (T_ATRIBUTO**) malloc(sizeof(T_ATRIBUTO)*QUANTIDADE_DE_ATRIBUTO );
    int vetor[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
    atributos[0] = novo_atributo(24,vetor);
    int vetor1[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    atributos[1] = novo_atributo(12,vetor1);
    int vetor2[] = {0,1,2,3,4,5,6};
    atributos[2] = novo_atributo(13,vetor2);
    int vetor3[] = {2005,2006,2007,2008,2009,2010,2011,2012,2013,2014,2015,2016,2017};
    atributos[3] = novo_atributo(7,vetor3);
    return atributos;
}



//ENCONTRA VALOR DO ATRIBUTO
int encontrar_id_valor_atributo(T_ATRIBUTO* atributo, int valor){
  for(int i = 0; i < atributo->quantidade_de_elementos_discreto; i++)  {
      if (atributo->elementos_discretos[i] == valor) return i;
    }
}

/*
*
* CODIGO RELACIONADO COM O CONTADOR
*
*
*
*/

//CRIAR NOVO CONTADOR
T_ATRIBUTO_ACUMULATOR* novo_contador(T_ATRIBUTO* vetor_atributos ){
    T_ATRIBUTO_ACUMULATOR* contador = (T_ATRIBUTO_ACUMULATOR*) malloc(sizeof(T_ATRIBUTO_ACUMULATOR));
    
    contador->tamanho_vetor = vetor_atributos->quantidade_de_elementos_discreto * QUANTIDADE_DE_LABEL;

    contador->vetor_contador = (int*) malloc(sizeof(int) * contador->tamanho_vetor);
    for (int i = 0; i<contador->tamanho_vetor;i++){
      
        contador->vetor_contador[i] = 0;
    }
    return contador;
  
}

//CRIAR TODOS OS CONTADORES
T_ATRIBUTO_ACUMULATOR** novos_contador_folha(T_ATRIBUTO** atributos) {
  T_ATRIBUTO_ACUMULATOR ** contadores = (T_ATRIBUTO_ACUMULATOR **) malloc(sizeof(T_ATRIBUTO_ACUMULATOR *));
  for (int i =0 ;  i < QUANTIDADE_DE_ATRIBUTO; i ++ )  {
      contadores[i] = novo_contador(atributos[i]);
      Serial.println("...");
      
    }
   return contadores;
}




// CRIAR CONTADOR DOS LABEL
T_ACUMULADOR_LABEL* criar_contador_acumulador_label(){
    T_ACUMULADOR_LABEL *contador = (T_ACUMULADOR_LABEL*) malloc(sizeof(T_ACUMULADOR_LABEL));
    contador->vetor_contador = (int*) malloc(sizeof(int) * QUANTIDADE_DE_LABEL);
    
    for (int i = 0; i <  QUANTIDADE_DE_LABEL; i++)
      contador->vetor_contador[i] = 0;
     
     return contador;
  }




/*
 * AÇÃO DO TRABALHO
 * 
 * 
 */

float entropy(T_ACUMULADOR_LABEL* contador_label ){
  int controlador = 0;
  float entropy = 0;
  float total = 0;
  for (int i = 0; i < QUANTIDADE_DE_LABEL; i++)total += contador_label->vetor_contador[i];
  
  for (int i = 0; i < QUANTIDADE_DE_LABEL; i++){
      if (contador_label->vetor_contador[i] == 0) continue;
      controlador ++;
      Serial.println(contador_label->vetor_contador[i]);
      int total_atual = contador_label->vetor_contador[i];
      entropy -= log2(total_atual/total)*(total_atual/total);
    }    
    if (controlador>1) return entropy;
    return -1;
 }


  //INSERIR NOVO VALOR NO CONTADOR
void novo_valor_para_contador(T_ATRIBUTO_ACUMULATOR** contadores,T_ACUMULADOR_LABEL* contador_label,T_ATRIBUTO** atributos , int* dados ){
  int label = dados[QUANTIDADE_DE_ATRIBUTO] - 1;
  contador_label->vetor_contador[label]++;
  
  for (int i = 0; i < QUANTIDADE_DE_ATRIBUTO; i++ ) {
    int id = encontrar_id_valor_atributo(atributos[i], dados[i]);
    //INCREMENTANDO O CONTADOR
    contadores[0]->vetor_contador[QUANTIDADE_DE_LABEL*label + id]++;
  }
  Serial.println(entropy(contador_label));
  Serial.println("-----");
}

  
