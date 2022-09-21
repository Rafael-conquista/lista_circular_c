#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char valor[60];
    struct No *proximo;
} No;

typedef struct {
    No *inicio, *fim;
    int tam;
} Lista;

void imprimir(Lista *lista) {
    int i;
    printf("\n\n");
    No *inicio = lista->inicio;
    while(inicio != NULL) {
        printf("%s \n", inicio->valor);
        inicio = inicio->proximo;
    }
    printf("\n\n");
}

void imprimir_tamanho(Lista *lista){
   No *inicio = lista->inicio;
   int i = 0;
   while(inicio != NULL){
        i = i + 1;
        inicio = inicio->proximo;
   }
   printf("\n\n");
   printf("O tamanho da lista é de: %d", i);
   printf("\n\n");
}

void inserirInicio(Lista *lista, char valor[], int tamanho) {
    No *novo = (No*)malloc(sizeof(No));
    int i;
    for(i=0; i<tamanho; i++){
        novo->valor[i] = valor[i];
    }
    if(lista->inicio == NULL) {
        novo->proximo = NULL;
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        novo->proximo = lista->inicio;
        lista->inicio = novo;
    }
    lista->tam++;
}

void inserirFim(Lista *lista, char valor[], int tamanho) {
    No *novo = (No*)malloc(sizeof(No));
    int i;
    for(i=0; i<tamanho; i++){
        novo->valor[i] = valor[i];
    }
    novo->proximo = NULL;

    if(lista->inicio == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        lista->fim->proximo = novo;
        lista->fim = novo;
    }
    lista->tam++;
}

char* remover(Lista *lista, char valor[],int tamanho) {
    No *inicio = lista->inicio;
    No * noARemover = NULL;
    int diferentes = 0;
    for(int i = 0; i<tamanho; i++){
        if(inicio->valor[i] != valor[i]){
            diferentes = diferentes + 1;
        }
    }
    
    if(inicio != NULL && diferentes == 0) {
        noARemover = lista->inicio;
        lista->inicio = noARemover->proximo;
        if(lista->inicio == NULL)
            lista->fim = NULL;
    } else {
        while(inicio != NULL && inicio->proximo != NULL && diferentes != 0) {
            for(int i = 0; i<tamanho; i++){
                if(inicio->proximo->valor[i] != valor[i]){
                    diferentes = 0;
                }
            }
            inicio = inicio->proximo;
        }
        if(inicio != NULL && inicio->proximo != NULL) {
            noARemover = inicio->proximo;
            inicio->proximo = noARemover->proximo;
            if(inicio->proximo == NULL)
                lista->fim = inicio;
        }
    }
    if(noARemover) {
        free(noARemover);
        lista->tam--;
        if(inicio->proximo == NULL){
            return lista->inicio->valor;
        }else{
            return inicio->proximo->valor;
        }
    }
}

void buscar(Lista *lista, char valor[], int tamanho){
    No *inicio = lista -> inicio;
    int encontrado = 0;
    while(inicio != NULL){
        int i;
        int diferentes = 0;
        for(i = 0; i<tamanho; i++){
            if(inicio->valor[i] != valor[i]){
                diferentes = diferentes + 1;
            }
        }
        if(diferentes == 0){
            encontrado = 1;
        }
        inicio = inicio->proximo;
    }
    if(encontrado == 1){
        printf("\nA música %s foi encontrada com sucesso\n\n!!", valor);
    }else{
        printf("\nA música %s não foi encontrada\n", valor);
    }
}

char* musica_atual(Lista *lista){
    No *inicio = lista -> inicio;
    return inicio->valor;
}

char* proxima_musica(Lista *lista, char valor[], int tamanho){
    No *inicio = lista -> inicio;
    int encontrado = 0;
    while(encontrado != 1){
        int i;
        int diferentes = 0;
        for(i = 0; i<tamanho; i++){
            if(inicio->valor[i] != valor[i]){
                diferentes = diferentes + 1;
            }
        }
        if(diferentes == 0){
            encontrado = 1;
        }
        if(inicio-> proximo == NULL){
            inicio = lista -> inicio;
        }else{
            inicio = inicio->proximo;   
        }
    }
    if(encontrado == 1){
        return inicio->valor;
    }
}

