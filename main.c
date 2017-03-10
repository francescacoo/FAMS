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
void add_new_job(Job **arrayJobs, int *totLines2 );
void view_employee(Employee **arrayEmployees, int *totLines );
void view_job_information_time_due(Job **arrayJobs, int *totLines2 );
void save_data(Employee **arrayEmployees, int *totLines, Job **arrayJobs, int *totLines2 );

void sort_employee(Employee **arrayEmployees, int *totLines );
void sort_employee_by_id(Employee **arrayEmployees, int *totLines );

void sort_job_information_by_customer(Job **arrayJobs, int *totLines2 );
void sort_job_information_by_date_time_due(Job **arrayJobs, int *totLines2 );

void view_job_information_by_id(Job **arrayJobs, int *totLines2 );
void view_job_information_by_employee(Job **arrayJobs, int *totLines2 );
void view_job_information_by_due_date(Job **arrayJobs, int *totLines2 );


void set_job_as_completed(Job **arrayJobs, int *totLines2);
void view_employee_by_name(Employee **arrayEmployees, int *totLines);

void continue_enter();

int main() {
    int chosenOption = 0;
    Employee **arrayEmployees;    /* Array of employees*/
    void** arrayData;
    Job **arrayJobs;    /* Array of jobs */
    int totLines3;         /* Total number of read lines */
    int totLines4;         /* Total number of read lines */

    arrayData=load_data(&totLines3,&totLines4);
    arrayEmployees=arrayData[1];
    arrayJobs=arrayData[0];

    chosenOption = display_menu();


    while (chosenOption!=14) {


        switch(chosenOption){
            case 1:
                add_new_employee(arrayEmployees, &totLines3 ); //Add an Employee
                break;
            case 2:
                add_new_job(arrayJobs, &totLines4); // Add a job
                break;
            case 3:
                view_employee(arrayEmployees, &totLines3); //View all employee information
                break;
            case 4:
                view_employee_by_name(arrayEmployees, &totLines3); //view all employees sorted by name

                break;
            case 5:
                sort_employee(arrayEmployees, &totLines3); //Sort employee by name and export to external file
      //          view_job_information_time_due(arrayJobs, &totLines4); //View all jobs information by date and time due
                break;
            case 6:
                sort_employee_by_id(arrayEmployees, &totLines3); //Sort employee by ID and export to external file

                break;
            case 7:
                view_job_information_time_due(arrayJobs, &totLines4);
         //       view_job_information_by_id(arrayJobs, &totLines4); // view details of a job id
                break;
            case 8:
                view_job_information_by_employee(arrayJobs, &totLines4);
          //      sort_job_information_by_customer(arrayJobs, &totLines4);//Sort job information by customer
                break;
            case 9:
                view_job_information_by_id(arrayJobs, &totLines4);
         //       sort_job_information_by_date_time_due(arrayJobs, &totLines4);//
                break;
            case 10:

                view_job_information_by_due_date(arrayJobs, &totLines4);
                break;
            case 11:
                sort_job_information_by_customer(arrayJobs, &totLines4);
                break;
            case 12:
                sort_job_information_by_date_time_due(arrayJobs, &totLines4);
                break;
            case 13:
                set_job_as_completed(arrayJobs, &totLines4);
                break;
        }
        chosenOption = display_menu();
    }

    if(chosenOption==14){
        save_data( arrayEmployees,  &totLines3,  arrayJobs,  &totLines4 );
    }





        return 0;
    }

// Function 1:  display_menu
int display_menu() {
    int chosenOption = 0;
    puts("\n#################");
    puts("###    Menu   ###");
    puts("#################\n");

        while (chosenOption == 0) {

            puts("1. Add an Employee");
            puts("2. Add a job");
            puts("#####EMPLOYEES######");

            puts("3. View all employees information");
            puts("4. View all employees sorted by name");

            puts("5. Export employees sorted by name");
            puts("6. Export employees by id");

            puts("#####JOBS######");
            puts("7. View all jobs sorted by date and time due");

            puts("8. Search jobs by employee");
            puts("9. Search a job by id");
            puts("10. Search jobs by date and time due");

            puts("11. Export job information by customer");
            puts("12. Export job information by date and time due");

            puts("13. Set job as completed");

            puts("14. Exit");
            printf("Please select an option:  "); // prompt to insert the input file name
            scanf("%d", &chosenOption);
            if (chosenOption > 14) {
                puts("The number selected is not valid.");
                chosenOption = 0;
            }

            printf("You selected option: %d\n", chosenOption);



        }

        // CASE FOR EACH SELECTED OPTION for 10 exit()
        return chosenOption;

    }

