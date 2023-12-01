#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> 
#include <time.h>
#include <ctype.h>

typedef struct {
    int matricula;
    char nome[1000];
    int esta_presente;
} Estudante;

void listarAlunos(Estudante estudantes[], int tamanho);

int acharEstudante(Estudante estudantes[], int tamanho, int matricula) {
    for (int i = 0; i < tamanho; i++) {
        if (estudantes[i].matricula == matricula) {
            return i;  // Retorna o índice se a matrícula já existir
        }
    }
    return -1;  // Retorna -1 se a matrícula não existir
}

int adcEstudante(Estudante estudantes[], int *tamanho) {
    if (*tamanho >= 1000) {
        printf("ERRO: O VETOR DE ALUNOS ESTA CHEIO.\n");
        return -1;
    }

    int matricula;
    char nome[1000];

    do {
    // Solicitar a matrícula
    printf("\n");
    printf("              -> DIGITE A MATRICULA DO ALUNO: ");
    if (scanf("%d", &matricula) != 1 || getchar() != '\n') {
        printf("ERRO: A MATRICULA DEVE CONTER APENAS NUMEROS.\n");
        while (getchar() != '\n');  // Limpar o buffer de entrada
    } else {
        // Verificar se a matrícula já existe usando a função acharEstudante
        int index = acharEstudante(estudantes, *tamanho, matricula);
        if (index != -1) {
            printf("MATRICULA EXISTENTE\n");
        } else {
            break;  // Saia do loop se a matrícula for válida
        }
    }
    } while (1);  // Loop até que uma matrícula válida seja inserida

    do {
        // Solicitar o nome do aluno
        printf("              -> DIGITE O NOME DO ALUNO: ");
        fflush(stdin);
        if (fgets(nome, sizeof(nome), stdin) == NULL) {
            return -1;  // Erro ao ler nome
        }

        // Remover o caractere de nova linha, se presente
        size_t lengthNome = strlen(nome);
        if (lengthNome > 0 && nome[lengthNome - 1] == '\n') {
            nome[lengthNome - 1] = '\0';
        }

        // Verificar se o nome contém apenas letras
        int nomeValido = 1;
        for (size_t i = 0; i < strlen(nome); i++) {
            if (!isalpha(nome[i]) && nome[i] != ' ') {
                printf("ERRO: O NOME DEVE CONTER APENAS LETRAS.\n");
                nomeValido = 0;
                break;
            }
        }

        if (nomeValido) {
            break;  // Saia do loop se o nome for válido
        }

    } while (1);  // Loop até que um nome válido seja inserido

    // Se chegou aqui, matrícula e nome são válidos
    strcpy(estudantes[*tamanho].nome, nome);
    estudantes[*tamanho].matricula = matricula;
    estudantes[*tamanho].esta_presente = 0;
    (*tamanho)++;
    return 0;
}

int editarEstudante(Estudante estudantes[], int *tamanho, int matricula) {
    if (*tamanho >= 1) {
        int index = acharEstudante(estudantes, *tamanho, matricula);

        if (index != -1) {
            printf("ALUNO ENCONTRADO\n");
            printf("              -> DIGITE O NOVO NOME DO ALUNO: ");
            
            // Limpar o buffer de entrada
            while (getchar() != '\n');
            
            // Solicitar o novo nome do aluno
            fflush(stdin);
            fgets(estudantes[index].nome, sizeof(estudantes[index].nome), stdin);
            
            // Remover o caractere de nova linha, se presente
            estudantes[index].nome[strcspn(estudantes[index].nome, "\n")] = '\0';

            printf("ALUNO EDITADO COM SUCESSO!\n");
            return 0;  // Indica que a edição foi bem-sucedida
        } else {
            printf("MATRICULA NAO ENCONTRADA. NENHUMA EDICAO REALIZADA.\n");
            return -1;  // Indica que a matrícula não foi encontrada
        }
    } else {
        printf("ERRO: NENHUM ALUNO PARA EDITAR.\n");
        return -1;  // Indica que não há alunos para editar
    }
}
int removerEstudante(Estudante estudantes[], int *tamanho, int matricula) {
    if (*tamanho >= 1) {
        int index = acharEstudante(estudantes, *tamanho, matricula);

        if (index != -1) {
            // Matrícula encontrada, realizar remoção
            for (int i = index; i < *tamanho - 1; i++) {
                estudantes[i] = estudantes[i + 1];
            }

            (*tamanho)--;
            printf("ALUNO REMOVIDO COM SUCESSO!\n");
            return 0;  // Indica que a remoção foi bem-sucedida
        } else {
            printf("Erro: MATRICULA NAO ENCONTRADA. NENHUM ALUNO REMOVIDO.\n");
            return -1;  // Indica que a matrícula não foi encontrada
        }
    } else {
        printf("ERRO: ALUNO INEXISTENTE.\n");
        return -1;  // Indica que não há alunos para remover
    }
}

