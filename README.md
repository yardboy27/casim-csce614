# casim
Computer Architecture Simulation Infrastructure for CSCE 614 Computer Architecture



##### 1. Apply a path file for cse server

```
$ git apply cse_server.patch
```

##### 2. Unzip benchmarks files

```
zip -F benchmarks.zip --out single-benchmark.zip && unzip single-benchmark.zip && mkdir benchmarks/parsec-2.1/inputs/streamcluster
```

### 3. Environemnt setup

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

##### 4. Compile zsim

```
$ cd zsim
$ scons -j4
```

You need to compile the code each time you make a change.

##### 5. Launch a test to run

```
./build/opt/zsim tests/simple.cfg
```



###### For more information, check `zsim/README.md`
