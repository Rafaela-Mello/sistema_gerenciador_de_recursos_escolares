#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#define NUM_MAX 100
typedef struct Alimento {
    int ocupado;
	char nome[101];
	int quantidade;
	char validade[11];
	int dia, mes, ano;
} Alimento;
Alimento vetor_alimento[NUM_MAX];
int total_alimento = 0;
char caminho_arquivo_alimento[101];
void cadastro_inicializar();
void cadastro_inicializar_arquivo(); //cria o arquivo de dados (caso ele n�o exista) que ir� guardar os dados do cadastro
void cadastro_carregar_dados_arquivo(); //carrega os dados de um arquivo de texto para o vetor de estruturas Alimento
void cadastro_salvar_dados_arquivo(); //salva os dados do vetor de estrutura Alimento em um arquivo de texto
int tela_menu(); //mostra a tela com o menu de op��es (retorna -1 se for inv�lida)
void tela_cadastrar(); //mostra a tela de cadastro
void tela_pesquisar(); //mostra a tela de pesquisa pelo nome
void tela_remover(); //mostra a tela remover alimento do cadastro
void tela_relatorio(); //mostra a tela de relat�rio do estoque
int tela_sair(); //mostra a tela sair (retorna 1 para encerrar e 0 para n�o encerrar)
int estoque_vazio(); //mostra que o estoque est� vazio (utilizado em pesquisa, remover e relat�rio)
int tela_mensagem(char *mensagem);
int main()
{
    setlocale(LC_ALL, "portuguese");
    system("chcp 1252 > null");
    int sair = 0;   //controla quando o program deve ser encerrao
    int opcao;      //guarda a op��o escolhida pelo usu�rio no menu de op��o
    int erro;       //indicador de erro usado na leitura de valores do teclado
    int continuar;  //controla se o usu�rio quer continuar: cadastrar, pesquisar, ou remover um alimento;
    cadastro_inicializar(); //faz as inicializa��es do cadastro de alimentos
    cadastro_inicializar_arquivo(); //cria o arquivo de dados (caso ele n�o exista) que ir� guardar os dados do cadastro
    cadastro_carregar_dados_arquivo(); //carrega os dados de um arquivo de texto para o vetor de estruturas Alimento
	char nome[101];
	int quantidade;
	int dia, mes, ano;
	char validade[11];
    int idxPesquisa = -1; //guarda o indice de: alimento pesquisado - alimento que ser� removida
    do {
        opcao = tela_menu();
        switch(opcao)
        {
            case 1:
                tela_cadastrar();
            break;
            case 2:
                tela_pesquisar();
            break;
            case 3:
                tela_remover();
            break;
            case 4:
                tela_relatorio();
            break;
            case 5:
                sair = tela_sair();
            break;
            default:
                printf("\nOp��o Inv�lida !!! \n");
                system("pause");
        }
    } while (sair == 0);
    cadastro_salvar_dados_arquivo();
    system("cls");
    printf("\nFim da execu��o do programa!\n");
    return 0;
}
void cadastro_inicializar()
{
    total_alimento = 0; //zera o contador de alimentos cadastrados (vari�vel global) - guarda o total de alimentos cadastrados
    for(int i = 0; i < NUM_MAX; i++)
    {
        vetor_alimento[i].ocupado = 0;
    }
}
int tela_menu()
{
    int opcao;
    system("cls");
    printf("Menu de Op��es do Estoque de Alimentos \n");
    printf("1 - Cadastrar \n");
    printf("2 - Pesquisar \n");
    printf("3 - Remover \n");
    printf("4 - Relat�rio do estoque \n");
    printf("5 - Sair \n\n");
    printf("Escolha uma op��o: "); //faz a leitura da op��o escolhida
    int erro = scanf("%d", &opcao);
    if(erro != 1) {
        fflush(stdin); //limpa o buffer do tecaldo (windows)
        opcao = -1; //como teve uma falha na leitura, marca uma op��o inv�lida
    }
    return opcao; //retorna a op��o escolhida
}
void tela_cadastrar()
{
	char nome[101];
	int quantidade;
	int dia, mes, ano;
	char validade[11];
	int idxPesquisa = -1; //guarda o indice de: alimento pesquisado - alimento que ser� removida
    int continuar; //controla se o usu�rio quer cadastrar um novo alimento
    int erro;       //indicador de erro usado na leitura de valores do teclado
    do {
        system("cls");
        printf("1 - Cadastrar \n");
        if(total_alimento >= NUM_MAX)
        {
            printf("\nERRO: O cadastro j� atingiu sua capacidade m�xima de 100 alimentos!\n");
            system("pause");
            break;
        }
        do
        {
            erro = 0;
            printf("\nDigite o nome: ");
            scanf(" %100[^\n]", nome);
            fflush(stdin);
            if(strlen(nome) > 100)
            {
                erro = 1; //marca a ocorr�ncia de um erro
                printf("ERRO: O nome do alimento deve possuir no m�ximo 100 (cem) carracteres!\n");
            }
            if(strlen(nome) < 2) {
                erro = 1; //marca a ocorr�ncia de um erro
                printf("ERRO: O nome do alimento deve possuir pelo menos 2 (dois) carracteres!\n");
            }
        } while(erro == 1);
        do
        {
            printf("\nDigite a quantidade: ");
            erro = scanf("%d", &quantidade);
            fflush(stdin); //limpa o buffer do teclado para o caso do scanf falhar, ou o usu�rio digitar alguma coisa ap�s o n�mero inteiro
            if(erro != 1)
            {
                printf("ERRO: Digite um valor inteiro v�lido!\n");
            }
        } while(erro != 1); //FIM DA ENTRADA DA QUANTIDADE
        do
        {
            erro = 0;
            printf("\nDigite a validade (xx/xx/xxxx): ");
            scanf(" %10[^\n]", validade);
            fflush(stdin);
            if((strlen(validade) != 10) || (validade[2] != '/' || validade[5] != '/'))
            {
                erro = 1; //marca a ocorr�ncia de um erro
                printf("ERRO 1: A validade deve possuir 10 caracteres e no formato indicado!\n");
            }
            if (sscanf(validade, "%d/%d/%d", &dia, &mes, &ano) != 3) {
                erro = 1;
                printf("ERRO 2: Deve ser informada no formato xx/xx/xxxx!\n");
            }
            if ((dia < 1 || dia > 31) || (mes < 1 || mes > 12) || (ano < 2020 || ano > 2100)) {
                erro = 1;
                printf("ERRO 3: Validade inv�lida!\n");
            }
        }while(erro == 1);
        idxPesquisa = -1;
        for(int i = 0; i < NUM_MAX; i++)
        {
            if(strcasecmp(vetor_alimento[i].nome, nome) == 0)
            {
                idxPesquisa = i; //indice do alimento com o mesmo nome no vetor de cadastro
                break;
            }
        }
        if(idxPesquisa != -1)
        {
            printf("\nErro: N�o foi poss�vel inserir os dados pois j� existe um alimento com o mesmo nome no cadastro:\v");
            printf("\nAlimento com o mesmo nome: \n");
            printf("Nome:         %s\n", vetor_alimento[idxPesquisa].nome);
            printf("Quantidade:   %d\n", vetor_alimento[idxPesquisa].quantidade);
            printf("Validade:     %s\n\n",vetor_alimento[idxPesquisa].validade);
            system("pause");
        }
        else {
            for(int i = 0; i < NUM_MAX; i++)
            {
                if(vetor_alimento[i].ocupado == 0)
                {
                    vetor_alimento[i].ocupado = 1; //marca a posi��o do vetor como ocupada
                    strcpy(vetor_alimento[i].nome, nome);
                    vetor_alimento[i].quantidade = quantidade;
                    strcpy(vetor_alimento[i].validade, validade);
                    total_alimento = total_alimento + 1; //incrementa a variavel global que contem o total de alimentos cadastrados
                    printf("\nDados cadastrados com sucesso! \n");
                    system("pause");
                    break;
                }
            }
        }
        continuar = tela_mensagem("\nGostaria de cadastrar outro alimento? ");
    } while(continuar == 1);
}
void tela_pesquisar()
{
    char nome[101];
    int idxPesquisa = -1; //guarda o indice de: alimento pesquisado - alimento que ser� removida
    int continuar; //controla se o usu�rio quer cadastrar um novo alimento
    int erro;       //indicador de erro usado na leitura de valores do teclado
    do{
        system("cls");
        printf("2 - Pesquisar \n");
        if (estoque_vazio()) {
            return; // sai da fun��o se o estoque estiver vazio
        }
        do {
            erro = 0; //marca que por enquanto n�o houve erro
            printf("\nDigite o nome: "); //ler no m�ximo 100 caracteres
            scanf(" %100[^\n]", nome);
            fflush(stdin); // limpa lixo no buffer do teclado
        } while(erro == 1); // FIM ENTRADA DO NOME
        idxPesquisa = -1;
        for(int i = 0; i < NUM_MAX; i++){
            if(vetor_alimento[i].ocupado == 1) {
                if(strcasecmp(vetor_alimento[i].nome, nome) == 0){
                    idxPesquisa = i;
                    break;
                }
            }
        }
        if(idxPesquisa != -1) {
            printf("\nAlimento Encontrado: \n");
            printf("Nome:         %s\n", vetor_alimento[idxPesquisa].nome);
            printf("Quantidade:   %d\n", vetor_alimento[idxPesquisa].quantidade);
            printf("Validade:     %s\n\n", vetor_alimento[idxPesquisa].validade);
            system("pause");
        }
        else {
            printf("\nN�o foi encontrado um alimento com o nome informado!\n\n");
            system("pause");
        }
        continuar = tela_mensagem("\nGostaria de pesquisar outro alimento? ");
    } while(continuar == 1);
}
void tela_remover()
{
    char nome[101];
    int idxPesquisa = -1; //guarda o indice de: alimento pesquisado - alimento que ser� removida
    int continuar; //controla se o usu�rio quer cadastrar um novo alimento
    int erro;       //indicador de erro usado na leitura de valores do teclado
    do {
        system("cls");
        printf("3 - Remover \n");
        if (estoque_vazio()) {
            return; // sai da fun��o se o estoque estiver vazio
        }
        do {
            erro = 0; //marca que por enquanto n�o houve erro
            printf("\nDigite o nome: ");
            scanf(" %100[^\n]", nome);
            fflush(stdin); // limpa lixo no buffer do teclado!!!
        } while(erro == 1); // FIM ENTRADA DO NOME DO ALIMENTO
        idxPesquisa = -1; //indica que por enquanto n�o encontrou ninguem com o nome pesquisado
        for(int i = 0; i < NUM_MAX; i++) {
            if(vetor_alimento[i].ocupado == 1) {
                if(strcasecmp(vetor_alimento[i].nome, nome) == 0){
                    total_alimento = total_alimento - 1;
                    vetor_alimento[i].ocupado = 0;
                    idxPesquisa = i;
                    break;
                }
            }
        }
        if(idxPesquisa != -1) {
            printf("\nAlimento removido com sucesso!\n\n");
        }
        else {
            printf("\nN�o foi poss�vel remover o alimento do cadastro!\n\n");
        }
        system("pause");
        continuar = tela_mensagem("\nGostaria de remover outro alimento? ");
    } while(continuar);
}
void tela_relatorio()
{
    system("cls");
    printf("4 - Relat�rio \n");
    if (estoque_vazio()) {
        return; // sai da fun��o se o estoque estiver vazio
    }
    printf("Total de Alimentos Cadastrados: %d\n\n", total_alimento);
    for(int i = 0; i < NUM_MAX; i++){
        if(vetor_alimento[i].ocupado == 1) {
            printf("Nome:         %s\n", vetor_alimento[i].nome);
            printf("Quantidade:   %d\n", vetor_alimento[i].quantidade);
            printf("Validade:     %s\n\n", vetor_alimento[i].validade);
        }
    }
    system("pause");
}
int tela_sair()
{
    int sair;
    system("cls");
    printf("5 - Sair \n");
    sair = tela_mensagem("\nDeseja mesmo sair?");
    return sair;
}
int estoque_vazio()
{
    if (total_alimento == 0) {
        printf("\nEstoque vazio, portanto n�o h� alimentos cadastrados!!\n\n");
        system("pause");
        return 1; // estoque vazio
    }
    return 0; // estoque n�o vazio
}
int tela_mensagem(char *mensagem)
{
    char ch;              //usado no controle de op��es "sim" ou "n�o"
    char texto[101] = ""; //cria uma string vazia com capacidade de at� 100 caracteres
    int erro;             //indicador de erro usado na leitura de valores do teclado
    strcat(texto, mensagem); //copia a mensagem e coloca " (s/n): " no final
    strcat(texto, " (s/n): ");
    do {
        erro = 0; //limpa / indica que ainda n�o ocorreu um erro
        printf(texto); //imprime a mensagem
        scanf(" %c", &ch); //l� a escolha do usu�rio
        fflush(stdin);
        ch = toupper(ch);
        if(!(ch == 'S' || ch == 'N')) {
            erro = 1;
            printf("ERRO: S�o aceitos apenas os valores 's' ou 'n'!\n");
        }
    } while(erro);
    if(ch == 'S')
        return 1;
    else
        return 0;
}
void cadastro_inicializar_arquivo()
{
	strcpy(caminho_arquivo_alimento, "EstoqueAlimentos.txt");
	FILE *fp = fopen(caminho_arquivo_alimento, "r");
	if(fp == NULL)
    {
		fp = fopen(caminho_arquivo_alimento, "w");
		fprintf(fp, "%d\n", total_alimento);
		fclose(fp);
	}
	else
    {
		fclose(fp);
	}
}
void cadastro_carregar_dados_arquivo()
{
	FILE *fp = fopen (caminho_arquivo_alimento, "r");
	if(fp == NULL){
		printf("Erro ao abrir o arquivo !!!");
		exit(EXIT_FAILURE);
	}
	fscanf(fp, "%d ", &total_alimento);
	for(int i = 0; i < total_alimento; i++){
		Alimento alimento;
		fscanf(fp, "%100[^\n] ", alimento.nome);
		fscanf(fp, "%d ", &alimento.quantidade);
		fscanf(fp, "%10[^\n] ", alimento.validade);
		alimento.ocupado = 1;
		vetor_alimento[i] = alimento;
	}
	fclose(fp);
}
void cadastro_salvar_dados_arquivo()
{
	FILE *fp = fopen (caminho_arquivo_alimento, "w");
	if(fp == NULL){
		printf("Erro ao abrir o arquivo !!!");
		exit(EXIT_FAILURE);
	}
	fprintf(fp, "Total de Alimentos: %d\n\n", total_alimento);
	for(int i = 0; i < NUM_MAX; i++)
    {
        if(vetor_alimento[i].ocupado == 1) {
            fprintf(fp, "Nome: %s\n", vetor_alimento[i].nome);
            fprintf(fp, "Quantidade: %d\n", vetor_alimento[i].quantidade);
            fprintf(fp, "Validade: %s\n\n", vetor_alimento[i].validade);
        }
    }
	fclose(fp);
}
