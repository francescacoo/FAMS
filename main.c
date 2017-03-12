#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// structs
typedef struct
{
    int Number;     //employee number
    char* firstName;//first name
    char* lastName; //last name
}Employee;

typedef struct
{
    int EmployeeNumber;     //employee number
    int jobNumber;          //job number
    char* customer;         //customer
    time_t dueDate;         //The job due date
    time_t completedDate;  //The job's actual completion date
}Job;

// FUNCTION prototypes
int display_menu();

Employee** load_data_employee(char* filename, int *totLines);
Job** load_data_job(char* filename, int *totLines2);
void** load_data(int *totLines3,int *totLines4);

void add_new_employee(Employee **arrayEmployees, int *totLines );
void add_new_job(void** arrayData, int *totLines2, int *totLinesEmployees);
// EMPLOYEES FUNCTIONS
void view_employee(Employee **arrayEmployees, int *totLines );
void view_employee_by_name(Employee **arrayEmployees, int *totLines);
void sort_employee(Employee **arrayEmployees, int *totLines );
void sort_employee_by_id(Employee **arrayEmployees, int *totLines );
//JOBS FUNCTIONS
void sort_job_information_by_customer(void** arrayData, int *totLines2, int *totLines1 );
void sort_job_information_by_date_time_due(void** arrayData, int *totLines2, int *totLinesEmployees );
void view_job_information_customer(void** arrayData, int *totLines2, int *totLinesEmployees );
void view_job_information_by_id(void** arrayData, int *totLines2, int *totLinesEmployees );
void view_job_information_by_employee(void** arrayData, int *totLines2, int *totLinesEmployees );
void view_job_information_by_due_date(void** arrayData, int *totLines2, int *totLinesEmployees );
void set_job_as_completed(void** arrayData, int *totLines2, int *totLinesEmployees);

void save_data(Employee **arrayEmployees, int *totLines, Job **arrayJobs, int *totLines2 );

// UTILITIES
char* employee_name(Employee** arrayEmployees, int *totLines, int empNumber);
void continue_enter();
Employee** sort_employees(Employee** arrayToSort,int totLines,char* fieldToSort );
Job** sort_jobs(Job** arrayToSort,int totLines,char* fieldToSort );
void print_jobs(int jobNumber, char* customer, char* EmployeeName, time_t dueDate, time_t completedDate);
void print_jobs_header();
void print_jobs_file(int jobNumber, char* customer, char* EmployeeName, time_t dueDate, time_t completedDate, FILE *f3);
char* convert_date(time_t dateToConvert);

int main() {
    int chosenOption = 0;           // define and reset the chosenOption from the menu
    Employee **arrayEmployees;      // Array of employees
    Job **arrayJobs;                // Array of jobs //
    void** arrayData;               // Array containing arrayEmployees and arrayJobs
    int totLinesEmployees;          // Total number of lines in arrayEmployees
    int totLinesJobs;               // Total number of lines in arrayJobs

    arrayData=load_data(&totLinesEmployees,&totLinesJobs); // call the function to load the data for the arrays and store the result
    arrayEmployees=arrayData[1];    // array of employees
    arrayJobs=arrayData[0];         // array of jobs

    chosenOption = display_menu();  // call the function to display the menu and store the chose option

    // loop until the user select to exit
    while (chosenOption!=14) {

        switch(chosenOption){
            case 1:
                add_new_employee(arrayEmployees, &totLinesEmployees ); //Add an Employee
                break;
            case 2:
                add_new_job(arrayData, &totLinesJobs, &totLinesEmployees);// Add a job
                break;
            case 3:
                view_employee(arrayEmployees, &totLinesEmployees); //View all employees information
                break;
            case 4:
                view_employee_by_name(arrayEmployees, &totLinesEmployees); //view all employees sorted by name
                break;
            case 5:
                sort_employee(arrayEmployees, &totLinesEmployees); //Sort employees by name and export to external file
                break;
            case 6:
                sort_employee_by_id(arrayEmployees, &totLinesEmployees); //Sort employees by ID and export to external file
                break;
            case 7:
                view_job_information_customer(arrayData, &totLinesJobs, &totLinesEmployees);    // view all jobs sorted customore
                break;
            case 8:
                view_job_information_by_employee(arrayData, &totLinesJobs, &totLinesEmployees); // search jobs of a selected employee
                break;
            case 9:
                view_job_information_by_id(arrayData, &totLinesJobs, &totLinesEmployees);   //search a job by id
                break;
            case 10:
                view_job_information_by_due_date(arrayData, &totLinesJobs, &totLinesEmployees); // search jobs due at a selected date
                break;
            case 11:
                sort_job_information_by_customer(arrayData, &totLinesJobs, &totLinesEmployees); // sort jobs by customer and export them to an external file
                break;
            case 12:
                sort_job_information_by_date_time_due(arrayData, &totLinesJobs, &totLinesEmployees);    // sort jobs by due date and export them to an external file
                break;
            case 13:
                set_job_as_completed(arrayData, &totLinesJobs, &totLinesEmployees); // set a job as completed
                break;
            default:
                break;
        }
        chosenOption = display_menu();  //  display the menu
    }
    // if the user selects exits
    if(chosenOption==14){
        save_data( arrayEmployees,  &totLinesEmployees,  arrayJobs,  &totLinesJobs ); //call the save data function passing the two arrays
    }
    return 0;
}

