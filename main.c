#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COURSE 100
#define MAX_STUDENT 1000

typedef struct Course{
    int course_id;
    char course_name[50];
    float credit;
    int year;
    int semester;
}Course;

typedef struct Student{
    int student_id;
    char student_name[50];
    char password[20];
    char address[100];
    char dept[5];
    int number_of_courses;
    Course course[5];
}Student;

Course courses[MAX_COURSE];
Student students[MAX_STUDENT];
int course_number = 0;
int student_number = 0;

void mainMenu();
void listCourses();
void listStudents();
void studentDetails();
void readCourse();
Course searchCourse(int course);
Student* searchStudent(int id);

void mainMenu(){
    while(1){
        int choice;
        printf("MAIN MENU \n");
        printf("1. List Courses \n2. List Students \n3. Student Details \n4. Register Course \n5. Exit \n");
        printf("Enter choice (1 - 5) : ");
        scanf("%d",&choice);
        switch(choice){
        case 1:
            listCourses();
            break;
        case 2:
            listStudents();
            break;
        case 3:
            studentDetails();
            break;
        case 4:
            registerCourse();
            break;
        case 5:
            exit(0);
        default:
            printf("Enter a valid choice!\n");
        }
    }
}

Course searchCourse(int course){
    for(int i = 0; i < course_number; i++){
        if(courses[i].course_id == course)
            return courses[i];
    }
}

void listCourses() {
    printf("%-3s \t%-10s \t %-50s \t %-10s \t %-5s \t %-5s\n","Serial","Course ID","Course Name","Credit","Year","Semester");
    for(int i = 0; i < course_number; i++) {
        printf("%-3d. \t%-10d \t %-50s \t %.1f \t\t  %-5d \t %-5d\n", i + 1, courses[i].course_id, courses[i].course_name, courses[i].credit, courses[i].year, courses[i].semester);
    }
}

void listStudents(){
    printf("%-3s \t%-10s \t %-50s \t %-100s \t %-5s\n","Serial","Student ID","Student Name","Student Address","Department");
    for(int i = 0; i < student_number; i++) {
        printf("%-3d. \t%-10d \t %-50s \t %-100s \t %-5s\n", i + 1, students[i].student_id, students[i].student_name, students[i].address, students[i].dept);
    }
}

void studentDetails(){
    printf("STUDENT INFORMATIONS\n");
    printf("Enter student ID: ");
    int id;
    scanf("%d",&id);
    Student *temp = searchStudent(id);
    printf("Student Name: %s\n",temp->student_name);
    printf("Student ID: %d\n",temp->student_id);
    printf("Student Address: %s\n",temp->address);
    printf("Student Department: %s\n",temp->dept);
    printf("Registered Courses:\n");
    for(int i = 0; i < temp->number_of_courses; i++){
        printf("%d. %d %s %.1f\n", i + 1, temp->course[i].course_id, temp->course[i].course_name, temp->course[i].credit);
    }
}

void registerCourse(){
    printf("COURSE REGISTRATION\n");
    printf("Enter student ID: ");
    int id;
    scanf("%d",&id);
    Student *temp = searchStudent(id);
    printf("Enter password: ");
    char pass[20];
    scanf("%s",pass);
    if(strcmp(pass,temp->password) == 0){
        printf("Logged In!\n");
        printf("Number of Courses: ");
        scanf("%d",&temp->number_of_courses);
        for(int i = 0; i < temp->number_of_courses; i++){
            int course;
            printf("Enter course ID: ");
            scanf("%d",&course);
            temp->course[i] = searchCourse(course);
        }
    }
    else
        printf("Wrong Credentials!\n");
}

Student* searchStudent(int id){
    for(int i = 0; i < student_number; i++){
        if(students[i].student_id == id)
            return &students[i];
    }
}

void readCourse(){
    FILE *file;
    char filename[] = "course.txt";
    file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    while (fscanf(file, "%d,%49[^,],%f,%d,%d\n", &courses[course_number].course_id, courses[course_number].course_name, &courses[course_number].credit, &courses[course_number].year, &courses[course_number].semester) != EOF) {
        course_number++;
        if (course_number >= MAX_COURSE) {
            fprintf(stderr, "Error: Too many courses in file.\n");
            break;
        }
    }

    fclose(file);
}

void readStudent(){
    FILE *file;
    char filename[] = "student.txt";
    file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    while (fscanf(file, "%d,%49[^,],%99[^,],%4[^,]\n", &students[student_number].student_id, students[student_number].student_name, students[student_number].address, students[student_number].dept) != EOF) {
        student_number++;
        if (student_number >= MAX_STUDENT) {
            fprintf(stderr, "Error: Too many students in file.\n");
            break;
        }
    }

    fclose(file);
}

void readCredentials(){
    FILE *file;
    char filename[] = "credentials.txt";
    file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    int tempID;
    char tempPassword[20];

    while (fscanf(file, "%d,%19[^\n]\n", &tempID, tempPassword) != EOF) {
        Student *temp = searchStudent(tempID);
        strcpy(temp->password,tempPassword);
    }

    fclose(file);
}

int main(){
    printf("WELCOME TO COURSE REGISTRATION SYSTEM\n");
    printf("-------------------------------------\n");
    readCourse();
    readStudent();
    readCredentials();
    mainMenu();
    return 0;
}