int validarData(int dia, int mes, int ano) {
    // Verifica se o ano está dentro de um intervalo 
    if (ano < 2023 || ano > 2023) {
        return 0; // Ano inválido
    }

    // Verifica se o mês está no intervalo de 1 a 12
    if (mes < 1 || mes > 12) {
        return 0; // Mês inválido
    }

    // Verifica o número máximo de dias permitidos para cada mês
    int max_dias;
    if (mes == 2) {
        // Verifica se é um ano bissexto
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
            max_dias = 29; // Fevereiro em um ano bissexto
        } else {
            max_dias = 28; // Fevereiro em um ano não bissexto
        }
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        max_dias = 30; // Abril, junho, setembro, novembro
    } else {
        max_dias = 31; // Janeiro, março, maio, julho, agosto, outubro, dezembro
    }

    // Verifica se o dia está no intervalo válido para o mês
    if (dia < 1 || dia > max_dias) {
        return 0; // Dia inválido
    }

    // Se todas as verificações passaram, a data é válida
    return 1;
}
int validarDataString(const char *dataStr) {
    int dia, mes, ano;
    int numItensLidos = sscanf(dataStr, "%d-%d-%d", &dia, &mes, &ano);

    // Verifica se foram lidos três itens e se a data é válida
    if (numItensLidos == 3 && validarData(dia, mes, ano)) {
        return 1; // Data válida
    } else {
        return 0; // Data inválida
    }
}

int realizarChamada(Estudante estudantes[], int tamanho, char data_input[]) {
    if (tamanho == 0) {
        printf("ERRO NENHUM ALUNO INSERIDO. IMPOSSIVEL REALIZAR CHAMADA.\n");
        return 1;
    }

    FILE *file;
    char nome_arquivo[25];

    sprintf(nome_arquivo, "%s.txt", data_input);

    file = fopen(nome_arquivo, "w");
    if (file == NULL) {
        printf("Erro: Falha ao abrir o arquivo %s para escrita.\n", nome_arquivo);
        return 1;
    }
    printf("\n");
    printf("              -> LISTA DE ALUNOS:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("\n");
        printf("                 -> NOME: %s\n                 -> MATRICULA: %d\n", estudantes[i].nome, estudantes[i].matricula);

        int resposta;
        do {
        printf("\n");
        printf("              -> O ALUNO ESTA PRESENTE? (1 PARA SIM, 0 PARA NAO): ");
            scanf("%d", &resposta);

            if (resposta != 0 && resposta != 1) {
                printf("POR FAVOR, INSIRA UM VALOR VALIDO (0 ou 1).\n");
            }
        } while (resposta != 0 && resposta != 1);

        estudantes[i].esta_presente = resposta;

        fprintf(file, "%d,%s,%d\n", estudantes[i].matricula, estudantes[i].nome,
                estudantes[i].esta_presente);
    }

    fclose(file);
    printf("\n");
    printf("              -> CHAMADA REALIZADA COM SUCESSO. DADOS SALVOS EM %s\n", nome_arquivo);

    return 0;
}


