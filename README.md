
# Introduction: 
In this assignment, we were asked to find (both experimentally and mathematically) the optimal crossover point for a hybrid implementation of Strassen’s algorithm and traditional matrix multiplication. While we saw in class and in previous assignments that the divide-and-conquer approach (with Strassen’s algebra trick) was asymptotically faster than the standard O(n3) algorithm, intuitively it was apparent that Strassen’s would run slower on small matrices. This is because (while there are 7 rather than 8 matrix multiplications) there are 18 additions/subtractions. So the standard method will be faster up to a certain point.

(see [github.com/condaatje/strassen/blob/master/code2.pdf](https://github.com/condaatje/strassen/blob/master/code2.pdf) for the full writeup)
