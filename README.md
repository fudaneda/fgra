# FGRA

## App-Compiler

Put your application file into benchmarks foler, then:

```shell
cd <your-application-folder>
../compile.sh <your-application-file> <your-application-function>
../dot2json.sh 
```

## FGRA-Mapper

Change your application json into `run.sh`, then:

```shell
./run.sh
```

## FGRA-MG

Change your architecture file into `src/main/resources/fusion_spec.json`, then

```shell
./script/build-verilog.sh
```

## Simulation

Change your Mapper's output `cgra_execute.c` and `cgra_call.txt` to create a file in `software/test/bareMetal` like `add.c`, modify `Makefile` in `software/test/bareMetal`, then:

```shell
./script/build-verilator.sh
cd software/test && ./build.sh
cd .. && ./script/run-verilator.sh <your-application-name-without-postfix>
```