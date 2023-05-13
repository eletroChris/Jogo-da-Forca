#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "forca.h"



void abertura(){
    printf("*********************\n");
    printf("*** Jogo da Forca ***\n");
    printf("*********************\n\n");
}

int jachutou(char letra,char chutes[],int chutesDados){
    int achou =0;
    for(int j=0; j<chutesDados;j++){
        if(chutes[j]==letra){
            achou =1;
            break;
        }
    }
    return achou;
}

void chuta(char chutes[26],int* chutesDados){
    char chute;
    printf("Qual letra? ");
    scanf(" %c",&chute);
    
    //Verifica se o jogador repetiu a letra que já foi chutada
    int chuteRepetido=0;
    for(int i =0;i<strlen(chutes);i++){
        if(chute == chutes[i]){            
            chuteRepetido=1;
            break;
        }
    }

    if(chuteRepetido){
        printf("---> Você já chutou essa letra <---\n\n");
    }else{ //Adiciona a letra ao array de chutes
        chutes[(*chutesDados)]=chute;
        (*chutesDados)++;
    }
    
}

void desenhaForca(char palavraSecreta[], char chutes[26],int chutesDados){
    int erros = chutesErrados(palavraSecreta,chutes,chutesDados);
    printf("  _______       \n");
    printf(" |/      %c      \n",(erros>=1 ? '|' : ' '));
    printf(" |      %c%c%c  \n", (erros>=2?'(':' '), 
    (erros>=2?'_':' '), (erros>=2?')':' '));
    printf(" |      %c%c%c  \n", (erros>=4?'\\':' '), 
    (erros>=3?'|':' '), (erros>=4?'/': ' '));
    printf(" |       %c     \n", (erros>=3?'|':' '));
    printf(" |      %c %c   \n", (erros>=5?'/':' '), 
    (erros>=5?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");
    
    printf("Você já deu %d chutes\n", chutesDados);
    for(int i=0;i<strlen(palavraSecreta);i++){
        if(jachutou(palavraSecreta[i],chutes,chutesDados)){
            printf("%c ",palavraSecreta[i]);
        }else{
            printf("_ ");
        }
    }
    printf("\n");
}

void escolhePalavra(char palavraSecreta[TAMANHO_PALAVRA]){
    FILE * f;
    f=fopen("palavras.txt","r");

    if(f==0){
        printf("Desculpe, banco de dados não disponível\n\n");
        exit(1);
    }
    
    int qtddepalavras;
    fscanf(f,"%d",&qtddepalavras);
    srand(time(0));
    int randomico =rand() % qtddepalavras;
    
    for(int i =0; i<=randomico; i++){
        fscanf(f,"%s",palavraSecreta);
    }
    fclose(f);
    
}

int chutesErrados(char palavraSecreta[],char chutes[],int chutesDados){
    int erros =0;
    for(int i =0;i<chutesDados;i++){
        int existe = 0;
        for(int j =0; j<strlen(palavraSecreta);j++){
            if(chutes[i]==palavraSecreta[j]){
                existe=1;
                break;
            }
        }
        if(!existe){
            erros++;
        }
    }
    return erros;
}

int enforcou(char palavraSecreta[],char chutes[],int chutesDados){
    
    return chutesErrados(palavraSecreta,chutes,chutesDados) >= 5;
}

int acertou(char palavraSecreta[], char chutes[],int chutesDados){
    for(int i =0; i<strlen(palavraSecreta);i++){
        if(!jachutou(palavraSecreta[i],chutes,chutesDados)){
            return 0;
        }
    }
    return 1;
}

void adicionaPalavra(){
    char quer = 'N';
    char novapalavra[20];
    printf("Você deseja adicionar uma nova palavra no jogo? (S/N)");
    scanf(" %c",&quer);
    if(quer == 'S'){
        
        printf("Qual a nova palavra? ");
        scanf("%s",novapalavra);
    
        FILE * f;
        f=fopen("palavras.txt","r+");
        if(f==0){
            printf("Desculpe, banco de dados não disponível\n\n");
            exit(1);
        }
        int qtd;
        fscanf(f,"%d",&qtd);
        qtd++;

        fseek(f,0,SEEK_SET);
        fprintf(f,"%d",qtd);

        fseek(f,0,SEEK_END);
        fprintf(f,"\n%s",novapalavra);

        fclose(f);
    }
}

int main(){
    char palavraSecreta[TAMANHO_PALAVRA];
    char chutes[26];
    int chutesDados = 0;
    
    //printf("%s\n",palavraSecreta);

    //int acertou =0;
    //int enforcou =0;

    
    abertura();
    escolhePalavra(palavraSecreta);
    int venceu = 0;
    int perdeu = 0;

    do{
        desenhaForca(palavraSecreta,chutes,chutesDados);
        chuta(chutes,&chutesDados);
        venceu = acertou(palavraSecreta, chutes,chutesDados);
        perdeu = enforcou(palavraSecreta,chutes,chutesDados);
    }while(!venceu && !perdeu);
    
    desenhaForca(palavraSecreta,chutes,chutesDados);
    if(venceu){
        printf("**** Parabéns, você ganhou! ****\n");
    }else if(perdeu){
        printf("Sinto muito, você perdeu\n");
        printf("A palavra era: %s\n",palavraSecreta);
    }

    adicionaPalavra();
}