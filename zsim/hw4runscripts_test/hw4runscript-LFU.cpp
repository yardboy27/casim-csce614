#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    // Define benchmarks
    char *PARSEC_benchmarks[] = {"blackscholes", "bodytrack", "canneal", "dedup", "fluidanimate", "freqmine", "streamcluster", "swaptions", "x264"};
    char *SPEC_benchmarks[] = {"bzip2", "gcc", "mcf", "hmmer", "sjeng", "libquantum", "xalancbmk", "milc", "cactusADM", "leslie3d", "namd", "soplex", "calculix", "lbm"};
    int num_PARSEC_benchmarks = sizeof(PARSEC_benchmarks) / sizeof(PARSEC_benchmarks[0]);
    int num_SPEC_benchmarks = sizeof(SPEC_benchmarks) / sizeof(SPEC_benchmarks[0]);

    // Run LFU benchmarks
    printf("--------------- Starting LFU child processes -----------------\n");
    for (int i = 0; i < num_PARSEC_benchmarks; ++i) {
        int child_status;
        int pid = fork();
        
        if (pid == 0) {
            char* args[] = {const_cast<char*>("./hw4runscript"), const_cast<char*>(PARSEC_benchmarks[i]), const_cast<char*>("LFU"), NULL};
            execvp(args[0], args);
        }
        
        printf("Waiting on benchmark: %s (LFU)\n", PARSEC_benchmarks[i]);
        wait(&child_status);
        printf("Benchmark: %s (LFU) is complete.\n", PARSEC_benchmarks[i]);
    }

    for (int i = 0; i < num_SPEC_benchmarks; ++i) {
        int child_status;
        int pid = fork();
        
        if (pid == 0) {
            char* args[] = {const_cast<char*>("./hw4runscript"), const_cast<char*>(SPEC_benchmarks[i]), const_cast<char*>("LFU"), NULL};
            execvp(args[0], args);
        }
        
        printf("Waiting on benchmark: %s (LFU)\n", SPEC_benchmarks[i]);
        wait(&child_status);
        printf("Benchmark: %s (LFU) is complete.\n", SPEC_benchmarks[i]);
    }
    printf("--------------- FINISHED all LFU child processes ---------------\n\n");

    return 0;
}
