# Combinatorial Verilog Generator

This is a C program that takes a .h file representation of a Sleptsov net from an NDR file from Tina using [NDRtoSN](https://github.com/dimazaitsev/SNCtools/tree/main/NDRtoSN) to make the .h file and this will then be used to generate verilog code for the provided net.

The code is based on [verilog_generator](https://github.com/ZhangS2000/verilog_generator) and has been modified to make the verilog file in a combinatorial layout rather than a sequential. This has then also been expanded on to support the Salwicki rule.

## How to compile and run
To compile the program using gcc simply run the following command and this will compile the .c file to an executable file with the following name:
```gcc Sleptsov_Generator.c -o Sleptsov_Generator```
```gcc Salwicki_Generator.c -o Salwicki_Generator```
To then be able to run this program and have it output the Verilog code to a Verilog file run the following command:
```Sleptsov_Generator > Verilog.v```
```Salwicki_Generator > Verilog.v```

## How to use

1. Use ```Tina``` to create a net and then export this as .ndr file.
2. Use ```NDRtoSN``` to convert the .ndr file to a .h file.
3. Then use one of the two generators to generate Verilog code.
4. You must add an include in the top of the file for the .h file that will be used.
5. You must also add a define for RES_PL as the result place of the net.
6. This shall then be compiled and ran and this shall output the Verilog code to the terminal.

