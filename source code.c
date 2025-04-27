//The following code is for simple Exam Registration System 
//This code is only been tested on vs code terminal and can be run on CLI also
//A text file name users.txt is essential to create before running this code as without the file you cannot login or register to start the program 
/*For results you have to create another file name results.txt and have to enter results in the following manner
Student Name: 
Exam: 
Marks:*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void view_profile(char username[], char password[]) {
    printf("\n--- Profile Information ---\n");
    printf("User ID   : %s\n", username);
    printf("Password : %s\n", password);
}

void exam_registration(char username[], char password[]) {
        int exam_choice;
        char name[100], address[200], phone[15], DOB[10], email[30] ;
        const char *exams[] = {"JEE", "NEET", "GATE", "UPSC", "CAT", "SAT", "SSC", "OLYMPIAD", "AFCAT", "CDS"};
    
        printf("Exams you can Register:\n");
        for (int i = 0; i < 10; i++) {
            printf("%d. %s\n", i + 1, exams[i]);
        }
    
        printf("Enter the exam you want to register for (1-10): ");
        scanf("%d", &exam_choice);
    
        if (exam_choice < 1 || exam_choice > 10) {
            printf("Invalid choice.\n");
            return;
        }
    
        printf("Enter your Full Name: ");
        getchar(); 
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
    
        printf("Enter your Address: ");
        fgets(address, sizeof(address), stdin);
        address[strcspn(address, "\n")] = '\0';

        printf("Enter your DOB: ");
        fgets(DOB, sizeof(DOB), stdin);
        DOB[strcspn(DOB, "\n")] = '\0';

        printf("Enter your Email:");
        getchar();
        fgets(email,sizeof(email),stdin);
        email[strcspn(email, "\n")] = '\0';
    
        printf("Enter your Phone Number: ");
        scanf("%s", phone);
    
        int payment;
        printf("Proceed to Payment?\n1. Yes\n2. No\nEnter choice: ");//Without payment you cannot register for the exam
        scanf("%d", &payment);
    
        if (payment != 1) {
            printf("Payment Failed or Cancelled.\nRegistration aborted.\n");
            return;
        }
    
        char filename[100];
        sprintf(filename, "%s_%s_exam.txt", username, password);
        FILE *fp = fopen(filename, "a");
        if (fp == NULL) {
            printf("Error saving registration data.\n");
            return;
        }
    
        fprintf(fp, "Exam Registered: %s\n", exams[exam_choice - 1]);
        fprintf(fp, "Name           : %s\n", name);
        fprintf(fp, "Date Of Birth  : %s\n", DOB);
        fprintf(fp, "Email          : %s\n", email);
        fprintf(fp, "Address        : %s\n", address);
        fprintf(fp, "Phone          : %s\n", phone);
        fprintf(fp, "Payment Status : Paid\n");
        fprintf(fp, "--------------------------\n");
    
        fclose(fp);
        printf("Registration and Payment Successful! Details saved.\n");
    }

void view_exam_schedule() {
        FILE *fp = fopen("exam_schedule.txt", "r");
        if (fp == NULL) {
            printf("Error opening exam_schedule.txt\n");
            return;
        }
    
        int exam_choice;
        char *exams[] = {"JEE", "NEET", "GATE", "UPSC", "CAT", "SAT", "SSC", "OLYMPIAD", "AFCAT", "CDS"};
        
        printf("\nAvailable Exams:\n");
        for (int i = 0; i < 10; i++) {
            printf("%d. %s\n", i + 1, exams[i]);
        }
    
        printf("Enter your exam choice number: ");
        scanf("%d", &exam_choice);
    
        if (exam_choice < 1 || exam_choice > 10) {
            printf("Invalid choice.\n");
            fclose(fp);
            return;
        }
    
        char line[100], selected_exam[20];
        strcpy(selected_exam, exams[exam_choice - 1]);
    
        int found = 0;
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, selected_exam)) {
                printf("\n--- Exam Schedule ---\n");
                printf("%s", line);
                printf("Admit card will be available 2 days before the exam.\n");
                found = 1;
                break;
            }
        }
    
        if (!found) {
            printf("Schedule for %s not found.\n", selected_exam);
        }
    
        fclose(fp);
    }

    void view_result_by_name() {
        FILE *fp = fopen("results.txt", "r");
        if (fp == NULL) {
            printf("Error: Could not open results.txt file.\n");
            return;
        }
    
        char line[256];
        char input_name[50];
        int found = 0;
    
        printf("Enter your name to view your result: ");
        scanf("%s", input_name);
    
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, input_name) != NULL) {
                // Print the line with the name
                printf("\n--- Result Found ---\n");
                printf("%s", line);
                found = 1;
    
                // Print the next two lines
                for (int i = 0; i < 2; i++) {
                    if (fgets(line, sizeof(line), fp)) {
                        printf("%s", line);
                    } else {
                        break; // No more lines
                    }
                }
    
                break; // Stop after finding the first match
            }
        }
    
        if (!found) {
            printf("No result found for '%s'.\n", input_name);
        }
    
        fclose(fp);
    }
     
void user_dashboard(char username[], char password[]) {
    int choice;
    while (1) {
        printf("\n--- Welcome %s ---", username);
        printf("\n1. View Profile\n2. Exam Registration\n3. Exam Schedule\n4. Results\n5. Logout\n");;
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                view_profile(username, password);
                break;
            case 2:{
                printf("Exam Registration selected.\n");
                exam_registration(username, password);
                break;}
            case 3:{
                printf("Exam Schedule displayed.\n");
                view_exam_schedule() ;  
                break;}
            case 4:{
                printf("Your Results:");
                view_result_by_name();
                break;}
            case 5:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void login(char username[], char password[]) { //For testing purpose username and password use PHANTOM and 123 respectively
    FILE *fp;
    char stored_username[50], stored_password[50];
    int found = 0;

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    fp = fopen("users.txt", "a+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    while (fscanf(fp, "%s %s", stored_username, stored_password) != EOF) {
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(fp); 

    if (found) {
        printf("Login Successful!\n");
        user_dashboard(username, password); 
    } 
    else {
        printf("Login Failed. Username or Password incorrect.\n");
    }
}

void register_user(char username[], char password[]) {
    FILE *fp = fopen("users.txt", "a");
    if (fp == NULL) {
        printf("Error opening file for registration.\n");
        return;
    }
    printf("Enter new Username: ");
    scanf("%s", username);
    printf("Enter new Password: ");
    scanf("%s", password);

    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);
    printf("Registration successful!\n");
}

int main() {   
    int choice;
    char username[50], password[50];

    while (1) {
        printf("\nSelect the operation you want to perform");
        printf("\n1. Login \n2. Registration \n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                login(username, password); 
                break;
            case 2:
                register_user(username, password);
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
        }
    }

    return 0;
}