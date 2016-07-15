Hierarchical Supervised Imputation Method (HSIM) is written in C++ programming language and should be started from the command prompt (Windows) or a terminal window (Linux).
The format of the data file is Weka's ARFF format. Datasets used in our¹ experiment are kept in the "datasets" folder.

To start HSIM, enter the following commands:
Compilation: g++ -Wall -o hsim hsim.cpp
Running: ./hsim -i [Name of input file] -o [Name of output file]

Running command example: ./hsim -i datasets/Church_single.arff -o datasets/Church_imputed.arff

[1] L. Galvão and L. Merschmann. HSIM: A Supervised Imputation Method for Hierarchical Classification Scenario. In International Conference on Discovery Science.
