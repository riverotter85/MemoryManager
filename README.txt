Program: MemoryManager
Author: Logan Davis

The memory management code is provided with a main driver that tests each
of the project's main features, both for MemoryHeader and Matrix. This includes
allocating and freeing memory, traversing and printing the contents of MemoryHeader's
free list, allocating and freeing matrices, and multiplying two matrices. Of course, feel
free to use your own driver for the code. Simply include "Matrix.h" and "MemoryHeader.h"
in order to begin testing the features.

In order to run the driver, execute the following commands in your local Linux
environment (in my case, I am using Ubuntu):

1. make
2. ./MemoryManager <num_matrices>

This will allocate a list of matrices equal to the value provided and randomly free matrices
from said list. During this time, the contents of the matrices and free list (along with any
errors) will be printed. The driver will also test multiplying two different matrices together. One case
will perform a multiplication within memory constraints, whereas the other will attempt to multiply
with matrix sizes far beyond our hardware limitations.

NOTE: Situations and test cases that would normally result in a segmentation fault instead
print an error message and make an early return from the function. This is meant to be helpful
more than anything else. However, Dr. Boshart, if you need me to remove these safeguards so
the code will result in a segmentation fault as normal, I can always make the changes and resubmit.

THANK YOU!