// (EXAM Function 1:  display_menu)
//
// return integer of the chosen option
int display_menu() {
    int chosenOption = 0;
    puts("\n#################");
    puts("###    Menu   ###");
    puts("#################\n");
    //loop until a valid selection is made
    while (chosenOption == 0) {

        puts("1. Add an Employee");
        puts("2. Add a job");
        puts("#####EMPLOYEES######");

        puts("3. View all employees information");
        puts("4. View all employees sorted by name");

        puts("5. Export employees sorted by name");
        puts("6. Export employees by id");

        puts("#####JOBS######");
        puts("7. View all jobs sorted by customer");
        puts("8. View jobs sorted by employee");

        puts("9. Search a job by id");
        puts("10. Search jobs by date and time due");

        puts("11. Export job information by customer");
        puts("12. Export job information by date and time due");

        puts("13. Set job as completed");

        puts("14. Exit");
        printf("Please select an option:  "); // prompt to select an option
        scanf("%d", &chosenOption);

        if (chosenOption > 14) {
            puts("The number selected is not valid.");
            chosenOption = 0;
        }

        printf("You selected option: %d\n", chosenOption);

    }
    return chosenOption;
}

//
/* (EXAM Function 2:  load_data)
 * + subfunctions load_data_employee and  load_data_job
 */

void** load_data(int *totLines3, int *totLines4) {
    *totLines3=0; // reset
    *totLines4=0; // reset
    void **mydata = NULL;   // array of pointers
    int totLines;         /* Total number of read lines */
    int totLines2;         /* Total number of read lines */
    mydata = calloc(2, sizeof(void*)); // initialize the array of pointers
    mydata[1]=load_data_employee("employeeFile.txt", &totLines);    // call the function to load the employees
    mydata[0]=load_data_job("jobFile.txt", &totLines2);             // call the function to load the jobs
    *totLines3=totLines;    //set the output value for the number of lines arrayEmployees
    *totLines4=totLines2;   // set the output value for the number of lines arrayEmployees
    return mydata;          // return the array of pointers
}


Employee** load_data_employee(char *filename, int *totLines) {

    puts("Employee load data started..");
    FILE *employeeFile; // Input file

    //if the file doesn’t exist:
    if ((employeeFile = fopen(filename, "r")) == NULL) {
        printf("The file doesn't exist. Creating it..");
        employeeFile = fopen(filename, "wb"); //create the file
    }

    Employee** array=NULL;  // array of pointers
    int i;                   /* Loop counter */
    char line[100];           /* Buffer to read each line */
    int line_count;          /* counter for the number of lines */
    char temp[200];         // buffer to hold the strings
    // Clear the output parameter for the number of lines */
    *totLines = 0;

    // Get the count of lines in the file
    line_count = 0;
    while (fgets(line, sizeof(line), employeeFile) != NULL) {
        line_count++;
    }

    // Move to the beginning of the file.
    rewind(employeeFile);

    // allocate memory for the Employee pointers
    array = malloc(line_count * sizeof(Employee*));

    if (array == NULL) {
        // return NULL; /* Error */
    }

    // Read each line from the file and copy it in the array.
    for (i = 0; i < line_count; i++) {
        //allocate memory
        array[i] = malloc(sizeof(Employee));

        fscanf(employeeFile, "%s", temp); //Employee Number
        array[i]->Number = (int) strtol(temp, (char **)NULL, 10); // convert the char to integer and store it in the array

        fscanf(employeeFile, "%s", temp); //Employee first Name
        array[i]->firstName = calloc(strlen(temp) + 1, sizeof(char)); // allocate memory for the char
        strcpy(array[i]->firstName, temp);  // copy the string to the array

        fscanf(employeeFile, "%s", temp); //Employee Last Name
        array[i]->lastName = calloc(strlen(temp) + 1, sizeof(char));
        strcpy(array[i]->lastName, temp);
    }

    // Update the output parameter with the total number of lines
    *totLines = line_count;
    fclose(employeeFile); // closing the file
    /* Return the array of employees */
    return array;
}


Job** load_data_job(char *filename, int *totLines2) {

    printf("\n Job load data started..");
    FILE *jobFile; // Input file

//if the file doesn’t exist:
    if ((jobFile = fopen(filename, "r")) == NULL) {
        printf("The file doesn't exist. Creating it..");
        jobFile = fopen(filename, "wb"); // create the file
    }

    Job** array = NULL;       // array of Job (struct) pointers
    int i;                    // Loop counter
    char line[100];           // Buffer to read each line
    int line_count;           // Total number of lines
    char temp[200];
    // Clear the output parameter for the number of lines */
    *totLines2 = 0;

    // Get the count of lines in the file
    line_count = 0;
    while (fgets(line, sizeof(line), jobFile) != NULL) {
        line_count++;
    }

    // Move to the beginning of the file.
    rewind(jobFile);
    // allocate memory for the Job pointers
    array = malloc(line_count * sizeof(Job*));

    if (array == NULL) {
        // return NULL; /* Error */
    }

    // Read each line from the file and copy it in the array.
    for (i = 0; i < line_count; i++) {
        //allocate memory
        array[i] = malloc(sizeof(Job));

        fscanf(jobFile, "%s", temp); //Employee Number
        array[i]->EmployeeNumber = (int) strtol(temp, (char **)NULL, 10);// convert the char to integer and store it in the array

        fscanf(jobFile, "%s", temp); //Job Number
        array[i]->jobNumber = (int) strtol(temp, (char **)NULL, 10);    // convert the char to integer and store it in the array

        fscanf(jobFile, "%s", temp); //customer
        array[i]->customer = calloc(strlen(temp) + 1, sizeof(char)); //allocate memory for the char
        strcpy(array[i]->customer, temp); //copy the string to the array

        //Get the Due Date and store it in the data structure
        fscanf(jobFile, "%s", temp); //Due Date
        array[i]->dueDate = (time_t)strtoull(temp, NULL, 10);

        //Get the Completion Date and store in the data structure
        fscanf(jobFile, "%s", temp); //Completed Date
        array[i]->completedDate = (time_t)strtoull(temp, NULL, 10);
    }

    // Update the output parameter with the total number of lines
    *totLines2 = line_count;
    fclose(jobFile); //closing the file
    /* Return the array of job pointers */
    return array;

}