char* musica_anterior(Lista *lista, char valor[], int tamanho){
    No *inicio = lista -> inicio;
    int encontrado = 0;
    char *ultimo;
    char *anterior;
    if(inicio->valor == valor){
        while(inicio->valor != NULL){
            ultimo = inicio->valor;
            inicio = inicio->proximo;
        }
        return ultimo;
    }
    
    while(encontrado != 1){
        int i;
        int diferentes = 0;
        for(i=0; i<tamanho; i++){
            if(inicio->valor[i] != valor[i]){
                diferentes = diferentes + 1;
            }
        }
        if(diferentes != 0){
            anterior = inicio -> valor;
        }else{
            encontrado = 1;
        }
        inicio = inicio -> proximo;
    }
    return anterior;
}

int main()
{
    Lista lista;
    //musicas inseridas como exemplo
    inserirFim(&lista, "musica 1", 8);
    inserirFim(&lista, "musica 2", 8);
    inserirFim(&lista, "musica 3", 8);
    inserirFim(&lista, "musica 4", 8);
    
    int sair = 0;
    int res;
    int menu = 0;
    char musica[60];
    char *resultado = musica_atual(&lista);
    while(sair == 0){
        while(sair == 0){
            printf("\t<<Musica Anterior(digite 1)");
            if(resultado == NULL || resultado == "(null)"){
                resultado = musica_atual(&lista);
            }
            printf("\t\t%s", resultado);
            printf("\t\tMusica Seguinte(digite 2)>>");
            printf("\n\tOpções(digite 3)");
            printf("\n\tDeseja sair? (digite 0)");
            printf("\n\tResposta: ");
            scanf("%d", &res);
            if(res == 1){
                int tamanho = strlen(resultado);
                resultado = musica_anterior(&lista, resultado, tamanho);
            }
            if(res == 2){
                int tamanho = strlen(resultado);
                resultado = proxima_musica(&lista, resultado, tamanho);
            }else if(res == 0){
                sair = 1;
            }else if(res ==3){
                printf("\nDeseja adicionar uma nova música no começo da lista? (digite 1)");
                printf("\nDeseja adicionar uma nova música no final da lista? (digite 2)");
                printf("\nDeseja listar todas as músicas da lista? (digite 3)");
                printf("\nDeseja procurar por uma música especifica? (digite 4)");
                printf("\nDeseja ver a quantidade de músicas da lista? (digite 5)");
                printf("\nDeseja remover uma música? (digite 6)");
                printf("\nDeseja sair? (digite 0)");
                printf("\nResposta: ");
                scanf("%d", &res);
                if(res == 0){
                    sair = 1;
                }else if(res == 1){
                    printf("\nDigite o nome da música a ser adicionada: ");
                    scanf("\n%[^\n]",musica);
                    printf("%s adicionada\n", musica);
                    int tamanho = strlen(musica);
                    inserirInicio(&lista, musica, tamanho);
                }else if(res == 2){
                    printf("\nDigite o nome da música a ser adicionada: ");
                    scanf("\n%[^\n]",musica);
                    printf("%s adicionada\n", musica);
                    int tamanho = strlen(musica);
                    inserirFim(&lista, musica, tamanho);
                }else if(res == 3){
                    imprimir(&lista);
                }else if(res == 4){
                    printf("\nDigite o nome da musica a ser buscada: \n");
                    scanf("\n%[^\n]",musica);
                    int tamanho = strlen(musica);
                    buscar(&lista, musica, tamanho);
                }else if(res == 5){
                    imprimir_tamanho(&lista);
                }else if(res == 6){
                    printf("Digite o nome da musica a ser excluida: ");
                    scanf("\n%[^\n]",musica);
                    int tamanho = strlen(musica);
                    resultado = remover(&lista, musica, tamanho);
                }
            }
        }
    }
    return 0;
}
