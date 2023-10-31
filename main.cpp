#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

#define TAM 100

struct Data
{
	int dia;
	int mes;
	int ano;
};

struct Produtos
{
	int codigoProduto;
	char descricao[TAM];
	int estoque;
	float preco = 0.0;
	Data dataDeValidade;
	int codigoFornecedor;
};

struct Fornecedores
{
	int codigoFornecedor;
	char nomeFornecedor[TAM];
	char cidade[TAM];
};

struct Clientes
{
	char cpf[12];
	char nomeCliente[TAM];
	int quantidadeDeCompras;
	float valorTotalGasto = 0.0;
};

struct Vendas
{
	int codigoVenda;
	char cpfDoCliente[12];
	Data dataDaVenda;
	float totalDaVenda;
};

struct Vendas_Produtos
{
	int codigoVenda;
	int codigoProduto;
	int quantidade;
	float valorUnitario = 0.0;
};

char pegarLetra(void)
{
	return toupper(getche());
}
//--------------------------------------------------------------------------BUSCAS-----------------------------------------------------
int buscarCliente(Clientes cliente[], char cpf[], int contadorClientes)
{ // cod==codigo que o usuario vai digitar
	int resultado;
	printf("TO AQUI");
	for (int i = 0; i < contadorClientes; i++)
	{

		printf("Comparando CPF: |%s| com |%s|\n", cliente[i].cpf, cpf);
		if (strcmp(cliente[i].cpf, cpf) == 0)
		{
			return i;
		}
	}
	return -1; // Retorna -1 se o valor não for encontrado no vetor
}

int buscaFornecedor(Fornecedores fornecedores[], int codigoFornecedor, int contadorFornecedores)
{
	for (int i = 0; i < contadorFornecedores; i++)
	{
		if (fornecedores[i].codigoFornecedor == codigoFornecedor)
		{
			return i;
		}
	}
	return -1;
}

int buscarProduto(Produtos produtos[], int codigoProduto, int contadorProdutos)
{
	for (int i = 0; i < contadorProdutos; i++)
	{
		if (produtos[i].codigoProduto == codigoProduto)
		{
			return i;
		}
	}
	return -1;
}

int buscarVenda(Vendas vendas[], int contadorVenda, int codigoVenda)
{
	for (int i = 0; i < contadorVenda; i++)
	{
		if (vendas[i].codigoVenda == codigoVenda)
		{
			return i;
		}
	}
	return -1;
}
//---------------------------------------------------------------------------------CADASTROS-----------------------------------------------------------
void cadastrarCliente(Clientes cliente[], int &contadorClientes)
{
	int codigoCliente;
	int posicaoCliente;
	char cpf[12];
	system("cls");
	printf("\nDigite o cpf do cliente: ");
	fflush(stdin);
	gets(cpf);

	if (strlen(cpf) == 11)
	{
		posicaoCliente = buscarCliente(cliente, cpf, contadorClientes);
		if (posicaoCliente == -1)
		{
			printf("\nNome do Cliente:\n");
			fflush(stdin);
			gets(cliente[contadorClientes].nomeCliente);

			strcpy(cliente[contadorClientes].cpf, cpf);
			cliente[contadorClientes].quantidadeDeCompras = 0;
			cliente[contadorClientes].valorTotalGasto = 0.0;
			contadorClientes++;
		}
		else
		{
			printf("\nJá existe um cliente com este código!\n");
		}
	}
	else
	{
		printf("\nCPF inválido!\n");
	}

	return;
}

void cadastrarProduto(Produtos produto[], Fornecedores fornecedores[], int &contadorProdutos)
{
	system("cls");
	int codigoProduto, codigoFornecedor;
	int posicaoProduto, posicaoFornecedor;

	printf("Codigo do Produto:\n");
	scanf("%d", &codigoProduto);

	posicaoProduto = buscarProduto(produto, codigoProduto, contadorProdutos);

	printf("Codigo do Fornecedor:\n");
	scanf("%d", &codigoFornecedor);

	posicaoFornecedor = buscaFornecedor(fornecedores, codigoFornecedor, TAM);

	if (posicaoProduto == -1 && posicaoFornecedor != -1)
	{
		printf("\nDescricao do produto:\n");
		fflush(stdin);
		gets(produto[contadorProdutos].descricao);

		printf("\nPreco do produto:\n");
		fflush(stdin);
		scanf("%f", &produto[contadorProdutos].preco);

		printf("\nQuantidade de estoque:\n");
		fflush(stdin);
		scanf("%d", &produto[contadorProdutos].estoque);

		printf("\nData de validade do produto [dd/mm/aaaa]:\n");

		printf("\nDia: \n");
		scanf("%d", &produto[contadorProdutos].dataDeValidade.dia);
		printf("\nMes: \n");
		scanf("%d", &produto[contadorProdutos].dataDeValidade.mes);
		printf("\nAno: \n");
		scanf("%d", &produto[contadorProdutos].dataDeValidade.ano);

		produto[contadorProdutos].codigoFornecedor = codigoFornecedor;
		produto[contadorProdutos].codigoProduto = codigoProduto;
		contadorProdutos++;
	}
	else
	{
		printf("\nJá existe um produto com este codigo ou Codigo de Fornecedor invalido\n");
	}

	return;
}

