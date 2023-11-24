#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> 

typedef struct {
   int matricula; 
   char nome[1000];
   int esta_presente;
} Estudante; 

int acharEstudante(Estudante estudantes[], int tamanho, int matricula) { 
   for (int i = 0; i < tamanho; i++) {
       if (estudantes[i].matricula == matricula) {
           return i;
       }
   }
   printf("Erro: Aluno não encontrado.\n");
   return -1;
}

int adcEstudante(Estudante estudantes[], int *tamanho) {
    if (*tamanho >= 1000) {
        printf("Erro: O vetor de alunos estão cheio.\n");
        return -1;
    }


    printf("Digite a matricula do aluno: ");
    scanf("%d", &estudantes[*tamanho].matricula);
    while (getchar() != '\n');
    if (*tamanho >= 1)
    {
        int index = acharEstudante(estudantes,*tamanho,estudantes[*tamanho].matricula);
        if (index != -1)
       {
         printf("Matricula existente\n");
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
            printf("ID: %d, Nome: %s\n",
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
         printf("Matricula existente\n");
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

int marcacaoFalta(Estudante estudantes[], int tamanho, char nome_arquivo[]) {
   FILE *file = fopen(nome_arquivo, "w");
   if (file == NULL) {
       printf("Erro: Foi detectado um erro ao abrir o arquivo %s.\n", nome_arquivo);
       return 0;
   }
   for (int i = 0; i < tamanho; i++) {
       fprintf(file, "%d,%s,%d\n", estudantes[i].matricula, estudantes[i].nome, estudantes[i].esta_presente);
   }
   fclose(file);
   return 0;
}
//RETIREI A FUNÇÃO MARCAR_ATENDIMENTO POIS REALIZA A MSM FUNÇÃO QUE O CASO 6....



int main(){
    setlocale(LC_ALL, "Portuguese");
   Estudante estudantes[1000]; //alterei o vetor para 1000 de capacidade evitando gargalo
   int tamanho = 0;
   int matri=0;
   int alternativa=0; 
    
    // MENU SOLICITADO PELO PROFESSOR :)
    //1. Inserir um novo aluno;
    // 2. Listar alunos;
    //3. Buscar aluno;
    //4. Editar aluno;
    //5. Remover aluno;
    //6. Realizar chamada, marcando alunos faltantes;
    //7. Ler uma data e salvar chamada em arquivo nomeado pela data.

   while (1) { // alterei e coloquei o menu correto 
       printf("Escolha uma alternativa:\n");
       printf("1. Inserir novo aluno\n");
       printf("2. Listar alunos\n");
       printf("3. Buscar aluno\n");
       printf("4. Editar aluno\n");
       printf("5. Remover aluno\n");
       printf("6. Realizar chamada\n");
       if (scanf("%d", &alternativa) != 1) {
           printf("Erro: Entrada inválida.\n");
           return 1;
       }
       switch (alternativa) {
          case 1:
               adcEstudante(estudantes, &tamanho);
               break;
           case 2:
               listarAlunos(estudantes, tamanho);
               break;
// FUNÇÃO OK :)
           case 3:
               printf("Para realizar a busca do aluno,digite sua matricula: ");
               scanf("%d", &matri);
               acharEstudante(estudantes,tamanho, matri);
               break;//CORRIGIDO
            case 4:
               printf("Digite o ID do aluno a ser editado: ");
               scanf("%d", &matri);
               editarEstudante(estudantes, &tamanho, matri);
               break;// CORRIGIDO 
           case 5:
               printf("Digite o ID do aluno a ser removido: ");
               scanf("%d", &matri);
               removerEstudante(estudantes, &tamanho, matri);
               break;// CORRIGIDO
           case 6:
               //MarcacaoFalta(); //precisa implementar a FUNÇÃO com os parámetros..
               // precisa colocar a condição para chamada;
           default:
               printf("Erro: Alternativa inválida.\n");
       }
   }
   return 0;
}
