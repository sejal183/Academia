/*
Author: 	Sejal Khandelwal
Roll No.: 	MT2023069
*/

#include "../macros.h"

void viewAllCourses(int sock);
void enrollCourse(int sock);
void dropCourse(int sock);
void viewEnrolledCourses(int sock);
void changePassword(int sock);

int studentMenu(char *login_id,int  sock){//used in client.c
	printf("\n------- Welcome to Student Menu --------\n");
	printf("1. View All Courses\n");
	printf("2. Enroll (pick) New Course\n");
	printf("3. Drop Course \n");
	printf("4. View Enrolled Course Details \n");
	printf("5. Change Password\n");
	printf("6. Logout & Exit\n");

	int choice;
	printf("Enter Your Choice: ");
	scanf(" %d", &choice);
	
	write(sock, &choice, sizeof(choice));

	switch(choice) {
		case 1: viewAllCourses(sock);
		break;

		case 2: enrollCourse(sock);
		break;

		case 3: dropCourse(sock);
		break;

		case 4: viewEnrolledCourses(sock);
		break;

		case 5: changePassword(sock);
		break;

		case 6: return -1;

		default: return -1;
	}
}

void viewAllCourses(int sock) {
	
	int n;
	struct Courses course[n];
	read(sock, &n, sizeof(n));
	read(sock, &course, sizeof(course));
	if(n >= 1) {
		for(int i = 0; i < n; i++) {
			write(STDOUT_FILENO, "_______Course Details_____\n", strlen("_______Course Details_____\n"));
    		printf("\nId: %s", course[i].course_id);
			printf("\nName: %s", course[i].name);
			printf("\nDepartment: %s", course[i].department);
			printf("\nCredits: %d", course[i].credits);
			printf("\nNo. Of Available Seats: %d", course[i].no_of_available_seats);
			printf("\nNo. Of Seats: %d\n \n", course[i].no_of_seats);
			write(STDOUT_FILENO, "\n \n", strlen("\n"));
		}	
	}
	else {
		write(STDOUT_FILENO, "No Course Found!", 17);
	}
}

void enrollCourse(int sock) {
	char courseId[5];
	int isCourseFull;
	printf("\nEnter course Id: ");
	scanf(" %s", courseId);
	write(sock, &courseId, sizeof(courseId));

	read(sock, &isCourseFull, sizeof(isCourseFull));

	if(isCourseFull) {
		printf("\nCourse is Full");
	}
	else {
		printf("\nSuccessfully enrolled");
	}
}

void dropCourse(int sock) {
	char courseId[5];

	printf("\nEnter course Id: ");
	scanf(" %s", courseId);
	write(sock, &courseId, sizeof(courseId));

	printf("\n Course Successfully Dropped1");
}

void viewEnrolledCourses(int sock) {
	int n = 2;
	read(sock, &n, sizeof(n));
	struct Courses course[n];
	
	read(sock, &course, sizeof(course));

	for(int i = 0; i < n; i++) {
			printf("\n_______Enrolled Courses_____\n");
    		printf("\nId: %s", course[i].course_id);
			printf("\nName: %s", course[i].name);
			printf("\nDepartment: %s", course[i].department);
			printf("\nCredits: %d", course[i].credits);
			printf("\nNo. Of Available Seats: %d", course[i].no_of_available_seats);
			printf("\nNo. Of Seats: %d\n \n", course[i].no_of_seats);
			write(STDOUT_FILENO, "\n \n", strlen("\n"));
	}
}

// void changePassword(sock) {

// }
