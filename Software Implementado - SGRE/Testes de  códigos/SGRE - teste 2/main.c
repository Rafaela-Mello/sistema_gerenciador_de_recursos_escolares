#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>

#define NUM_MAX 100 // n�mero m�ximo de alimentos cadastrados permitidos

typedef struct Alimento {
    int ocupado;
	char nome[101]; //o nome tem 100 caracteres, e tem o espaco do '\0'
	int quantidade;
	char validade[11]; //a validade tem 10 caracteres, e tem o espaco do '\0'
	int dia, mes, ano;
} Alimento;

        // Vari�veis Globais
Alimento vetor_alimento[NUM_MAX]; //cria um vetor com capacidade de armazenar os dados de 100 alimentos
int total_alimento = 0; //guarda o total de alimentos cadastradas
char caminho_arquivo_alimento[101]; //guarda o caminho do arquivo com os dados dos alimentos


// Prot�tipo das fun��es respons�veis por gerenciar o cadastro de alimentos

void cadastro_inicializar(); //inicializa o vetor e o contador de cadastro //cria o arquivo de texto onde os dados do cadastro ser�o salvos

void cadastro_inicializar_arquivo(); //cria o arquivo de dados (caso ele n�o exista) que ir� guardar os dados do cadastro

void cadastro_carregar_dados_arquivo(); //carrega os dados de um arquivo de texto para o vetor de estruturas Alimento

void cadastro_salvar_dados_arquivo(); //salva os dados do vetor de estrutura Alimento em um arquivo de texto


        // Prot�tipo da Fun��o com a Tela
int tela_menu(); //mostra a tela com o menu de op��es - retorna a op��o (um valor de 1 a 5) escolhida - retorna -1 caso o usu�rio escolha uma op��o inv�lida


        // Prot�tipo das Fun��es de Mensagem e Entrada/Leitura de Dados do Teclado
int tela_mensagem(char *mensagem); //mostra uma mensagem com a op�ao de escolher "sim" ou "n�o" - retorna 1 caso seja escolhido o "sim" e 0 caso seja escolhido o "n�o"




//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




