#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char word[15];
    struct node *left;
    struct node *right;
    int occ;
} Node;


//inicializar a árvore
Node *treeCreate(){
    return NULL;
}


//inserir palavras
Node* treeInsert(Node *root, char newWord[]){
    // Node *p,*q,*r;
    // Node *q,*r;

    //  p = (Node *)calloc(1,sizeof(Node));
    // p = (Node *)malloc(sizeof(Node));

    if (root == NULL){
        Node *aux = (Node *)malloc(sizeof(Node));

        strcpy(aux->word,newWord);
        aux->left = NULL;
        aux->right = NULL;
        aux->occ = 1;
        // root = aux;
        return aux;
    }
    
    else{
        // q = root;
        // while (q != NULL){
        // r = q;
        if (strcmp(newWord, root->word) < 0){
            // q = q->left;
            root->left = treeInsert(root->left, newWord);
        }
        else if(strcmp(newWord, root->word) > 0){
            // q = q->right;
            root->right = treeInsert(root->right, newWord);
        }
        else{
            // printf("Palavra ja existe no dicionario, contador incrementado!\n");
            root->occ ++;
        }
    }
    return root;
}


//consultar palavra e informar ocorrências
Node* treeSearch(Node *root, char checkWord[]){

    if(root != NULL){
        if(strcmp(checkWord, root->word) == 0){
            // printf("Palavra encontrada!\n");
            // printf("Palavra %d encontrada!\n", root->word);
            if(root->occ == 1){
                printf("Palavra %s aparece %d vez!\n", checkWord, root->occ);
            }
            else{
                printf("Palavra %s aparece %d vezes!\n", checkWord, root->occ);
            }
            return root;
        }
        else{
            if(strcmp(checkWord, root->word) < 0){
                return treeSearch(root->left, checkWord);
            }
            else if(strcmp(checkWord, root->word) > 0){
                return treeSearch(root->right, checkWord);
            }
        }
    }
    printf("Palavra nao encontrada!\n");
    return root;
}


//encontrar o menor elemento da árvore - utilizado na remoção
Node *treeMin(Node *root){

    if(root != NULL){
        Node *aux = root;
        while(aux->left != NULL){
            // aux = aux->left;
            strcpy(aux,aux->left);
        }
        return aux;
    }
    return NULL;
}


// remover palavra
Node* treeRemove(Node *root, char removeWord[]){

    if(root != NULL){
        if(strcmp(removeWord, root->word) > 0){
            root->right = treeRemove(root->right, removeWord); 
            return root;
        }
        else if(strcmp(removeWord, root->word) < 0){
            root->left = treeRemove(root->left, removeWord);     
            return root;
        }

        else{ //encontrou a palavra a ser removida

            //sem filhos
            if (root->left == NULL && root->right == NULL){
                free(root);
                // printf("Palavra nao encontrada!");
                return NULL; 
            }

            //filho à direita
            else if (root->left == NULL && root->right != NULL){
                Node *aux = root->right;
                free(root);
                return aux;
            }

            //filho à esquerda
            else if (root->right == NULL && root->left != NULL){
                    Node *aux = root->left;
                    free(root);
                    return aux;
                }   

            //dois filhos
            else {
                Node *aux;
                aux = treeMin(root->right);
                Node *auxNode;
                strcpy(auxNode->word,aux->word);
                root = treeRemove(root, auxNode->word);
                strcpy(root->word,auxNode->word);
            }
        }
        return root;
    }
    return NULL;
}


//tamanho da árvore > quantidade palavras
int treeSize(Node *root){
    if(root != NULL){
        return 1 + treeSize(root->left) + treeSize(root->right);
    }
    else{
        return 0;
    }
}


//soma de contadores das palavras
int treeCount(Node *root){
    if(root != NULL){
        return root->occ + treeCount(root->left) + treeCount(root->right);
    }
    else{
        return 0;
    }
}


//imprimir a árvore
void treePrint(Node *root){

    if (root == NULL){
        return;
    }
    
    printf("%s\n", root->word);
    treePrint(root->left);
    treePrint(root->right);
}


//imprimir a árvore de A a Z
void treePrintAZ(Node *root){

    if(root == NULL){
        return;
    }
    
    treePrintAZ(root->left);
    printf("%s\n", root->word);
    treePrintAZ(root->right);
}