//
/* Function 2:  load_data + subfunctions load_data_employee and  load_data_job
 *
 * This function is automatically called when the program is started.
 * It reads employee and job information from files.
 * If the files do not exist, notify the user, create the files and display the main menu.
 * Once a file is open, data is read into an array of structs by
 * dynamically creating sufficient memory for each entry read from the file.
 */

void** load_data(int *totLines3, int *totLines4) {
    *totLines3=0;
    *totLines4=0;
    void **mypointer = NULL;
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


        puts("Employee load data started..");
        FILE *employeeFile; // Input file

        //if the file doesn’t exist:
        if ((employeeFile = fopen(filename, "r")) == NULL) {
            printf("The file doesn't exist. Creating it..");
            employeeFile = fopen("employeeFile.txt", "wb");
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

        /* Read each line from file and copy in the array. */
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
        fclose(employeeFile); // closing the file
        /* Return the array of lines */
        return array;

    }


Job** load_data_job(char *filename, int *totLines2) {

    printf("\n job load data started");
    FILE *jobFile; // Input file

//if the file doesn’t exist:
    if ((jobFile = fopen(filename, "r")) == NULL) {
        printf("The file doesn't exist. Creating it..");
        jobFile = fopen("employeeFile.txt", "wb");
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
    fclose(jobFile); //closing the file
    /* Return the array of lines */
    return array;

}

/*/////////////////////////////////////////////ADD EMPLOYEES AND ADD JOBS /////////////////////////////////////////////////////////*/

/* Function 3:  add_new_employee
 *
 * When the user selects the “add new employee” menu item, prompt them for the data for the new employee.
 * Append the new employee to the array of current
 * employees and notify the user that the new record has been added successfully.
 */
void add_new_employee(Employee **arrayEmployees, int *totLines ){

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

        printf("The new employee has been added:\n");
        printf("\n[%d]: %d", (newtot), arrayEmployees[newtot-1]->Number);
        printf("  %s", arrayEmployees[newtot-1]->firstName);
        printf(" %s", arrayEmployees[newtot-1]->lastName);

    continue_enter();
}


/* Function 4:  add_new_job
 *
 * When the user selects the “add new job” menu item, prompt them for the new job information.
 * Append the new job to the array of current jobs and notify the user that
 * the new record has been added successfully.
 */


void add_new_job(Job **arrayJobs, int *totLines2) {

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

    int newtot=*totLines2+1;
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

    arrayJobs[*totLines2] = malloc(sizeof(Job));


    arrayJobs[*totLines2]->EmployeeNumber = EmployeeNumber;
    arrayJobs[*totLines2]->jobNumber = jobNumber;

    arrayJobs[*totLines2]->customer = calloc(strlen(customer) + 1, sizeof(char));
    strcpy(arrayJobs[*totLines2]->customer, customer);

    arrayJobs[*totLines2]->dueDate = dueDate;


        printf("\n[%d]: %d", (*totLines2 + 1), arrayJobs[*totLines2]->EmployeeNumber);
        printf(" %d", arrayJobs[*totLines2]->jobNumber);
        printf(" %s", arrayJobs[*totLines2]->customer);

        time_t dueDateString= arrayJobs[*totLines2]->dueDate;
        //    time(&dueDateString);

        time_t completedDateString= arrayJobs[*totLines2]->completedDate;
        //     time(&completedDateString);
        printf(" %s", ctime(&dueDateString));
        printf(" %s", ctime(&completedDateString));
    *totLines2=newtot;

    continue_enter();
}


/*////////////////////////////////////////////////////////////            //////////////////////////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////// EMPLOYEES  //////////////////////////////////////////////////////////////////////////////////*/
/*////////////////////////////////////////////////////////////            //////////////////////////////////////////////////////////////////////////////////*/

/* Function 5:  view_employees
 *
 * When the user selects the “view employees” option, this function prints a list
 * of all employee information on record.
 * Make sure that the employee information is in a report with headers,
 * not simply a list of raw information.
 */
//

void view_employee(Employee **arrayEmployees, int *totLines){

    printf("%s\n", "#### ALL EMPLOYEES ####");
    printf("%5s   %-15s   %-15s\n", "Number", "Name","Surname");
    printf("%5s   %-15s   %-15s\n", "------", "-------------", "--------------");


    for (int i = 0; i < *totLines; i++) {
        printf("%6d   %-15s   %-15s\n", arrayEmployees[i]->Number,arrayEmployees[i]->firstName,arrayEmployees[i]->lastName);


    }

    continue_enter();
}

void view_employee_by_name(Employee **arrayEmployees, int *totLines) {
    int pass; // passes counter
    int i; //comparison counter
    int comparison;
    Employee *hold; //temporary location used to swap array elements
    int linecount;
    linecount = *totLines;
    Employee **newArray;
    newArray = malloc(linecount * sizeof(Employee*));

    memcpy(newArray, arrayEmployees, linecount * sizeof(Employee*));

    /* loop to control number of passes */
    for (pass = 1 ; pass < *totLines; pass++){

        /* loop to control number of comparisons per pass */
        for (i = 0 ; i < *totLines-1; i++){

            comparison=strcmp(newArray[i]->lastName,newArray[i+1]->lastName);
            if (comparison>0) {

                hold = newArray[i];
                newArray[i]   = newArray[i+1];
                newArray[i+1] = hold;
            } // end if
        } // end inner for
    } // end outer for
    printf("%s\n", "#### ALL EMPLOYEES SORTED BY NAME ####");
    printf("%5s   %-15s   %-15s\n", "Number", "Name","Surname");
    printf("%5s   %-15s   %-15s\n", "------", "-------------", "--------------");


    for (int i = 0; i < *totLines; i++) {
        printf("%6d   %-15s   %-15s\n", newArray[i]->Number,newArray[i]->firstName,newArray[i]->lastName);


    }

    continue_enter();


}

/* Function 6: sort_employee
 *
 * Give the user the option to sort employees by name.
 * Store the sorted information and notify the user of the name of the file.
 * This function displays the employee, number, sorted by employee.
 * Make a copy of the original array of employees to perform the sorting function.
 * Make sure that the employee information is in a report with headers,
 * not simply a list of raw information.
 *
 */
void sort_employee(Employee **arrayEmployees, int *totLines ){

    int pass; // passes counter
    int i; //comparison counter
    int comparison;
    Employee *hold; //temporary location used to swap array elements
    int linecount;
    linecount = *totLines;
    Employee **newArray;
    newArray = malloc(linecount * sizeof(Employee*));

    memcpy(newArray, arrayEmployees, linecount * sizeof(Employee*));

    /* loop to control number of passes */
    for (pass = 1 ; pass < *totLines; pass++){

        /* loop to control number of comparisons per pass */
        for (i = 0 ; i < *totLines-1; i++){

            comparison=strcmp(newArray[i]->lastName,newArray[i+1]->lastName);
            if (comparison>0) {

                hold = newArray[i];
                newArray[i]   = newArray[i+1];
                newArray[i+1] = hold;
            } // end if
        } // end inner for
    } // end outer for
    printf("%s\n", "#### ALL EMPLOYEES SORTED BY NAME ####");
    printf("%5s   %-15s   %-15s\n", "Number", "Name","Surname");
    printf("%5s   %-15s   %-15s\n", "------", "-------------", "--------------");


    for (int i = 0; i < *totLines; i++) {
        printf("%6d   %-15s   %-15s\n", newArray[i]->Number,newArray[i]->firstName,newArray[i]->lastName);


    }

    FILE *f3 = fopen("SortedEmployeeFile.txt", "w");
    if (f3 == NULL)
    {
        printf("The file doesn't exist. Creating it..");
        f3 = fopen("SortedEmployeeFile.txt", "wb");
    }

    for (int l = 0; l < linecount; l++) {
        fprintf(f3, "%d %s %s", newArray[l]->Number, newArray[l]->firstName, newArray[l]->lastName);
        fprintf(f3, "\r\n");
    }
    puts("\nData sorted and saved in SortedEmployeeFile.txt");
    fclose(f3); // closing file

    continue_enter();


}

// EXPORT EMPLOYEES SORTED BY ID
void sort_employee_by_id(Employee **arrayEmployees, int *totLines ){

    int pass; // passes counter
    int i; //comparison counter
    Employee *hold; //temporary location used to swap array elements
    int linecount;
    linecount = *totLines;
    Employee **newArray;
    newArray = malloc(linecount * sizeof(Employee*));

    memcpy(newArray, arrayEmployees, linecount * sizeof(Employee*));

    /* loop to control number of passes */
    for (pass = 1 ; pass < *totLines; pass++){

        /* loop to control number of comparisons per pass */
        for (i = 0 ; i < *totLines-1; i++){


            if (newArray[i]->Number>newArray[i+1]->Number) {

                hold = newArray[i];
                newArray[i]   = newArray[i+1];
                newArray[i+1] = hold;
            } // end if
        } // end inner for
    } // end outer for
    printf("%s\n", "#### ALL EMPLOYEES SORTED BY ID ####");
    printf("%5s   %-15s   %-15s\n", "Number", "Name","Surname");
    printf("%5s   %-15s   %-15s\n", "------", "-------------", "--------------");


    for (int i = 0; i < *totLines; i++) {
        printf("%6d   %-15s   %-15s\n", newArray[i]->Number,newArray[i]->firstName,newArray[i]->lastName);


    }

    FILE *f3 = fopen("SortedEmployeeByIDFile.txt", "w");
    if (f3 == NULL)
    {
        printf("The file doesn't exist. Creating it..");
        f3 = fopen("SortedEmployeeByIDFile.txt", "wb");
    }

    for (int l = 0; l < linecount; l++) {
        fprintf(f3, "%d %s %s", newArray[l]->Number, newArray[l]->firstName, newArray[l]->lastName);
        fprintf(f3, "\r\n");
    }
    puts("\nData sorted and saved in SortedEmployeeByIDFile.txt");
    fclose(f3); // closing the file

    continue_enter();


}
/*////////////////////////////////////////////////////////////       //////////////////////////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////// JOBS  //////////////////////////////////////////////////////////////////////////////////*/
/*////////////////////////////////////////////////////////////       //////////////////////////////////////////////////////////////////////////////////*/


/* *****************************************************
 *
 * VIEW ALL JOBS SORTED BY DATE DUE ----- MENU 7
 *
 * *****************************************************/

void view_job_information_time_due(Job **arrayJobs, int *totLines) {

    int pass; // passes counter
    int i; //comparison counter

    Job *hold; //temporary location used to swap array elements
    int linecount;
    linecount = *totLines;
    Job **newArray;
    newArray = malloc(linecount * sizeof(Employee *));

    memcpy(newArray, arrayJobs, linecount * sizeof(Job *));

/* loop to control number of passes */
    for (pass = 1; pass < *totLines; pass++) {

        /* loop to control number of comparisons per pass */
        for (i = 0; i < *totLines - 1; i++) {

            if (newArray[i]->dueDate > newArray[i + 1]->dueDate) {

                hold = newArray[i];
                newArray[i] = newArray[i + 1];
                newArray[i + 1] = hold;
            } // end if
        } // end inner for
    } // end outer for
    printf("sorted");
    printf("\n%5s%-20s%-5s%-21s%-21s\n", "JobID  ", "Customer", "EmpID  ", "Due Date", "Completed Date");
    printf("%5s%-20s%-5s%-21s%-21s\n", "-----", " -------------------- ", "----- ", "------------------- ", "--------------------");
    for (int i = 0; i < *totLines; i++) {

        char *dueDateString2 = calloc(20, sizeof(char)); //"Apr 20, 2017 @12:00" + NULL
        char *completedDateString2 = calloc(20, sizeof(char)); //"Thu Apr 20, 2017" + NULL

        time_t dueDateString = newArray[i]->dueDate;
        time_t completedDateString = newArray[i]->completedDate;
        //     time(&completedDateString);

        if( (int)dueDateString==83886080){
            dueDateString2="No date inserted";
        }
        else{
            strftime(dueDateString2, 20, "%b %d, %Y %H:%M", localtime(&dueDateString));

        }
        if((int)completedDateString==83886080){
            completedDateString2="No date inserted";
        }

        else{
            strftime(completedDateString2, 20, "%b %d, %Y %H:%M", localtime(&completedDateString));
        }



        printf("%5d  %-20s%-5d  %-21s%-21s\n", newArray[i]->jobNumber, newArray[i]->customer,
               newArray[i]->EmployeeNumber, dueDateString2, completedDateString2);


    }


    continue_enter();


}

/* *****************************************************
 *
 * SEARCH JOBS OF A SELECTED EMPLOYEE ----- MENU 8
 *
 * *****************************************************/

void view_job_information_by_employee(Job **arrayJobs, int *totLines){
    int tot_found=0; // counter for the job found -> if it is 0 after the loop print a not found message
    int employee_id;
    printf("Insert the employee ID :  "); // prompt to insert the input file name
    scanf("%d",&employee_id);

    int pass; // passes counter
    int i; //comparison counter

    Job *hold; //temporary location used to swap array elements
    int linecount;
    linecount = *totLines;
    Job **newArray;
    newArray = malloc(linecount * sizeof(Job*));

    memcpy(newArray, arrayJobs, linecount * sizeof(Job*));

    /* loop to control number of passes */

    for (pass = 1 ; pass < *totLines; pass++){

        /* loop to control number of comparisons per pass */

        for (i = 0 ; i < *totLines-1; i++){

            if (newArray[i]->dueDate > newArray[i+1]->dueDate) {

                hold = newArray[i];
                newArray[i]   = newArray[i+1];
                newArray[i+1] = hold;
            } // end if
        } // end inner for
    } // end outer for


    printf("\n%5s%-20s%-5s%-21s%-21s\n", "JobID  ", "Customer", "EmpID  ", "Due Date", "Completed Date");
    printf("%5s%-20s%-5s%-21s%-21s\n", "-----", " -------------------- ", "----- ", "------------------- ", "--------------------");

    for (int i = 0; i < *totLines; i++) {
        if(newArray[i]->EmployeeNumber==employee_id){
            tot_found++; // increase the counter
            char *dueDateString2 = calloc(20, sizeof(char)); //"Apr 20, 2017 @12:00" + NULL
            char *completedDateString2 = calloc(20, sizeof(char)); //"Thu Apr 20, 2017" + NULL

            time_t dueDateString = newArray[i]->dueDate;
            time_t completedDateString = newArray[i]->completedDate;
            //     time(&completedDateString);

            if( (int)dueDateString==83886080){
                dueDateString2="No date inserted";
            }
            else{
                strftime(dueDateString2, 20, "%b %d, %Y %H:%M", localtime(&dueDateString));

            }
            if((int)completedDateString==83886080){
                completedDateString2="No date inserted";
            }

            else{
                strftime(completedDateString2, 20, "%b %d, %Y %H:%M", localtime(&completedDateString));
            }



            printf("%5d  %-20s%-5d  %-21s%-21s\n", newArray[i]->jobNumber, newArray[i]->customer,
                   newArray[i]->EmployeeNumber, dueDateString2, completedDateString2);


        }
    }
    if(tot_found == 0){
        printf("No jobs found for the selected employee!\n");
    }
    continue_enter();
}

/* *****************************************************
 *
 * SEARCH A JOB BY ID ----- MENU 9
 *
 * *****************************************************/

void view_job_information_by_id(Job **arrayJobs, int *totLines){
    int tot_found=0; // counter for the tot record found. If 0 display a non found message
    int job_id;
    printf("Insert the job ID :  "); // prompt to insert the input file name
    scanf("%d",&job_id);

    int pass; // passes counter
    int i; //comparison counter

    Job *hold; //temporary location used to swap array elements
    int linecount;
    linecount = *totLines;
    Job **newArray;
    newArray = malloc(linecount * sizeof(Job*));

    memcpy(newArray, arrayJobs, linecount * sizeof(Job*));

    /* loop to control number of passes */

    for (pass = 1 ; pass < *totLines; pass++){

        /* loop to control number of comparisons per pass */

        for (i = 0 ; i < *totLines-1; i++){

            if (newArray[i]->dueDate > newArray[i+1]->dueDate) {

                hold = newArray[i];
                newArray[i]   = newArray[i+1];
                newArray[i+1] = hold;
            } // end if
        } // end inner for
    } // end outer for
    printf("\n%5s%-20s%-5s%-21s%-21s\n", "JobID  ", "Customer", "EmpID  ", "Due Date", "Completed Date");
    printf("%5s%-20s%-5s%-21s%-21s\n", "-----", " -------------------- ", "----- ", "------------------- ", "--------------------");
    for (int i = 0; i < *totLines; i++) {
        if(newArray[i]->jobNumber==job_id){
            tot_found++;
            char *dueDateString2 = calloc(20, sizeof(char)); //"Apr 20, 2017 @12:00" + NULL
            char *completedDateString2 = calloc(20, sizeof(char)); //"Thu Apr 20, 2017" + NULL

            time_t dueDateString = newArray[i]->dueDate;
            time_t completedDateString = newArray[i]->completedDate;
            //     time(&completedDateString);

            if( (int)dueDateString==83886080){
                dueDateString2="No date inserted";
            }
            else{
                strftime(dueDateString2, 20, "%b %d, %Y %H:%M", localtime(&dueDateString));

            }
            if((int)completedDateString==83886080){
                completedDateString2="No date inserted";
            }

            else{
                strftime(completedDateString2, 20, "%b %d, %Y %H:%M", localtime(&completedDateString));
            }



            printf("%5d  %-20s%-5d  %-21s%-21s\n", newArray[i]->jobNumber, newArray[i]->customer,
                   newArray[i]->EmployeeNumber, dueDateString2, completedDateString2);

        }
    }
    if(tot_found==0){
        printf("No jobs found with the selected ID!\n");
    }

    continue_enter();

}

/* *****************************************************
 *
 * SEARCH JOBS BY DATE AND TIME DUE ----- MENU 10
 *
 * *****************************************************/

void view_job_information_by_due_date(Job **arrayJobs, int *totLines){
    int tot_found=0; // counter for the tot record found. If 0 display a non found message

    int year_selected=0; // to hold the input for the year to search
    int month_selected=0; // to hold the input for the year to search
    int day_selected=0; // to hold the input for the year to search

    printf("Insert the year :  "); // prompt to insert the year
    scanf("%d",&year_selected);
    while(year_selected<1980) {
        puts("The year inserted is not valid. \nInsert the year "); // prompt to insert the input file name
        scanf(" %d", &year_selected);
    }

    printf("Insert the month :  "); // prompt to insert the year
    scanf("%d",&month_selected);
    while(month_selected>12) {
        puts("The month inserted is not valid. \nInsert the month "); // prompt to insert the input file name
        scanf(" %d", &year_selected);
    }

    int validDay = (month_selected == 2 ?
                    (year_selected % 4 ? 28 : (year_selected % 100 ? 29 : (year_selected % 400 ? 28 : 29))) :
                    ((month_selected - 1) % 7 % 2 ? 30 : 31));

    printf("Insert the day :  "); // prompt to insert the year
    scanf("%d",&day_selected);
    while(day_selected>validDay) {
        puts("The day inserted is not valid. \nInsert the day "); // prompt to insert the input file name
        scanf(" %d", &day_selected);
    }

    // create minimum - day selected 00:00
    struct tm newTimeS;
    newTimeS.tm_year = year_selected - 1900;
    newTimeS.tm_mon = month_selected - 1; //April
    newTimeS.tm_mday = day_selected;
    newTimeS.tm_hour = 00;
    newTimeS.tm_min = 00;

    newTimeS.tm_isdst = -1;
    newTimeS.tm_sec = 0;
    newTimeS.tm_wday = -1;
    newTimeS.tm_yday = -1;

    time_t minDateSelected = mktime(&newTimeS);

    // create maximum - day selected 00:00
    struct tm newTimeS2;
    newTimeS2.tm_year = year_selected - 1900;
    newTimeS2.tm_mon = month_selected - 1; //April
    newTimeS2.tm_mday = day_selected;
    newTimeS2.tm_hour = 23;
    newTimeS2.tm_min = 59;

    newTimeS2.tm_isdst = -1;
    newTimeS2.tm_sec = 0;
    newTimeS2.tm_wday = -1;
    newTimeS2.tm_yday = -1;

    time_t maxDateSelected = mktime(&newTimeS2);


    printf("\n%5s%-20s%-5s%-21s%-21s\n", "JobID  ", "Customer", "EmpID  ", "Due Date", "Completed Date");
    printf("%5s%-20s%-5s%-21s%-21s\n", "-----", " -------------------- ", "----- ", "------------------- ", "--------------------");
    for (int i = 0; i < *totLines; i++) {
        if(arrayJobs[i]->dueDate>=minDateSelected && arrayJobs[i]->dueDate<=maxDateSelected){
            tot_found++;
            char *dueDateString2 = calloc(20, sizeof(char)); //"Apr 20, 2017 @12:00" + NULL
            char *completedDateString2 = calloc(20, sizeof(char)); //"Thu Apr 20, 2017" + NULL

            time_t dueDateString = arrayJobs[i]->dueDate;
            time_t completedDateString = arrayJobs[i]->completedDate;
            //     time(&completedDateString);

            if( (int)dueDateString==83886080){
                dueDateString2="No date inserted";
            }
            else{
                strftime(dueDateString2, 20, "%b %d, %Y %H:%M", localtime(&dueDateString));

            }
            if((int)completedDateString==83886080){
                completedDateString2="No date inserted";
            }

            else{
                strftime(completedDateString2, 20, "%b %d, %Y %H:%M", localtime(&completedDateString));
            }



            printf("%5d  %-20s%-5d  %-21s%-21s\n", arrayJobs[i]->jobNumber, arrayJobs[i]->customer,
                   arrayJobs[i]->EmployeeNumber, dueDateString2, completedDateString2);

        }
    }
    if(tot_found==0){
        printf("No jobs found with the selected due date!\n");
    }

    continue_enter();

}
/* Function 8: sort_job_information_by_customer
 *
 * When the user selects the “sort job information by customer” menu options,
 * this function display all jobs sorted by customer.
 * Store the sorted information and notify the user of the name of the file.
 * Make a copy of the original array of jobs to perform the sorting function.
 * Make sure that the job information is in a report with headers,
 * not simply a list of raw information
 */


/* *****************************************************
 *
 * EXPORT JOB INFORMATION BY CUSTOMER ----- MENU 11
 *
 * *****************************************************/

void sort_job_information_by_customer(Job **arrayJobs, int *totLines2 ){
    int pass=0; // passes counter
    int i=0; //
    int comparison=0;//comparison counter
    Job *hold; //temporary location used to swap array elements
    int linecount = *totLines2;
    Job **newArray;
    newArray = malloc(linecount * sizeof(Job*)); //allocate memory for the new array

    memcpy(newArray, arrayJobs, linecount * sizeof(Job*)); // copy the array

    /* loop to control number of passes */
    for (pass = 1 ; pass < *totLines2; pass++){
        /* loop to control number of comparisons per pass */
        for (i = 0 ; i < *totLines2-1; i++){

            comparison=strcmp(newArray[i]->customer,newArray[i+1]->customer);
            if (comparison>0) {

                hold = newArray[i];
                newArray[i]   = newArray[i+1];
                newArray[i+1] = hold;
            } // end if
        } // end inner for
    } // end outer for


    printf("\n%5s%-20s%-5s%-21s%-21s\n", "JobID  ", "Customer", "EmpID  ", "Due Date", "Completed Date");
    printf("%5s%-20s%-5s%-21s%-21s\n", "-----", " -------------------- ", "----- ", "------------------- ", "--------------------");


    for (int i = 0; i < *totLines2; i++) {
        char *dueDateString2 = calloc(20, sizeof(char)); //"Apr 20, 2017 @12:00" + NULL
        char *completedDateString2 = calloc(20, sizeof(char)); //"Thu Apr 20, 2017" + NULL

        time_t dueDateString = newArray[i]->dueDate;
        time_t completedDateString = newArray[i]->completedDate;
        //     time(&completedDateString);

        if( (int)dueDateString==83886080){
            dueDateString2="No date inserted";
        }
        else{
            strftime(dueDateString2, 20, "%b %d, %Y %H:%M", localtime(&dueDateString));

        }
        if((int)completedDateString==83886080){
            completedDateString2="No date inserted";
        }

        else{
            strftime(completedDateString2, 20, "%b %d, %Y %H:%M", localtime(&completedDateString));
        }



        printf("%5d  %-20s%-5d  %-21s%-21s\n", newArray[i]->jobNumber, newArray[i]->customer,
               newArray[i]->EmployeeNumber, dueDateString2, completedDateString2);

    }
    FILE *f3 = fopen("SortedJobsByCustomer.txt", "w");
    if (f3 == NULL)
    {
        printf("Error opening file!\n");
        printf("The file doesn't exist. Creating it..");
        f3 = fopen("SortedJobsByCustomer.txt", "wb");
    }

    for (int i = 0; i < linecount;i++) {
        fprintf(f3, "%d %d %s %li %li", newArray[i]->EmployeeNumber, newArray[i]->jobNumber, newArray[i]->customer, newArray[i]->dueDate, newArray[i]->completedDate);
        fprintf(f3, "\r\n");
    }
    puts("\nData sorted and saved in SortedJobsByCustomer.txt");
    fclose(f3); // closing file
    continue_enter();
}

/* *****************************************************
 *
 * EXPORT JOB INFORMATION BY DATE AND TIME DUE ----- MENU 12
 *
 * *****************************************************/
void sort_job_information_by_date_time_due(Job **arrayJobs, int *totLines2) {
    int pass=0; // passes counter
    int i=0; //

    Job *hold; //temporary location used to swap array elements
    int linecount = *totLines2;
    Job **newArray;
    newArray = malloc(linecount * sizeof(Job*)); //allocate memory for the new array

    memcpy(newArray, arrayJobs, linecount * sizeof(Job*)); // copy the array

    /* loop to control number of passes */
    for (pass = 1 ; pass < *totLines2; pass++) {
        /* loop to control number of comparisons per pass */
        for (i = 0; i < *totLines2 - 1; i++) {

            if (newArray[i]->dueDate > newArray[i + 1]->dueDate) {
                {

                    hold = newArray[i];
                    newArray[i] = newArray[i + 1];
                    newArray[i + 1] = hold;
                } // end if
            } // end inner for
        } // end outer for

    }
        printf("\n%5s%-20s%-5s%-21s%-21s\n", "JobID  ", "Customer", "EmpID  ", "Due Date", "Completed Date");
        printf("%5s%-20s%-5s%-21s%-21s\n", "-----", " -------------------- ", "----- ", "------------------- ",
               "--------------------");


        for (int i = 0; i < *totLines2; i++) {
            char *dueDateString2 = calloc(20, sizeof(char)); //"Apr 20, 2017 @12:00" + NULL
            char *completedDateString2 = calloc(20, sizeof(char)); //"Thu Apr 20, 2017" + NULL

            time_t dueDateString = newArray[i]->dueDate;
            time_t completedDateString = newArray[i]->completedDate;
            //     time(&completedDateString);

            if ((int) dueDateString == 83886080) {
                dueDateString2 = "No date inserted";
            } else {
                strftime(dueDateString2, 20, "%b %d, %Y %H:%M", localtime(&dueDateString));

            }
            if ((int) completedDateString == 83886080) {
                completedDateString2 = "No date inserted";
            } else {
                strftime(completedDateString2, 20, "%b %d, %Y %H:%M", localtime(&completedDateString));
            }


            printf("%5d  %-20s%-5d  %-21s%-21s\n", newArray[i]->jobNumber, newArray[i]->customer,
                   newArray[i]->EmployeeNumber, dueDateString2, completedDateString2);

        }
        FILE *f3 = fopen("SortedJobsByDueDate.txt", "w");
        if (f3 == NULL) {
            printf("Error opening file!\n");
            printf("The file doesn't exist. Creating it..");
            f3 = fopen("SortedJobsByDueDate.txt", "wb");
        }

        for (int i = 0; i < linecount; i++) {
            fprintf(f3, "%d %d %s %li %li", newArray[i]->EmployeeNumber, newArray[i]->jobNumber, newArray[i]->customer,
                    newArray[i]->dueDate, newArray[i]->completedDate);
            fprintf(f3, "\r\n");
        }
        puts("\nData sorted and saved in SortedJobsByDueDate.txt");
        fclose(f3); // closing file

    continue_enter();
    }


/* *****************************************************
 *
 * SET JOB AS COMPLETED ----- MENU 13
 *
 * *****************************************************/
void set_job_as_completed(Job **arrayJobs, int *totLines2){
    int tot_found=0; // counter for the tot record found. If 0 display a non found message
    int job_id;
    printf("Insert the job ID :  "); // prompt to insert the input file name
    scanf("%d",&job_id);

    // loop through the job array
    for (int i = 0; i < *totLines2; i++) {
        if (arrayJobs[i]->jobNumber == job_id) {                                // if it matches the job ID entered
            tot_found++;                                                        //increase the counter
            arrayJobs[i]->completedDate = time(NULL);

            printf("\n[%d]: %d", (i + 1), arrayJobs[i]->EmployeeNumber);
            printf(" %d", arrayJobs[i]->jobNumber);
            printf(" %s", arrayJobs[i]->customer);

            time_t dueDateString = arrayJobs[i]->dueDate;
            //    time(&dueDateString);

            time_t completedDateString = arrayJobs[i]->completedDate;
            //     time(&completedDateString);
            if (dueDateString != 0 && dueDateString != NULL) {
                printf(" %s", ctime(&dueDateString));
            } else { printf("No due date entered!"); }
            if (completedDateString != 0 && completedDateString != NULL) {
                printf(" %s", ctime(&completedDateString));
            } else { printf("No completed date entered!"); }

        }
    } //end for loop
    if(tot_found==0){printf("The job ID selected doesn't exist\n");} //print error message if the job ID is not found

    continue_enter();
}

/* *****************************************************
 *
 * SAVE DATA (AND EXIT) ----- MENU 14
 *
 * *****************************************************/
/* Function 11: save_data
 *
 * This function is called when the user chooses to exit the system.
 * Open all data files and write out the information contained in the respective arrays.
 */
void save_data(Employee **arrayEmployees, int *totLines, Job **arrayJobs, int *totLines2 ){

    FILE *f = fopen("employeeFile.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < *totLines; i++) {
        fprintf(f, "%d %s %s", arrayEmployees[i]->Number, arrayEmployees[i]->firstName, arrayEmployees[i]->lastName);
        fprintf(f, "\r\n");
    }
    fclose(f); // closing file
    FILE *f2 = fopen("jobFile.txt", "w");
    if (f2 == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < *totLines2; i++) {
        fprintf(f2, "%d %d %s %li %li", arrayJobs[i]->EmployeeNumber, arrayJobs[i]->jobNumber, arrayJobs[i]->customer, arrayJobs[i]->dueDate, arrayJobs[i]->completedDate);
        fprintf(f2, "\r\n");
    }

    fclose(f2); //closing file
    printf("File saved!\n");
    exit(1);
}


/*////////////////////////////////////////////////////////////            //////////////////////////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////// UTILITIES  //////////////////////////////////////////////////////////////////////////////////*/
/*////////////////////////////////////////////////////////////            //////////////////////////////////////////////////////////////////////////////////*/
// ask the user to press enter to continue

void continue_enter(){
    printf("\n\nPress [Enter] to continue.\n");
    while(getchar()!='\n'); // option TWO to clean stdin
    getchar(); // wait for ENTER
}