void cadastrarFornecedor(Fornecedores fornecedores[], int &contadorFornecedores)
{
	int codigoFornecedor;
	int posicaoFornecedor;

	system("cls");

	printf("CADASTRAR FORNECEDORES\n\n");
	printf("Digite o Codigo do Fornecedor:\n");
	scanf("%d", &codigoFornecedor);

	posicaoFornecedor = buscaFornecedor(fornecedores, codigoFornecedor, contadorFornecedores);

	if (posicaoFornecedor == -1)
	{
		printf("\nNome do Fornecedor:\n");
		fflush(stdin);
		gets(fornecedores[contadorFornecedores].nomeFornecedor);

		printf("\nCidade do Fornecedor:\n");
		fflush(stdin);
		gets(fornecedores[contadorFornecedores].cidade);

		fornecedores[contadorFornecedores].codigoFornecedor = codigoFornecedor;
		contadorFornecedores++;
	}
	else
	{
		printf("\nFornecedor ja cadastrado!\n");
	}
}

//---------------------------------------------------------------------------vender----------------------------------------
void venderProduto(Produtos produtos[], Vendas vendas[], Vendas_Produtos produtosVendidos[], Clientes clientes[], int &contadorVendas, int &contadorVendidos)
{
	int codigoProduto, posicaoProduto, posicaoCliente;
	int quantidadeDeProdutos;
	char cpfDoCliente[12];
	printf("\nDigite o cpf do cliente: ");
	fflush(stdout);
	gets(cpfDoCliente);

	printf("Codigo do Produto:\n");
	scanf("%d", &codigoProduto);

	posicaoProduto = buscarProduto(produtos, codigoProduto, TAM);
	posicaoCliente = buscarCliente(clientes, cpfDoCliente, TAM);
	if (posicaoProduto != -1 && posicaoCliente != -1)
	{

		printf("Digite a quantidade de produtos: ");
		scanf("%d", &quantidadeDeProdutos);

		bool temQuantidadeEmEstoque = quantidadeDeProdutos <= produtos[posicaoProduto].estoque;

		if (temQuantidadeEmEstoque)
		{
			vendas[contadorVendas].codigoVenda = contadorVendas;

			// vendas[contadorVendas].cpfDoCliente = cpfDoCliente;
			strcpy(vendas[contadorVendas].cpfDoCliente, cpfDoCliente);

			vendas[contadorVendas].totalDaVenda = ((float)quantidadeDeProdutos * produtos[posicaoProduto].preco);
			printf("\nData da venda :\n");
			printf("\nDia: \n");
			scanf("%d", &vendas[contadorVendas].dataDaVenda.dia);
			printf("\nMes: \n");
			scanf("%d", &vendas[contadorVendas].dataDaVenda.mes);
			printf("\nAno: \n");
			scanf("%d", &vendas[contadorVendas].dataDaVenda.ano);

			produtos[posicaoProduto].estoque -= quantidadeDeProdutos;

			// Adicionando a tabela do VENDAS_PRODUTOS os valores
			produtosVendidos[contadorVendidos].codigoVenda = contadorVendas;
			produtosVendidos[contadorVendidos].codigoProduto = codigoProduto;
			produtosVendidos[contadorVendidos].quantidade = quantidadeDeProdutos;
			produtosVendidos[contadorVendidos].valorUnitario = produtos[posicaoProduto].preco;

			// Adicionando os valores da compra para a tabela cliente
			clientes[posicaoCliente].quantidadeDeCompras++;
			clientes[posicaoCliente].valorTotalGasto += vendas[contadorVendas].totalDaVenda;

			contadorVendidos++;
			contadorVendas++;
		}
		else
		{
			printf("Quantidade indisponivel!");
		}
	}
	else
	{
		printf("Produto ou cliente nao existe!");
	}
}

