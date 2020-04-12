# Homework 1: C Programming
## ***COMPSCI250: Computer Architecture***
## C Files
### bySeventeen.c
* Makes use of a for loop to compute and print out the first N multiplies of 17.

### recurse.c
* Uses recursion to compute f(N) =  3 * f(N - 1) + 4 * f(N - 2) + 2.

### grades.c
* Implements a hash table where students with the same hash (student ID % 13) are held in the same linked list, or "bucket" of the hashtable. 
* The elements of the outer linked list each point to the head of one of the linked lists previously described in ascending order of the students' shared hash.  
* The program supports insertion, removal, and lookup of a student using the student's name and ID, a number. 
