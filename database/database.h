#include "../macros.h"

struct Courses {
    char course_id[10];
    char name[30];
    char department[20];
    char faculty_id[10];
    int no_of_seats;
    int credits;
    int no_of_available_seats;
	int isActive;
};

struct Student {
    char login_id[10];
    char name[30];
    int age;
    char address[50];
    char password[PASSWORD_LENGTH];
    char email[30];
    char *courses_enrolled[6];
    int courseCount;
	int isActive;
};

struct Faculty {
    char login_id[10];
    char name[30];
    int age;
    char address[30];
    char email[30];
    char password[PASSWORD_LENGTH];
    int courseCount;
};

struct Admin {
    char login_id[10];
    char name[30];
    char password[PASSWORD_LENGTH];
    char email[30];
};