//-----------------------------------------------------------------------LISTAS---------------------------------------------------------

void listaProduto(Produtos produtos[], int contadorProdutos)
{

	int i = 0;
	system("cls");

	if (contadorProdutos > 0)
	{
		printf("[F] LISTA DE PRODUTOS\n\n");
		printf("%-20s %-30s %-15s %-10s\n", "Codigo", "Descricao", "Estoque", "Preco");

		for (int i = 0; i < contadorProdutos; i++)
		{
			// Limita a descrição a, por exemplo, 25 caracteres e adiciona reticências se necessário
			char descricaoFormatada[31]; // Espaço para 30 caracteres + terminador nulo
			strncpy(descricaoFormatada, produtos[i].descricao, 30);
			descricaoFormatada[30] = '\0'; // Garante que a string seja terminada corretamente

			printf("%-20d %-30s %-15d %-10.2f\n", produtos[i].codigoProduto, descricaoFormatada, produtos[i].estoque, produtos[i].preco);
		}
	}
	else
		printf("Nao existem Produtos Cadastrados!\n");

	getch();
}

void listaFornecedores(Fornecedores fornecedores[], int contadorFornecedores)
{
	int i = 0;
	system("cls");
	if (contadorFornecedores > 0)
	{
		printf("[D] LISTA DE FORNECEDORES\n\n");
		for (i = 0; i < contadorFornecedores; i++)
		{
			printf("[%d] FORNECEDOR\n", i + 1);
			printf("Codigo do Fornecedor: %d\n", fornecedores[i].codigoFornecedor);
			printf("Nome: %s\n", fornecedores[i].nomeFornecedor);
			printf("Cidade de Origem: %s\n", fornecedores[i].cidade);
		}
	}
	else
		printf("Nao existem Fornecedores Cadastrados!\n");
	getch();
}

void listaClientes(Clientes clientes[], int contadorClientes)
{
	int i = 0;
	system("cls");
	printf("[C] LISTA DE CLIENTES\n\n");
	// pular espaços para printar em formato de tabela
	printf("%-11s %-30s %-25s %-25s\n", "CPF", "NOME", "QUANTIDADE DE COMPRAS", "VALOR TOTAL COMPRADO");

	for (i = 0; i < contadorClientes; i++)
	{ // pular espaços para printar em formato de tabela
		printf("%-11s %-30s %-25d  %-25f\n", clientes[i].cpf, clientes[i].nomeCliente, clientes[i].quantidadeDeCompras, clientes[i].valorTotalGasto);
	}
}
//--------------------------------------------------------------------CONSULTAS--------------------------------------------------------------------------
void consultarClientes(Clientes cliente[], int contadorClientes)
{
	char cpfDoCliente[11];
	int posicaoCliente;
	printf("\nDigite o cpf do cliente: ");
	fflush(stdout);
	gets(cpfDoCliente);

	posicaoCliente = buscarCliente(cliente, cpfDoCliente, contadorClientes);

	if (posicaoCliente != -1)
	{
		printf("%-20s %-30s %-25s %-30s\n", "CPF", "NOME", "QUANTIDADE DE COMPRAS", "VALOR TOTAL COMPRADO");
		printf("%-20s %-30s %-25d %-30f\n", cliente[posicaoCliente].cpf, cliente[posicaoCliente].nomeCliente, cliente[posicaoCliente].quantidadeDeCompras, cliente[posicaoCliente].valorTotalGasto);
	}
	else
	{
		printf("\nCliente não encontrado");
	}
}

void consultarFornecedores(Fornecedores fornecedores[], int contadorFornecedores)
{
	int codDoFornecedor, posicaoFornecedor;
	printf("\nDigite o codigo do fornecedor: ");
	scanf("%d", &codDoFornecedor);
	posicaoFornecedor = buscaFornecedor(fornecedores, codDoFornecedor, contadorFornecedores);

	if (posicaoFornecedor != -1)
	{
		printf("%-20s %-30s\n", "CODIGO DO FORNECEDOR", "NOME DO FORNECEDOR");
		printf("%-20d %-30s\n", fornecedores[posicaoFornecedor].codigoFornecedor, fornecedores[posicaoFornecedor].nomeFornecedor);
	}
	else
	{
		printf("\nFornecedor não encontrado");
	}
}

