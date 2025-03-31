#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct automovel {
  int id;
  char marca[50];
  char modelo[50];
  char cor[70];
  char tipo;
  char placa[10];
  int ano;
  float preco;
  int quilometragem;
};
typedef struct automovel c;
int main() {
  system("clear");
  setlocale(LC_ALL, "Portuguese");
  FILE *arquivo;
  char *nomearq = "automoveis.dat";
  int e, id, tam = 0, n, nregs, reg, v, ano, q;
  float p;
  c *vetor, aut;
  do {
    printf("\ndigite uma opção\n1 - adicionar um automovel\n2 - listar todos "
           "os automoveis\n3 - procurar automovel especifico\n4 - excluir um "
           "automovel\n5 - para editar um "
           "automovel\n0 - sair\n\nescreva: ");
    scanf("%i", &e);
    getchar();
    if (e == 1) {
      id = 0;
      system("clear");
      arquivo = fopen("automoveis.dat", "ab+");
      fseek(arquivo, 0, SEEK_END);
      do {
        v = 0;
        do {
          printf("digite o id do veiculo: ");
          scanf("%d", &aut.id);
          getchar();
          if (aut.id < 0) {
            printf("id negativo não pode!\n");
          }
        } while (aut.id < 0);
        id = aut.id;
        fseek(arquivo, 0, SEEK_SET);
        while (!feof(arquivo)) {
          fread(&aut, sizeof(c), 1, arquivo);
          if (feof(arquivo)) {
            break;
          }
          if (aut.id == id) {
            v++;
          }
        }
        if (v != 0) {
          printf("id ja existente\n");
        }
      } while (v >= 1);
      aut.id = id;
      printf("digite a marca: ");
      gets(aut.marca);
      printf("digite o modelo: ");
      gets(aut.modelo);
      printf("digite a cor: ");
      gets(aut.cor);
      do {
        printf("digite o tipo(somente p ou u): ");
        scanf("%c", &aut.tipo);
        getchar();
      } while (aut.tipo != 'p' && aut.tipo != 'u');
      printf("digite a placa: ");
      gets(aut.placa);
      do {
        printf("digite o ano de fabricação: ");
        scanf("%i", &ano);
        getchar();
        if (ano < 0) {
          printf("ano negativo não pode!\n");
        }
      } while (ano < 0);
      aut.ano = ano;
      do {
        printf("digite o preço: ");
        scanf("%f", &p);
        getchar();
        if (p < 0) {
          printf("preço negativo não pode!\n");
        }
      } while (p < 0);
      aut.preco = p;
      do {
        printf("digite a quilometragem: ");
        scanf("%i", &q);
        getchar();
        if (q < 0) {
          printf("quilometragem negativa não pode!\n");
        }
      } while (q < 0);
      aut.quilometragem = q;
      fwrite(&aut, sizeof(c), 1, arquivo);
      fclose(arquivo);
      system("clear");
      printf("dados preenchidos!");
    } // insere carro
    else if (e == 2) {
      system("clear");
      arquivo = fopen("automoveis.dat", "ab+");
      fseek(arquivo, 0, SEEK_SET);
      tam = 0;
      if (arquivo == NULL) {
        printf("erro ao abrir arquivo\n");
      } else if (arquivo != NULL) {
        do {
          n = fread(&aut, sizeof(c), 1, arquivo);
          if (n != 0) {
            if (feof(arquivo)) {
              break;
            }
            printf("//------------------------------//");
            printf("\nautomovel %i", tam);
            printf("\nid: %i", aut.id);
            printf("\nmarca: %s", aut.marca);
            printf("\nmodelo: %s", aut.modelo);
            printf("\ncor: %s", aut.cor);
            printf("\ntipo: %c", aut.tipo);
            printf("\nplaca: %s", aut.placa);
            printf("\nano de fabricação: %i", aut.ano);
            printf("\npreço: %.2f\n", aut.preco);
            printf("quilometragem: %i\n", aut.quilometragem);
            printf("//------------------------------//\n");
            tam++;
          }
        } while (!feof(arquivo));
      }
      fclose(arquivo);
      printf("\n");
    } // listar
    else if (e == 4) {
      system("clear");
      printf("digite o id do carro a ser removido: ");
      scanf("%i", &id);
      getchar();
      arquivo = fopen(nomearq, "rb"); // abrir o arquivo para leitura binária
      if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo,pois ele não existe\n");
      }
      n = fread(&aut, sizeof(c), 1, arquivo);
      if (n != 0) {
        fseek(arquivo, 0, SEEK_END);
        nregs = ftell(arquivo) /
                sizeof(c); // pega o tamanho do arquivo e divide pelo tamanho da
                           // struct para dar um valor aproximado ao que esta
                           // gravado no arquivo e não seu tamanho total
        fseek(arquivo, 0, SEEK_SET);
        vetor = malloc(nregs * sizeof(c));
        fread(vetor, sizeof(c), nregs, arquivo);
        fclose(arquivo);
        arquivo = fopen(nomearq, "wb"); // abrir o arquivo para escrita binária
        for (reg = 0; reg < nregs; reg++) {
          if (vetor[reg].id != id) {
            fwrite(&vetor[reg], sizeof(c), 1, arquivo);
          } else if (vetor[reg].id == id) {
            printf("carro excluido:\n");
          }
        }
        free(vetor);
        fclose(arquivo);
      } else if (n == 0)
        printf("arquivo vazio:\n");
    } // exclui
    else if (e == 5) {
      system("clear");
      arquivo = fopen(nomearq, "rb"); // abrir o arquivo para leitura binaria
      if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo, pois ele não existe\n");
      }
      n = fread(&aut, sizeof(c), 1, arquivo);
      if (n != 0) {
        e = 0;
        fseek(arquivo, 0, SEEK_END);
        nregs = ftell(arquivo) / sizeof(c);
        fseek(arquivo, 0, SEEK_SET);
        vetor = malloc(nregs * sizeof(c));
        fread(vetor, sizeof(c), nregs, arquivo);
        fclose(arquivo);
        do {
          system("clear");
          printf("selecione uma das opções abaixo para a "
                 "edição:\n\n1-marca\n2-modelo\n3-cor\n4-tipo\n5-placa\n6-ano "
                 "de fabricação\n7-preço\n8-quilometragem\n9-editar "
                 "tudo\n10-sair\nescreva:");
          scanf(" %i", &e);
          getchar();
          switch (e) {
          case 1: {
            system("clear");
            printf("digite o id para a edição: ");
            scanf("%i", &id);
            getchar();
            if (id > 0) {
              for (reg = 0; reg < nregs; reg++) {
                if (vetor[reg].id == id) {
                  printf("\ndigite a marca do carro: ");
                  gets(vetor[reg].marca);
                  system("clear");
                }
              }
            } else if (id < 0) {
              system("clear");
              printf("id negativo não pode!\n");
            }
          } break;
          case 2: {
            printf("digite o id para a edição: ");
            scanf("%i", &id);
            getchar();
            if (id > 0) {
              for (reg = 0; reg < nregs; reg++) {
                if (vetor[reg].id == id) {
                  printf("\ndigite o modelo do carro: ");
                  gets(vetor[reg].modelo);
                  system("clear");
                }
              }
            } else if (id < 0) {
              system("clear");
              printf("id negativo não pode!\n");
            }
          } break;
          case 3: {
            printf("digite o id para a edição: ");
            scanf("%i", &id);
            getchar();
            if (id > 0) {
              for (reg = 0; reg < nregs; reg++) {
                if (vetor[reg].id == id) {
                  printf("\ndigite a cor do carro: ");
                  gets(vetor[reg].cor);
                  system("clear");
                }
              }
            } else if (id < 0) {
              system("clear");
              printf("id negativo não pode!\n");
            }
          } break;
          case 4: {
            printf("digite o id para a edição: ");
            scanf("%i", &id);
            getchar();
            if (id > 0) {
              for (reg = 0; reg < nregs; reg++) {
                if (vetor[reg].id == id) {
                  do {
                    printf("\ndigite o tipo carro(somente p ou u): ");
                    scanf("%c", &vetor[reg].tipo);
                    getchar();
                  } while (vetor[reg].tipo != 'p' && vetor[reg].tipo != 'u');
                  system("clear");
                }
              }
            } else if (id < 0) {
              system("clear");
              printf("id negativo não pode!\n");
            }
          } break;
          case 5: {
            printf("digite o id para a edição: ");
            scanf("%i", &id);
            getchar();
            if (id > 0) {
              for (reg = 0; reg < nregs; reg++) {
                if (vetor[reg].id == id) {
                  printf("\ndigite a placa carro: ");
                  gets(vetor[reg].placa);
                  system("clear");
                }
              }
            } else if (id < 0) {
              system("clear");
              printf("id negativo não pode!\n");
            }
          } break;
          case 6: {
            printf("digite o id para a edição: ");
            scanf("%i", &id);
            getchar();
            if (id > 0) {
              for (reg = 0; reg < nregs; reg++) {
                if (vetor[reg].id == id) {
                  do {
                    printf("\ndigite o ano de fabricação carro: ");
                    scanf("%i", &ano);
                    getchar();
                    if (ano < 0) {
                      printf("ano negativo não pode!\n");
                    }
                  } while (ano < 0);
                  vetor[reg].ano = ano;
                  system("clear");
                }
              }
            } else if (id < 0) {
              system("clear");
              printf("id negativo não pode!\n");
            }
          } break;
          case 7: {
            printf("digite o id para a edição: ");
            scanf("%i", &id);
            getchar();
            if (id > 0) {
              for (reg = 0; reg < nregs; reg++) {
                if (vetor[reg].id == id) {
                  do {
                    printf("\ndigite o preço do carro: ");
                    scanf("%f", &p);
                    getchar();
                    if (p < 0) {
                      printf("preço negativo não pode!\n");
                    }
                  } while (p < 0);
                  vetor[reg].preco = p;
                  system("clear");
                }
              }
            } else if (id < 0) {
              system("clear");
              printf("id negativo não pode!\n");
            }
          } break;
          case 8: {
            printf("digite o id para a edição: ");
            scanf("%i", &id);
            getchar();
            if (id > 0) {
              for (reg = 0; reg < nregs; reg++) {
                if (vetor[reg].id == id) {
                  do {
                    printf("\ndigite a quilometragem do carro: ");
                    scanf("%i", &q);
                    getchar();
                    if (q < 0) {
                      printf("quilometragem negativa não pode!\n");
                    }
                  } while (q < 0);
                  system("clear");
                  vetor[reg].quilometragem = q;
                }
              }
            } else if (id < 0) {
              system("clear");
              printf("id negativo não pode!\n");
            }
          } break;
          case 9: {
            printf("digite o id para a edição: ");
            scanf("%i", &id);
            getchar();
            if (id > 0) {
              for (reg = 0; reg < nregs; reg++) {
                if (vetor[reg].id == id) {
                  printf("\ndigite a marca: ");
                  gets(vetor[reg].marca);
                  printf("\ndigite o modelo do carro: ");
                  gets(vetor[reg].modelo);
                  printf("\ndigite a cor do carro: ");
                  gets(vetor[reg].cor);
                  do {
                    printf("\ndigite o tipo carro(somente p ou u): ");
                    scanf("%c", &vetor[reg].tipo);
                    getchar();
                  } while (vetor[reg].tipo != 'p' && vetor[reg].tipo != 'u');
                  printf("\ndigite a placa carro: ");
                  gets(vetor[reg].placa);
                  do {
                    printf("\ndigite o ano de fabricação carro: ");
                    scanf("%i", &ano);
                    getchar();
                    if (ano < 0) {
                      printf("ano negativo não pode!\n");
                    }
                  } while (ano < 0);
                  vetor[reg].ano = ano;
                  do {
                    printf("\ndigite o preço do carro: ");
                    scanf("%f", &p);
                    getchar();
                    if (p < 0) {
                      printf("preço negativo não pode!\n");
                    }
                  } while (p < 0);
                  vetor[reg].preco = p;
                  do {
                    printf("\ndigite a quilometragem do carro: ");
                    scanf("%i", &q);
                    getchar();
                    if (q < 0) {
                      printf("quilometragem negativa não pode!\n");
                    }
                  } while (q < 0);
                  system("clear");
                  vetor[reg].quilometragem = q;
                }
              }
            } else if (id < 0) {
              system("clear");
              printf("id negativo não pode!\n");
            }
          } break;
          case 10: {
            system("clear");
            printf("saindo da edição:");
          } break;
          default: {
            system("clear");
            printf("opção invalida!");
          } break;
          }
          arquivo =
              fopen(nomearq, "wb"); // abrir o arquivo para escrita binaria
          if (arquivo == NULL) {
            printf("\nerro ao abrir o arquivo, pois ele não existe\n");
          }
          fwrite(vetor, sizeof(c), nregs, arquivo);
        } while (e != 10);
        free(vetor);
        fclose(arquivo);
        system("clear");
      } else if (n == 0)
        printf("arquivo vazio:\n");
    } else if (e == 0) {
      printf("finalizando...");
    }else if (e == 3) {
        printf("Digite o ID do carro: ");
        scanf("%i", &id);
        getchar(); 
        system("clear");
        arquivo = fopen(nomearq, "rb"); 
        if (arquivo == NULL) {
            printf("Erro ao abrir arquivo\n");
        } else {
            int acho = 0;
             do{
                if (aut.id == id) { 
                  printf("carro encontrado!\n");
                  printf("//------------------------------//\n");
                  printf("id: %i", aut.id);
                  printf("\nmarca: %s", aut.marca);
                  printf("\nmodelo: %s", aut.modelo);
                  printf("\ncor: %s", aut.cor);
                  printf("\ntipo: %c", aut.tipo);
                  printf("\nplaca: %s", aut.placa);
                  printf("\nano de fabricação: %i", aut.ano);
                  printf("\npreço: %.2f\n", aut.preco);
                  printf("quilometragem: %i\n", aut.quilometragem);
                  printf("//------------------------------//\n");
                  acho = 1;
                  break;
                }
            }while (fread(&aut, sizeof(c), 1, arquivo));
            if (acho != 1) {
                printf("Carro com ID %i não encontrado.\n", id);
            }
            fclose(arquivo);
        }
        printf("\n");
    }
else {
    system("clear");
    printf("\nOpção inválida\n");
  }
}
while (e != 0);
}