void listarAlunos(Estudante estudantes[], int tamanho) {
    if (tamanho == 0) {
        printf("NENHUM ALUNO CADASTRADO.\n");
        return;
    }

    printf("\n");
    printf("              -> LISTA DE ALUNOS:\n");
    printf("\n");
    for (int i = 0; i < tamanho; i++) {
            printf("                 -> NOME: %s\n                 -> MATRICULA: %d\n",
                    estudantes[i].nome,estudantes[i].matricula);
            printf("\n");
    }
}

int main(){
   setlocale(LC_ALL, "Portuguese");
   Estudante estudantes[1000]; 
   int matri=0;
   int alternativa=0; 
   int tamanho=0;
   int index=-1;

   while (1) { 
        printf("\n");
        printf("                                 ........................\n");
        printf("                                 Escolha uma alternativa:\n");
        printf("                                 ........................\n");
        printf("\n");
        printf("                                 1. Inserir novo aluno\n"); //OK
        printf("\n");
        printf("                                 2. Listar alunos\n"); //OK
        printf("\n");
        printf("                                 3. Buscar aluno\n"); 
        printf("\n");
        printf("                                 4. Editar aluno\n");
        printf("\n");
        printf("                                 5. Remover aluno\n"); //OK
        printf("\n");
        printf("                                 6. Realizar chamada\n");
        printf("\n");
        if (scanf("%d", &alternativa) != 1) {
           printf("ERRO: ENTRADA INVALIDA.\n");
           return 1;
       }
       switch (alternativa) {
          case 1:
               adcEstudante(estudantes, &tamanho);
               break;
// FUNÇÃO OK!
           case 2:
                listarAlunos(estudantes, tamanho);
                break;
// FUNÇÃO OK :)
           case 3:
                printf("\n");
                printf("              -> PARA REALIZAR A BUSCA DO ALUNO, DIGITE SUA MATRICULA: ");
                scanf("%d", &matri);
                index=acharEstudante(estudantes,tamanho, matri);
                if (index != -1) {
                    printf("ALUNO ENCONTRADO!\n");
                    printf("NOME: %d, MATRICULA: %s\n", estudantes[index].nome,estudantes[index].matricula);
                }          
                else {
                    printf("ALUNO NAO ENCONTRADO.\n");
                }
                break;
//FUNÇÃO OK!
            case 4:
                printf("\n");
                printf("              -> DIGITE A MATRICULA DO ALUNO A SER EDITADO: ");
                scanf("%d", &matri);

            if (editarEstudante(estudantes, &tamanho, matri) == 0) {
            } else {
            printf("DESEJA ADICIONAR UM NOVO ALUNO? (S/N): ");
        
            char resposta;
            scanf(" %c", &resposta);  // O espaço antes do %c ignora espaços e quebras de linha
        
            if (resposta == 'S' || resposta == 's') {
                adcEstudante(estudantes, &tamanho);
                printf("NOVO ALUNO ADICIONADO COM SUCESSO!\n");
            } else {
                printf("NENHUM ALUNO FOI EDITADO.\n");
            }   
    }
    break;
//FUNÇÃO OK!
           case 5:
                printf("\n");
                printf("              -> DIGITE A MATRICULA DO ALUNO A SER REMOVIDA: ");
                scanf("%d", &matri);

            if (removerEstudante(estudantes, &tamanho, matri) == 0) {
            } else {
        }
        break;
//FUNÇÃO OK!
         case 6:
               {
                     char dataStr[20]=""; 

                    
                    while (!validarDataString(dataStr)) {
                    printf("\n");
                    printf("              -> DIGITE UMA DATA (FORMATO: dd-mm-aaaa): ");
                    scanf("%s", dataStr);
                    if (!validarDataString(dataStr)){
                    printf("DATA INVALIDA !!! INSIRA NOVAMENTE\n");}
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);

                    }
                    realizarChamada(estudantes, tamanho,dataStr);
}
                break;
                default:
                printf("ERRO: ALTERNATIVA INVALIDA.\n");
       }
   }
   return 0;
}