void consultarProdutos(Produtos produtos[], int contadorProdutos)
{
	int codDoProduto;
	int posicaoProduto;

	printf("\nDigite o codigo do produto: ");
	scanf("%d", &codDoProduto);
	posicaoProduto = buscarProduto(produtos, codDoProduto, contadorProdutos);

	if (posicaoProduto != -1)
	{
		printf("%-20s %-30s %-25s %-30s\n", "CODIGO DO PRODUTO", "DESCRICAO DO PRODUTO", "VALOR UNITARIO", "ESTOQUE");
		printf("%-20d %-30s %-25f %-30d\n", produtos[posicaoProduto].codigoProduto, produtos[posicaoProduto].descricao, produtos[posicaoProduto].preco, produtos[posicaoProduto].estoque);
	}
	else
	{

		printf("\nProduto não encontrado");
	}
}

void consultarVendas(Vendas vendas[], int contadorVendas)
{
	int codDaVenda;
	int posicaoVenda;
	printf("\nDigite o codigo da venda: ");
	scanf("%d", &codDaVenda);
	posicaoVenda = buscarVenda(vendas, contadorVendas, codDaVenda);
	if (posicaoVenda != -1)
	{
		printf("%-20s %-30s\n", "CODIGO DA VENDA", "VALOR DA VENDA");
		printf("%-20d %-30f\n", vendas[posicaoVenda].codigoVenda, vendas[posicaoVenda].totalDaVenda);
	}
	else
	{

		printf("\nCodigo de venda não encontrado");
	}
	getch();
}
//---------------------------------------------------------------------ALTERAÇÕES-------------------------------------------------------
void alterarCliente(Clientes cliente[], int contadorClientes)
{
	char cpfDoCliente[11];
	int posicaoCliente;
	printf("\nDigite o cpf do cliente: ");
	fflush(stdout);
	gets(cpfDoCliente);

	posicaoCliente = buscarCliente(cliente, cpfDoCliente, contadorClientes);

	if (posicaoCliente != -1)
	{
		printf("\nDigite o novo nome do cliente: ");
		scanf("%s", cliente[posicaoCliente].nomeCliente);
	}
	else
	{
		printf("\nCliente nao encontrado");
	}
}
void alterarProduto(Produtos produtos[], int contadorProdutos)
{
	system("cls");
	int codigoProduto, posicaoProduto;
	char opcao;
	float preco = 0.0;
	int quantidadeAlterada;

	printf("Codigo do Produto:\n");
	scanf("%d", &codigoProduto);

	posicaoProduto = buscarProduto(produtos, codigoProduto, contadorProdutos);

	if (posicaoProduto != -1)
	{
		printf("Escolha uma opcao:\n");
		printf("A. Alterar descricao do produto\n");
		printf("B. Alterar preco do produto\n");
		printf("C. Alterar quantidade em estoque do produto\n");
		opcao = pegarLetra();

		switch (opcao)
		{
		case 'A':
			printf("Digite a descricao do produto: ");
			fflush(stdin);
			gets(produtos[posicaoProduto].descricao);
			printf("Produto alterado com sucesso!");
			break;

		case 'B':
			printf("Digite o preco do produto: ");
			scanf("%f", &preco);

			produtos[posicaoProduto].preco = preco;
			printf("Produto alterado com sucesso!");
			break;

		case 'C':
		{

			printf("Deseja aumentar(A) ou diminuir(D) a quantidade em estoque ");
			opcao = pegarLetra();

			printf("Quantidade a ser alterada do estoque\n");
			scanf("%d", &quantidadeAlterada);

			if (opcao == 'A')
			{
				produtos[posicaoProduto].estoque += quantidadeAlterada;
			}
			else if (opcao == 'D')
			{
				if (produtos[posicaoProduto].estoque - quantidadeAlterada > 0)
				{
					produtos[posicaoProduto].estoque -= quantidadeAlterada;
				}
				else
				{
					printf("\nQuantidade de estoque insuficiente\n");
					return;
				}
			}
			else
			{
				printf("\nOpcao invalida\n");
				return;
			}

			printf("\nEstoque alterado com sucesso\n");

			break;
		}

		default:
			printf("Opção inválida.\n");
			break;
		}
	}
	getch();
}
void alterarFornecedor(Fornecedores fornecedor[], int contadorFornecedor)
{
	int codigoFornecedor, posicaoFornecedor;
	char opcao;

	printf("\nDigite o CODIGO do fornecedor: ");
	scanf("%d", &codigoFornecedor);

	posicaoFornecedor = buscaFornecedor(fornecedor, codigoFornecedor, contadorFornecedor);

	if (posicaoFornecedor != -1)
	{
		printf("Escolha uma opção:\n");
		printf("A. Alterar nome do fornecedor\n");
		printf("B. Alterar cidade do fornecedor\n");
		opcao = toupper(getche());

		switch (opcao)
		{
		case 'A':
			printf("Digite o nome do fornecedor: ");
			fflush(stdin);
			gets(fornecedor[posicaoFornecedor].nomeFornecedor);
			printf("\n Nome do fornecedor alterado com sucesso");
			break;
		case 'B':
			printf("Digite a cidade do fornecedor: ");
			fflush(stdin);
			gets(fornecedor[posicaoFornecedor].cidade);
			printf("\n Nome da cidade alterada com sucesso");
			break;
		default:
			printf("opcao invalida!");
			break;
		}
	}
}

