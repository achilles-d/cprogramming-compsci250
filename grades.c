/*
 * ECE/CS 250.
 * 
 * Grades assignment starter code.
 */

// Include useful standard libraries.
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


// TODO: Implement
struct student{
    int studentId;
    int exam1;
    int exam2;
    char theName[16]; 
    struct student *next; 
};

struct student* table[13] = {};
/*
 * Simple hash function.
 */
int hash(int i)
{
    return i % 13;
}

/*
 * Deallocate the hash table.
 */
void dealloc_hash_table()
{
    int i = 0;
    
    for(int i = 0; i < 13; i++){

        

        if(table[i] != 0){
            struct student *place;
            struct student *temp;

            place = table[i];
            temp = place; 
            place = place -> next;
            free(temp);

            while(place != 0){
                temp = place; 
                place = place -> next;
                free(temp);
            }

        }
    }

    
}

/*
 * Insert the record unless a record with the same ID already exists in the hash table.
 * If the record already exists, print "INSERT (<ID>) cannot insert because record exists".
 * If the record does not exist, print "INSERT (<ID>) <Exam 1 Score> <Exam 2 Score> <Name>".
 */
void insert_student(int student_id, int exam1_score, int exam2_score, char name[])
{
    int insHash = hash(student_id);
    struct student *place = malloc( sizeof(struct student) );
    struct student *temp = place; 
    if(table[insHash] != 0){
        place = table[insHash];
            while(place != 0){ 
            //Check if fields match 
                if(place -> studentId == student_id){
                    printf("INSERT (%d) cannot insert because record exists\n", student_id);
                    return; 
                }
                temp = place; 
                place = place -> next;

            }
        //Insert new entry 
        struct student *newEntry = malloc( sizeof(struct student));
        newEntry -> studentId = student_id;
        newEntry -> exam1 = exam1_score; 
        newEntry -> exam2 = exam2_score; 
        strcpy(newEntry -> theName, name);
        newEntry -> next = 0; 
        temp -> next = newEntry;
        
        printf("INSERT (%d) %d %d %s\n", newEntry -> studentId, newEntry -> exam1, 
                newEntry-> exam2, newEntry -> theName);
        return;
    }

    //Insert new entry at head of LinkedList
    else{
        table[insHash] = place; 
        place -> studentId = student_id;
        place -> exam1 = exam1_score; 
        place -> exam2 = exam2_score; 
        strcpy(place -> theName, name);
        place -> next = 0; 
        printf("INSERT (%d) %d %d %s\n", student_id, exam1_score, exam2_score, name);
        return;
    }
}

/*
 * Delete the record for the specified ID, if it exists in the hash table.
 * If the record already exists, print "DELETE (<ID>) <Exam 1 Score> <Exam 2 Score> <Name>".
 * If the record does not exist, print "DELETE (<ID>) cannot delete because record does not exist".
 */
void delete_student(int student_id)
{
    int insHash = hash(student_id);
    struct student *place = malloc( sizeof(struct student) );

    if(table[insHash] != 0){
        place = table[insHash];

        //Matching element is the leading element in the list 
        if(place -> studentId == student_id){
            table[insHash] = place -> next;
            printf("DELETE (%d) %d %d %s\n", place -> studentId, place -> exam1, 
                    place -> exam2, place -> theName);
            free(place); 
            return; 
        }

        //Matching element is elsewhere, if it is present 
        while(place -> next != 0){ 
            
            if(place -> next-> studentId == student_id){

                struct student *front = place; 
                    
                //Handle case that matching element is not last in the list 
                if(place -> next -> next != 0){
                    place = place -> next;
                    front -> next = place -> next;
                }
                //Handle case that matching element IS last in the list  
                else{
                    place = place -> next;
                    front -> next = 0;
                }

                printf("DELETE (%d) %d %d %s\n", place -> studentId, place -> exam1, 
                        place -> exam2, place -> theName);
                free(place);
                return; 

            }

            place = place -> next; 

        }
    }

    printf("DELETE (%d) cannot delete because record does not exist\n", student_id);
}

/*
 * Print all the member variables for the record with the specified ID, if it exists in the hash table.
 * If the record already exists, print "LOOKUP (<ID>) <Exam 1 Score> <Exam 2 Score> <Name>".
 * If the record does not exist, print "LOOKUP (<ID>) record does not exist".
 */
void lookup_student(int student_id)
{
    int insHash = hash(student_id);
    struct student *place = malloc( sizeof(struct student) );
    if(table[insHash] != 0){
        place = table[insHash];
        while(place != 0){ 
            //Print if found
            if(place -> studentId == student_id){
                printf("LOOKUP (%d) %d %d %s\n", place -> studentId, place -> exam1, place -> exam2,
                place -> theName);
                return; 
            }
            place = place -> next; 
        }
    }

    printf("LOOKUP (%d) record does not exist\n", student_id);
}

/*
 * main:
 *   - Reads in a filename from the command line arguments.
 *   - Opens and parses the file.
 *   - Calls the appropriate hash table functions.
 */
int main(int argc, char *argv[])
{
    FILE *fptr;

    if (argc != 2)
    {
        printf("Expected one argument but got %d", argc - 1);
        return EXIT_FAILURE;
    }

    if ((fptr = fopen(argv[1], "r")) == NULL)
    {
        printf("Error opening file `%s`!", argv[1]);
        return EXIT_FAILURE;
    }

    char command_type;
    int student_id, exam1_score, exam2_score;
    char name[16];

    while (fscanf(fptr, "%c %d %d %d %s\n", &command_type, &student_id, &exam1_score, &exam2_score, name) != EOF)
    {
        if (command_type == 'i')
        {
            insert_student(student_id, exam1_score, exam2_score, name);
        }
        else if (command_type == 'd')
        {
            delete_student(student_id);
        }
        else if (command_type == 'l')
        {
            lookup_student(student_id);
        }
        else
        {
            printf("Invalid command type `%c`!", command_type);
            return EXIT_FAILURE;
        }
    }

    fclose(fptr);

    dealloc_hash_table();

    return EXIT_SUCCESS;
}
