/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : Yuchi Zheng
Student ID#: 025 848 151
Email      : yzheng103@myseneca.ca
Section    : NAA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

// System Libraries
#include <stdio.h>

// String Libraries
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"

// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// 1.main menu (hub) for application
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// 2.Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// 3.Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// 4.Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// 5.Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)    
{
    int i, count = 0;

    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();        
    }

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            count += 1;
        }
        else
        {
            displayPatientData(&patient[i], fmt);
        }
    }

    if (count == i)
    {
        printf("*** No records found ***");
    }
    putchar('\n');
}


// 6.Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection = 0;

    do {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            searchPatientByPatientNumber(patient, max);
            suspend();
        }
        else if (selection == 2)
        {
            searchPatientByPhoneNumber(patient, max);
            putchar('\n');
            suspend();
        }

    } while (selection);
}


// 7.Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int indexFree = 0;

    indexFree = findPatientIndexByPatientNum(0, patient, max);

    if (indexFree == -1)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        patient[indexFree].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[indexFree]);
        printf("*** New patient record added ***\n\n");
    }
}


// 8.Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int inputPatientNumber, existIndex = 0;

    printf("Enter the patient number: ");
    inputPatientNumber = inputIntPositive();
    putchar('\n');

    existIndex = findPatientIndexByPatientNum(inputPatientNumber, patient, max);

    if (existIndex >= 0)
    {
        menuPatientEdit(&patient[existIndex]);
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}


// 9.Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    struct Patient safeEmpty = { 0 };       

    int inputPatientNumber, existIndex = 0;
    char selection = '\0';

    printf("Enter the patient number: ");
    inputPatientNumber = inputIntPositive();
    putchar('\n');

    existIndex = findPatientIndexByPatientNum(inputPatientNumber, patient, max);

    if (existIndex >= 0)
    {
        displayPatientData(&patient[existIndex], FMT_FORM);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        selection = inputCharOption("yn");

        if (selection == 'y')
        {
            patient[existIndex] = safeEmpty;       // or use memset£¨0£¬sizeof(type)£©
            printf("Patient record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)                
{
    int i = 0, count = 0, mathchedInedx = 0;

    sortAppointsByDateTime(data->appointments, data->maxAppointments);
    displayScheduleTableHeader(&data->appointments->date, FMT_ALL_RECORDS);

    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientNumber == 0)
        {
            count++;
        }
        else
        {
            mathchedInedx = findPatientIndexByPatientNum(data->appointments[i].patientNumber,
                                                         data->patients, data->maxPatient);

            displayScheduleData(&data->patients[mathchedInedx], 
                                &data->appointments[i], FMT_INCLUDE_DATE_FIELD);
        }
    }

        if (count == i)
        {
            printf("*** No records found ***");
        }
        putchar('\n');
}


// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data)     
{
    struct Date temp = { 0 };                    //why cant't set "struct Date* temp"
    int i, count = 0, mathchedInedx = 0;                       

    inputDate(&temp);                           //get user input for year, month and day

    putchar('\n');
    displayScheduleTableHeader(&temp, !FMT_ALL_RECORDS);

    sortAppointsByDateTime(data->appointments, data->maxAppointments);
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].date.year == temp.year &&
            data->appointments[i].date.month == temp.month &&
            data->appointments[i].date.day == temp.day)
        {
            mathchedInedx = findPatientIndexByPatientNum(data->appointments[i].patientNumber,
                                                         data->patients, data->maxPatient);

            displayScheduleData(&data->patients[mathchedInedx], &data->appointments[i], !FMT_INCLUDE_DATE_FIELD);
            count++;
        }
    }

    if (count == 0)
    {
        printf("\n*** No records found ***\n");
    }
    putchar('\n');
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment appoints[], int maxAppoints,
                    struct Patient patients[], int maxPatient)          
{
    int indexFree = 0;

    indexFree = findAppointIndexByPatientNum(0, appoints, maxAppoints);

    if (indexFree == -1)
    {
        printf("ERROR: Appointment listing is Full!\n\n");
    }
    else
    {
        //Get user input for a patient number of new appointment record 
        //and check is it in patient file list
        inputPatientNumber(&appoints[indexFree].patientNumber, patients, maxPatient);

        inputAppointmentData(&appoints[indexFree], appoints, maxAppoints);
    }    
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment appoints[], int maxAppoints,
                       struct Patient patients[], int maxPatient)       
{
    int inputPatientNumber, valid = 0, i, existIndex = 0;
    char selection = '\0';

