
#define QUANTIDADE_DE_ATRIBUTO 4
#define QUANTIDADE_DE_LABEL 8
typedef struct caracteristica_do_atributo{
    int quantidade_de_elementos_discreto;
    int* elementos_discretos;
    
}T_ATRIBUTO;


T_ATRIBUTO* novo_atributo(int quantidade,int* elementos_discretos);

T_ATRIBUTO** inicializacao_atributos();



typedef struct atributo_acumulate{
  int tamanho_vetor;
  int *vetor_contador;
}T_ATRIBUTO_ACUMULATOR;


typedef struct acumulador_label {
  int *vetor_contador;
} T_ACUMULADOR_LABEL;

T_ATRIBUTO_ACUMULATOR* novo_contador(T_ATRIBUTO* vetor_atributos);


T_ATRIBUTO_ACUMULATOR** novos_contador_folha(T_ATRIBUTO** atributos);




T_ACUMULADOR_LABEL* criar_contador_acumulador_label();

void novo_valor_para_contador(T_ATRIBUTO_ACUMULATOR** contadores,T_ACUMULADOR_LABEL* contador_label,T_ATRIBUTO** atributos , int* dados );
