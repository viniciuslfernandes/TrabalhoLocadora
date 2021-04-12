#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h> /// a biblioteca windows foi adcionada para corrigir erros
                    /// de leitura de caracteres especiais
#define linhas 16
#define preco 3

void  jogos () /// fun��o para abrir o jogos
{
    FILE *jg;
    char jogo[60];


    jg = fopen("jogos.txt", "r");

    if(jg == NULL)
    {
        printf("Erro ao ler arquivo!");
    }

    for(int i = 0; i < linhas; i++)
    {
        fgets(jogo, 60, jg);
        printf("%s", jogo);
        setbuf(stdin, NULL);
    }

    fclose(jg);
}
void alugar(char nome[]) /// fun��o para alugar
{
    int o, *cpr, lin = 1;
    FILE *alg;
    char jog[40];
    int dias;
    float val=0;
    printf("\n\nO valor do aluguel de cada jogo � R$3,00 por dia!");
    printf("\n\nDigite o n�mero referente ao jogo que deseja alugar: ");
    scanf("%d", &o);
    printf("\n\nInforme quantos dias voc� pretende ficar com o jogo:\n1- 15 dias\n2- 7 dias\n3- 3 dias\n");
    printf("\nOp��o: ");
    scanf("%d",&dias);
    if(dias==1)
    {
        val=preco*15;
    }
    else if (dias==2)
    {
        val=preco*7;
    }
    else if (dias==3)
    {
        val=preco*3;
    }
    else
    {
        printf("op��o invalida");
    }

    alg = fopen("jogos.txt", "r");

    for(int c = 0; c < linhas; c++)
    {
        fgets(jog, 40, alg);

        if(lin == o)
        {
            printf("\n\nO valor pago: R$%.2f.",val);
            printf("\n\n Jogo  %s alugado com sucesso, divirta-se %s!", jog, nome);
        }
        lin++;
    }

    fclose(alg);

}
void devolve (char n[]) /// fun��o de  devolu��o
{
    int o, *cpr, lin = 1;
    FILE *alg;
    char jog[40];

    printf("\n\nDigite o n�mero referente ao jogo que deseja devovler: ");
    scanf("%d", &o);

    alg = fopen("jogos.txt", "r");

    for(int c = 0; c < linhas; c++)
    {
        fgets(jog, 40, alg);

        if(lin == o)
        {
            printf("\n\n Jogo  %s devolvido com sucesso, alugue mais %s!", jog, n);
        }
        lin++;
    }

    fclose(alg);
}
char cadastrar() /// fun��o para cadastro
{
    unsigned int cp = 1252;
    unsigned int cpIn = GetConsoleCP();
    unsigned int cpOut = GetConsoleOutputCP();
    char nome[30], cidade[30], estado[30], user[30];
    int ddd, numero;
    char email[30];
    FILE *dados;

    /// pede os dados do usu�rio--------------------------------

    SetConsoleCP(cp);
    SetConsoleOutputCP(cp);
    printf("\nInforme seu nome completo: ");/// nome
    fflush(stdin);
    gets(nome);
    printf("\nCrie um nome de usu�rio: "); /// usu�rio
    fflush(stdin);
    gets(user);

    printf("\nDigite seu DDD e o n�mero (separado  por espa�o, respectivamente): "); /// DDD e n�mero
    scanf("%d %d", &ddd, &numero);

    printf("\nDigite seu e-mail: "); /// e-mail
    scanf("%s", &email);

    printf("\nSua cidade e Estado (separado  por espa�o, respectivamente): "); /// cidade Estado
    scanf("%s %s", &cidade, &estado);


    ///-------------------------------------------------------------

    /// abre um arquivo txt--------------------------------------------------------------------
    dados = fopen("Dados clientes.txt", "a");

    if(dados == NULL) /// certificar de que o arquivo abriu
    {
        printf("\n\nERRO\n\n");
        exit(0);
    }
    /// grava os dados no arquivo
    fprintf(dados, "Nome: %s\nUsuario: %s\nTelefone: %d%d\nE-mail: %s\nCidade: %s-%s\n\n", nome, user, ddd, numero, email, cidade, estado);

    fclose(dados);
    /// fecha arquivo ap�s a grava��o----------------------------------------------------------------------

    printf("\n\nObrigado por cadastrar-se, %s!", nome);
    getch();
    system("cls");
    printf("Seja bem vindo(a) a Locadora, %s!", user);
    fflush(stdin);
    Menu(user);

    SetConsoleCP(cpIn);
    SetConsoleOutputCP(cpOut);
    return nome;
}
void ConferirCadastro() /// fun��o para conferir cadastro
{
    unsigned int cp = 1252;
    unsigned int cpIn = GetConsoleCP();
    unsigned int cpOut = GetConsoleOutputCP();
    FILE *confere;
    int opc, op;
    char user[30], user1[30];

    SetConsoleCP(cp);
    SetConsoleOutputCP(cp);
    confere  = fopen("Dados clientes.txt", "r");

    if(confere == NULL)
    {
        printf("\n\nERRO!\n\n");
    }

    printf("Possui um usu�rio? (1)sim ou (2) n�o: ");
    scanf("%d",&opc);

    switch(opc) /// conferir a op��o digitada
    {
    case 1:
        printf("Digite seu nome de us�rio: ");
        fflush(stdin);
        gets(user);

        while(!feof(confere)) /// !feof confere o arquivo at� o final
        {
            fscanf(confere,"%s",user1);

            if(strcmp(user, user1) == 0) /// confere o usu�rio
            {
                system("cls");
                printf("Seja bem vindo(a) de volta %s!\n\n", user1); /// resposta ao usu�rio caso encontrado
                Menu(user1);
            }
        }
        printf("\n\nN�o encontramos o usu�rio! Tente de novo, por favor!\n\n"); /// se n�o  encontrar o usu�rio

        main();
        break;
    case 2:
        printf("\n\nVamos fazer um cadastro? (1)sim ou (2)n�o: ");
        scanf("%d", &op);
        if(op == 1)
        {
            cadastrar();
        }
        else if(op == 2)
        {
            printf("\n\nAhhh que pena :(, numa pr�xima vez ent�o...\n\n");
            exit(0);
        }
        else
        {
            printf("\n\nOp��o inv�lida!\n\n");
        }

        break;
    default:
        printf("Op��o inv�lida! Tente novamente!");
        main();
        break;
    }

    SetConsoleCP(cpIn);
    SetConsoleOutputCP(cpOut);
}
void Menu(char nome[]) /// fun��o responsav�l pelo menu
{
    setlocale(LC_ALL, "");
    int opc;

    do
    {
        printf("\nSelecione uma das op��es abaixo: \n\n");

        printf("1 - Alugar jogos\n");
        printf("2 - Devolu��o\n");
        printf("3 - Sair\n");
        printf("\nDigite a op��o: ");
        scanf("%d", &opc);

        switch(opc)
        {
        case 1:

            system("cls");
            jogos();
            alugar(nome);
            getch();
            system("cls");
            break;
        case 2:

            system("cls");
            jogos();
            devolve(nome);
            getch();
            system("cls");
            break;
        case 3:
            printf("Obrigado! At� a pr�xima!");
            fflush(stdin);
            getchar();
            exit(0);
            break;
        default:
            printf("Op��o inv�lida!");
            break;

        }
    }
    while(opc != 3);

}

int main() /// fun��o principal
{
    setlocale(LC_ALL, "");

    ConferirCadastro();

    return 0;
}