    struct Appointment temp = { 0 };
    struct Appointment safeEmpty = { 0 };

    printf("Patient Number: ");
    inputPatientNumber = inputIntPositive();

    existIndex = findPatientIndexByPatientNum(inputPatientNumber, patients, maxPatient);

    if (existIndex >= 0)
    {
        inputDate(&temp.date);
        putchar('\n');

        for (i = 0; valid == 0 && i < maxAppoints; i++)
        {
            if (appoints[i].patientNumber == inputPatientNumber &&
                appoints[i].date.year == temp.date.year &&
                appoints[i].date.month == temp.date.month &&
                appoints[i].date.day == temp.date.day)
            {
                valid = 1;
                
                displayPatientData(&patients[existIndex], FMT_FORM);
                printf("Are you sure you want to remove this appointment (y,n): ");
                selection = inputCharOption("y,n");

                if (selection == 'y')
                {
                    appoints[i] = safeEmpty;
                    printf("\nAppointment record has been removed!\n\n");
                }
                else
                {
                    printf("Operation aborted.\n\n");
                }
            }
        }
        
        if(valid == 0)
        {
            printf("ERROR: Appointment record not found!\n\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max) //max = 20
{
    int inputPatientNumber, existIndex = 0;

    printf("Search by patient number: ");
    inputPatientNumber = inputIntPositive();
    putchar('\n');

    existIndex = findPatientIndexByPatientNum(inputPatientNumber, patient, max);

    if (existIndex >= 0)
    {
        displayPatientData(&patient[existIndex], FMT_FORM);
        putchar('\n');
    }
    else
    {
        printf("*** No records found ***\n\n");
    }
}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i, count = 0;
    char inputPhoneNumber[PHONE_LEN + 1] = { '\0' };

    printf("Search by phone number: ");
    inputCString(inputPhoneNumber, PHONE_LEN, PHONE_LEN);               
    putchar('\n');

    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (strcmp(inputPhoneNumber, patient[i].phone.number) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            count += 1;
        }
    }

    if (count == 0)
    {
        printf("\n*** No records found ***\n");
    }
}


// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i, maxPatientNumber = 0;

    for (i = 0; i < max; i++)
    {
        if (i == 0)
        {
            maxPatientNumber = patient[i].patientNumber;
        }
        else if (maxPatientNumber < patient[i].patientNumber)
        {
            maxPatientNumber = patient[i].patientNumber;
        }
    }
    maxPatientNumber += 1;

    return maxPatientNumber;
}


// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i, valid = 0, matchedIndex = 0;

    for (i = 0; valid == 0 && i < max; i++)     //must && 
    {
        if (patientNumber == patient[i].patientNumber)
        {
            valid = 1;
            matchedIndex = i;
        }
    }

    if (valid == 0)
    {
        matchedIndex = -1;
    }

    return matchedIndex;
}



// NEW FUNCTION
// Sort the appointments by date and time in ascending order    
void sortAppointsByDateTime(struct Appointment appoints[], int max)
{
    int i, j;
    struct Appointment tempAppoint = {0};

    for (i = max - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if ((appoints[j].date.year > appoints[j + 1].date.year) ||

                ((appoints[j].date.year == appoints[j + 1].date.year) &&
                 (appoints[j].date.month > appoints[j + 1].date.month)) ||

                ((appoints[j].date.year == appoints[j + 1].date.year) &&
                 (appoints[j].date.month == appoints[j + 1].date.month) &&
                 (appoints[j].date.day > appoints[j + 1].date.day)) ||

                ((appoints[j].date.year == appoints[j + 1].date.year) &&
                 (appoints[j].date.month == appoints[j + 1].date.month) &&
                 (appoints[j].date.day == appoints[j + 1].date.day) &&
                 (appoints[j].time.hour > appoints[j + 1].time.hour)) ||

                ((appoints[j].date.year == appoints[j + 1].date.year) &&
                 (appoints[j].date.month == appoints[j + 1].date.month) &&
                 (appoints[j].date.day == appoints[j + 1].date.day) &&
                 (appoints[j].time.hour == appoints[j + 1].time.hour) &&
                 (appoints[j].time.min > appoints[j + 1].time.min)))

            {
                tempAppoint = appoints[j];
                appoints[j] = appoints[j + 1];
                appoints[j + 1] = tempAppoint;
            }
        }
    }
}


