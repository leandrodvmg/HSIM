### Available Datasets
#### Preservation of Predictive Power
8 bioinformatics datasets related to gene functions of yeast.<br>
<br>
### Available Source Code
<b>Hierarchical Supervised Imputation Method (HSIM)</b> is written in C++ programming language and should be started from the command prompt (Windows) or a terminal window (Linux).<br>
The format of the data file is Weka's ARFF format. Datasets used in first batch of experiments are kept in the "yeast_datasets" folder while datasets used in second batch of experiments are kept in the "protein_datasets" folder.<br>
<br>
To start HSIM, enter the following commands:<br>
Compilation: g++ -Wall -o hsim hsim.cpp<br>
Running: ./hsim -i [Name of input file] -o [Name of output file]<br>
<br>
<b>Running command example</b><br>
./hsim -i yeast_datasets/Church_single.arff -o yeast_datasets/Church_imputed.arff<br>
<br>
[1] L. Galvão and L. Merschmann. HSIM: A Supervised Imputation Method for Hierarchical Classification Scenario. In International Conference on Discovery Science.