/*/////////////////////////////////////////////ADD EMPLOYEES AND ADD JOBS /////////////////////////////////////////////////////////*/

/*
 *(EXAM Function 3:  add_new_employee)
 */
void add_new_employee(Employee **arrayEmployees, int *totLines ){

    int newtot=*totLines+1; // new line total
    arrayEmployees=realloc(arrayEmployees,newtot* sizeof(Employee*)); // reallocate memory for the array with one more Employee

    char firstName[20];//
    char lastName[20];//

    printf("Insert the employee first name :  ");
    scanf("%s",firstName);
    printf("Insert the employee last name :  ");
    scanf("%s",lastName);

    arrayEmployees[*totLines] = malloc(sizeof(Employee)); //allocate memory

    arrayEmployees[*totLines]->Number = newtot; // set the array max index as Employee Number

    arrayEmployees[*totLines]->firstName = calloc(strlen(firstName) + 1, sizeof(char)); // allocate memory for the char
    strcpy(arrayEmployees[*totLines]->firstName, firstName);

    arrayEmployees[*totLines]->lastName = calloc(strlen(lastName) + 1, sizeof(char));   // allocate memory for the char
    strcpy(arrayEmployees[*totLines]->lastName, lastName);

    *totLines=newtot; //update the total of Employees

    // notify the user that the employee has been added
    printf("The new employee has been added:\n");
    printf("\n[%d]: %d", (newtot), arrayEmployees[newtot-1]->Number);
    printf("  %s", arrayEmployees[newtot-1]->firstName);
    printf(" %s", arrayEmployees[newtot-1]->lastName);

    continue_enter();
}


/* (EXAM Function 4:  add_new_job)
 *
 */


void add_new_job(void** arrayData, int *totLines2, int *totLinesEmployees) {
    Employee **arrayEmployees=arrayData[1];
    Job **arrayJobs=arrayData[0];
    int EmployeeNumber;//employee number
    char *customer[25];
    int day, month, year, minute, hour; // to hold the date inserted by the user
    time_t dueDate;         //The job due date
    char* EmployeeName;


    int newtot=*totLines2+1;
    arrayJobs=realloc(arrayJobs,newtot* sizeof(Job*)); //reallocate memory for the array with one more Job

    // calculate the current time
    struct tm *current;
    time_t timenow;
    time(&timenow); //the current time in seconds
    current = localtime(&timenow); // to fill the tm structure1
    int currentmonth = current->tm_mon+1;
    int currentday = current->tm_mday;
    int currentyear = current->tm_year+1900;
    int currenthour = current->tm_hour;
    int currentminute = current->tm_min;

    // collect input from the user
    printf("Insert the employee number :  ");
    scanf("%d",&EmployeeNumber);
    printf("Insert the customer :  ");
    scanf("%s",&customer);
    puts("Insert the due date ");

    printf("Insert the year: ");
    scanf(" %d", &year);
    // check that the due year is not less than current year
    while(year<currentyear) {
        puts("The year inserted is not valid. \nInsert the year ");
        scanf(" %d", &year);
    }

    printf("Insert the month "); // prompt to insert the month
    scanf(" %d", &month);
    // check that the due month is valid and if the year is the current, that is not less than current month
    while(month>12 || (month<currentmonth && year==currentyear)) {
        puts("The month inserted is not valid. \nInsert the month "); // prompt to insert the input file name
        scanf(" %d", &month);
    }
    // check how many days the selected month has
    int validDay = (month == 2 ?
                    (year % 4 ? 28 : (year % 100 ? 29 : (year % 400 ? 28 : 29))) :
                    ((month - 1) % 7 % 2 ? 30 : 31));

    printf("Insert the day ");
    scanf(" %d", &day);
    // check that the month is valid and, if month and year and the current, that the day is not less than current
    while(day>validDay || (day<currentday && month==currentmonth && year==currentyear)) {
        puts("The day inserted is not valid. \nInsert the day "); // prompt to insert the input file name
        scanf(" %d", &day);
    }

    printf("Insert the hour ");
    scanf(" %d", &hour);

    // check that the hour is correct and not less than today hour
    while(hour>23 || (hour<currenthour && day==currentday && month==currentmonth && year==currentyear)) {
        puts("The hour inserted is not valid. \nInsert the hour "); // prompt to insert the input file name
        scanf(" %d", &hour);
    }
    puts("Insert the minute ");
    scanf(" %d", &minute);
    // check that the minute is correct and not less than current time
    while(minute>59 || (minute<currentminute && hour==currenthour && day==currentday && month==currentmonth && year==currentyear)) {
        puts("The hour inserted is not valid. \nInsert the minute "); // prompt to insert the day
        scanf(" %d", &minute);
    }

    //create the new struct with the inserted time
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
    // convert to time_t
    dueDate = mktime(&newTimeS);

    // copy values in the job array
    arrayJobs[*totLines2] = malloc(sizeof(Job));

    arrayJobs[*totLines2]->EmployeeNumber = EmployeeNumber;
    arrayJobs[*totLines2]->jobNumber = newtot; // set the job number as the new max array index

    arrayJobs[*totLines2]->customer = calloc(strlen(customer) + 1, sizeof(char)); // allocate memory for the string
    strcpy(arrayJobs[*totLines2]->customer, customer);

    arrayJobs[*totLines2]->dueDate = dueDate;

    // confirm that the job has been added and print the details, converting date to human readable
    EmployeeName=employee_name(arrayEmployees, totLinesEmployees, arrayJobs[*totLines2]->EmployeeNumber);
    print_jobs(arrayJobs[*totLines2]->jobNumber, arrayJobs[*totLines2]->customer, EmployeeName, arrayJobs[*totLines2]->dueDate, arrayJobs[*totLines2]->completedDate);

    *totLines2=newtot;

    continue_enter();
}

