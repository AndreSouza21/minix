#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
 
int main() {
    int i;
    pid_t pids[4];
    struct timeval inicio_geral, agora;
 
    gettimeofday(&inicio_geral, NULL);
 
    for(i = 0; i < 4; i++) {
        pids[i] = fork();
        if(pids[i] == 0) {
            struct timeval t_inicio, t_fim;
            long j;
            double tempo_inicio, tempo_fim;
 
            gettimeofday(&t_inicio, NULL);
            tempo_inicio = (t_inicio.tv_sec - inicio_geral.tv_sec) + 
                           (t_inicio.tv_usec - inicio_geral.tv_usec) / 1e6;
 
            printf("Processo %d INICIOU em %.2f s\n", i, tempo_inicio);
            fflush(stdout);
 
            /* Trabalho pesado de CPU */
            long x = 1;
            for(j = 0; j < 300000000L; j++) x = x * 2 + 1;
 
            gettimeofday(&t_fim, NULL);
            tempo_fim = (t_fim.tv_sec - inicio_geral.tv_sec) + 
                        (t_fim.tv_usec - inicio_geral.tv_usec) / 1e6;
 
            printf("Processo %d TERMINOU em %.2f s (durou %.2f s)\n", 
                   i, tempo_fim, tempo_fim - tempo_inicio);
            fflush(stdout);
            return 0;
        }
    }
 
    for(i = 0; i < 4; i++) wait(NULL);
    printf("\nTodos os processos terminaram.\n");
    printf("\nSe FCFS: processos terminam UM POR VEZ (0 termina, depois 1, depois 2...)\n");
    printf("Se Round Robin: processos terminam QUASE JUNTOS\n");
    return 0;
}