//-----------------------------------------------------------------------EXCLUIR--------------------------------------------------------

void excluirCliente(Clientes cliente[], Vendas vendas[], Vendas_Produtos vendidos[], int &contadorClientes, int &contadorVendas, int &contadorVendidos)
{
	char cpf[12];
	printf("\nDigite o cpf do cliente: ");
	fflush(stdin);
	gets(cpf);
	int posicaoCliente;

	posicaoCliente = buscarCliente(cliente, cpf, contadorClientes);

	if (posicaoCliente != -1)
	{

		for (int i = posicaoCliente; i < contadorClientes - 1; i++)
		{
			strcpy(cliente[i].cpf, cliente[i + 1].cpf);
			strcpy(cliente[i].nomeCliente, cliente[i + 1].nomeCliente);
			cliente[i].quantidadeDeCompras = cliente[i + 1].quantidadeDeCompras;
			cliente[i].valorTotalGasto = cliente[i + 1].valorTotalGasto;
		}

		// Decrementar o contador de clientes
		contadorClientes--;

		for (int i = 0; i < contadorVendas; i++)
		{
			if (strcmp(vendas[i].cpfDoCliente, cpf) == 0)
			{
				// Remove a venda da tabela de vendas
				for (int j = i; j < contadorVendas - 1; j++)
				{
					vendas[j] = vendas[j + 1];
				}
				contadorVendas--;

				// Remove os produtos vendidos associados a essa venda
				for (int j = 0; j < contadorVendidos; j++)
				{
					if (vendidos[j].codigoVenda == vendas[i].codigoVenda)
					{
						for (int k = j; k < contadorVendidos - 1; k++)
						{
							vendidos[k] = vendidos[k + 1];
						}
						contadorVendidos--;
						j--; // Ajusta o índice após a remoção
					}
				}
				i--; // Ajusta o índice após a remoção
			}
		}
	}
	else
	{
		printf("\nCliente nao encontrado");
	}
}
void excluirFornecedor(Fornecedores fornecedores[], Produtos produtos[], int &contadorFornecedores, int &contadorProdutos)
{
	int codigoFornecedor;

	printf("\nDigite o codigo do fornecedor que deseja excluir: ");
	scanf("%d", &codigoFornecedor);

	int posicaoFornecedor = buscaFornecedor(fornecedores, codigoFornecedor, contadorFornecedores);

	if (posicaoFornecedor != -1)
	{
		// Verificar se existem produtos associados a esse fornecedor
		bool fornecedorTemProdutos = false;
		for (int i = 0; i < contadorProdutos; i++)
		{
			if (produtos[i].codigoFornecedor == codigoFornecedor)
			{
				fornecedorTemProdutos = true;
				break;
			}
		}

		if (fornecedorTemProdutos)
		{
			printf("Nao e possivel excluir o fornecedor, pois existem produtos associados a ele.\n");
		}
		else
		{
			// Remover o fornecedor da lista
			for (int i = posicaoFornecedor; i < contadorFornecedores - 1; i++)
			{
				fornecedores[i] = fornecedores[i + 1];
			}
			(contadorFornecedores)--;
			printf("Fornecedor excluido com sucesso!\n");
		}
	}
	else
	{
		printf("Fornecedor não encontrado.\n");
	}
}
void excluirProduto(Produtos produtos[], int &contadorProdutos)
{
	int codigoProduto;
	printf("Digite o código do produto a ser removido: ");
	scanf("%d", &codigoProduto);

	int posicaoProduto = buscarProduto(produtos, codigoProduto, contadorProdutos);

	if (posicaoProduto != -1)
	{
		for (int i = posicaoProduto; i < contadorProdutos - 1; i++)
		{
			produtos[i] = produtos[i + 1];
		}

		contadorProdutos--;

		printf("Produto removido com sucesso!\n");
	}
	else
	{
		printf("Produto não encontrado. Remoção cancelada.\n");
	}
}

