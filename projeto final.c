#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   int id;
   char name[100];
   int is_present;
} Student;

int addStudent(Student students[], int *size) {
   if (*size >= 100) {
       printf("Erro: O array de alunos está cheio.\n");
       return -1;
   }
   printf("Digite o ID do aluno: ");
   scanf("%d", &students[*size].id);
   printf("Digite o nome do aluno: ");
   scanf("%s", students[*size].name);
   students[*size].is_present = 0;
   (*size)++;
   return 0;
}

int findStudent(Student students[], int size, int id) {
   for (int i = 0; i < size; i++) {
       if (students[i].id == id) {
           return i;
       }
   }
   printf("Erro: Aluno não encontrado.\n");
   return -1;
}

int editStudent(Student students[], int size, int id) {
   int index = findStudent(students, size, id);
   if (index != -1) {
       printf("Digite o novo nome do aluno: ");
       scanf("%s", students[index].name);
       return 0;
   }
   return -1;
}

int removeStudent(Student students[], int *size, int id) {
   int index = findStudent(students, *size, id);
   if (index != -1) {
       students[index] = students[*size - 1];
       (*size)--;
       return 0;
   }
   return -1;
}

void saveAttendance(Student students[], int size, char filename[]) {
   FILE *file = fopen(filename, "w");
   if (file == NULL) {
       printf("Erro: Não foi possível abrir o arquivo %s.\n", filename);
       return;
   }
   for (int i = 0; i < size; i++) {
       fprintf(file, "%d,%s,%d\n", students[i].id, students[i].name, students[i].is_present);
   }
   fclose(file);
}

void takeAttendance(Student students[], int size) {
   for (int i = 0; i < size; i++) {
       students[i].is_present = 1;
   }
}

int main() {
   Student students[100];
   int size = 0;
   int option;
   while (1) {
       printf("Escolha uma opção:\n");
       printf("1. Adicionar aluno\n");
       printf("2. Editar aluno\n");
       printf("3. Remover aluno\n");
       printf("4. Salvar atendimento\n");
       printf("5. Marcar atendimento\n");
       printf("6. Sair\n");
       if (scanf("%d", &option) != 1) {
           printf("Erro: Entrada inválida.\n");
           return 1;
       }
       switch (option) {
           case 1:
               addStudent(students, &size);
               break;
           case 2:
               printf("Digite o ID do aluno a ser editado: ");
               scanf("%d", &option);
               editStudent(students, size, option);
               break;
           case 3:
               printf("Digite o ID do aluno a ser removido: ");
               scanf("%d", &option);
               removeStudent(students, &size, option);
               break;
           case 4:
               saveAttendance(students, size, "attendance.csv");
               break;
           case 5:
               takeAttendance(students, size);
               break;
           case 6:
               return 0;
           default:
               printf("Erro: Opção inválida.\n");
       }
   }
   return 0;
}