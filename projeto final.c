#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <locale.h> COLOCAR A BIBILIOTECA DE ACENTUAÇÃO DENTRO DE CADA FUNÇÃO APOS TERMINAR DE CONCERTAR AS FUNÇÕES
// as letras que tem acento estarão em maiusculas

typedef struct {
   int matricula; 
   char nome[1000];
   int esta_presente; //esta_presente
} Estudante; 

int adcEstudante(Estudante estudantes[], int *tamanho) { 
   if (*tamanho >= 1000) {
       printf("Erro: O array de alunos estA cheio.\n");
       return -1;
   }
   printf("Digite o ID do aluno: ");
   scanf("%d", &estudantes[*tamanho].matricula);
   printf("Digite o nome do aluno: ");
   scanf("%s", estudantes[*tamanho].nome);
   estudantes[*tamanho].esta_presente = 0;
   (*tamanho)++;
   return 0;
}

int acharEstudante(Estudante estudantes[], int tamanho, int matricula) { 
   for (int i = 0; i < tamanho; i++) {
       if (estudantes[i].matricula == matricula) {
           return i;
       }
   }
   printf("Erro: Aluno nAo encontrado.\n");
   return -1;
}

int editarEstudante(Estudante estudantes[], int tamanho, int matricula) { 
   int index = acharEstudante(estudantes, tamanho, matricula);
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

int salvarAtendimento(Estudante estudantes[], int tamanho, char nome_arquivo[]) {
   FILE *file = fopen(nome_arquivo, "w");
   if (file == NULL) {
       printf("Erro: Foi detectado um erro ao abrir o arquivo %s.\n", nome_arquivo);
       return;
   }
   for (int i = 0; i < tamanho; i++) {
       fprintf(file, "%d,%s,%d\n", estudantes[i].matricula, estudantes[i].nome, estudantes[i].esta_presente);
   }
   fclose(file);
   return 0;
}

int marcarAtendimento(Estudante estudantes[], int tamanho) {
   for (int i = 0; i < tamanho; i++) {
       estudantes[i].esta_presente = 1;
   }
   return 0;
}

int main() {
   Estudante estudantes[100];
   int tamanho = 0;
   int alternativa; //alternativa
   while (1) {
       printf("Escolha uma alternativa:\n");
       printf("1. Adicionar aluno\n");
       printf("2. Editar aluno\n");
       printf("3. Remover aluno\n");
       printf("4. Salvar atendimento\n");
       printf("5. Marcar atendimento\n");
       printf("6. Sair\n");
       if (scanf("%d", &alternativa) != 1) {
           printf("Erro: Entrada invAlida.\n");
           return 1;
       }
       switch (alternativa) {
           case 1:
               adcEstudante(estudantes, &tamanho);
               break;
           case 2:
               printf("Digite o ID do aluno a ser editado: ");
               scanf("%d", &alternativa);
               editarEstudante(estudantes, tamanho, alternativa);
               break;
           case 3:
               printf("Digite o ID do aluno a ser removido: ");
               scanf("%d", &alternativa);
               removerEstudante(estudantes, &tamanho, alternativa);
               break;
           case 4:
               salvarAtendimento(estudantes, tamanho, "attendance.csv");
               break;
           case 5:
               marcarAtendimento(estudantes, tamanho);
               break;
           case 6:
               return 0;
           default:
               printf("Erro: Alternativa inexistente.\n");
       }
   }
   return 0;
}
