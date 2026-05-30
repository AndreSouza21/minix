#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>

volatile unsigned long long x = 1;

double tempo_decorrido(struct timeval inicio)
{
    struct timeval agora;
    gettimeofday(&agora, NULL);

    return (agora.tv_sec - inicio.tv_sec) +
           (agora.tv_usec - inicio.tv_usec) / 1e6;
}

int main()
{
    int i;
    pid_t pid;
    struct timeval inicio_geral;

    gettimeofday(&inicio_geral, NULL);

    printf("Criando processos...\n\n");

    for(i = 0; i < 4; i++)
    {
        pid = fork();

        if(pid == 0)
        {
            printf("P%d iniciou em %.3f s\n",
                   i,
                   tempo_decorrido(inicio_geral));
            fflush(stdout);

            unsigned long long limite;

            if(i == 0)
                limite = 3000000000ULL;  // MUITO longo
            else
                limite = 300000000ULL;   // curtos

            for(unsigned long long j = 0; j < limite; j++)
            {
                x = x * 13 + 7;
            }

            printf("P%d terminou em %.3f s\n",
                   i,
                   tempo_decorrido(inicio_geral));
            fflush(stdout);

            exit(0);
        }
    }

    while(wait(NULL) > 0);

    return 0;
}
