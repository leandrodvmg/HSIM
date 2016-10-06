<b>Available Datasets</b><br>
8 bioinformatics datasets related to gene functions of yeast.<br>
<br>
<b>Hierarchical Supervised Imputation Method (HSIM)</b> is written in C++ programming language and should be started from the command prompt (Windows) or a terminal window (Linux).<br>
The format of the data file is Weka's ARFF format. Datasets used in our¹ experiment are kept in the "datasets" folder.<br>
<br>
To start HSIM, enter the following commands:<br>
Compilation: g++ -Wall -o hsim hsim.cpp<br>
Running: ./hsim -i [Name of input file] -o [Name of output file]<br>
<br>
<b>Running command example</b><br>
./hsim -i datasets/Church_single.arff -o datasets/Church_imputed.arff<br>
<br>
[1] L. Galvão and L. Merschmann. HSIM: A Supervised Imputation Method for Hierarchical Classification Scenario. In International Conference on Discovery Science.
