#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define Max_Contas 5
#define Max_Projectos 20
#define Max_Servicos 50
#define Max_Custos 200
#define Max_Datas 5000
#define Max_Horas 5000

typedef struct
{
    int Dia;
    int Mes;
    int Ano;
}t_Data;

typedef struct
{
    int hora;
    int min;
}t_Hora;

typedef struct
{
    int Identificador_Conta;
    char Designacao_Conta [50];
    char Plataforma_Fornecedor_Servicos [50];
    char Organizacao [50];
    char Dominio [50];
    float Saldo_Conta;
}t_Conta;

typedef struct
{
    int Identificador_Projeto;
    char Nome_Projeto [50];
    char Equipa_Projeto [50];
    t_Data Data;
}t_Projeto;

typedef struct
{
    int Identificador_Servico;
    char Designacao_Servico [50];
    char Tipo_Servico [50];
    char Unidade_Medida [50];
    float Custo_Por_Unidade;
}t_Servico;

typedef struct
{
    t_Data Data_Inicio;
    t_Data Data_Fim;
    t_Hora Hora_Inicio;
    t_Hora Hora_Fim;
    int Quantidade;
    float Valor_Pago;
}t_Custo;

//Prototipos das Funções
char menu_opcoes(void);
int confirmar_saida(void);
float Ler_Numero(float, float);
int Validar_Data(int, int, int);
void ler_dados_conta (t_Conta[], int);
void mostrar_dados_conta (t_Conta[], int);
void Ler_Dados_Projeto(t_Projeto[], int);
void mostrar_dados_projeto (t_Projeto[], t_Conta[], int);
void Ler_Dados_Servico(t_Servico[], int);
void Mostrar_Dados_Servicos(t_Servico[], int);
int Ler_Dados_Custo(t_Custo[], int);
int Procurar_Identificador_contas(t_Conta[], int, int);
int Procurar_Identificador_Projetos(t_Projeto[], int, int);
int Procurar_Identificador_Servicos(t_Servico[], int, int);

int Ler_Hora_Inicio(t_Custo[], int);
int Ler_Hora_Fim(t_Custo[], int);

//void ler_data_projeto(t_Projeto[], int);