/*////////////////////////////////////////////////////////////            //////////////////////////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////// EMPLOYEES  //////////////////////////////////////////////////////////////////////////////////*/
/*////////////////////////////////////////////////////////////            //////////////////////////////////////////////////////////////////////////////////*/

/*
 *(EXAM Function 5:  view_employee)
 * View all employees unsorted
 */

void view_employee(Employee **arrayEmployees, int *totLines){
    // print the header
    printf("%s\n", "#### ALL EMPLOYEES ####");
    printf("%5s   %-15s   %-15s\r\n", "Number", "Name","Surname");
    printf("%5s   %-15s   %-15s\r\n", "------", "-------------", "--------------");
    // loop through the unsorted array
    for (int i = 0; i < *totLines; i++) {
        printf("%6d   %-15s   %-15s\r\n", arrayEmployees[i]->Number,arrayEmployees[i]->firstName,arrayEmployees[i]->lastName);
    }
    continue_enter();
}
/*
 * View all employees sorted by name
 */
void view_employee_by_name(Employee **arrayEmployees, int *totLines) {

    int linecount= *totLines;
    Employee **newArray;    // new array of Employees pointers
    newArray = malloc(linecount * sizeof(Employee*)); //allocate memory for the array

    memcpy(newArray, arrayEmployees, linecount * sizeof(Employee*)); // copy the employeesArray to the new array

    newArray=sort_employees(newArray,linecount,"LastName" ); // call the sorting function passing the new array, lines count and parameter to sort on

    // print headers
    printf("%s\n", "#### ALL EMPLOYEES SORTED BY NAME ####");
    printf("%5s   %-15s   %-15s\r\n", "Number", "Name","Surname");
    printf("%5s   %-15s   %-15s\r\n", "------", "-------------", "--------------");

    // print the sorted array
    for (int i = 0; i < *totLines; i++) {
        printf("%6d   %-15s   %-15s\r\n", newArray[i]->Number,newArray[i]->firstName,newArray[i]->lastName);
    }
    continue_enter();
}

/*
 * (EXAM Function 6:  view_employee)
 * Sort the employees by name, display them and save in an external file
 *
 */
void sort_employee(Employee **arrayEmployees, int *totLines ){

    int linecount= *totLines;
    Employee **newArray; // new array of Employee pointers
    newArray = malloc(linecount * sizeof(Employee*)); // allocate memory for the new array

    memcpy(newArray, arrayEmployees, linecount * sizeof(Employee*)); // copy the array
    newArray=sort_employees(newArray,linecount,"LastName" ); // call the sorting function passing the new array, lines count and parameter to sort on

    // print the header
    printf("%s\n", "#### ALL EMPLOYEES SORTED BY NAME ####");
    printf("%5s   %-15s   %-15s\r\n", "Number", "Name","Surname");
    printf("%5s   %-15s   %-15s\r\n", "------", "-------------", "--------------");

    // print the sorted array
    for (int i = 0; i < *totLines; i++) {
        printf("%6d   %-15s   %-15s\n", newArray[i]->Number,newArray[i]->firstName,newArray[i]->lastName);
    }

    //try to open the report file - if it doesn't exist create it
    FILE *f3 = fopen("SortedEmployeeFile.txt", "w");
    if (f3 == NULL) {
        printf("The file doesn't exist. Creating it..");
        f3 = fopen("SortedEmployeeFile.txt", "wb");
    }
    // set the header in the report file
    fprintf(f3,"%s\n", "#### ALL EMPLOYEES SORTED BY NAME ####\r\n");
    fprintf(f3,"%5s   %-15s   %-15s\r\n", "Number", "Name","Surname");
    fprintf(f3,"%5s   %-15s   %-15s\r\n", "------", "-------------", "--------------");
    // save the sorted array to the file
    for (int l = 0; l < linecount; l++) {
        fprintf(f3, "%6d   %-15s   %-15s", newArray[l]->Number, newArray[l]->firstName, newArray[l]->lastName);
        fprintf(f3, "\r\n");
    }
    puts("\nData sorted and saved in SortedEmployeeFile.txt");
    fclose(f3); // closing file

    continue_enter();
}

