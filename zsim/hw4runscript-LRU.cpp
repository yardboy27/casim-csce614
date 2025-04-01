#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <unordered_map>
#include <set>

constexpr size_t MAX_RUNNING_PROCESSES = 1;

void start_stop_processes(std::vector<pid_t> &child_pids, std::unordered_map<pid_t, char *> &pid_benchmark_map,
                          char **benchmarks, int num_benchmarks, char *benchmark_suite, char *repl_policy)
{
    int child_status;

    for (int i = 0; i < num_benchmarks; ++i)
    {
        int pid = fork();

        if (pid != 0)
        { // if it is the parent, then we want to collect the child pid and wait until it his sigstop
            child_pids.push_back(pid);
            pid_benchmark_map[pid] = benchmarks[i];
            waitpid(pid, &child_status, WUNTRACED);
        }
        else
        { // stop the child process -> we only want the processes in the queue to run
            std::cout << "Stopping process for: " << benchmarks[i] << ", with pid: " << getpid() << std::endl;
            raise(SIGSTOP);
            char *args[] = {const_cast<char *>("./hw4runscript"),
                            const_cast<char *>(benchmark_suite),
                            const_cast<char *>(benchmarks[i]),
                            const_cast<char *>(repl_policy),
                            NULL};
            execvp(args[0], args);
        }
    }
}

void restart_processes(std::vector<pid_t> &child_pids, std::unordered_map<pid_t, char *> pid_benchmark_map)
{
    std::set<pid_t> running_pids;
    int child_status;

    while (!child_pids.empty() || !running_pids.empty())
    {
        while (!child_pids.empty() && (running_pids.size() < MAX_RUNNING_PROCESSES))
        {
            pid_t stopped_pid = child_pids.back();
            child_pids.pop_back();

            kill(stopped_pid, SIGCONT); // restart the child process
            std::cout << "Running benchmark " << pid_benchmark_map[stopped_pid];
            std::cout << " with pid " << stopped_pid << std::endl;

            running_pids.insert(stopped_pid);
        }

        pid_t finished_pid = waitpid(-1, &child_status, 0);
        if (finished_pid > 0)
        {
            std::cout << "Finished benchmark " << pid_benchmark_map[finished_pid];
            std::cout << " with pid " << finished_pid << std::endl;
            running_pids.erase(finished_pid);
        }
    }
}

int main(void)
{
    // Define benchmarks
    char *PARSEC_benchmarks[] = {"blackscholes", "bodytrack", "canneal", "dedup", "fluidanimate", "freqmine", "streamcluster", "swaptions", "x264"};
    char *SPEC_benchmarks[] = {"bzip2", "gcc", "mcf", "hmmer", "sjeng", "libquantum", "xalancbmk", "milc", "cactusADM", "leslie3d", "namd", "soplex", "calculix", "lbm"};
    int num_PARSEC_benchmarks = sizeof(PARSEC_benchmarks) / sizeof(PARSEC_benchmarks[0]);
    int num_SPEC_benchmarks = sizeof(SPEC_benchmarks) / sizeof(SPEC_benchmarks[0]);

    // Run LRU benchmarks
    std::cout << "--------------- Starting LRU child processes -----------------" << std::endl;

    std::unordered_map<pid_t, char *> pid_benchmark_map;
    std::vector<pid_t> child_pids;

    // create and stop the child processes
    start_stop_processes(child_pids, pid_benchmark_map,
                         PARSEC_benchmarks, num_PARSEC_benchmarks,
                         const_cast<char *>("PARSEC"), const_cast<char *>("LRU"));
    std::cout << "Issued and stopped all PARSEC benchmarks" << std::endl;

    start_stop_processes(child_pids, pid_benchmark_map,
                         SPEC_benchmarks, num_SPEC_benchmarks,
                         const_cast<char *>("SPEC"), const_cast<char *>("LRU"));
    std::cout << "Issued and stopped all SPEC benchmarks" << std::endl;

    std::cout << "Running benchmarks in a controlled manner according to MAX_RUNNING_PROCESSES: ";
    std::cout << MAX_RUNNING_PROCESSES << std::endl;

    // restart the child processes in a controlled manner
    restart_processes(child_pids, pid_benchmark_map);

    std::cout << "--------------- Finishing LRU child processes -----------------" << std::endl;

    return 0;
}