//Função Main
int main()
{
    int flag = 0,num_datas = 0, num_contas = 0, num_projetos = 0, num_servicos = 0, num_custos = 0, Ano, Mes, Dia;
    char op;

    t_Data Datas[Max_Datas];
    t_Hora Horas[Max_Horas];
    t_Conta Contas[Max_Contas];
    t_Projeto Projetos[Max_Projectos];
    t_Servico Servicos[Max_Servicos];
    t_Custo Custos[Max_Custos];

    setlocale(LC_ALL, "Portuguese");

    do {
	    op = menu_opcoes();

	    switch(op) {
            case '1':
                printf("\n\t----- Menu para registar dados de uma Conta -----\n");

                printf("\nIntroduza um número para identificar a sua conta (máximo 3 dígitos): ");
                Contas[num_contas].Identificador_Conta = Ler_Numero(0, 999);

                flag = Procurar_Identificador_contas(Contas, num_contas, Contas[num_contas].Identificador_Conta);

                if(flag == 0){

                ler_dados_conta(Contas, num_contas);
                num_contas++;
                }else if(flag == 1){
                    printf("\n\n\nJá existe outra conta identificada pelos mesmos dígitos.\n\n\n");
                }
                break;

            case '2':
                printf("\n\t----- Dados das Contas -----\n");

                mostrar_dados_conta(Contas, num_contas);

                break;

            case '3':
                printf("\n\t----- Menu para registar dados de um Projeto -----\n");

                printf("\nIntroduza um número para identificar o seu projeto (máximo 3 dígitos): ");
                Projetos[num_projetos].Identificador_Projeto = Ler_Numero(0, 999);

                flag = Procurar_Identificador_Projetos(Projetos, num_projetos, Projetos[num_projetos].Identificador_Projeto);

                if(flag == 0){

                    printf("\nIntroduza o identificador da conta a que está associado o projeto: ");
                    Contas[num_contas].Identificador_Conta = Ler_Numero(0, 999);

                    flag = Procurar_Identificador_contas(Contas, num_contas, Contas[num_contas].Identificador_Conta);

                    if(flag == 1){

                        Ler_Dados_Projeto(Projetos, num_projetos);

                        printf("\nIntroduza o dia: ");
                        Dia = Ler_Numero(1, 31);
                        printf("\nIntroduza o mes: ");
                        Mes = Ler_Numero(1, 12);
                        printf("\nIntroduza o ano: ");
                        Ano = Ler_Numero(1900, 9999);

                        flag = Validar_Data(Dia, Mes, Ano);

                        if(flag == 1){
                            Projetos[num_projetos].Data.Dia = Dia;
                            Projetos[num_projetos].Data.Mes = Mes;
                            Projetos[num_projetos].Data.Ano = Ano;
                            num_projetos++;

                        }else{
                        printf("\n\n\n*ERRO* Data inválida.\n\n\n");
                        }

                    }else if(flag == 0){
                    printf("\n\n\n*ERRO* Não existe nenhuma conta com esse identificador, tente de novo.\n\n\n");
                    }

                }else if(flag == 1){
                    printf("\n\n\nJá existe outro projeto identificado pelos mesmos dígitos.\n\n\n");
                }

                break;

            case '4':
                printf("\n\t----- Dados dos Projetos -----\n");

                mostrar_dados_projeto(Projetos, Contas, num_projetos);

                break;

            case '5':
                printf("\n\t----- Menu para registar dados de um Serviço -----\n");

                printf("\nIntroduza um número para identificar o seu Serviço (máximo 3 dígitos): ");
                Servicos[num_servicos].Identificador_Servico = Ler_Numero(0, 999);

                flag = Procurar_Identificador_Servicos(Servicos, num_servicos, Servicos[num_servicos].Identificador_Servico);

                if(flag == 0){

                Ler_Dados_Servico(Servicos, num_servicos);
                num_servicos++;

                }else if(flag == 1){
                    printf("\n\n\nJá existe outro Serviço identificado pelos mesmos dígitos.\n\n\n");
                }

                break;

            case '6':
                printf("\n\t----- Dados dos Serviços -----\n");

                Mostrar_Dados_Servicos(Servicos, num_servicos);

                break;

            case '7':
                printf("\n\t----- Menu para registar dados dos Custos -----\n");

                printf("\nIntroduza o identificador do serviço onde será aplicado este custo: ");
                Servicos[num_servicos].Identificador_Servico = Ler_Numero(0, 999);

                flag = Procurar_Identificador_Servicos(Servicos, num_servicos, Servicos[num_servicos].Identificador_Servico);

                if(flag == 1){
                    printf("\nIntroduza o identificador do projeto onde foi utilizado o serviço: ");
                    Projetos[num_projetos].Identificador_Projeto = Ler_Numero(0, 999);

                    flag = Procurar_Identificador_Projetos(Projetos, num_projetos, Projetos[num_projetos].Identificador_Projeto);

                    if(flag == 1){

                        printf("\t---- Introduzir data de Ínicio de Utilização do Projeto----");
                        printf("\nIntroduza o dia: ");
                        Dia = Ler_Numero(1, 31);
                        printf("\nIntroduza o mes: ");
                        Mes = Ler_Numero(1, 12);
                        printf("\nIntroduza o ano: ");
                        Ano = Ler_Numero(1900, 9999);

                        flag = Validar_Data(Dia, Mes, Ano);

                        if(flag == 1){
                            Custos[num_custos].Data_Inicio.Dia = Dia;
                            Custos[num_custos].Data_Inicio.Mes = Mes;
                            Custos[num_custos].Data_Inicio.Ano = Ano;

                            printf("\n\n\t---- Introduzir Hora de Ínicio de Utilização do Projeto----");
                            Ler_Hora_Inicio(Custos, num_custos);

                            printf("\t---- Introduzir data de Fim de Utilização do Projeto----");
                            printf("\nIntroduza o dia: ");
                            Dia = Ler_Numero(1, 31);
                            printf("\nIntroduza o mes: ");
                            Mes = Ler_Numero(1, 12);
                            printf("\nIntroduza o ano: ");
                            Ano = Ler_Numero(1900, 9999);

                            flag = Validar_Data(Dia, Mes, Ano);

                            if(flag == 1){
                                Custos[num_custos].Data_Fim.Dia = Dia;
                                Custos[num_custos].Data_Fim.Mes = Mes;
                                Custos[num_custos].Data_Fim.Ano = Ano;

                                printf("\n\n\t---- Introduzir Hora de Fim de Utilização do Projeto----");
                                Ler_Hora_Fim(Custos, num_custos);
                                num_custos++;

                                Ler_Dados_Custo(Custos, num_custos);

                            }else{
                            printf("\n\n\n*ERRO* Data inválida.\n\n\n");
                            }

                        }else{
                        printf("\n\n\n*ERRO* Data inválida.\n\n\n");
                        }

                    }else if(flag == 0){
                        printf("\n\n\n*ERRO* Não existe nenhum projeto com esse identificador, tente de novo.\n\n\n");
                    }

                }else if(flag == 0){
                    printf("\n\n\n*ERRO* Não existe nenhum serviço com esse identificador, tente de novo.\n\n\n");
                }

                break;

            case '8':

                Mostrar_Dados_Custo(Custos, Projetos, Servicos, num_custos);

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

//Função do Menu de Opçoes
char menu_opcoes(void) {

    char op;

        do {
            printf("\n\t----- Menu de Opcoes -----\n\n");
            printf(" 1 - Registar dados de uma Conta\n");
            printf(" 2 - Mostrar dados das Contas\n"); //futuramente alterar para mostrar apenas a escolhida
            printf(" 3 - Registar dados de um Projeto\n");
            printf(" 4 - Mostrar dados dos Projeto\n");
            printf(" 5 - Registar dados de um Serviço\n");
            printf(" 6 - Mostrar dados dos Serviços\n");
            printf(" 7 - Registar dados dos Custos de Utilização de um Serviço\n");
            printf(" 8 - Mostrar dados dos Custos de Utilização dos Serviço\n");
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

//Função para ler um numero
float Ler_Numero(float lim_inf, float lim_sup)
{
    float num;

    do {
	scanf(" %f", &num);

    if (num < lim_inf || num > lim_sup)
    {
        printf("\nNumero invalido, tente de novo: ");
    }

    } while(num < lim_inf || num > lim_sup);

    return num;
}

//Função para ler a data num projeto
/*void ler_data_projeto(t_Projeto data[], int num_projetos)
{
    int Dia, Mes, Ano, flag = 0;

    printf("\nIntroduza o dia: ");
    Dia = Ler_Numero(1, 31);
    printf("\nIntroduza o mes: ");
    Mes = Ler_Numero(1, 12);
    printf("\nIntroduza o ano: ");
    Ano = Ler_Numero(1900, 9999);

    flag = Validar_Data(Dia, Mes, Ano);

    if(flag == 1){

        data[num_projetos].Data.Dia = Dia;
        data[num_projetos].Data.Mes = Mes;
        data[num_projetos].Data.Ano = Ano;
        num_projetos++;

    }else{
        printf("\n\n\n*ERRO* Data inválida.\n\n\n");
    }
}*/

//Função para validar a data
int Validar_Data(int Dia, int Mes, int Ano)
{
    int flag = 0;
    //Ver o ano
    if(Ano>=1900 && Ano<=9999)
    {
        //Ver o mês
        if(Mes>=1 && Mes<=12)
        {
            //Ver o dia
            if((Dia>=1 && Dia<=31) && (Mes==1 || Mes==3 || Mes==5 || Mes==7 || Mes==8 || Mes==10 || Mes==12)){
                printf("% \n");
                flag = 1;
            }
            else if((Dia>=1 && Dia<=30) && (Mes==4 || Mes==6 || Mes==9 || Mes==11)){
                    printf("% \n");
                    flag = 1;
            }
            else if((Dia>=1 && Dia<=28) && (Mes==2)){
                printf("% \n");
                flag = 1;
            }
           else if (Dia==29 && Mes==2 && ( Ano %400==0 ||( Ano %4==0 && Ano %100!=0 )))
           {
                printf("% \n");
                flag = 1;
           }
            else{
                printf("Dia inválido.\n");
            }
        }
        else
        {
            printf("Mes inválido.\n");
        }
    }
    else
    {
        printf("Ano inválido.\n");
    }
      return flag;
}

//Função de Ler os dados das contas
void ler_dados_conta(t_Conta contas[], int num_contas)
{

        printf("\nDesigne a sua conta: ");
        fflush(stdin);
        fgets(contas[num_contas].Designacao_Conta, 50, stdin);

        printf("\nIndique a sua Plataforma de Fornecedor: ");
        fflush(stdin);
        fgets(contas[num_contas].Plataforma_Fornecedor_Servicos, 50, stdin);

        printf("\nIndique qual a sua organização: ");
        fflush(stdin);
        fgets(contas[num_contas].Organizacao, 50, stdin);

        printf("\nIndique o seu domínio: ");
        fflush(stdin);
        fgets(contas[num_contas].Dominio, 50, stdin);

        printf("\nIntroduza o saldo da sua conta: ");
        contas[num_contas].Saldo_Conta = Ler_Numero(0, 9999999999999999999999.99);

}

//Função de Mostrar os dados das contas
void mostrar_dados_conta(t_Conta contas[], int num_contas)
{
    int i;

    for(i = 0; i<num_contas; i++) {

        printf("\n\n\t----------------------------");
        printf("\tInformação da %dº conta: ", i+1);
        printf("\t----------------------------");

        printf("\nNumero identificador da sua conta: %d\n", contas[i].Identificador_Conta);
        printf("\nDesignação da sua conta: %s\n", contas[i].Designacao_Conta);
        printf("\nPlataforma do Fornecedor de Serviços: %s\n", contas[i].Plataforma_Fornecedor_Servicos);
        printf("\nA Organização Indicada é: %s\n", contas[i].Organizacao);
        printf("\nO domínio é: %s\n", contas[i].Dominio);
        printf("\nO saldo atual da conta é: %0.2f euros\n", contas[i].Saldo_Conta);
    }
}

//Função de ler os dados dos projetos
void Ler_Dados_Projeto(t_Projeto projetos[], int num_projetos)
{
    //int Dia, Mes, Ano, flag = 0;
    printf("\nIndique o nome do Projeto: ");
    fflush(stdin);
    fgets(projetos[num_projetos].Nome_Projeto, 50, stdin);

    printf("\nIntroduza o nome da sua equipa: ");
    fflush(stdin);
    fgets(projetos[num_projetos].Equipa_Projeto, 50, stdin);

    //ler_data_projeto(projetos, num_projetos);
}

//Função de Mostrar os dados dos projetos
void mostrar_dados_projeto(t_Projeto projetos[], t_Conta contas[], int num_projetos)
{
    int i;

    for(i = 0; i<num_projetos; i++) {

        printf("\n\n\t----------------------------");
        printf("\tInformação da %dº projeto: ", i+1);
        printf("\t----------------------------");

        printf("\nNumero identificador do seu projeto: %d\n", projetos[i].Identificador_Projeto);
        printf("\nIdentificador da conta a que está assossiado o projeto: %d\n", contas[i].Identificador_Conta);
        printf("\nNome do projeto: %s\n", projetos[i].Nome_Projeto);
        printf("\nEquipa do projeto: %s\n", projetos[i].Equipa_Projeto);
        printf("\nData de criação do projeto: %d/%d/%d\n", projetos[i].Data.Dia, projetos[i].Data.Mes, projetos[i].Data.Ano);
    }
}

//Função para ler os dados dos serviços
void Ler_Dados_Servico(t_Servico servicos[], int num_servicos)
{

        printf("\nDesigne o seu Serviço: ");
        fflush(stdin);
        fgets(servicos[num_servicos].Designacao_Servico, 50, stdin);

        printf("\nIndique qual o seu tipo de serviço: ");
        fflush(stdin);
        fgets(servicos[num_servicos].Tipo_Servico, 50, stdin);

        printf("\nIndique a Unidade de medida(GByte, hora, segundo, etc): ");
        fflush(stdin);
        fgets(servicos[num_servicos].Unidade_Medida, 50, stdin);

        printf("\nIndique o Custo por Unidade: ");
        servicos[num_servicos].Custo_Por_Unidade = Ler_Numero(0, 9999999999999999999999);
}

//Função de Mostrar os dados dos Serviços
void Mostrar_Dados_Servicos(t_Servico servicos[], int num_servicos)
{
    int i;

    for(i = 0; i<num_servicos; i++) {

        printf("\n\n\t----------------------------");
        printf("\tInformação da %dº conta: ", i+1);
        printf("\t----------------------------");

        printf("\nNumero identificador do serviço: %d\n", servicos[i].Identificador_Servico);
        printf("\nDesignação do serviço: %s\n", servicos[i].Designacao_Servico);
        printf("\nTipo de Serviço: %s\n", servicos[i].Tipo_Servico);
        printf("\nUnidade de medida aplicada ao serviço: %s\n", servicos[i].Unidade_Medida);
        printf("\nCusto por Unidade: %0.2f euros\n", servicos[i].Custo_Por_Unidade);
    }
}

//Função para ler os dados dos custos
int Ler_Dados_Custo(t_Custo custos[], int num_custos)
{
        printf("\nQuantidade de horas utilizadas: ");
        custos[num_custos].Quantidade = Ler_Numero(0, 9999999999999999999999);

        printf("\nValor a pagar: ");
        custos[num_custos].Valor_Pago = Ler_Numero(0, 9999999999999999999999);
}

//Função de Mostrar os dados dos Custos
void Mostrar_Dados_Custo(t_Custo custos[],t_Projeto projetos[], t_Servico servicos[], int num_custos)
{
    int i;

    for(i = 0; i<num_custos; i++) {

        printf("\n\n\t----------------------------");
        printf("\tInformação do %dº custo: ", i+1);
        printf("\t----------------------------");

        printf("\nNumero identificador do serviço onde foi aplicado este custo: %d\n", servicos[i].Identificador_Servico);
        printf("\nNumero identificador do projeto onde foi utilizado o serviço acima: %d\n", projetos[i].Identificador_Projeto);
        printf("\nData/Hora de inicio de utilização: %d-%d-%d  %d:%d\n", custos[i].Data_Inicio.Dia, custos[i].Data_Inicio.Mes, custos[i].Data_Inicio.Ano, custos[i].Hora_Inicio.hora, custos[i].Hora_Inicio.min);
        printf("\nData/Hora de fim de utilização: %d-%d-%d  %d:%d\n", custos[i].Data_Fim.Dia, custos[i].Data_Fim.Mes, custos[i].Data_Fim.Ano, custos[i].Hora_Fim.hora, custos[i].Hora_Fim.min);
        printf("\nQuantidade de horas utilizadas: %d\n", custos[i].Quantidade);
        printf("\nValor a pagar: %0.2f\n", custos[i].Valor_Pago);

    }
}

//Função de Confirmar saída do programa
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

//Função de Verificação de Identificador das contas
int Procurar_Identificador_contas(t_Conta identificador[], int numero_contas, int numero_da_conta)
{
    int i, flag=0;

    for(i = 0; i<numero_contas; i++) {
    	if(identificador[i].Identificador_Conta == numero_da_conta) {
            flag = 1;
        }
    }
    return flag;
}

//Função de Verificação de Identificador dos Projetos
int Procurar_Identificador_Projetos(t_Projeto identificador[], int numero_projetos, int numero_do_projeto)
{
    int i, flag=0;

    for(i = 0; i<numero_projetos; i++) {
    	if(identificador[i].Identificador_Projeto == numero_do_projeto) {
            flag = 1;
        }
    }
    return flag;
}

//Função de Verificação de Identificador dos Serviços
int Procurar_Identificador_Servicos(t_Servico identificador[], int numero_servicos, int numero_do_servico)
{
    int i, flag=0;

    for(i = 0; i<numero_servicos; i++) {
    	if(identificador[i].Identificador_Servico == numero_do_servico) {
            flag = 1;
        }
    }
    return flag;
}

//Função de Ler as horas de inicio
int Ler_Hora_Inicio(t_Custo horas[], int num_custos)
{
    int hora, min;

    printf("\nIndique a hora: ");
    horas[num_custos].Hora_Inicio.hora = Ler_Numero(0, 23);
    printf("\nIndique os minutos: ");
    horas[num_custos].Hora_Inicio.min = Ler_Numero(0, 59);
}

//Função de Ler as horas de fim
int Ler_Hora_Fim(t_Custo horas[], int num_custos)
{

    printf("\nIndique a hora: ");
    horas[num_custos].Hora_Fim.hora = Ler_Numero(0, 23);
    printf("\nIndique os minutos: ");
    horas[num_custos].Hora_Fim.min = Ler_Numero(0, 59);
}