/*/* *****************************************************
 *
 * Sort the employees by id, display them and save in an external file
 *
 * *****************************************************/

void sort_employee_by_id(Employee **arrayEmployees, int *totLines ){

    int linecount;
    linecount = *totLines;
    Employee **newArray; // new array of Employee pointers
    newArray = malloc(linecount * sizeof(Employee*)); // allocate memory for the new array

    memcpy(newArray, arrayEmployees, linecount * sizeof(Employee*)); // copy the array
    newArray=sort_employees(newArray,linecount,"Number" ); // call the sorting function passing the new array, lines count and parameter to sort on


    // print the header
    printf("%s\n", "#### ALL EMPLOYEES SORTED BY ID ####\r\n");
    printf("%5s   %-15s   %-15s\r\n", "Number", "Name","Surname");
    printf("%5s   %-15s   %-15s\r\n", "------", "-------------", "--------------");

    for (int i = 0; i < *totLines; i++) {
        printf("%6d   %-15s   %-15s\r\n", newArray[i]->Number,newArray[i]->firstName,newArray[i]->lastName);
    }

    //try to open the report file - if it doesn't exist create it
    FILE *f3 = fopen("SortedEmployeeByIDFile.txt", "w");
    if (f3 == NULL)
    {
        printf("The file doesn't exist. Creating it..");
        f3 = fopen("SortedEmployeeByIDFile.txt", "wb");
    }
    // Print the header
    fprintf(f3,"\n%5s%-20s%-25s%-21s%-21s\r\n", "JobID  ", "Customer", "Employee  ", "Due Date", "Completed Date");
    fprintf(f3,"%5s%-20s%-25s%-21s%-21s\r\n", "-----", " -------------------- ", "------------------------ ", "------------------- ", "--------------------");

    // save the sorted array to the file
    for (int l = 0; l < linecount; l++) {
        fprintf(f3, "%6d   %-15s   %-15s", newArray[l]->Number, newArray[l]->firstName, newArray[l]->lastName);
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
 * VIEW ALL JOBS SORTED BY CUSTOMER ----- MENU 7
 *
 * *****************************************************/
/*
 * (EXAM Function 8:  sort_job_information_by_customer)
 * Display all jobs sorted by customer
 *
 */
void view_job_information_customer(void** arrayData, int *totLines, int *totLinesEmployees) {
    Employee **arrayEmployees=arrayData[1];
    Job **arrayJobs=arrayData[0];
    int linecount= *totLines; // tot number of jobs
    char* EmployeeName;
    Job **newArray; // new array of Job pointers
    newArray = malloc(linecount * sizeof(Employee *)); // allocate memory for the new array

    memcpy(newArray, arrayJobs, linecount * sizeof(Job *));  // copy the array

    newArray=sort_jobs(newArray,linecount,"customer" ); // call the sorting function passing the new array, lines count and parameter to sort on

    printf("sorted");
    print_jobs_header();
    // loop through the array and print all
    for (int i = 0; i < linecount; i++) {
        // get the employee name
        EmployeeName=employee_name(arrayEmployees, totLinesEmployees, newArray[i]->EmployeeNumber);
        // print the job details
        print_jobs(newArray[i]->jobNumber, newArray[i]->customer, EmployeeName, newArray[i]->dueDate, newArray[i]->completedDate);
    }
    continue_enter();
}

/* *****************************************************
 *
 * VIEW JOBS OF ORDERED BY EMPLOYEE ----- MENU 8
 * (Exam function 10: view_job_information_by_employee)
 *
 * *****************************************************/

void view_job_information_by_employee(void** arrayData, int *totLines, int *totLineEmployees){
    Employee **arrayEmployees=arrayData[1];
    Job **arrayJobs=arrayData[0];
    char* EmployeeName;
    int linecount = *totLines;
    Job **newArray; // new array of Job pointers
    newArray = malloc(linecount * sizeof(Job*)); // allocate memory for the new array

    memcpy(newArray, arrayJobs, linecount * sizeof(Job*)); // copy the array

    newArray=sort_jobs(newArray,linecount,"EmployeeNumber" ); // call the sorting function passing the new array, lines count and parameter to sort on

    print_jobs_header();
    for (int i = 0; i < linecount; i++) {
        // get the employee name
        EmployeeName=employee_name(arrayEmployees, totLineEmployees, newArray[i]->EmployeeNumber);
        // print the job details
        print_jobs(newArray[i]->jobNumber, newArray[i]->customer, EmployeeName, newArray[i]->dueDate, newArray[i]->completedDate);
    }

    continue_enter();
}

/* *****************************************************
 *
 * SEARCH A JOB BY ID ----- MENU 9
 * (Exam function 7: Function 7: view_job_information_time_due)
 * The function prompts for a job number and display the information
 *
 * *****************************************************/

void view_job_information_by_id(void** arrayData, int *totLines, int *totLineEmployees){
    Employee **arrayEmployees=arrayData[1];
    Job **arrayJobs=arrayData[0];
    char* EmployeeName;
    int tot_found=0; // counter for the tot record found. If 0 display a non found message
    int job_id;
    printf("Insert the job ID :  "); // prompt to insert the job id
    scanf("%d",&job_id);
    // Print the header
    print_jobs_header();
    // loop through the array
    for (int i = 0; i < *totLines; i++) {
        // if the id is found print the details of the job
        if(arrayJobs[i]->jobNumber==job_id){
            tot_found++; // increase tot found counter
            // get employee name
            EmployeeName=employee_name(arrayEmployees, totLineEmployees, arrayJobs[i]->EmployeeNumber);
            // print job details
            print_jobs(arrayJobs[i]->jobNumber, arrayJobs[i]->customer, EmployeeName, arrayJobs[i]->dueDate, arrayJobs[i]->completedDate);
        }
    }
    // if no jobs found print the error
    if(tot_found==0){
        printf("No jobs found with the selected ID!\n");
    }
    continue_enter();
}

/* *****************************************************
 *
 * SEARCH JOBS BY DATE AND TIME DUE ----- MENU 10
 *
 * Prompt the user for a date and show the jobs due in that day
 * *****************************************************/

void view_job_information_by_due_date(void** arrayData, int *totLines, int *totLineEmployees){
    Employee **arrayEmployees=arrayData[1];
    Job **arrayJobs=arrayData[0];
    char* EmployeeName;
    int tot_found=0; // counter for the tot record found. If 0 display a non found message

    int year_selected=0; // to hold the input for the year to search
    int month_selected=0; // to hold the input for the month to search
    int day_selected=0; // to hold the input for the day to search

    printf("Insert the year :  "); // prompt to insert the year
    scanf("%d",&year_selected);
    while(year_selected<1980) {
        puts("The year inserted is not valid. \nInsert the year ");
        scanf(" %d", &year_selected);
    }

    printf("Insert the month :  "); // prompt to insert the month
    scanf("%d",&month_selected);
    while(month_selected>12) {
        puts("The month inserted is not valid. \nInsert the month ");
        scanf(" %d", &year_selected);
    }
    // check the valid days for the selected month
    int validDay = (month_selected == 2 ?
                    (year_selected % 4 ? 28 : (year_selected % 100 ? 29 : (year_selected % 400 ? 28 : 29))) :
                    ((month_selected - 1) % 7 % 2 ? 30 : 31));

    printf("Insert the day :  "); // prompt to insert the day
    scanf("%d",&day_selected);
    while(day_selected>validDay) {
        puts("The day inserted is not valid. \nInsert the day "); // prompt to insert the input file name
        scanf(" %d", &day_selected);
    }

    // create minimum time - day selected 00:00
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

    // create maximum time - day selected 00:00
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

    // Print the header
    print_jobs_header();
    // loop the array
    for (int i = 0; i < *totLines; i++) {
        // if the due date is between the minimum and maximum print the details
        if(arrayJobs[i]->dueDate>=minDateSelected && arrayJobs[i]->dueDate<=maxDateSelected){
            tot_found++;
            // get the employee name
            EmployeeName=employee_name(arrayEmployees, totLineEmployees, arrayJobs[i]->EmployeeNumber);
            // print the job details
            print_jobs(arrayJobs[i]->jobNumber, arrayJobs[i]->customer, EmployeeName, arrayJobs[i]->dueDate, arrayJobs[i]->completedDate);
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
 * (Exam function 8: sort_job_information_by_customer)
 *
 *
 * *****************************************************/

void sort_job_information_by_customer(void** arrayData, int *totLines2, int *totLineEmployees ){
    Employee **arrayEmployees=arrayData[1];
    Job **arrayJobs=arrayData[0];
    char* EmployeeName;
    int linecount = *totLines2;
    Job **newArray; //new array of Job pointers
    newArray = malloc(linecount * sizeof(Job*)); //allocate memory for the new array

    memcpy(newArray, arrayJobs, linecount * sizeof(Job*)); // copy the array

    newArray=sort_jobs(newArray,linecount,"customer" ); // call the sorting function passing the new array, lines count and parameter to sort on

    print_jobs_header(); // print the header
    //loop through the sorted array and call the print function to print the records
    for (int i = 0; i < linecount; i++) {
        // get the employee name
        EmployeeName=employee_name(arrayEmployees, totLineEmployees, newArray[i]->EmployeeNumber);
        // print the job details
        print_jobs(newArray[i]->jobNumber, newArray[i]->customer, EmployeeName, newArray[i]->dueDate, newArray[i]->completedDate);
    }
    // open destination file for writing, if it doesn't exist create it
    FILE *f3 = fopen("SortedJobsByCustomer.txt", "w");
    if (f3 == NULL) {
        printf("Error opening file!\n");
        printf("The file doesn't exist. Creating it..");
        f3 = fopen("SortedJobsByCustomer.txt", "wb");
    }
    // Print the header
    fprintf(f3,"####### JOBS SORTED BY CUSTOMER #######\r\n\r\n");
    fprintf(f3,"\n%5s%-20s%-25s%-21s%-21s\r\n", "JobID  ", "Customer", "Employee  ", "Due Date", "Completed Date");
    fprintf(f3,"%5s%-20s%-25s%-21s%-21s\r\n", "-----", " -------------------- ", "------------------------ ", "------------------- ", "--------------------");

    for (int i = 0; i < linecount;i++) {
        // get the employee name
        EmployeeName=employee_name(arrayEmployees, totLineEmployees, newArray[i]->EmployeeNumber);
        // print job details to file
        print_jobs_file(newArray[i]->jobNumber, newArray[i]->customer, EmployeeName, newArray[i]->dueDate, newArray[i]->completedDate, f3);
    }
    puts("\nData sorted and saved in SortedJobsByCustomer.txt");
    fclose(f3); // closing file
    continue_enter();
}

/* *****************************************************
 *
 * EXPORT JOB INFORMATION BY DATE AND TIME DUE ----- MENU 12
 *
 *
 *
 * *****************************************************/

void sort_job_information_by_date_time_due(void** arrayData, int *totLines2, int *totLineEmployees) {
    Employee **arrayEmployees=arrayData[1]; // arrayEmployees
    Job **arrayJobs=arrayData[0]; // arrayJobs
    char* EmployeeName; // to hold the EmployeeName
    int linecount = *totLines2;
    Job **newArray; // new array of Job pointers
    newArray = malloc(linecount * sizeof(Job*)); //allocate memory for the new array

    memcpy(newArray, arrayJobs, linecount * sizeof(Job*)); // copy the array
    newArray=sort_jobs(newArray,linecount,"dueDate" ); // call the sorting function passing the new array, lines count and parameter to sort on

    print_jobs_header(); //print the header
    //loop through the sorted array and call the print function to print the records
    for (int i = 0; i < linecount; i++) {
        // get the employee name
        EmployeeName=employee_name(arrayEmployees, totLineEmployees, newArray[i]->EmployeeNumber);
        // print the job details
        print_jobs(newArray[i]->jobNumber, newArray[i]->customer, EmployeeName, newArray[i]->dueDate, newArray[i]->completedDate);
    }
    // try to open file for reading, if it doesn't exist create it
    FILE *f3 = fopen("SortedJobsByDueDate.txt", "w");
    if (f3 == NULL) {
        printf("Error opening file!\n");
        printf("The file doesn't exist. Creating it..");
        f3 = fopen("SortedJobsByDueDate.txt", "wb");
    }
    // Print the header
    fprintf(f3,"####### JOBS SORTED BY DATE AND TIME DUE #######\r\n\r\n");
    fprintf(f3,"\n%5s%-20s%-25s%-21s%-21s\r\n", "JobID  ", "Customer", "Employee  ", "Due Date", "Completed Date");
    fprintf(f3,"%5s%-20s%-25s%-21s%-21s\r\n", "-----", " -------------------- ", "------------------------ ", "------------------- ", "--------------------");

    for (int i = 0; i < linecount; i++) {
        // get the employee name
        EmployeeName=employee_name(arrayEmployees, totLineEmployees, newArray[i]->EmployeeNumber);
        // print the job details
        print_jobs_file(newArray[i]->jobNumber, newArray[i]->customer, EmployeeName, newArray[i]->dueDate, newArray[i]->completedDate, f3);
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
void set_job_as_completed(void** arrayData, int *totLines2, int *totLineEmployees){
    Employee **arrayEmployees=arrayData[1];
    Job **arrayJobs=arrayData[0];
    int tot_found=0; // counter for the tot record found. If 0 display a non found message
    int job_id;
    printf("Insert the job ID :  "); // prompt to insert the job ID to find
    scanf("%d",&job_id);
    char* EmployeeName;
    print_jobs_header();
    // loop through the job array
    for (int i = 0; i < *totLines2; i++) {
        if (arrayJobs[i]->jobNumber == job_id) {     // if it matches the job ID entered
            tot_found++;                             //increase the counter
            arrayJobs[i]->completedDate = time(NULL);// set completedDate to current time
            // get the employee name
            EmployeeName=employee_name(arrayEmployees, totLineEmployees, arrayJobs[i]->EmployeeNumber);
            // print job details
            print_jobs(arrayJobs[i]->jobNumber, arrayJobs[i]->customer, EmployeeName, arrayJobs[i]->dueDate, arrayJobs[i]->completedDate);
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
    // open employeeFile for writing
    FILE *f = fopen("employeeFile.txt", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    // loop through the array and print the details
    for (int i = 0; i < *totLines; i++) {
        fprintf(f, "%d %s %s", arrayEmployees[i]->Number, arrayEmployees[i]->firstName, arrayEmployees[i]->lastName);
        fprintf(f, "\r\n");
    }
    fclose(f); // closing file
    //open file for writing
    FILE *f2 = fopen("jobFile.txt", "w");
    if (f2 == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    // loop through the array and print the details
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

// function to return the Name and Surname of an employee
char* employee_name(Employee **arrayEmployees, int *totLines, int empNumber){
    char* name;
    int totFound=0;
    for (int i = 0; i < *totLines - 1; i++) {
        if(arrayEmployees[i]->Number==empNumber){
            totFound++;
            name = calloc(strlen(arrayEmployees[i]->firstName) + strlen(arrayEmployees[i]->lastName)+4, sizeof(char));
            strcpy(name, arrayEmployees[i]->firstName);
            strcat(name, " ");
            strcat(name, arrayEmployees[i]->lastName);
        }
    }
    if(totFound==0){
        calloc(18, sizeof(char));
        name="Employee not found";
    }
    return name;
}

// ask the user to press enter to continue
void continue_enter(){
    printf("\n\nPress [Enter] to continue.\n");
    while(getchar()!='\n'); // to clean stdin
    getchar(); // wait for ENTER
}

// array sort function for Employee
Employee** sort_employees(Employee** arrayToSort,int totLines,char* fieldToSort ){
    int pass; // passes counter
    int comparison;
    Employee *hold; //temporary location used to swap array elements

    /* loop to control number of passes */

    if(fieldToSort=="LastName") {
        for (pass = 1; pass < totLines; pass++) {
            /* loop to control number of comparisons per pass */
            for (int i = 0; i < totLines - 1; i++) {
                comparison = strcmp(arrayToSort[i]->lastName, arrayToSort[i + 1]->lastName);
                // check the strings and swap if comparison >0
                if (comparison > 0) {
                    hold = arrayToSort[i];
                    arrayToSort[i] = arrayToSort[i + 1];
                    arrayToSort[i + 1] = hold;
                } // end if
            } // end inner for
        } // end outer for
    }
    if(fieldToSort=="Number"){
        for (pass = 1; pass < totLines; pass++) {
            /* loop to control number of comparisons per pass */
            for (int i = 0; i < totLines - 1; i++) {
                // if the number is greater swap the elements
                if (arrayToSort[i]->Number > arrayToSort[i+1]->Number) {
                    hold = arrayToSort[i];
                    arrayToSort[i] = arrayToSort[i + 1];
                    arrayToSort[i + 1] = hold;
                } // end if
            } // end inner for
        } // end outer for
    }
    // return the sorted array
    return arrayToSort;
}

// array sort function for Job
Job** sort_jobs(Job** arrayToSort,int totLines,char* fieldToSort ){
    int pass; // passes counter
    int comparison;
    Job *hold; //temporary location used to swap array elements

    /* loop to control number of passes */

    if(fieldToSort=="customer") {
        for (pass = 1; pass < totLines; pass++) {
            /* loop to control number of comparisons per pass */
            for (int i = 0; i < totLines - 1; i++) {
                comparison = strcmp(arrayToSort[i]->customer, arrayToSort[i + 1]->customer);
                // check the strings and swap if comparison >0
                if (comparison > 0) {
                    hold = arrayToSort[i];
                    arrayToSort[i] = arrayToSort[i + 1];
                    arrayToSort[i + 1] = hold;
                } // end if
            } // end inner for
        } // end outer for
    }
    if(fieldToSort=="dueDate"){
        for (pass = 1; pass < totLines; pass++) {
            /* loop to control number of comparisons per pass */
            for (int i = 0; i < totLines - 1; i++) {
                // check if the due date is greater and swap the elements
                if (arrayToSort[i]->dueDate > arrayToSort[i+1]->dueDate) {
                    hold = arrayToSort[i];
                    arrayToSort[i] = arrayToSort[i + 1];
                    arrayToSort[i + 1] = hold;
                } // end if
            } // end inner for
        } // end outer for
    }
    if(fieldToSort=="EmployeeNumber"){
        for (pass = 1; pass < totLines; pass++) {
            /* loop to control number of comparisons per pass */
            for (int i = 0; i < totLines - 1; i++) {
                if (arrayToSort[i]->EmployeeNumber > arrayToSort[i+1]->EmployeeNumber) {

                    hold = arrayToSort[i];
                    arrayToSort[i] = arrayToSort[i + 1];
                    arrayToSort[i + 1] = hold;
                } // end if
            } // end inner for
        } // end outer for
    }
    // return the sorted array
    return arrayToSort;
}

// print the header for the jobs
void print_jobs_header(){

    printf("\n%5s%-20s%-25s%-21s%-21s\n", "JobID  ", "Customer", "Employee  ", "Due Date", "Completed Date");
    printf("%5s%-20s%-25s%-21s%-21s\n", "-----", " -------------------- ", "------------------------ ", "------------------- ", "--------------------");
}

// to print the jobs formatted in an external file
void print_jobs_file(int jobNumber, char* customer, char* EmployeeName, time_t dueDate, time_t completedDate, FILE *f3){

    char *dueDateString2;
    char *completedDateString2; // allocate memory for the completed date


    dueDateString2=convert_date(dueDate);
    completedDateString2=convert_date(completedDate);

    fprintf(f3, "%5d  %-20s%-25s%-21s%-21s", jobNumber, customer, EmployeeName, dueDateString2, completedDateString2);
    fprintf(f3, "\r\n");

}

// to print the jobs formatted
void print_jobs(int jobNumber, char* customer, char* EmployeeName, time_t dueDate, time_t completedDate) {

    char *dueDateString2;
    char *completedDateString2; // allocate memory for the completed date


    dueDateString2=convert_date(dueDate);
    completedDateString2=convert_date(completedDate);
    // print the record
    printf("%5d  %-20s%-25s%-21s%-21s\n", jobNumber, customer,
           EmployeeName, dueDateString2, completedDateString2);
}

// To convert a date in time_t to human readable
char* convert_date(time_t dateToConvert){
    char *dateToConvert2=calloc(20, sizeof(char)); // allocate memory for the date
    if((int)dateToConvert==83886080){
        dateToConvert2="No valid date";
    }
    else{
        strftime(dateToConvert2, 20, "%b %d, %Y %H:%M", localtime(&dateToConvert));
    }
    return dateToConvert2;
}