#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

}Job;


int display_menu();
Employee** load_data(char* filename, int *totLines);

int main() {
    int chosenOption = 0;
    Employee **arrayEmployees;    /* Array of employees*/
    char **arrayJobs = NULL;    /* Array of jobs */
    int totLines;         /* Total number of read lines */

    chosenOption = display_menu();
    printf("you selected %d", chosenOption);

    arrayEmployees=load_data("employeeFile.txt", &totLines);

    //  arrayJobs=load_data("jobsFile.txt", &totLines);
    for (int i = 0; i < 3; i++) {
        printf("[%d]: %d\n", (i + 1), arrayEmployees[i]->Number);
        printf("[%d]: %s\n", (i + 1), arrayEmployees[i]->firstName);
        printf("[%d]: %s\n", (i + 1), arrayEmployees[i]->lastName);

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

Employee** load_data(char *filename, int *totLines) {


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

        /* Allocate an array of pointers to strings
         * (one item per line). */
        //array = malloc(line_count * sizeof(char *));
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
            /* Copy the line into the newly allocated space. */
            //       strcpy(array[i], line);
        }

        /* Write output param */
        *totLines = line_count;

        /* Return the array of lines */
        return array;

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