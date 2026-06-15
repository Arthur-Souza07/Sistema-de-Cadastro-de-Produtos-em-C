#include <stdio.h>
#include <math.h>
#include <string.h>
struct Item{
	int codigo_produto;
	char nome[50];
	float preco;
	};
	struct Carrinho{
		struct Item produto_comprado;
		int quantidade;
	};
int main() {
	FILE *bancoDados;
	char nome_busca[50];
	int opcao;
	int encontrado;
	int proximo_codigo = 1;
	int codigoSelecao;
	struct Item produto;
	struct Carrinho cart[50];
	int indice_livre = 0;
	float saldo = 10000;
	bancoDados = fopen("bancoDados.txt", "r");
	if (bancoDados != NULL) {
    	while (fscanf(bancoDados, "%d\n%[^\n]\n%f\n", &produto.codigo_produto, produto.nome, &produto.preco) != EOF) {
        proximo_codigo = produto.codigo_produto + 1;
    	}
    fclose(bancoDados);
	}
	do {
		printf("----MENU----\n");
		printf("Saldo: %.2f\n", saldo);
		printf("Escolha o que deseja.\n");
		printf("1-Cadastrar item\n");
		printf("2-Procurar Item\n");
		printf("3-Carrinho\n");
		printf("4-Sair\n");
		scanf("%i", &opcao);
		switch(opcao) {
			case 1:
				printf("Digite o nome do produto: \n");
				scanf(" %[^\n]", produto.nome);
				printf("Digite o preco: ");
				scanf(" %f", &produto.preco);
				produto.codigo_produto = proximo_codigo;
				proximo_codigo++;
				bancoDados = fopen("bancoDados.txt", "a");
				fprintf(bancoDados, "%03d\n%s\n%f\n", produto.codigo_produto, produto.nome, produto.preco);
				fclose(bancoDados);
				break;
			case 2:
				encontrado = 0;
				printf("Digite o nome do produto que deseja: ");
				scanf(" %[^\n]", nome_busca);
				bancoDados = fopen("bancoDados.txt", "r");
				if (bancoDados != NULL) {
				while (fscanf(bancoDados, "%d\n%[^\n]\n%f\n", &produto.codigo_produto, produto.nome, &produto.preco) != EOF) {
					char nome_produto_minusculo[50];
					char busca_minuscula[50];
					strcpy(nome_produto_minusculo, produto.nome);
					strcpy(busca_minuscula, nome_busca);
					strlwr(nome_produto_minusculo);
					strlwr(busca_minuscula);
					if(strstr(nome_produto_minusculo, busca_minuscula) != NULL) {
						printf("Codigo: %03i\n", produto.codigo_produto);
						printf("Nome: %s\n", produto.nome);
        				printf("Preco: R$ %.2f\n", produto.preco);
        				printf("---------------\n");
        				encontrado = 1;
						}
					} if(encontrado == 1) {
						fclose(bancoDados);
						bancoDados = fopen("bancoDados.txt", "r");
						printf("Digite o codigo do produto que deseja por no carrinho, se nao, digite 0\n");
        				scanf("%i", &codigoSelecao);
        				if(codigoSelecao != 0) {
							while (fscanf(bancoDados, "%d\n%[^\n]\n%f\n", &produto.codigo_produto, produto.nome, &produto.preco) != EOF) {
        						if(codigoSelecao == produto.codigo_produto) {
									cart[indice_livre].produto_comprado = produto;
									cart[indice_livre].quantidade = 1;
									indice_livre++;
									printf("Produto adicionado ao carrinho com sucesso!\n");
								break;
								} 
							}
						}
					}
				} else {
					printf("Nao há produtos cadaatrados.");
					break;
				}
				if (encontrado == 0) {
    				printf("Nenhum produto encontrado com o nome '%s'.\n", nome_busca);
				}
				fclose(bancoDados);
				break;
			case 3:
				if(indice_livre == 0) {
					printf("Nenhum produto foi adicionado.\n");
					break;
				} else {
					int resposta;
					int i;
					float total = 0;
					for(i=0; i<indice_livre; i++) {
						printf("Codigo: %03d\n", cart[i].produto_comprado.codigo_produto);
						printf("Nome: %s\n", cart[i].produto_comprado.nome);
						printf("Preco: R$ %.2f\n", cart[i].produto_comprado.preco);
						printf("-------------------\n");
						total = total+cart[i].produto_comprado.preco;
					}
					printf("Valor Total: R$ %.2f\n", total);
					printf("Deseja finalizar a compra?\n");
					printf("1-Sim\n");
					printf("2-Nao\n");
					scanf("%i", &resposta);
					if(resposta == 1) {
						if (saldo >= total) {
                            printf("Obrigado por comprar conosco!\n");
                            saldo = saldo - total;
                            indice_livre = 0;
                        } else {
                            printf("Saldo insuficiente para finalizar a compra.\n");
                        }
					}
				}
				break;
			case 4:
				break;
		}
	} while(opcao != 4);
	return 0;
}