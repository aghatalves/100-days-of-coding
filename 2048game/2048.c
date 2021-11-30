#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <wchar.h>
#define e 4
#define vermelho "\x1b[31m"
#define verde "\x1b[32m"
#define amarelo "\x1b[33m"
#define azul "\x1b[34m"
#define roxo "\x1b[35m"
#define ciano "\x1b[36m"
#define preto "\x1b[0m"
//Declaro ação de uma struct para auxiliar a leitura e a reescrita do arquivo.
typedef struct
{
    long int score[5];
    char nome[5][100];
} Pontuacao;
//Função que imprime o placar quando usuário não atinge uma pontuação mínima para entrar no placar.
void Imprime_Placar_atual()
{
    FILE *file;
    char Placar[5][5];
    char Placar_nome[5][100];
    int a;
    Pontuacao Placar_atual[5];
    //Abrindo o arquivo
    file = fopen("Rank.txt", "r");
    //Condição que confere se o arquivo foi aberto corretamente
    if (file == NULL)
    {
        printf("Erro, nao foi possivel abrir o arquivo\n");
        exit(1);
    }
    //Imprimindo o placar
    printf("---------PLACAR ATUAL------------\n");
    for (a = 0; a < 5; a++)
    {
        fscanf(file, "%s %s\n", Placar[a], Placar_nome[a]);
        Placar_atual[a].score[a] = atoi(Placar[a]);
        strcpy(Placar_atual[a].nome[a], Placar_nome[a]);
        printf("%ld e %s\n", Placar_atual[a].score[a], Placar_atual[a].nome[a]);
    }
    //Fechando o arquivo
    fclose(file);
}
//Função que reescreve o placar com os novos records do usuário
void Novo_Placar(long int v[5], char m[5][100])
{
    FILE *file;
    //Abrindo o arquivo
    file = fopen("Rank.txt", "w");
    //Condição que confere se o arquivo foi aberto corretamente
    if (file == NULL)
    {
        printf("Erro, nao foi possivel abrir o arquivo\n");
        exit(1);
    }
    //Reescreve no arquivo original
    for (int i = 0; i < 5; i++)
    {
        fprintf(file, "%ld ", v[i]);
        fprintf(file, "%s\n", m[i]);
    }
    //Fechando o arquivo
    fclose(file);
}
//Atribuição do ranking
void rank(char n[], long int t)
{
    FILE *file;
    file = fopen("Rank.txt", "r+");
    //Condição que confere se o arquivo foi aberto corretamente
    if (file == NULL)
    {
        printf("Erro, nao foi possivel abrir o arquivo\n");
        exit(1);
    }
    //Declaração de variáveis auxiliares que atribuem o ranking a struct
    char inteiro[5][5];
    char string[5][100];
    long int score_aux[5];
    char nome_aux[5][100];
    Pontuacao pontos[5];

    int i;
    //Atribui os dados da leitura do arquivo as variáveis da struct
    for (i = 0; i < 5; i = i + 1)
    {
        fscanf(file, "%s %s\n", inteiro[i], string[i]);
        pontos[i].score[i] = atoi(inteiro[i]);
        strcpy(pontos[i].nome[i], string[i]);
    }
    //Fechando arquivo
    fclose(file);
    //Checa se a pontuação do usuário entra no ranking
    if (pontos[0].score[0] > t)
    {
        score_aux[0] = t;
        strcpy(nome_aux[0], n);
        for (int i = 1; i < 5; i++)
        {
            score_aux[i] = pontos[i - 1].score[i - 1];
            strcpy(nome_aux[i], pontos[i - 1].nome[i - 1]);
        }
    }
    else
    {
        for (int i = 1; i < 5; i++)
        {
            if (pontos[i].score[i] > t)
            {
                score_aux[i] = t;
                strcpy(nome_aux[i], pontos[i].nome[i]);
                for (int i = 2; i < 5; i++)
                {
                    score_aux[i] = pontos[i - 1].score[i - 1];
                    strcpy(nome_aux[i], pontos[i - 1].nome[i - 1]);
                }
            }
        }
    }
    //Imprimindo o novo ranking
    printf("------NOVO PLACAR------\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%ld %s\n", score_aux[i], nome_aux[i]);
    }
    Novo_Placar(score_aux, nome_aux);
}
int CondicaoVouD(int tabuleiro[][e])
{
    //Declarando variáveis
    int i, j, contador;
    for (i = 0; i < e; i++)
    {
        for (j = 0; j < e; j++)
        {
            //Confere se há posições da matriz com valor igual a 0
            if (tabuleiro[i][j] == 0)
            {
                contador = 1;
                break;
            }
            else if (tabuleiro[i][j] == tabuleiro[i][j + 1] && j != 3)
            {
                contador = 1;
                break;
            }
            else if (tabuleiro[i][j] == tabuleiro[i][j - 1] && j != 0)
            {
                contador = 1;
                break;
            }
            else if (tabuleiro[i][j] == tabuleiro[i + 1][j] && i != 3)
            {
                contador = 1;
                break;
            }
            else if (tabuleiro[i][j] == tabuleiro[i - 1][j] && i != 0)
            {
                contador = 1;
                break;
            }
            //Confere se há alguma posição da matriz com valor igual a 2048
            else if (tabuleiro[i][j] == 2048)
            {
                contador = 2;
                break;
            }
            else
                contador = 3;
        }
        if (contador == 1 || contador == 2)
        {
            break;
        }
    }
    return contador;
}

