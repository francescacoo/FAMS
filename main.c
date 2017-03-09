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

void** load_data(int *totLines3,int *totLines4);

void add_new_employee(Employee **arrayEmployees, int *totLines );
void add_new_job(Job **arrayJobs, int *totLines );
void view_employee(Employee **arrayEmployees, int *totLines );
void view_jobs(Job **arrayJobs, int *totLines );
void exit_and_save(void** arrayData);


int main() {
    int chosenOption = 0;
    Employee **arrayEmployees;    /* Array of employees*/
    void** arrayData;
    Job **arrayJobs;    /* Array of jobs */
    int totLines3;         /* Total number of read lines */
    int totLines4;         /* Total number of read lines */

    chosenOption = display_menu();
    arrayData=load_data(&totLines3,&totLines4);
    arrayEmployees=arrayData[1];
    arrayJobs=arrayData[0];
    printf("you selected %d\n", chosenOption);
    switch(chosenOption){
        case 1:
            add_new_employee(arrayEmployees, &totLines3 );
            break;
        case 2:
            add_new_job(arrayJobs, &totLines4);
            break;
        case 3:
            view_employee(arrayEmployees, &totLines3);
            break;
        case 4:
  //          add_new_job();
            break;
        case 5:
            view_jobs(arrayJobs, &totLines4);
            break;
        case 6:
   //         add_new_job();
            break;
        case 7:
  //          add_new_job();
            break;
        case 8:
//            add_new_job();
            break;
        case 9:
//            add_new_job();
            break;
        case 10:
//            exit_and_save();
            break;
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

// Function 2:  load_data + subfunctions
void** load_data(int *totLines3, int *totLines4) {
    *totLines3=0;
    void **mypointer = NULL;
//    Job **arrayJobs;    /* Array of jobs */
    int totLines;         /* Total number of read lines */
    int totLines2;         /* Total number of read lines */
    mypointer = calloc(2, sizeof(void*));
    mypointer[1]=load_data_employee("employeeFile.txt", &totLines);
    mypointer[0]=load_data_job("jobFile.txt", &totLines2);
    *totLines3=totLines;
    *totLines4=totLines2;
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
        *totLines = line_count;

        /* Return the array of lines */
        return array;

    }


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

/*When the user selects the “add new employee” menu item, prompt them for the data for the new employee.
 * Append the new employee to the array of current
 * employees and notify the user that the new record has been added successfully.
 */
void add_new_employee(Employee **arrayEmployees, int *totLines ){

    Employee** NewArray=NULL;

    int newtot=*totLines+1;
    arrayEmployees=realloc(arrayEmployees,newtot* sizeof(Employee*));

    int Number;//employee number
    char firstName[20];//
    char lastName[20];//

    printf("Insert the employee ID :  "); // prompt to insert the input file name
    scanf("%d",&Number);
    printf("Insert the employee first name :  "); // prompt to insert the input file name
    scanf("%s",firstName);
    printf("Insert the employee last name :  "); // prompt to insert the input file name
    scanf("%s",lastName);

    arrayEmployees[*totLines] = malloc(sizeof(Employee));


    arrayEmployees[*totLines]->Number = Number;


    arrayEmployees[*totLines]->firstName = calloc(strlen(firstName) + 1, sizeof(char));
    strcpy(arrayEmployees[*totLines]->firstName, firstName);


    arrayEmployees[*totLines]->lastName = calloc(strlen(lastName) + 1, sizeof(char));
    strcpy(arrayEmployees[*totLines]->lastName, lastName);
    *totLines=newtot;

    for (int i = 0; i <= *totLines; i++) {
        printf("\n[%d]: %d", (i + 1), arrayEmployees[i]->Number);
        printf("  %s", arrayEmployees[i]->firstName);
        printf(" %s", arrayEmployees[i]->lastName);

    }
 /*   FILE *f = fopen("employeeFile.txt", "ab");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(f, "%d %s %s", Number, firstName,lastName);
    fprintf(f,"\r\n");

*/

}




// Function 4:  add_new_job
void add_new_job(Job **arrayJobs, int *totLines) {

        int EmployeeNumber;//employee number
        int jobNumber;
        char *customer[30];
        int day;
        int month;
        int year;
        int minute;
        int hour;
        time_t dueDate;         //The job due date
        time_t completedDate;  //The job's actual completion date

    int newtot=*totLines+1;
    arrayJobs=realloc(arrayJobs,newtot* sizeof(Job*));

    struct tm *current;
    time_t timenow;
    time(&timenow);
    current = localtime(&timenow);
    int currentmonth = current->tm_mon+1;
    int currentday = current->tm_mday;
    int currentyear = current->tm_year+1900;
    int currenthour = current->tm_hour;
    int currentminute = current->tm_min;

    printf("Insert the employee number :  "); // prompt to insert the input file name
    scanf("%d",&EmployeeNumber);
    printf("Insert the job number :  "); // prompt to insert the input file name
    scanf(" %d",&jobNumber);
    printf("Insert the customer :  "); // prompt to insert the input file name
    scanf("%s",&customer);
    puts("Insert the due date "); // prompt to insert the input file name

    puts("Insert the year: "); // prompt to insert the input file name
    scanf(" %d", &year);

    while(year<currentyear) {
        puts("The year inserted is not valid. \nInsert the year "); // prompt to insert the input file name
        scanf(" %d", &year);
    }

    puts("Insert the month "); // prompt to insert the month
    scanf(" %d", &month);

    while(month>12 || (month<currentmonth && year==currentyear)) {
        puts("The month inserted is not valid. \nInsert the month "); // prompt to insert the input file name
        scanf(" %d", &month);
    }
    int validDay = (month == 2 ?
                       (year % 4 ? 28 : (year % 100 ? 29 : (year % 400 ? 28 : 29))) :
                       ((month - 1) % 7 % 2 ? 30 : 31));

    puts("Insert the day "); // prompt to insert the input file name
    scanf(" %d", &day);

    while(day>validDay || (month<currentmonth && month==currentmonth && year==currentyear)) {
        puts("The day inserted is not valid. \nInsert the day "); // prompt to insert the input file name
        scanf(" %d", &day);
    }

    puts("Insert the hour "); // prompt to insert the hour
    scanf(" %d", &hour);

    while(hour>23 || (hour<currenthour && day==currentday && month==currentmonth && year==currentyear)) {
        puts("The day inserted is not valid. \nInsert the day "); // prompt to insert the input file name
        scanf(" %d", &hour);
    }
    puts("Insert the minute "); // prompt to insert the day
    scanf(" %d", &minute);

    while(minute>59 || (minute<currentminute && hour==currenthour && day==currentday && month==currentmonth && year==currentyear)) {
        puts("The day inserted is not valid. \nInsert the day "); // prompt to insert the day
        scanf(" %d", &minute);
    }


    struct tm newTimeS;
    newTimeS.tm_year = year - 1900;
    newTimeS.tm_mon = month - 1; //April
    newTimeS.tm_mday = day;
    newTimeS.tm_hour = hour;
    newTimeS.tm_min = minute;

    newTimeS.tm_isdst = -1;
    newTimeS.tm_sec = 0;
    newTimeS.tm_wday = -1;
    newTimeS.tm_yday = -1;

    dueDate = mktime(&newTimeS);




    // ARRAY

    arrayJobs[*totLines] = malloc(sizeof(Job));


    arrayJobs[*totLines]->EmployeeNumber = EmployeeNumber;
    arrayJobs[*totLines]->jobNumber = jobNumber;

    arrayJobs[*totLines]->customer = calloc(strlen(customer) + 1, sizeof(char));
    strcpy(arrayJobs[*totLines]->customer, customer);

    arrayJobs[*totLines]->dueDate = dueDate;


    for (int i = 0; i <= *totLines; i++) {
        printf("\n[%d]: %d", (i + 1), arrayJobs[i]->EmployeeNumber);
        printf(" %d", arrayJobs[i]->jobNumber);
        printf(" %s", arrayJobs[i]->customer);
        printf(" %li", arrayJobs[i]->dueDate);

        time_t dueDateString= arrayJobs[i]->dueDate;
        //    time(&dueDateString);

        time_t completedDateString= arrayJobs[i]->completedDate;
        //     time(&completedDateString);
        printf(" %s", ctime(&dueDateString));
        printf(" %s", ctime(&completedDateString));
    }


}
// Function 5:  view_employees

void view_employee(Employee **arrayEmployees, int *totLines){


    for (int i = 0; i < *totLines; i++) {
        printf("\n[%d]: %d", (i + 1), arrayEmployees[i]->Number);
        printf("  %s", arrayEmployees[i]->firstName);
        printf(" %s", arrayEmployees[i]->lastName);

    }

}


// Function 6: sort_employee

// Function 7:  view_job_information_time_due

void view_jobs(Job **arrayJobs, int *totLines){

    for (int i = 0; i < *totLines; i++) {
        printf("\n[%d]: %d", (i + 1), arrayJobs[i]->EmployeeNumber);
        printf(" %d", arrayJobs[i]->jobNumber);
        printf(" %s", arrayJobs[i]->customer);
        printf(" %li", arrayJobs[i]->dueDate);

        time_t dueDateString= arrayJobs[i]->dueDate;
        //    time(&dueDateString);

        time_t completedDateString= arrayJobs[i]->completedDate;
        //     time(&completedDateString);
        printf(" %s", ctime(&dueDateString));
        printf(" %s", ctime(&completedDateString));
    }
}

// Function 8: sort_job_information_by_customer

// Function 9: set_job_completed

// Function 10: view_job_information_by_employee

// Function 11: save_data