int main()
{

    //muda a localiza��o para Portugu�s do Brasil
    setlocale(LC_ALL, "portuguese");
    system("chcp 1252 > null");

    //variaveis utilizadas para controlar o loop de execu��o do programa
    int sair = 0;   //controla quando o program deve ser encerrao
    int opcao;      //guarda a op��o escolhida pelo usu�rio no menu de op��o
    int erro;       //indicador de erro usado na leitura de valores do teclado
    int continuar;  //controla se o usu�rio quer continuar: cadastrar, pesquisar, ou remover um alimento;

    cadastro_inicializar(); //faz as inicializa��es do cadastro de alimentos

    cadastro_inicializar_arquivo(); //cria o arquivo de dados (caso ele n�o exista) que ir� guardar os dados do cadastro

    cadastro_carregar_dados_arquivo(); //carrega os dados de um arquivo de texto para o vetor de estruturas Alimento

    //vari�veis utilizadas para fazer a leitura dos dados do alimento do teclado!
	char nome[101];
	int quantidade;
	int dia, mes, ano;
	char validade[11];
    int idxPesquisa = -1; //guarda o indice de: alimento pesquisado - alimento que ser� removida

    //loop de execu��o do programa
    do {
        //TELA COM O MENU DE OP��ES
        opcao = tela_menu();

        //verifica qual op��o foi escolhida
        switch(opcao)
        {

            //TELA DE CADASTRO
            case 1:
                do {
                    system("cls");
                    printf("1 - Cadastrar \n");

                    //verifica se o cadastro chegou na capacidade m�xima
                    if(total_alimento >= NUM_MAX)
                    {
                        //indica que o cadastro j� est� cheio
                        printf("\nERRO: O cadastro j� atingiu sua capacidade m�xima de 100 alimentos!\n");
                        system("pause");
                        break; //encerra o la�o do-while
                    }

                    //FAZ A ENTRADA DO NOME
                    do
                    {
                        erro = 0; //marca que ainda n�o ocorreu um erro

                        printf("\nDigite o nome: ");
                        scanf(" %100[^\n]", nome);

                        fflush(stdin); // limpa o buffer do teclado ap�s a leitura

                        //o nome pode ter no m�ximo 100 caracteres e no m�nimo 2 caracteres
                        if(strlen(nome) > 100)
                        {
                            erro = 1; //marca a ocorr�ncia de um erro
                            printf("ERRO: O nome do alimento deve possuir no m�ximo 100 (cem) carracteres!\n");
                        }
                        if(strlen(nome) < 2) {
                            erro = 1; //marca a ocorr�ncia de um erro
                            printf("ERRO: O nome do alimento deve possuir pelo menos 2 (dois) carracteres!\n");
                        }
                    } while(erro == 1); //FIM DA ENTRADA DO NOME

                    //FAZ A ENTRADA DA QUANTIDADE
                    do
                    {
                        printf("\nDigite a quantidade: ");
                        erro = scanf("%d", &quantidade);

                        fflush(stdin); //limpa o buffer do teclado para o caso do scanf falhar, ou o usu�rio digitar alguma coisa ap�s o n�mero inteiro

                        //verifica se houve um erro de leitua do scanf
                        if(erro != 1)
                        {
                            printf("ERRO: Digite um valor inteiro v�lido!\n");
                        }
                    } while(erro != 1); //FIM DA ENTRADA DA QUANTIDADE


                    //FAZ A ENTRADA DA VALIDADE
                    do
                    {
                        erro = 0; //marca que ainda n�o ocorreu um erro

                        printf("\nDigite a validade (xx/xx/xxxx): ");
                        scanf(" %10[^\n]", validade);

                        fflush(stdin); //limpa o buffer do teclado para o caso do scanf falhar, ou o usu�rio digitar alguma coisa ap�s o n�mero inteiro

                        //a validade pode ter no m�ximo 10 caracteres e deve conter esse formato: xx/xx/xxxx
                        if((strlen(validade) != 10) || (validade[2] != '/' || validade[5] != '/'))
                        {
                            erro = 1; //marca a ocorr�ncia de um erro
                            printf("ERRO 1: A validade deve possuir 10 caracteres e no formato indicado!\n");
                        }

                        //verifica se a data � v�lida
                        if (sscanf(validade, "%d/%d/%d", &dia, &mes, &ano) != 3) {
                            erro = 1;
                            printf("ERRO 2: Deve ser informada no formato xx/xx/xxxx!\n");
                        }

                        if ((dia < 1 || dia > 31) || (mes < 1 || mes > 12) || (ano < 2020 || ano > 2100)) {
                            erro = 1;
                            printf("ERRO 3: Validade inv�lida!\n");
                        }
                    }while(erro == 1); //FIM DA ENTRADA DA VALIDADE

                    idxPesquisa = -1;  //indica que por enquanto n�o encontrou ninguem com o mesmo nome

                    //verifica se j� existe um alimento cadastrada com o mesmo nome
                    for(int i = 0; i < NUM_MAX; i++)
                    {
                        //compara as strings, se encontrar com o mesmo nome
                        if(strcmp(vetor_alimento[i].nome, nome) == 0)
                        {
                            idxPesquisa = i; //indice do alimento com o mesmo nome no vetor de cadastro
                            break;
                        }
                    }

                    //caso o idxPesquisa seja diferente de -1, quer dizer que encontrou um alimento com o nome igual no cadastro.
                    if(idxPesquisa != -1)
                    {
                        //indica que j� existe um alimento com o mesmo nome no cadastro
                        printf("\nErro: N�o foi poss�vel inserir os dados pois j� existe um alimento com o mesmo nome no cadastro:\v");

                        printf("\nAlimento com o mesmo nome: \n");
                        printf("Nome:         %s\n", vetor_alimento[idxPesquisa].nome);
                        printf("Quantidade:   %d\n", vetor_alimento[idxPesquisa].quantidade);
                        printf("Validade:     %s\n\n",vetor_alimento[idxPesquisa].validade);
                        system("pause");
                    }

                    //n�o encontrou um alimento j� cadastrada com o mesmo nome!
                    else {
                        //procura um elemento livre (n�o ocupado) no vetor de alimentos!
                        for(int i = 0; i < NUM_MAX; i++)
                        {
                            //encontrou uma posi��o livre
                            if(vetor_alimento[i].ocupado == 0)
                            {
                                vetor_alimento[i].ocupado = 1; //marca a posi��o do vetor como ocupada

                                //insere os dados do alimento no vetor !!!
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

                    //mostra uma mensagem na tela perguntando se o usu�rio deseja cadastrar outro alimento // essa fun��o retorna 1 (escoheu sim) ou 0 (escolheu n�o)
                    continuar = tela_mensagem("\nGostaria de cadastrar outro alimento? ");

                } while(continuar == 1);
            break;


            //TELA DE PESQUISA
            case 2:

                // verifica se h� algum alimento cadastrado
                if (total_alimento == 0) {
                    printf("\nN�o h� alimentos cadastrados para pesquisar!\n\n");
                    system("pause");
                    break;
                }

                do{
                    system("cls");
                    printf("2 - Pesquisar \n");

                    //ENTRADA DO NOME DO ALIMENTO
                    do {
                        erro = 0; //marca que por enquanto n�o houve erro

                        printf("\nDigite o nome: "); //ler no m�ximo 100 caracteres
                        scanf(" %100[^\n]", nome);

                        fflush(stdin); // limpa lixo no buffer do teclado
                    } while(erro == 1); // FIM ENTRADA DO NOME

                    //indica que por enquanto n�o encontrou nenhum alimento com o nome pesquisado
                    idxPesquisa = -1;

                    //pesquisa um alimento no cadastro a partir do nome, percorre todo o vetor com o cadastro dos alimentos
                    for(int i = 0; i < NUM_MAX; i++){
                        //verifica se est� ocupado com os dados de um alimento
                        if(vetor_alimento[i].ocupado == 1) {
                            //verifica se o nome do alimento � igual ao nome pesquisado
                            if(strcmp(vetor_alimento[i].nome, nome) == 0){
                                //guarda o indice do alimento que tem o nome igual ao nome pesquisado
                                idxPesquisa = i;
                                break; //encontrou o alimento, encerra o la�o de busca
                            }
                        }
                    }

                    //caso o indice seja diferente de -1, quer dizer que encontrou um alimento com o nome igual ao nome pesquisado.
                    if(idxPesquisa != -1) {
                        printf("\nAlimento Encontrado: \n");
                        printf("Nome:         %s\n", vetor_alimento[idxPesquisa].nome);
                        printf("Quantidade:   %d\n", vetor_alimento[idxPesquisa].quantidade);
                        printf("Validade:     %s\n\n", vetor_alimento[idxPesquisa].validade);
                        system("pause");
                    }
                    //n�o encontrou um alimento
                    else {
                        printf("\nN�o foi encontrado um alimento com o nome informado!\n\n");
                        system("pause");
                    }

                    //mostra uma mensagem na tela perguntando se o usu�rio deseja cadastrar outro alimento // essa fun��o retorna 1 (escoheu sim) ou 0 (escolheu n�o)
                    continuar = tela_mensagem("\nGostaria de pesquisar outro alimento? ");

                } while(continuar == 1);
            break;


            // TELA DE REMO��O
            case 3:
                // verifica se h� algum alimento cadastrado
                if (total_alimento == 0) {
                    printf("\nN�o h� alimentos cadastrados para remover!\n\n");
                    system("pause");
                    break;
                }

                do {
                    system("cls");
                    printf("3 - Remover \n\n");

                    //ENTRADA DO NOME DO ALIMENTO
                    do {
                        erro = 0; //marca que por enquanto n�o houve erro

                        printf("\nDigite o nome: ");
                        scanf(" %100[^\n]", nome);

                        fflush(stdin); // limpa lixo no buffer do teclado!!!
                    } while(erro == 1); // FIM ENTRADA DO NOME DO ALIMENTO

                    idxPesquisa = -1; //indica que por enquanto n�o encontrou ninguem com o nome pesquisado

                    //percorre todo o vetor com os alimentos cadastradas
                    for(int i = 0; i < NUM_MAX; i++) {
                        //verifica apenas elementos do vetor de alimentos que realmente est�o ocupados
                        if(vetor_alimento[i].ocupado == 1) {
                            //verifica se o nome do alimento � igual ao nome passado como par�mentro
                            if(strcmp(vetor_alimento[i].nome, nome) == 0){
                                //encontrou o alimento, ent�o tem que decrementar o contador de alimentos
                                total_alimento = total_alimento - 1;
                                //marca o espa�o/elemento do vetor como livre, ou seja pode ser reutilizado para guardar os dados de outro alimento!
                                vetor_alimento[i].ocupado = 0;
                                //guarda o indice do alimento que tem o nome igual ao nome pesquisado
                                idxPesquisa = i;
                                break;
                            }
                        }
                    }

                    //caso o indice seja diferente de -1, quer dizer que encontrou um alimento com o nome igual ao nome pesquisado.
                    if(idxPesquisa != -1) {
                        printf("\nAlimento removido com sucesso!\n");
                    }
                    else {
                        printf("\nN�o foi poss�vel remover o alimento do cadastro!\n");
                    }
                    system("pause");

            //mostra uma mensagem na tela perguntando se o usu�rio deseja cadastrar outro alimento // essa fun��o retorna 1 (escoheu sim) ou 0 (escolheu n�o)
            continuar = tela_mensagem("\nGostaria de remover outro alimento? ");
                } while(continuar);
            break;


            // TELA DE RELAT�RIO
            case 4:
                // verifica se h� algum alimento cadastrado
                if (total_alimento == 0) {
                    printf("\nN�o h� alimentos cadastrados!!\n\n");
                    system("pause");
                    break;
                }

                system("cls");
                printf("4 - Relat�rio \n\n");
                printf("Total de Alimentos Cadastrados: %d\n\n", total_alimento);

                //percorre todo o vetor com o cadastro dos alimentos
                for(int i = 0; i < NUM_MAX; i++){
                    if(vetor_alimento[i].ocupado == 1) {
                        printf("Nome:         %s\n", vetor_alimento[i].nome);
                        printf("Quantidade:   %d\n", vetor_alimento[i].quantidade);
                        printf("Validade:     %s\n\n", vetor_alimento[i].validade);
                    }
                }
                system("pause");
            break;


            // TELA ENCERRAR APLICA��O
            case 5:
                system("cls");
                printf("5 - Sair \n\n");

            //mostra uma mensagem na tela perguntando se o usu�rio deseja cadastrar outro alimento // essa fun��o retorna 1 (escoheu sim) ou 0 (escolheu n�o)
            sair = tela_mensagem("\nDeseja mesmo sair? ");
            break;


            // TRATAMENTO DE OP��O INV�LIDA
            default:
                printf("\nOp��o Inv�lida !!! \n"); //mostra uma mensagem informando que a op��o escolhida do "Menu de Op��es" � inv�lida!
                system("pause");
        }
    } while (sair == 0);

    cadastro_salvar_dados_arquivo(); //salva os dados do vetor de estrutura Alimento em um arquivo de texto

    system("cls");
    printf("\nFim da execu��o do programa!\n");

    return 0;
}




//---------------------------------------------------------------------------------------------------------------------------------------------

                            // FUN��ES

//---------------------------------------------------------------------------------------------------------------------------------------------



    // Iniciliza o vetor de cadastro
void cadastro_inicializar()
{
    total_alimento = 0; //zera o contador de alimentos cadastrados (vari�vel global) - guarda o total de alimentos cadastrados

    //inicializa o vetor de alimentos - livres / desocupados
    for(int i = 0; i < NUM_MAX; i++)
    {
        //marca a posi��o como livre/desocupada, ou seja, pode receber os dados de um alimento!
        vetor_alimento[i].ocupado = 0;
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------

    // Mostra a tela com o menu de op��es // retorna a op��o (um valor de 1 a 5) escolhida // retorna -1 caso o usu�rio escolha uma op��o inv�lida
int tela_menu()
{
    int opcao; //guarda a op��o escolhida pelo usu�rio

    //mostra a Tela com o "Menu de Op��es"
    system("cls");
    printf("Menu de Op��es do Estoque de Alimentos \n");
    printf("1 - Cadastrar \n");
    printf("2 - Pesquisar \n");
    printf("3 - Remover \n");
    printf("4 - Relat�rio do estoque \n");
    printf("5 - Sair \n\n");

    printf("Escolha uma op��o: "); //faz a leitura da op��o escolhida
    int erro = scanf("%d", &opcao);

    //verifica se houve uma falha na leitura do scanf
    if(erro != 1) {
        fflush(stdin); //limpa o buffer do tecaldo (windows)
        opcao = -1; //como teve uma falha na leitura, marca uma op��o inv�lida
    }
    return opcao; //retorna a op��o escolhida
}

//---------------------------------------------------------------------------------------------------------------------------------------------

    // Mostra uma mensagem com a op�ao de escolher "sim" ou "n�o" // retorna 1 caso seja escolhido o "sim" e 0 caso seja escolhido o "n�o"
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

        fflush(stdin); //limpa o buffer do tecaldo (windows), se o usu�rio digitar mais de um caracteres o buffer ficar� com lixo (por isso eu limpo)

        ch = toupper(ch); //converte o caractere lido para maiusculo

        if(!(ch == 'S' || ch == 'N')) { //verifica se o usu�rio selecionou um caractere v�lido
            erro = 1;
            printf("ERRO: S�o aceitos apenas os valores 's' ou 'n'!\n");
        }
    } while(erro); //executa o la�o enquanto o usu�rio n�o digitar 's' ou 'n'

    //retorna 1 se escolheu 's' e 1 se escolheu 'n'
    if(ch == 'S')
        return 1;
    else
        return 0;
}




//---------------------------------------------------------------------------------------------------------------------------------------------

                            // FUN��ES DE ARQUIVO

//---------------------------------------------------------------------------------------------------------------------------------------------




    // Cria o arquivo de dados (caso ele n�o exista) que ir� guardar os dados do cadastro
void cadastro_inicializar_arquivo()
{
	strcpy(caminho_arquivo_alimento, "EstoqueAlimentos.txt"); //caminho e nome do arquivo usado para salvar os dados do cadastro de alimentos - � uma vari�vel global

	FILE *fp = fopen(caminho_arquivo_alimento, "r"); //tenta abrir o arquivo para leitura, se conseguir quer dizer que ele existe

	if(fp == NULL) //indica que n�o conseguiu abrir o arquivo (ex: ele n�o existe)
    {
		fp = fopen(caminho_arquivo_alimento, "w"); //cria o arquivo pela primeira vez

		fprintf(fp, "%d\n", total_alimento); //a primeira linha do arquivo sempre ir� ter o total de alimentos salvos;

		fclose(fp); //fecha o arquivo
	}
	else //conseguiu abrir o arquivo, ent�o ele existe
    {
		fclose(fp); //fecha o arquivo
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------

    // Carrega os dados de um arquivo de texto para o vetor de estruturas Alimento
void cadastro_carregar_dados_arquivo()
{
	FILE *fp = fopen (caminho_arquivo_alimento, "r"); //abre o arquivo contendo os dados do cadastro - o arquivo deve existir

	if(fp == NULL){ //caso o arquivo n�o exista ou n�o seja entrado
		printf("Erro ao abrir o arquivo !!!");
		exit(EXIT_FAILURE); //encerra o programa sinalizando uma falha
	}

	//l� a primeira linha do arquivo que sempre ir� conter o total de alimentos cadastrados
    //o espa�o em branco no final do especificador de formato � para o scanf ler e descartar os caracteres '\n'
	fscanf(fp, "%d ", &total_alimento);

    //for utilizado para ler todos os cadastro de alimento do arquivo
	for(int i = 0; i < total_alimento; i++){

		Alimento alimento; //variavel usada para guardar os dados de um alimento

		//l� os dados do alimento no arquivo e salva na vari�vel alimento
        //o espa�o em branco no final do especificador de formato � para o scanf ler e descartar os caracteres '\n'
		fscanf(fp, "%100[^\n] ", alimento.nome);
		fscanf(fp, "%d ", &alimento.quantidade);
		fscanf(fp, "%10[^\n] ", alimento.validade);

		alimento.ocupado = 1; //marca a struct como ocupada (cont�m dados)

		vetor_alimento[i] = alimento; //insere a vari�vel alimento no vetor de alimento
	}
	fclose(fp); //fecha o arquivo
}

//---------------------------------------------------------------------------------------------------------------------------------------------

//salva os dados do vetor de estrutura Alimento em um arquivo de texto
void cadastro_salvar_dados_arquivo()
{
    //abre o arquivo contendo os dados do cadastro - o arquivo deve existir - abre o arquivo para escrita, apaga todo o conte�do dele
	FILE *fp = fopen (caminho_arquivo_alimento, "w");

	//caso o arquivo n�o exista ou n�o seja entrado
	if(fp == NULL){
		printf("Erro ao abrir o arquivo !!!");
		exit(EXIT_FAILURE); //encerra o programa sinalizando uma falha
	}

	fprintf(fp, "Total de Alimentos: %d\n\n", total_alimento); //grava, na primeira linha do arquivo, sempre o total de alimentos cadastrados

	//percorre todo o vetor de alimentos, salvando apenas os elementos do vetor que cont�m dados (est�o ocupados)
	for(int i = 0; i < NUM_MAX; i++)
    {
        //se o elemento do vetor conter os dados de um alimento
        if(vetor_alimento[i].ocupado == 1) {
            //salva os dados do alimento no arquivo
            fprintf(fp, "Nome: %s\n", vetor_alimento[i].nome);
            fprintf(fp, "Quantidade: %d\n", vetor_alimento[i].quantidade);
            fprintf(fp, "Validade: %s\n\n", vetor_alimento[i].validade);
        }
    }
	fclose(fp); //fecha o arquivo - nesse ponto os dados s�o salvos de fato no arquivo
}

//---------------------------------------------------------------------------------------------------------------------------------------------
