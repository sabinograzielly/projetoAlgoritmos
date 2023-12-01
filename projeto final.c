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
        printf("Erro: O vetor de alunos estA cheio.\n");
        return -1;
    }

    int matricula;
    char nome[1000];

    do {
    // Solicitar a matrícula
    printf("Digite a matrIcula do aluno: ");
    if (scanf("%d", &matricula) != 1 || getchar() != '\n') {
        printf("Erro: A matrIcula deve conter apenas nUmeros.\n");
        while (getchar() != '\n');  // Limpar o buffer de entrada
    } else {
        // Verificar se a matrícula já existe usando a função acharEstudante
        int index = acharEstudante(estudantes, *tamanho, matricula);
        if (index != -1) {
            printf("Erro: MatrIcula existente\n");
        } else {
            break;  // Saia do loop se a matrícula for válida
        }
    }
    } while (1);  // Loop até que uma matrícula válida seja inserida

    do {
        // Solicitar o nome do aluno
        printf("Digite o nome do aluno: ");
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
                printf("Erro: O nome deve conter apenas letras.\n");
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
            printf("Aluno encontrado\n");
            printf("Digite o novo nome do aluno: ");
            
            // Limpar o buffer de entrada
            while (getchar() != '\n');
            
            // Solicitar o novo nome do aluno
            fflush(stdin);
            fgets(estudantes[index].nome, sizeof(estudantes[index].nome), stdin);
            
            // Remover o caractere de nova linha, se presente
            estudantes[index].nome[strcspn(estudantes[index].nome, "\n")] = '\0';

            printf("Aluno editado com sucesso!\n");
            return 0;  // Indica que a edição foi bem-sucedida
        } else {
            printf("MatrIcula nAo encontrada. Nenhuma ediCAo realizada.\n");
            return -1;  // Indica que a matrícula não foi encontrada
        }
    } else {
        printf("Erro: Nenhum aluno para editar.\n");
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
            printf("Aluno removido com sucesso!\n");
            return 0;  // Indica que a remoção foi bem-sucedida
        } else {
            printf("Erro: MatrIcula nAo encontrada. Nenhum aluno removido.\n");
            return -1;  // Indica que a matrícula não foi encontrada
        }
    } else {
        printf("Erro: Aluno inexistente.\n");
        return -1;  // Indica que não há alunos para remover
    }
}

int validarData(int dia, int mes, int ano) {
    // Verifica se o ano está dentro de um intervalo razoável (pode ser ajustado conforme necessário)
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
    FILE *file;
    char nome_arquivo[25];

    sprintf(nome_arquivo, "%s.txt", data_input);

    file = fopen(nome_arquivo, "w");
    if (file == NULL) {
        printf("Erro: Falha ao abrir o arquivo %s para escrita.\n", nome_arquivo);
        return 1;
    }
    printf("Lista de alunos:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("MatrIcula: %d, Nome: %s\n", estudantes[i].matricula, estudantes[i].nome);

        int resposta;
        do {
            printf("O aluno estA presente? (1 para Sim, 0 para NAo): ");
            scanf("%d", &resposta);

            if (resposta != 0 && resposta != 1) {
                printf("Por favor, insira um valor vAlido (0 ou 1).\n");
            }
        } while (resposta != 0 && resposta != 1);

        estudantes[i].esta_presente = resposta;

        fprintf(file, "%d,%s,%d\n", estudantes[i].matricula, estudantes[i].nome,
                estudantes[i].esta_presente);
    }

    fclose(file);

    printf("Chamada realizada com sucesso. Dados salvos em %s\n", nome_arquivo);

    return 0;
}


void listarAlunos(Estudante estudantes[], int tamanho) {
    if (tamanho == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("Lista de alunos:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("MatrIcula: %d Nome: %s \n", estudantes[i].matricula,
               estudantes[i].nome);
    }
}

int main(){
   setlocale(LC_ALL, "Portuguese");
   Estudante estudantes[1000]; 
   int matri=0;
   int alternativa=0; 
   int tamanho=0;
   int index=-1;
    
    // MENU SOLICITADO PELO PROFESSOR :)
    //1. Inserir um novo aluno;
    // 2. Listar alunos;
    //3. Buscar aluno;
    //4. Editar aluno;
    //5. Remover aluno;
    //6. Realizar chamada, marcando alunos faltantes;
    //7. Ler uma data e salvar chamada em arquivo nomeado pela data.

   while (1) { 
       printf("Escolha uma alternativa:\n");
       printf("1. Inserir novo aluno\n"); //OK
       printf("2. Listar alunos\n"); //OK
       printf("3. Buscar aluno\n"); //OK
       printf("4. Editar aluno\n"); //OK
       printf("5. Remover aluno\n"); //OK
       printf("6. Realizar chamada\n"); //OK
       if (scanf("%d", &alternativa) != 1) {
           printf("Erro: Entrada invAlida.\n");
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
               printf("Para realizar a busca do aluno, digite sua matrIcula: ");
               scanf("%d", &matri);
               index=acharEstudante(estudantes,tamanho, matri);
               if (index != -1) {
                  printf("Aluno encontrado!\n");
                  printf("MatrIcula: %d, Nome: %s\n", estudantes[index].matricula,estudantes[index].nome);
               }          
               else {
                 printf("Aluno nAo encontrado.\n");
               }
               break;
//FUNÇÃO OK!
            case 4:
    printf("Digite a matrIcula do aluno a ser editado: ");
    scanf("%d", &matri);

    if (editarEstudante(estudantes, &tamanho, matri) == 0) {
        printf("Aluno editado com sucesso!\n");
    } else {
        // A matrícula não foi encontrada, pergunte se deseja adicionar um novo aluno
        printf("Deseja adicionar um novo aluno? (S/N): ");
        
        char resposta;
        scanf(" %c", &resposta);  // O espaço antes do %c ignora espaços e quebras de linha
        
        if (resposta == 'S' || resposta == 's') {
            adcEstudante(estudantes, &tamanho);
            printf("Novo aluno adicionado com sucesso!\n");
        } else {
            printf("Nenhum aluno foi editado.\n");
        }
    }
    break;
//FUNÇÃO OK!
           case 5:
    printf("Digite a matrIcula do aluno a ser removido: ");
    scanf("%d", &matri);

    if (removerEstudante(estudantes, &tamanho, matri) == 0) {
        printf("Aluno removido com sucesso!\n");
    } else {
    }
    break;
//FUNÇÃO OK!
         case 6:
               {
                     char dataStr[20]=""; // Ajuste o tamanho conforme necessário

                    // Chama a função para validar a data em formato de string
                    while (!validarDataString(dataStr)) {
                    printf("Digite uma data (formato: dd-mm-aaaa): ");
                    scanf("%s", dataStr);
                    if (!validarDataString(dataStr)){
                    printf("Data invalida!!! Insira novamente: \n");}
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);

                    }
                    realizarChamada(estudantes, tamanho,dataStr);
}
                break;
                default:
               printf("Erro: Alternativa invAlida.\n");
       }
   }
   return 0;
}
