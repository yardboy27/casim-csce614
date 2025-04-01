# casim
Computer Architecture Simulation Infrastructure for CSCE 614 Computer Architecture


##### 1. Unzip benchmarks files

```
zip -F benchmarks.zip --out single-benchmark.zip && unzip single-benchmark.zip && mkdir benchmarks/parsec-2.1/inputs/streamcluster
```

### 2. Environemnt setup

To set up the Python environment for the first time, run the following commands.

```
$ python -m venv venv
$ source venv/bin/activate
$ pip install scons
```

Everytime you want to build or run zsim, you need to setup the environment variables first.

```
$ source venv/bin/activate
$ source setup_env
```

### 3. Compile zsim

```
$ cd zsim
$ scons -j4
```

You need to compile the code each time you make a change.

### 4. Running Benchmarks
In order to run the benchmarks, use one of the `.cpp` files located in the `zsim` folder.

These files include:
```
hw4runscript-LRU.cpp
hw4runscript-LFU.cpp
hw4runscript-SRRIP.cpp
```
It is highly recommended that you execute these `.cpp` programs on a background session using `tmux`. With `tmux`, the executable will still run even if your session is disconnected. More information about how to create a `tmux` session can be found online.

Compile one of these files by running the following command:
`g++ -o hw4runscript-<config>.o hw4runscript-<config>.cpp`

Then, run the program:
`./hw4runscript-<config>.o`



###### For more information, check `zsim/README.md`
