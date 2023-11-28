#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> 
#include <time.h>


typedef struct {
   int matricula; 
   char nome[1000];
   int esta_presente;
} Estudante; 

int acharEstudante(Estudante estudantes[], int tamanho, int matricula) { 
   for (int i = 0; i < tamanho; i++) {
       if (estudantes[i].matricula == matricula) {
       
           return i;
           printf("Erro: Aluno nAo encontrado.\n");
       }
       
   }
   
   return -1;
}

int adcEstudante(Estudante estudantes[], int *tamanho) {
    if (*tamanho >= 1000) {
        printf("Erro: O vetor de alunos estA cheio.\n");
        return -1;
    }

// ERRO AQUI, ESTÁ ACEITANDO NOME NA MATRICULA. A MATRICULA DEVERIA SER APENAS NUMEROS0
    printf("Digite a matricula do aluno: ");
    scanf("%d", &estudantes[*tamanho].matricula);
    while (getchar() != '\n');
    if (*tamanho >= 1)
    {
        int index = acharEstudante(estudantes,*tamanho,estudantes[*tamanho].matricula);
        if (index != -1)
       {
         printf("MatrIcula existente\n");
         return 0;
       }
    }

    
    
    
    printf("Digite o nome do aluno: ");
    fgets(estudantes[*tamanho].nome, sizeof(estudantes[*tamanho].nome), stdin);
    estudantes[*tamanho].nome[strcspn(estudantes[*tamanho].nome, "\n")] = '\0'; 

    estudantes[*tamanho].esta_presente = 0;
    (*tamanho)++;
    return 0;
}

int listarAlunos(Estudante estudantes[], int tamanho) {
    printf("Lista de alunos:\n");
    for (int i = 0; i < tamanho; i++) {
        // Verifica se o aluno foi adicionado
        if (estudantes[i].matricula != 0) {
            printf("MatrIcula: %d Nome: %s\n",
                   estudantes[i].matricula, estudantes[i].nome);
        }
    }
    return 0;
}



int editarEstudante(Estudante estudantes[], int *tamanho, int matricula) { 
   if (*tamanho >= 1)
    {
        int index = acharEstudante(estudantes,*tamanho,estudantes[*tamanho].matricula);
        if (index != -1)
       {
         printf("MatrIcula existente\n");
         return 0;
       }
    }
   int index = acharEstudante(estudantes, *tamanho, matricula);
   if (index != -1) {
       printf("Digite o novo nome do aluno: ");
       scanf("%s", estudantes[index].nome);
       return 0;
   }
   return -1;
}

int removerEstudante(Estudante estudantes[], int *tamanho, int matricula) {
   int index = acharEstudante(estudantes, *tamanho, matricula);
   if (index != -1) {
       estudantes[index] = estudantes[*tamanho - 1];
       (*tamanho)--;
       return 0;
   }
   return -1;
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

        printf("O aluno estA presente? (1 para Sim, 0 para NAo): ");
        scanf("%d", &estudantes[i].esta_presente);

        fprintf(file, "%d,%s,%d\n", estudantes[i].matricula, estudantes[i].nome,
                estudantes[i].esta_presente);
    }

    fclose(file);

    printf("Chamada realizada com sucesso.Dados salvos em %s\n", nome_arquivo);

    return 0;
}



int main(){
   setlocale(LC_ALL, "Portuguese");
   Estudante estudantes[1000]; 
   int matri=0;
   int alternativa=0; 
   int tamanho=0;
    
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
       printf("3. Buscar aluno\n"); 
       printf("4. Editar aluno\n");
       printf("5. Remover aluno\n"); //OK
       printf("6. Realizar chamada\n");
       if (scanf("%d", &alternativa) != 1) {
           printf("Erro: Entrada invAlida.\n");
           return 1;
       }
       switch (alternativa) {
          case 1:
               adcEstudante(estudantes, &tamanho);
               break;
// FUNÇÃO COM ERRO NA MATRÍCULA
           case 2:
               listarAlunos(estudantes, tamanho);
               break;
// FUNÇÃO OK :)
           case 3:
               printf("Para realizar a busca do aluno,digite sua matricula: ");
               scanf("%d", &matri);
               acharEstudante(estudantes,tamanho, matri);
               break;
// QUANDO O ALUNO É ENCONTRADO NÃO APARECE NADA, VOLTA PARA O MENU 
            case 4:
               printf("Digite a matrIcula do aluno a ser editado: ");
               scanf("%d", &matri);
               editarEstudante(estudantes, &tamanho, matri);
               break;
//PODERIA COLOCAR UMA MENSAGEM DE CONFIRMAÇÃO DA ALTERAÇÃO :/
           case 5:
               printf("Digite a matrIcula do aluno a ser removido: ");
               scanf("%d", &matri);
               removerEstudante(estudantes, &tamanho, matri);
               break;
//PODERIA COLOCAR UMA MENSAGEM DE CONFIRMAÇÃO DA REMOÇÃO :/
         case 6:
               {
                     char dataStr[20]=""; // Ajuste o tamanho conforme necessário

                    // Chama a função para validar a data em formato de string
                    while (!validarDataString(dataStr)) {
                    printf("Digite uma data (formato: dd-mm-aaaa): ");
                    scanf("%s", dataStr);
                    if (!validarDataString(dataStr)){
                    printf("Data invalida!!!Insira novamente\n");}
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
