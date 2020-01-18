#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define Max_Contas 5
#define Max_Projectos 20
#define Max_Servicos 50
#define Max_Custos 200

//Structs
typedef struct{
    int Identificador;
    char Designacao [50];
    char Plataforma_Fornecedor_Servicos [50];
    char Organizacao [50];
    char Dominio [50];
    float Saldo;

    char Nome_Projeto [80];
    char Nome_Equipa [80];
    //int Data_Criacao_Projeto;

    int Data;

    char Tipo_Servico [80];
    char Unidade_Medida [40];
    float Custo_Unidade;

    //Data e Hora de Inicio e Fim
    int quantidade;
    float valor;
} t_Geral;

//Prototipos das Fun��es
char menu_opcoes(void);
int confirmar_saida(void);
float Ler_Numero(float, float);
void ler_dados_conta (t_Geral[], int);
void mostrar_dados_conta (t_Geral[], int);
void Ler_Dados_Projeto(t_Geral[], int);
void mostrar_dados_projeto (t_Geral[], int);

//Fun��o Main
int main()
{
    int flag = 0;
    int num_contas = 0, num_projetos = 0, num_servicos = 0;
    char op;

    t_Geral Contas[Max_Contas], Projetos[Max_Projectos];
    //Servicos[Max_Servicos], Custos[Max_Custos];

    setlocale(LC_ALL, "Portuguese");

    do {
	    op = menu_opcoes();

	    switch(op) {
            case '1':
                printf("\n\t----- Menu para registar dados de uma Conta -----\n");

                printf("\nIntroduza um n�mero para identificar a sua conta (m�ximo 3 d�gitos): ");
                Contas[num_contas].Identificador = Ler_Numero(0, 999);

                flag = Procurar_Identificador_contas(Contas, num_contas, Contas[num_contas].Identificador);

                if(flag == 0){

                ler_dados_conta(Contas, num_contas);
                num_contas++;
                }else if(flag == 1){
                    printf("\n\n\nJ� existe outra conta identificada pelos mesmos d�gitos.\n\n\n");
                }


                break;

            case '2':
                printf("\n\t----- Dados das Contas -----\n");

                mostrar_dados_conta(Contas, num_contas);

                break;

            case '3':
                printf("\n\t----- Menu para registar dados de um Projeto -----\n");

                printf("\nIntroduza um n�mero para identificar o seu projeto (m�ximo 3 d�gitos): ");
                Projetos[num_projetos].Identificador = Ler_Numero(0, 999);

                flag = Procurar_Identificador_Projetos(Projetos, num_projetos, Projetos[num_projetos].Identificador);

                if(flag == 0){

                    printf("\nIntroduza o identificador da conta a que est� associado o projeto: ");
                    Contas[num_contas].Identificador = Ler_Numero(0, 999);

                    flag = Procurar_Identificador_contas(Contas, num_contas, Contas[num_contas].Identificador);

                    if(flag == 1){

                    Ler_Dados_Projeto(Projetos, num_projetos);
                    num_projetos++;

                    }else if(flag == 0){
                    printf("\n\n\n*ERRO* N�o existe nenhuma conta com esse identificador, tente de novo.\n\n\n");
                    }

                }else if(flag == 1){
                    printf("\n\n\nJ� existe outro projeto identificado pelos mesmos d�gitos.\n\n\n");
                }

                break;

            case '4':
                /*printf("\n\t----- Dados dos Projetos -----\n");

                mostrar_dados_projeto(Projetos, num_projetos);*/

                break;

            case '5':
                /*printf("\n\t----- Menu para registar dados de um Servi�o -----\n");

                Ler_Dados_Servico(Servicos, num_servicos);
                num_servicos++;*/

                break;

            case '6':
                /*printf("\n\t----- Dados dos Servi�os -----\n");

                mostrar_dados_servico(Servicos, num_servicos);*/

                break;

            case '7':
                //Ler_Dados_Custo(Custos, num_contas);

                break;

            case '8':

                break;

            case '9':

                break;

            case '10':

                break;

            case '11':

                break;

            case '12':

                break;

            case '0':
                confirmar_saida();

                break;

            default:
                printf("Introduza uma opcao valida!");
       	    }

    } while(op != '0');

    return 0;
}

