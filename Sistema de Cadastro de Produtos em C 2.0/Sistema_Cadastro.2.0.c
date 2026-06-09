#include <stdio.h>
#include <math.h>
#include <string.h>
struct Item{
	int codigo_produto;
	char nome[50];
	float preco;
	};
int main() {
	FILE *bancoDados;
	char nome_busca[50];
	int opcao;
	int encontrado;
	int proximo_codigo = 1;
	struct Item produto;
	do {
		printf("----MENU----\n");
		printf("Escolha o que deseja.\n");
		printf("1-Cadastrar item\n");
		printf("2-Procurar Item\n");
		printf("3-Sair\n");
		scanf("%i", &opcao);
		switch(opcao) {
			case 1:
				printf("Digite o nome do produto: \n");
				scanf(" %[^\n]", produto.nome);
				printf("Digite o preço: ");
				scanf("%f", &produto.preco);
				produto.codigo_produto = proximo_codigo;
				proximo_codigo++;
				bancoDados = fopen("bancoDados.txt", "a");
				fprintf(bancoDados, "%03i\n%s\n%f\n", produto.codigo_produto, produto.nome, produto.preco);
				fclose(bancoDados);
				break;
			case 2:
				encontrado = 0;
				printf("Digite o nome do produto que deseja: ");
				scanf(" %[^\n]", nome_busca);
				bancoDados = fopen("bancoDados.txt", "r");
				if (bancoDados != NULL) {
				while (fscanf(bancoDados, "%i\n%[^\n]\n%f\n", &produto.codigo_produto, produto.nome, &produto.preco) != EOF) {
					char nome_produto_minusculo[50];
					char busca_minuscula[50];
					strcpy(nome_produto_minusculo, produto.nome);
					strcpy(busca_minuscula, nome_busca);
					strlwr(nome_produto_minusculo);
					strlwr(busca_minuscula);
					if(strstr(nome_produto_minusculo, busca_minuscula) != NULL) {
						printf("Código: %03i\n", produto.codigo_produto);
						printf("Nome: %s\n", produto.nome);
        				printf("Preço: R$ %.2f\n", produto.preco);
        				printf("---------------\n");
        				encontrado = 1;
					}
				}
				} else {
					printf("Nao há produtos cadaatrados.");
				}
				if (encontrado == 0) {
    			printf("Nenhum produto encontrado com o nome '%s'.\n", nome_busca);
				}
			fclose(bancoDados);
				break;
			case 3:
				break;
		}
	} while(opcao != 3);
}