//imprimir a árvore de Z a A
void treePrintZA(Node *root){

    if(root == NULL){
        return;
    }

    treePrintZA(root->right);
    printf("%s\n", root->word);	
    treePrintZA(root->left);
}


//liberar nós
void treeFree(Node *root){

    if(root != NULL){
        treeFree(root->left);
        treeFree(root->right);
        free(root);
    }
}


// exibir palavras que iniciam por x letra 
void treeLetter(Node *root, char checkLetter){

    if(root == NULL){
        return;
    }
    
    treeLetter(root->left, checkLetter);

    if(checkLetter == root->word[0]){
        if(root->occ == 1){
            printf("A palavra '%s' inicia com a letra '%c' e aparece %d vez!\n", root->word, checkLetter, root->occ);
        }
        else{
            printf("A palavra '%s' inicia com a letra '%c' e aparece %d vezes!\n", root->word, checkLetter, root->occ);
        }
    }

    treeLetter(root->right, checkLetter);
}


//escrever em ordem alfabética em txt
int treeWrite(Node *root, char file[50]){

    FILE *fo = fopen(file, "a");
    
    if(root == NULL){
        return;
    }
    
    treeWrite(root->left,file);
    fprintf(fo, "%s\n", root->word);
    fclose(fo);
    // printf("%s\n", root->word);
    treeWrite(root->right,file);
}


//menu
int main(){

    Node *root = treeCreate();
    Node *deleted = treeCreate();

    int op, c;
    char newWord[15], newLetter, fileOut[15];

    //  ler palavras em arquivo txt
        FILE *f = fopen("words.txt", "r");
        while(fscanf(f, "%s ", &newWord) == 1){
            root = treeInsert(root, newWord);
        }
        fclose(f);

    do{ // MENU
        printf("\nOpcoes:\n");
        printf("1 - Inserir nova palavra;\n");
        printf("2 - Consultar palavra;\n");
        printf("3 - Remover palavra;\n");
        printf("4 - Exibir total de palavras no dicionario;\n");
        printf("5 - Exibir total de ocorrencias no dicionario;\n");
        printf("6 - Exibir palavras com uma unica ocorrencia;\n");
        printf("7 - Exibir palavras deletadas;\n");
        printf("8 - Consultar palavras que iniciam com determinada letra;\n");
        printf("9 - Imprimir a arvore;\n");
        printf("\nDigite sua opcao ou 0 para sair:\n");
        scanf("%d", &op);
        getchar();
        printf("\n");

        switch(op){

            case 1: printf("Digite a palavra a ser inserida:\n");
                    scanf("%s", &newWord);
                    root = treeInsert(root, newWord);
                    break;

            case 2: printf("Digite a palavra a ser pesquisada:\n");
                    scanf("%s", &newWord);
                    treeSearch(root, newWord);
                    break;

            case 3: printf("Digite a palavra a ser removida:\n");
                    scanf("%s", &newWord);
                    root = treeRemove(root, newWord);
                    deleted = treeInsert(deleted, newWord);
                    break;

            case 4: printf("Palavras no dicionario: %d\n", treeSize(root));
                    break;

            case 5: printf("Ocorrencias no dicionario: %d\n", treeCount(root));
                    break;

            case 6: treePrintAZ(root);
                    printf("\n");
                    break;

            case 7: treePrint(deleted);
                    printf("\n");
                    break;

            case 8: printf("Digite a letra para verificar:\n");
                    scanf("%c", &newLetter);
                    treeLetter(root, newLetter);
					break;

            case 9: do {
                    c=1;
                    printf("Opcoes:\n");
                    printf("1 - Imprimir arvore;\n");
                    printf("2 - Imprimir arvore A>Z;\n");
                    printf("3 - Imprimir arvore Z>A;\n");
                    printf("4 - Imprimir arvore A>Z em arquivo txt;\n");
                    printf("\nDigite sua opcao:\n");
                    scanf("%d", &op);
                    printf("\n");

                    switch(op){

                        case 1: treePrint(root);
                                c++;
                                break;

                        case 2: treePrintAZ(root);
                                c++;
                                break;

                        case 3: treePrintZA(root);
                                c++;
                                break;

                        case 4: printf("Digite o nome do arquivo de saida:\n");
                                scanf("%s", fileOut);
                                treeWrite(root, fileOut);
                                printf("Arquivo criado com sucesso!\n");
                                c++;
                                break;
                    }
            } while(c==1);
        }
    } while (op!=0);

    treeFree(root);
    treeFree(deleted);

    return 0;
}