//Função que checa o tempo de jogo e passa para minutos
void passa_Pra_min(long int pontuacao)
{
    //Declaração de variáveis
    long int temp_min, temp_seg;
    //Confere se o tempo em segundos é suficiente para ser convertido em minutos inteiros
    if (pontuacao > 60)
    {
        temp_min = pontuacao / 60;
        temp_seg = pontuacao - (temp_min * 60);
        printf(" Seu tempo de jogo: %ld min e %ld seg\n", temp_min, temp_seg);
        //Caso não seja
    }
    if (pontuacao <= 60)
    {
        temp_seg = pontuacao;
        printf("Seu tempo de jogo: 0 min e %ld seg\n", temp_seg);
    }
}
//Função que imprime a matriz alterando a cor dos números diferente de 0
void ImprimeEalteraCOR(int tabuleiro[][e])
{
    //Para limpar as matrizes anteriores(evitar encher o terminal)
    system("clear");
    //Declarando variáveis necessárias
    int i, j;
    //Um for para percorrer a matriz
    for (i = 0; i < e; i++)
    {
        for (j = 0; j < e; j++)
        {
            //Confere se o número da posição atual é diferente de 0
            if (tabuleiro[i][j] != 0)
            {
                //Altera as cores dos números indicados nas condições
                if (tabuleiro[i][j] == 2)
                    printf(vermelho "| %d |" preto, tabuleiro[i][j]);
                else if (tabuleiro[i][j] == 4)
                    printf(verde "| %d |" preto, tabuleiro[i][j]);
                else if (tabuleiro[i][j] == 8)
                    printf(amarelo "| %d |" preto, tabuleiro[i][j]);
                else if (tabuleiro[i][j] == 16)
                    printf(azul "| %d |" preto, tabuleiro[i][j]);
                else if (tabuleiro[i][j] == 32)
                    printf(roxo "| %d |" preto, tabuleiro[i][j]);
                else if (tabuleiro[i][j] == 64)
                    printf(ciano "| %d |" preto, tabuleiro[i][j]);
                else if (tabuleiro[i][j] == 128)
                    printf(verde "| %d |" preto, tabuleiro[i][j]);
                else if (tabuleiro[i][j] == 256)
                    printf(amarelo "| %d |" preto, tabuleiro[i][j]);
                else if (tabuleiro[i][j] == 512)
                    printf(vermelho "| %d |" preto, tabuleiro[i][j]);
                else if (tabuleiro[i][j] == 1024)
                    printf(azul "| %d |" preto, tabuleiro[i][j]);
                else if (tabuleiro[i][j] == 2048)
                    printf(ciano "| %d |" preto, tabuleiro[i][j]);
            }
            //Se o número da posição atual for igual a 0 apenas imprime sem alterar a cor
            else
                printf("| 0 |");
        }
        printf("\n");
    }
}
//Função que gera um número aleatório no tabuleiro.
void randNUM(int tabuleiro[][e])
{
    //Declaração de variáveis
    int i, j, numero, aux;
    //Função que aumenta a aleatoriedade do rand
    srand(time(NULL));
    i = rand() % 3;
    j = rand() % 3;
    //Esquema usando função rand para alterar o valor da variável "número" para 2 ou 4.
    if (rand() % 3 == 0 || rand() % 3 == 1)
    {
        numero = 2;
    }
    else
    {
        numero = 4;
    }
    //Percorre a matriz até achar uma posição igual a 0 para subtituir pelo valor da variável "número"
    if (tabuleiro[i][j] == 0)
    {
        tabuleiro[i][j] = numero;
    }
    else
    {
        for (i = 0; i < e; i++)
        {
            for (j = 0; j < e; j++)
            {
                if (tabuleiro[i][j] == 0)
                {
                    tabuleiro[i][j] = numero;
                    aux++;
                    break;
                }
            }
            if (aux != 0)
                break;
        }
    }
}
void moveD(int MAT[][e], char a)
{
    int i, j;
    for (i = 0; i < e; i++)
    {
        for (j = 3; j >= 0; j--) //primogenito
        {
            if (MAT[i][j] == 0 && MAT[i][j - 1] != 0 && j != 0)
            {
                MAT[i][j] = MAT[i][j - 1];
                MAT[i][j - 1] = 0;
            }
        }
        for (j = 3; j >= 0; j--) //o segundo
        {
            if (MAT[i][j] == MAT[i][j - 3] && MAT[i][j - 1] == 0 && j != 0)
            {
                MAT[i][j] += MAT[i][j - 3];
                MAT[i][j - 3] = 0;
                break;
            }
            else if (MAT[i][j] == MAT[i][j - 2] && MAT[i][j - 1] == 0 && j != 0)
            {
                MAT[i][j] += MAT[i][j - 2];
                MAT[i][j - 2] = 0;
                break;
            }
            if (MAT[i][j] == MAT[i][j - 1] && j != 0)
            {
                MAT[i][j] += MAT[i][j - 1];
                MAT[i][j - 1] = 0;
            }
        }
        for (j = 3; j >= 0; j--) //o terceiro
        {
            if (MAT[i][j] == 0 && MAT[i][j - 1] != 0 && j != 0)
            {
                MAT[i][j] = MAT[i][j - 1];
                MAT[i][j - 1] = 0;
            }
        }
        for (j = 3; j >= 0; j--) //caçula
        {
            if (MAT[i][j] == 0 && MAT[i][j - 1] != 0 && j != 0)
            {
                MAT[i][j] = MAT[i][j - 1];
                MAT[i][j - 1] = 0;
            }
        }
    }
}
void moveW(int MAT[][e], char w)
{
    //Declarando variáveis auxiliares
    int i, j;
    //Percorre a matriz
    for (j = 0; j < e; j++)
    {
        for (i = 0; i < e; i++)
        {
            //Checa se os próximos números estão disponíveis para que o lugar seja ocupado
            if (MAT[i][j] == 0 && MAT[i + 1][j] != 0 && i != 3)
            {
                MAT[i][j] = MAT[i + 1][j];
                MAT[i + 1][j] = 0;
            }
        }
        //Checa se o número 3 casas antes é igual ao atual e o número entre eles é igual a 0, para que seja somado e levado ao extremo
        for (i = 0; i < e; i++)
        {
            if (MAT[i][j] == MAT[i + 3][j] && i != 3 && MAT[i + 1][j] == 0)
            {
                MAT[i][j] += MAT[i + 3][j];
                MAT[i + 3][j] = 0;
            }
        }
        //Checa se o número 2 casas antes é igual ao atual e o número entre eles é igual a 0, para que seja somado e levado ao extremo
        for (i = 0; i < e; i++)
        {
            if (MAT[i][j] == MAT[i + 2][j] && i != 3 && MAT[i + 1][j] == 0)
            {
                MAT[i][j] += MAT[i + 2][j];
                MAT[i + 2][j] = 0;
            }
        }
        //Checa se o próximo número depois do atual é igual, para que seja somado e levado ao extremo
        for (i = 0; i < e; i++)
        {
            if (MAT[i][j] == MAT[i + 1][j] && i != 3)
            {
                MAT[i][j] += MAT[i + 1][j];
                MAT[i + 1][j] = 0;
            }
        }
        //Checa se os próximos números estão disponíveis para que o lugar seja ocupado
        for (i = 0; i < e; i++)
        {
            if (MAT[i][j] == 0 && MAT[i + 1][j] != 0 && i != 3)
            {
                MAT[i][j] = MAT[i + 1][j];
                MAT[i + 1][j] = 0;
            }
        }
        //Checa se os próximos números estão disponíveis para que o lugar seja ocupado
        for (i = 0; i < e; i++)
        {
            if (MAT[i][j] == 0 && MAT[i + 1][j] != 0 && i != 3)
            {
                MAT[i][j] = MAT[i + 1][j];
                MAT[i + 1][j] = 0;
            }
        }
    }
}

