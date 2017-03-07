#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int Number;//employee number
    char* firstName;//
    char* lastName;//
}Employee;

typedef struct
{
    int EmployeeNumber;//employee number
    int jobNumber;
    char* customer;
    time_t dueDate;         //The job due date
    time_t completedDate;  //The job's actual completion date
}Job;


int display_menu();

Employee** load_data_employee(char* filename, int *totLines);
Job** load_data_job(char* filename, int *totLines2);

void** load_data();

int main() {
    int chosenOption = 0;
    Employee **arrayEmployees;    /* Array of employees*/
    void** arrayData;
    Job **arrayJobs;    /* Array of jobs */
    int totLines;         /* Total number of read lines */
    int totLines2;         /* Total number of read lines */

    chosenOption = display_menu();
    printf("you selected %d\n", chosenOption);
    arrayData=load_data();

    arrayEmployees=arrayData[1];

    for (int i = 0; i < 3; i++) {
        printf("\n[%d]: %d", (i + 1), arrayEmployees[i]->Number);
        printf("  %s", arrayEmployees[i]->firstName);
        printf(" %s", arrayEmployees[i]->lastName);

    }

    arrayJobs=arrayData[0];

        for (int i = 0; i < 2; i++) {
        printf("\n[%d]: %d", (i + 1), arrayJobs[i]->EmployeeNumber);
        printf("%d",  arrayJobs[i]->jobNumber);
        printf("%s", arrayJobs[i]->customer);
        printf(" %li", arrayJobs[i]->dueDate);
        printf(" %li", arrayJobs[i]->completedDate);

    }

        return 0;
    }

// Function 1:  display_menu
    int display_menu() {
        int chosenOption = 0;

        while (chosenOption == 0) {


            puts("1. Add an Employee");
            puts("2. Add a job");
            puts("3. View all employee information");
            puts("4. Sort employee information by name");
            puts("5. View job information by date and time due");
            puts("6. Sort job information by customer");
            puts("7. Sort job information by date and time due");
            puts("8. Set job as completed");
            puts("9. View job information by employee");
            puts("10. Exit");
            printf("Please select an option:  "); // prompt to insert the input file name
            scanf("%d", &chosenOption);
            if (chosenOption > 10) {
                puts("The number selected is not valid.");
                chosenOption = 0;
            }


        }

        // CASE FOR EACH SELECTED OPTION for 10 exit()
        return chosenOption;

    }

// Function 2:  load_data
void** load_data() {

    void **mypointer = NULL;
//    Job **arrayJobs;    /* Array of jobs */
    int totLines=0;         /* Total number of read lines */
    int totLines2=0;         /* Total number of read lines */
    mypointer = calloc(2, sizeof(void*));
    mypointer[1]=load_data_employee("employeeFile.txt", &totLines);
    mypointer[0]=load_data_job("jobFile.txt", &totLines2);
    return mypointer;

}


Employee** load_data_employee(char *filename, int *totLines) {


        printf("load data started");
        FILE *employeeFile; // Input file

//if the file doesn’t exist:
        while ((employeeFile = fopen(filename, "r")) == NULL) {
            fprintf(stderr, "Error opening the file");
        }

        Employee** array=NULL;
        int i;                   /* Loop counter */
        char line[100];           /* Buffer to read each line */
        int line_count;          /* Total number of lines */
        char temp[200];
        /* Clear output parameter. */
        *totLines = 0;

        /* Get the count of lines in the file */
        line_count = 0;
        while (fgets(line, sizeof(line), employeeFile) != NULL) {
            line_count++;
        }

        /* Move to the beginning of file. */
        rewind(employeeFile);

        array = malloc(line_count * sizeof(Employee*));

        if (array == NULL) {
            // return NULL; /* Error */
        }

        /* Read each line from file and deep-copy in the array. */
        for (i = 0; i < line_count; i++) {
            array[i] = malloc(sizeof(Employee));

            fscanf(employeeFile, "%s", temp); //Employee Last Name
            array[i]->Number = (int) strtol(temp, (char **)NULL, 10);

            fscanf(employeeFile, "%s", temp); //Employee Last Name
            array[i]->firstName = calloc(strlen(temp) + 1, sizeof(char));
            strcpy(array[i]->firstName, temp);

            fscanf(employeeFile, "%s", temp); //Employee Last Name
            array[i]->lastName = calloc(strlen(temp) + 1, sizeof(char));
            strcpy(array[i]->lastName, temp);
        }

        /* Write output param */
 //       *totLines = line_count;

        /* Return the array of lines */
        return array;

    }

// testing function 2




Job** load_data_job(char *filename, int *totLines2) {

    printf("\n job load data started");
    FILE *jobFile; // Input file

//if the file doesn’t exist:
    while ((jobFile = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening the file");
    }

    Job** array = NULL;
    int i;                   /* Loop counter */
    char line[100];           /* Buffer to read each line */
    int line_count;          /* Total number of lines */
    char temp[200];
    /* Clear output parameter. */
    *totLines2 = 0;

    /* Get the count of lines in the file */
    line_count = 0;
    while (fgets(line, sizeof(line), jobFile) != NULL) {
        line_count++;
    }

    /* Move to the beginning of file. */
    rewind(jobFile);

    array = malloc(line_count * sizeof(Job*));

    if (array == NULL) {
        // return NULL; /* Error */
    }

    /* Read each line from file and deep-copy in the array. */
    for (i = 0; i < line_count; i++) {
        array[i] = malloc(sizeof(Job));

        fscanf(jobFile, "%s", temp); //Employee Last Name
        array[i]->EmployeeNumber = (int) strtol(temp, (char **)NULL, 10);

        fscanf(jobFile, "%s", temp); //Employee Last Name
        array[i]->jobNumber = (int) strtol(temp, (char **)NULL, 10);

        fscanf(jobFile, "%s", temp); //Employee Last Name
        array[i]->customer = calloc(strlen(temp) + 1, sizeof(char));
        strcpy(array[i]->customer, temp);

        //Get the Due Date and store in the data structure
        fscanf(jobFile, "%s", temp); //Due Date
        array[i]->dueDate = (time_t)strtoull(temp, NULL, 10);

        //Get the Completion Date and store in the data structure
        fscanf(jobFile, "%s", temp); //Completion Date
        array[i]->completedDate = (time_t)strtoull(temp, NULL, 10);
    }

    /* Write output param */
    *totLines2 = line_count;

    /* Return the array of lines */
    return array;

    /* Allocate an array of pointers to strings
     * (one item per line). */
}
// Function 3:  add_new_employee

// Function 4:  add_new_job

// Function 5:  view_employee

// Function 6: sort_employee

// Function 7:  view_job_information_time_due

// Function 8: sort_job_information_by_customer

// Function 9: set_job_completed

// Function 10: view_job_information_by_employee

// Function 11: save_data