//Fun��o do Menu de Op�oes
char menu_opcoes(void) {

    char op;

        do {
            printf("\n\t----- Menu de Opcoes -----\n\n");
            printf(" 1 - Registar dados de uma Conta\n");
            printf(" 2 - Mostrar dados das Contas\n"); //futuramente alterar para mostrar apenas a escolhida
            printf(" 3 - Registar dados de um Projeto\n");
            printf(" 4 - Mostrar dados dos Projeto\n");
            printf(" 5 - Registar dados de um Servi�o\n");
            printf(" 6 - Mostrar dados dos Servi�os\n");
            printf(" 7 - Registar dados dos Custos de Utiliza��o de um Servi�o\n");
            printf(" 8 - Mostrar dados dos Custos de Utiliza��o dos Servi�o\n");
            printf(" 9 - Estatisticas\n");
            printf(" 10 - Gravar dados no ficheiro binario\n");
            printf(" 11 - Ler dados do ficheiro binario\n");
            printf(" 12 - Eliminar dados de...\n");
            printf(" 0 - Sair\n");
            printf("\n\tSelecione uma opcao -> ");
            scanf(" %c", &op);
        } while(op != '1' && op != '2' && op != '3' && op != '4' && op != '5' && op != '6' && op != '7' && op != '8' && op != '9' && op != '10' && op != '11' && op != '12' && op != '0');

	return op;
}

//Fun��o para ler um numero
float Ler_Numero(float lim_inf, float lim_sup)
{
    float num;

    do {
	scanf(" %f", &num);

	if (num < lim_inf || num > lim_sup)
        {
        printf("\nPor favor indique um numero de at� 3 digitos: ");
        }
    } while(num < lim_inf || num > lim_sup);

    return num;
}

//Fun��o de Ler os dados das contas
void ler_dados_conta(t_Geral contas[], int num_contas)
{

        printf("\nDesigne a sua conta: ");
        fflush(stdin);
        fgets(contas[num_contas].Designacao, 50, stdin);

        printf("\nIndique a sua Plataforma de Fornecedor: ");
        fflush(stdin);
        fgets(contas[num_contas].Plataforma_Fornecedor_Servicos, 50, stdin);

        printf("\nIndique qual a sua organiza��o: ");
        fflush(stdin);
        fgets(contas[num_contas].Organizacao, 50, stdin);

        printf("\nIndique o seu dom�nio: ");
        fflush(stdin);
        fgets(contas[num_contas].Dominio, 50, stdin);

        printf("\nIntroduza o saldo da sua conta: ");
        contas[num_contas].Saldo = Ler_Numero(0, 9999999999999999999999.99);

}

//Fun��o de Mostrar os dados das contas
void mostrar_dados_conta(t_Geral contas[], int num_contas)
{
    int i;

    for(i = 0; i<num_contas; i++) {

        printf("\n\n\t----------------------------");
        printf("\tInforma��o da %d� conta: ", i+1);
        printf("\t----------------------------");

        printf("\nNumero identificador da sua conta: %d\n", contas[i].Identificador);
        printf("\nDesigna��o da sua conta: %s\n", contas[i].Designacao);
        printf("\nPlataforma do Fornecedor de Servi�os: %s\n", contas[i].Plataforma_Fornecedor_Servicos);
        printf("\nA Organiza��o Indicada �: %s\n", contas[i].Organizacao);
        printf("\nO dom�nio �: %s\n", contas[i].Dominio);
        printf("\nO saldo atual da conta �: %0.2f euros\n", contas[i].Saldo);
    }
}

//Fun��o de ler os dados dos projetos
void Ler_Dados_Projeto(t_Geral projetos[], int num_projetos)
{
    int flag = 0, numero, dia, mes, ano;
    struct tm * tm;
    time_t t;
    char data[20];

    //assossiar o identificador a uma conta existente

    printf("\nIndique o nome do Projeto: ");
    fflush(stdin);
    fgets(projetos[num_projetos].Nome_Projeto, 50, stdin);

    printf("\nIntroduza o nome da sua equipa: ");
    fflush(stdin);
    fgets(projetos[num_projetos].Nome_Equipa, 50, stdin);

    printf("\nIntroduza a data de criacao do projecto DD/MM/AA: ");
    strftime(data, 20, "%d/%m/%y", tm);
    scanf("%s", data);
}

//Fun��o de Confirmar sa�da do programa
int confirmar_saida(void) {
    char resposta;

    printf("\nQuer mesmo sair? (S/N): ");
    scanf(" %c", &resposta);

    if (resposta == 'S' || resposta == 's'){
        printf("A sair... \n");
        return 0;
    } else
        main();

    return 0;
}

//Fun��o de Verifica��o de Identificador das contas
int Procurar_Identificador_contas(t_Geral identificador[], int numero_contas, int numero_da_conta)
{
    int i, flag=0;

    for(i = 0; i<numero_contas; i++) {
    	if(identificador[i].Identificador == numero_da_conta) {
            flag = 1;
        }
    }
    return flag;
}

//Fun��o de Verifica��o de Identificador dos Projetos
int Procurar_Identificador_Projetos(t_Geral identificador[], int numero_projetos, int numero_do_projeto)
{
    int i, flag=0;

    for(i = 0; i<numero_projetos; i++) {
    	if(identificador[i].Identificador == numero_do_projeto) {
            flag = 1;
        }
    }
    return flag;
}

//Fun��o Ler data
//int Ler_Data
