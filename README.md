# set-container
Implementation of a container which represents a set of elements of some type T. STL containers are used for storing information.   

The implemented container accepts objects of type T and stores them. It allows for searching for a value in the set, and if the value is not present, it returns a vector consisting of the greatest K elements smaller than that value, followed by the smallest K elements greater than that value. It also allows you to get a vector of all elements of the set that are between a given start value and a given end value.  
In either case, the elements in the returned vector are sorted in ascending order.    

The details regarding the implementation of these classes are given in the Set.h header file, in which the **methods are also implemented**  
A description is given in the pdf file provided.   
The file main.cpp contains illustration of some basic usage. 
The makefile will attempt to build the main file.    