char menu(void)
{
	system("cls");
	//------------CADASTROS----------------
	printf("[A]:Cadastro de Clientes\n");
	printf("[B]:Cadastro de Produtos\n");
	printf("[C]:Cadastro de Fornecedores\n\n");
	//----------LISTAS-----------------
	printf("[D]:Lista de Clientes\n");
	printf("[E]:Lista de Produtos\n");
	printf("[F]:Lista de Fornecedores\n\n");
	//----------CONSULTAS---------------
	printf("[G]:Consultar Clientes\n");
	printf("[H]:Consultar Produtos\n");
	printf("[I]:Consultar Fornecedores\n");
	printf("[J]:Consultar vendas\n\n");
	//-----------ALTERAR-------------
	printf("[K]:Alterar Clientes\n");
	printf("[L]:Alterar Produtos\n");
	printf("[M]:Alterar Fornecedores\n\n");
	//------------EXCLUIR------------
	printf("[N]:Excluir Cliente\n");
	printf("[O]:Excluir Produtos\n");
	printf("[P]:Excluir Fornecedor\n");
	//----------SALLES---------------
	printf("[Q]:Realizar vendas\n");
	printf("[ESC]: P/Sair\n\n");

	printf("\nSelecione uma Opcao:\n");

	return toupper(getche());
}

void executar()
{
	Clientes clientes[TAM];
	Fornecedores fornecedores[TAM];
	Produtos produtos[TAM];
	Vendas vendas[TAM];
	Vendas_Produtos produtosVendidos[TAM];

	int contadorClientes = 0, contadorFornecedores = 0;
	int contadorProdutos = 0, contadorVendas = 0;
	int contadorProdutosVendidos = 0;

	char opcao;

	do
	{
		opcao = menu();
		switch (opcao)
		{

		case 'A':
			cadastrarCliente(clientes, contadorClientes);
			getch();
			break;

		case 'B':

			cadastrarProduto(produtos, fornecedores, contadorProdutos);
			getch();
			break;

		case 'C':
			cadastrarFornecedor(fornecedores, contadorFornecedores);
			getch();
			break;

		case 'D':
			listaClientes(clientes, contadorClientes);
			getch();
			break;

		case 'E':
			listaProduto(produtos, contadorProdutos);
			getch();
			break;

		case 'F':
			listaFornecedores(fornecedores, contadorFornecedores);
			break;

		case 'G':
			consultarClientes(clientes, contadorClientes);
			getch();
			break;

		case 'H':
			consultarProdutos(produtos, contadorProdutos);
			getch();
			break;

		case 'I':
			consultarFornecedores(fornecedores, contadorFornecedores);
			getch();
			break;

		case 'J':
			consultarVendas(vendas, contadorVendas);
			break;

		case 'K':
			alterarCliente(clientes, contadorClientes);
			break;

		case 'L':
			alterarProduto(produtos, contadorProdutos);
			break;

		case 'M':
			alterarFornecedor(fornecedores, contadorFornecedores);
			getch();
			break;

		case 'N':
			excluirCliente(clientes, vendas, produtosVendidos, contadorClientes, contadorVendas, contadorProdutosVendidos);
			getch();
			break;

		case 'O':
			excluirProduto(produtos, contadorProdutos);
			break;

		case 'P':
			excluirFornecedor(fornecedores, produtos, contadorFornecedores, contadorProdutos);
			getch();
			break;

		case 'Q':
			venderProduto(produtos, vendas, produtosVendidos, clientes, contadorVendas, contadorProdutosVendidos);
			getch();
			break;
		}
	} while (opcao != 27);
}

int main()
{
	executar();
	return 0;
}
