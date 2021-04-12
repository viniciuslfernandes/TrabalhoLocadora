#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h> /// a biblioteca windows foi adcionada para corrigir erros
                    /// de leitura de caracteres especiais
#define linhas 16
#define preco 3

void  jogos () /// função para abrir o jogos
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
void alugar(char nome[]) /// função para alugar
{
    int o, *cpr, lin = 1;
    FILE *alg;
    char jog[40];
    int dias;
    float val=0;
    printf("\n\nO valor do aluguel de cada jogo é R$3,00 por dia!");
    printf("\n\nDigite o número referente ao jogo que deseja alugar: ");
    scanf("%d", &o);
    printf("\n\nInforme quantos dias você pretende ficar com o jogo:\n1- 15 dias\n2- 7 dias\n3- 3 dias\n");
    printf("\nOpção: ");
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
        printf("opção invalida");
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
void devolve (char n[]) /// função de  devolução
{
    int o, *cpr, lin = 1;
    FILE *alg;
    char jog[40];

    printf("\n\nDigite o número referente ao jogo que deseja devovler: ");
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
char cadastrar() /// função para cadastro
{
    unsigned int cp = 1252;
    unsigned int cpIn = GetConsoleCP();
    unsigned int cpOut = GetConsoleOutputCP();
    char nome[30], cidade[30], estado[30], user[30];
    int ddd, numero;
    char email[30];
    FILE *dados;

    /// pede os dados do usuário--------------------------------

    SetConsoleCP(cp);
    SetConsoleOutputCP(cp);
    printf("\nInforme seu nome completo: ");/// nome
    fflush(stdin);
    gets(nome);
    printf("\nCrie um nome de usuário: "); /// usuário
    fflush(stdin);
    gets(user);

    printf("\nDigite seu DDD e o número (separado  por espaço, respectivamente): "); /// DDD e número
    scanf("%d %d", &ddd, &numero);

    printf("\nDigite seu e-mail: "); /// e-mail
    scanf("%s", &email);

    printf("\nSua cidade e Estado (separado  por espaço, respectivamente): "); /// cidade Estado
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
    /// fecha arquivo após a gravação----------------------------------------------------------------------

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
void ConferirCadastro() /// função para conferir cadastro
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

    printf("Possui um usuário? (1)sim ou (2) não: ");
    scanf("%d",&opc);

    switch(opc) /// conferir a opção digitada
    {
    case 1:
        printf("Digite seu nome de usário: ");
        fflush(stdin);
        gets(user);

        while(!feof(confere)) /// !feof confere o arquivo até o final
        {
            fscanf(confere,"%s",user1);

            if(strcmp(user, user1) == 0) /// confere o usuário
            {
                system("cls");
                printf("Seja bem vindo(a) de volta %s!\n\n", user1); /// resposta ao usuário caso encontrado
                Menu(user1);
            }
        }
        printf("\n\nNão encontramos o usuário! Tente de novo, por favor!\n\n"); /// se não  encontrar o usuário

        main();
        break;
    case 2:
        printf("\n\nVamos fazer um cadastro? (1)sim ou (2)não: ");
        scanf("%d", &op);
        if(op == 1)
        {
            cadastrar();
        }
        else if(op == 2)
        {
            printf("\n\nAhhh que pena :(, numa próxima vez então...\n\n");
            exit(0);
        }
        else
        {
            printf("\n\nOpção inválida!\n\n");
        }

        break;
    default:
        printf("Opção inválida! Tente novamente!");
        main();
        break;
    }

    SetConsoleCP(cpIn);
    SetConsoleOutputCP(cpOut);
}
void Menu(char nome[]) /// função responsavél pelo menu
{
    setlocale(LC_ALL, "");
    int opc;

    do
    {
        printf("\nSelecione uma das opções abaixo: \n\n");

        printf("1 - Alugar jogos\n");
        printf("2 - Devolução\n");
        printf("3 - Sair\n");
        printf("\nDigite a opção: ");
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
            printf("Obrigado! Até a próxima!");
            fflush(stdin);
            getchar();
            exit(0);
            break;
        default:
            printf("Opção inválida!");
            break;

        }
    }
    while(opc != 3);

}

int main() /// função principal
{
    setlocale(LC_ALL, "");

    ConferirCadastro();

    return 0;
}
