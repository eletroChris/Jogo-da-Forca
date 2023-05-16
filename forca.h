#define TAMANHO_PALAVRA 20

void abertura();
int jachutou(char letra,char chutes[],int chutesDados);
void chuta(char chutes[26],int* chutesDados);
void desenhaForca(char palavraSecreta[], char chutes[26],int chutesDados);
void escolhePalavra(char palavraSecreta[20]);
int enforcou(char palavraSecreta[],char chutes[],int chutesDados);
int acertou(char palavraSecreta[], char chutes[],int chutesDados);
void adicionaPalavra();
int chutesErrados(char palavraSecreta[],char chutes[],int chutesDados);
void verificaChuteRepetido(char chutes[26],int* chutesDados, char chute);