# Combinatorial Verilog Generator

This is a C program that takes a .h file representation of a Sleptsov net from an NDR file from Tina using [NDRtoSN](https://github.com/dimazaitsev/SNCtools/tree/main/NDRtoSN) to make the .h file and this will then be used to generate verilog code for the net.

The code is based on [verilog_generator](https://github.com/ZhangS2000/verilog_generator) and has been modified to make the verilog file in a combinatorial layout rather than a sequential.

There is also a generator to also generate Verilog code that will follow the Salwicki rule allowing for maximal firing.