// NEW FUNCTION
// Check whether the user's input year is a leap year or not            
// Return the days of February related to the inputting year
int isLeapYear(const int inputYear)
{
    int februaryDays = 0;

    if (inputYear % 400 == 0 || 
       (inputYear % 4 == 0 && inputYear % 100 != 0))
    {
        februaryDays = 29;
    }
    else
    {
        februaryDays = 28;
    }

    return februaryDays;
}

// NEW FUNCTION
// Return the days of Month according to the input year and month 
int getMonthDays(const int inputYear, const int inputMonth)
{
    int monthDays = 0;          //31days: 1 3 5 7 8 10 12                          
                                //30days: 4 6 9 11
    if (inputMonth == 2)
    {
        monthDays = isLeapYear(inputYear);
    }
    else if(inputMonth == 4 || inputMonth == 6 || 
            inputMonth == 9 || inputMonth == 11)
    {
        monthDays = 30;
    }
    else
    {
        monthDays = 31;
    }

    return monthDays;
}


// NEW FUNCTION
// Find the appoinment array index by patient number (returns -1 if not found) 
int findAppointIndexByPatientNum(int patientNumber, const struct Appointment appoints[], int max)
{
    int i, valid = 0, matchedIndex = 0;

    for (i = 0; valid == 0 && i < max; i++)
    {
        if (patientNumber == appoints[i].patientNumber)
        {
            valid = 1;
            matchedIndex = i;
        }
    }

    if (valid == 0)
    {
        matchedIndex = -1;
    }

    return matchedIndex;
}

// NEW FUNCTION
// Validate it for an input appointment time (returns 0 if not valid) 
int isValidAppointTime(const struct Appointment appoint)
{
    int valid = 0, i, minuteOptionNum;

    if (appoint.time.hour < MIN_START_HOUR_APPOINT || 
        appoint.time.hour > MAX_END_HOUR_APPOINT)
    {
        valid = 0;
    }
    else if (appoint.time.hour == MAX_END_HOUR_APPOINT)         //16:00
    {
        if (appoint.time.min != 0)
        {
            valid = 0;
        }
        else
        {
            valid = 1;
        }
    }
    else
    {
        minuteOptionNum = 60 / APPOINT_MIN_INTERVAL;    //should use % , add to above if condition
        for (i = 0; valid == 0 && i < minuteOptionNum; i++)
        {
            if (appoint.time.min == i * APPOINT_MIN_INTERVAL)
            {
                valid = 1;
            }  
            else
            {
                valid = 0;
            }
        }
    }

    return valid;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n"
        "------------------\n");

    printf("Number: %05d\n", patient->patientNumber);

    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');

    inputPhoneData(&patient->phone);
}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int selection;
    char newLine = '\0';
    char fmt[50 + 1] = { '\0' };

    printf("Phone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n");

    printf("1. Cell\n"
           "2. Home\n"
           "3. Work\n"
           "4. TBD\n"
           "Selection: ");
    selection = inputIntRange(1, 4);
    putchar('\n');

    switch (selection)
    {
    case 1:
        strcpy(phone->description, "CELL");
        break;
    case 2:
        strcpy(phone->description, "HOME");
        break;
    case 3:
        strcpy(phone->description, "WORK");
        break;
    case 4:
        strcpy(phone->description, "TBD");
        strcpy(phone->number, "\0");
        break;
    }

    if (selection != 4)
    {
        printf("Contact: %s\n", phone->description);
        printf("Number : ");

        do {
            sprintf(fmt, "%%%d[^\n]%%c", PHONE_LEN);
            scanf(fmt, &phone->number, &newLine);       //fmt = "%10[^\n]%c"

            if (strlen(phone->number) != 10)            //or < 10,less 10 digits, newLine alrady caught '\n'
            {
                printf("Invalid %d-digit number! Number: ", PHONE_LEN);
            }
            else if (newLine != '\n')                   //  10 digits, left data in buffer
            {
                clearInputBuffer();
                printf("Invalid %d-digit number! Number: ", PHONE_LEN);
            }
        } while (strlen(phone->number) != 10 || newLine != '\n');

        putchar('\n');
    }
}


// NEW FUNCTION
// Get user input for year, month and day // new add function
void inputDate(struct Date* date)
{
    int maxInputDay = 0;

    printf("Year        : ");
    date->year = inputIntPositive();                         //intputYear

    printf("Month (%d-%d): ", MIN_MONTH, MAX_MONTH);
    date->month = inputIntRange(MIN_MONTH, MAX_MONTH);       //inputMonth

    maxInputDay = getMonthDays(date->year, date->month);

    printf("Day (%d-%d)  : ", MIN_DAY, maxInputDay);
    do {
        date->day = inputIntPositive();                      //inputDay

        if (date->day < MIN_DAY || date->day > maxInputDay)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ",
                MIN_DAY, maxInputDay);
        }
    } while (date->day < MIN_DAY || date->day > maxInputDay);
}