void moveA(int MAT[][e], char d)
{
    int i, j;
    for (i = 0; i < e; i++)
    {
        for (j = 0; j < e; j++)
        {
            if (MAT[i][j] == 0 && MAT[i][j + 1] != 0 && j != 3)
            {
                MAT[i][j] = MAT[i][j + 1];
                MAT[i][j + 1] = 0;
            }
        }
        for (j = 0; j < e; j++)
        {
            if (MAT[i][j] == MAT[i][j + 3] && MAT[i][j + 1] == 0 && j != 3)
            {
                MAT[i][j] += MAT[i][j + 3];
                MAT[i][j + 3] = 0;
                break;
            }
            else if (MAT[i][j] == MAT[i][j + 2] && MAT[i][j + 1] == 0 && j != 3)
            {
                MAT[i][j] += MAT[i][j + 2];
                MAT[i][j + 2] = 0;
                break;
            }
            else if (MAT[i][j] == MAT[i][j + 1] && j != 3)
            {
                MAT[i][j] += MAT[i][j + 1];
                MAT[i][j + 1] = 0;
                break;
            }
        }
        for (j = 0; j < e; j++)
        {
            if (MAT[i][j] == 0 && MAT[i][j + 1] != 0 && j != 3)
            {
                MAT[i][j] = MAT[i][j + 1];
                MAT[i][j + 1] = 0;
            }
        }
        for (j = 0; j < e; j++)
        {
            if (MAT[i][j] == 0 && MAT[i][j + 1] != 0 && j != 3)
            {
                MAT[i][j] = MAT[i][j + 1];
                MAT[i][j + 1] = 0;
            }
        }
    }
}
void moveS(int MAT[][e], char s)
{
    int i, j;
    for (j = 0; j < e; j++)
    {
        for (i = 3; i >= 0; i--)
        {
            //Checa se os próximos números estão disponíveis para que o lugar seja ocupado
            if (MAT[i][j] == 0 && MAT[i - 1][j] != 0 && i != 0)
            {
                MAT[i][j] = MAT[i - 1][j];
                MAT[i - 1][j] = 0;
            }
        }
        //Checa se o número 3 casas antes é igual ao atual e o número entre eles é igual a 0, para que seja somado e levado ao extremo
        for (i = 3; i > 0; i--)
        {
            if (MAT[i][j] == MAT[i - 3][j] && MAT[i - 1][j] == 0 && i != 0)
            {
                MAT[i][j] += MAT[i - 3][j];
                MAT[i - 3][j] = 0;
            }
        }
        //Checa se o número 2 casas antes é igual ao atual e o número entre eles é igual a 0, para que seja somado e levado ao extremo
        for (i = 3; i >= 0; i--)
        {
            if (MAT[i][j] == MAT[i - 2][j] && MAT[i - 1][j] == 0 && i != 0)
            {
                MAT[i][j] += MAT[i - 2][j];
                MAT[i - 2][j] = 0;
            }
        }
        //Checa se o próximo número depois do atual é igual, para que seja somado e levado ao extremo
        for (i = 3; i >= 0; i--)
        {
            if (MAT[i][j] == MAT[i - 1][j] && i != 0)
            {
                MAT[i][j] += MAT[i - 1][j];
                MAT[i - 1][j] = 0;
            }
        }
        //Checa se os próximos números estão disponíveis para que o lugar seja ocupado
        for (i = 3; i >= 0; i--)
        {
            if (MAT[i][j] == 0 && MAT[i - 1][j] != 0 && i != 0)
            {
                MAT[i][j] = MAT[i - 1][j];
                MAT[i - 1][j] = 0;
            }
        }
        //Checa se os próximos números estão disponíveis para que o lugar seja ocupado
        for (i = 3; i >= 0; i--)
        {
            if (MAT[i][j] == 0 && MAT[i - 1][j] != 0 && i != 0)
            {
                MAT[i][j] = MAT[i - 1][j];
                MAT[i - 1][j] = 0;
            }
        }
    }
}
void inicioDoGame(int tabuleiro[][e])
{
    //Impressões para declarar o início do jogo
    printf("             Bem-vindo(a)!");
    printf("\n");
    printf("    Digite ENTER para comecar o jogo.");
    scanf("%*c");
    //Limpa as impressões anteriores
    system("clear");
    //Surge um número aleatório
    randNUM(tabuleiro);
    //Imprime a matriz
    ImprimeEalteraCOR(tabuleiro);
}
int main()
{

    clock_t inicio, fim;
    long int tempo_de_game;
    inicio = clock();
    int tabuleiro[e][e] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}},
        aux = 0;
    char direc, nome[100];
    int aux_2;
    inicioDoGame(tabuleiro);
    scanf("%c%*c", &direc);
    while (CondicaoVouD(tabuleiro) == 1)
    {
        switch (direc)
        {
        case 'w':
            moveW(tabuleiro, direc);
            randNUM(tabuleiro);
            ImprimeEalteraCOR(tabuleiro);
            break;
        case 's':
            moveS(tabuleiro, direc);
            randNUM(tabuleiro);
            ImprimeEalteraCOR(tabuleiro);
            break;
        case 'd':
            moveD(tabuleiro, direc);
            randNUM(tabuleiro);
            ImprimeEalteraCOR(tabuleiro);
            break;
        case 'a':
            moveA(tabuleiro, direc);
            randNUM(tabuleiro);
            ImprimeEalteraCOR(tabuleiro);
            break;
        }
        scanf("%c", &direc);
    }
    if (CondicaoVouD(tabuleiro) != 1)
    {
        aux = CondicaoVouD(tabuleiro);
    }
    if (aux == 2)
    {
        printf("Parabens! Voce ganhou.\n");
    }
    else if (aux == 3)
    {
        printf("Voce perdeu!\n");
    }
    fim = clock();
    tempo_de_game = ((long int)(fim - inicio)) / CLOCKS_PER_SEC;
    passa_Pra_min(tempo_de_game);
    printf("Digite seu primeiro nome:");
    fgets(nome, 100, stdin);
    aux_2 = strlen(nome) - 1;
    nome[aux_2] = '\0';
    if (aux == 2)
    {
        rank(nome, tempo_de_game);
    }
    else
    {
        Imprime_Placar_atual();
    }
    return 0;
}