// NEW FUNCTION
// Get user input for hour and minute // new add function
void inputTime(struct Time* time)
{
    printf("Hour (%d-%d)  : ", MIN_HOUR, MAX_HOUR);       //0-23
    time->hour = inputIntRange(MIN_HOUR, MAX_HOUR);

    printf("Minute (%d-%d): ", MIN_MINUTE, MAX_MINUTE);   //0-59
    time->min = inputIntRange(MIN_MINUTE, MAX_MINUTE);
}


// NEW FUNCTION
// Get user input for a patient number of a new appointment record
// Search and check whether the input patient number is in the list of patient info file   
void inputPatientNumber(int* patientNumber, struct Patient patients[], int maxPatient)
{
    int inputPatientNumber, i, valid;

    printf("Patient Number: ");

    do {
        valid = 0;
        inputPatientNumber = inputIntPositive();

        for (i = 0; valid == 0 && i < maxPatient; i++)
        {
            if (inputPatientNumber == patients[i].patientNumber)
            {
                valid = 1;
                *patientNumber = inputPatientNumber;
            }
        }

        if (valid == 0)
        {
            printf("*** No records found ***\n");
        }

    } while (valid == 0);
}


// NEW FUNCTION
// Get user input for a new appointment record      
void inputAppointmentData(struct Appointment* appoint, 
                          const struct Appointment appoints[], int max)
{
    int invalid, i;
    struct Appointment temp = { 0 };
    temp.patientNumber = appoint->patientNumber;

    do {
        invalid = 0;

        inputDate(&temp.date);              //Get user input for an appointment date  
        inputTime(&temp.time);              //Get user input for an appointment time 

        for (i = 0; invalid == 0 && i < max; i++)
        {
            if (appoints[i].date.year == temp.date.year &&
                appoints[i].date.month == temp.date.month &&
                appoints[i].date.day == temp.date.day &&
                appoints[i].time.hour == temp.time.hour &&
                appoints[i].time.min == temp.time.min)

                //Time slot check           //isSameDate
                /*if (isSameDate(temp, appoints[i]) == 1 &&
                    appoints[i].time.hour == temp.time.hour &&
                    appoints[i].time.min == temp.time.min);*/
            {
                invalid = 1;
                printf("\nERROR: Appointment timeslot is not available!\n\n");
            }
        }

    } while (invalid == 1);

    if (invalid == 0)
    {
        do {
            if (isValidAppointTime(temp))   //1
            {
                invalid = 0;
                *appoint = temp;

                printf("\n*** Appointment scheduled! ***\n\n");
            }
            else
            {
                invalid = 1;
                printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n",
                    MIN_START_HOUR_APPOINT, MAX_END_HOUR_APPOINT, APPOINT_MIN_INTERVAL);
                inputTime(&temp.time);
            }

        } while (invalid == 1);
    }
}



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0; 
    char ch = '\0';

    FILE* fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (i < max && (fscanf(fp, "%d|%15[^|]|%4[^|]|",
               &patients[i].patientNumber, patients[i].name,
               patients[i].phone.description) == 3))
        {
            if (strcmp(patients[i].phone.description, "TBD") == 0)
            {
                fscanf(fp, "%c", &ch);          // or &char
                strcpy(patients[i].phone.number, "\0");
            }
            else
            {
                fscanf(fp, "%10s\n", patients[i].phone.number);
            }
            
            i++;
        }

        fclose(fp);
        fp = NULL;
    }
    else
    {
        printf("ERROR: Unable to open %s file!\n\n", datafile);
    }

    return i;
}


// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i = 0;

    FILE* fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (i < max && (fscanf(fp, "%d,%d,%d,%d,%d,%d\n",
               &appoints[i].patientNumber, &appoints[i].date.year,
               &appoints[i].date.month, &appoints[i].date.day,
               &appoints[i].time.hour, &appoints[i].time.min) == 6))
        {
            i++;
        }

        fclose(fp);
        fp = NULL;
    }
    else
    {
        printf("ERROR: Unable to open %s file!\n\n", datafile);
    }

    return i;
}
