/*
Author: 	Sejal Khandelwal
Roll No.: 	MT2023069
*/

#include "../macros.h"

void viewOfferingCourses(char* login_id,int sock);
void addNewCourse(int sock);
void removeCourse(int sock);
void updateCourse(int sock);
void changePassword(int sock);
void intToString(char* buffer, int value);

int facultyMenu(char* login_id,int  sock){//used in client.c
	printf("\n________________Faculty Menu______________\n");
	printf("1. View Offering Courses \n");
	printf("2. Add New Courses \n");
	printf("3. Remove Courses from Catalog\n");
	printf("4. Update Course Details \n");
	printf("5. Change Password \n");
	printf("6. Logout & Exit\n");
	
	int choice;
	char prompt[] = "Enter Your Choice: ";
	char buffer[10];

    write(STDOUT_FILENO, prompt, sizeof(prompt));

    ssize_t bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("read");
        return 0;
    }

    buffer[bytesRead] = '\0';

    if (sscanf(buffer, "%d", &choice) != 1) {
        fprintf(stderr, "\nInvalid input. Please enter an integer.\n");
        return 0;
    }
	write(sock, &choice, sizeof(choice));

	switch(choice) {
		case 1: viewOfferingCourses(login_id, sock);
		break;

		case 2: addNewCourse(sock);
		break;

		case 3: removeCourse(sock);
		break;

		case 4: updateCourse(sock);
		break;

		case 5: changePassword(sock);
		break;

		case 6: return -1;
	}
}

void viewOfferingCourses(char* login_id,int sock) {
	struct Courses course[6];
	int n;
	read(sock, &n, sizeof(n));
	read(sock, &course, sizeof(course));
	if(n >= 1) {
		for(int i = 0; i < n; i++) {
			write(STDOUT_FILENO, "******Course Details*****\n", strlen("******Course Details*****\n"));
    		printf("\nId: %s", course[i].course_id);
			printf("\nName: %s", course[i].name);
			printf("\nDepartment: %s", course[i].department);
			printf("\nCredits: %d", course[i].credits);
			printf("\nNo. Of Available Seats: %d", course[i].no_of_available_seats);
			printf("\nNo. Of Seats: %d\n \n", course[i].no_of_seats);
		}	
	}
	else {
		write(STDOUT_FILENO, "No Course Found!", 17);
	}
}

void addNewCourse(int sock) {
	struct Courses course;

	int isCourseFull;

	read(sock, &isCourseFull, sizeof(isCourseFull));

	if(isCourseFull) {
		write(STDOUT_FILENO, "You Cannot Add Any More Courses \n", sizeof("You Cannot Add Any More Courses \n"));
		return;
	}

	printf("\nEnter Course Name: ");
	scanf(" %s", course.name);

	printf("\nEnter Department: ");
	scanf(" %s", course.department);

	printf("\nEnter Number of Seats: ");
	scanf(" %d", &course.no_of_seats);

	printf("\nEnter Credits: ");
	scanf(" %d",&course.credits);

	printf("\nEnter Available Seats: ");
	scanf(" %d", &course.no_of_available_seats);

	write(sock, &course, sizeof(struct Courses));
}

void removeCourse(int sock) {
	char courseId[5];
	int isExist;
	int isValid;
	write(STDOUT_FILENO, "Enter Course Id to delete: ", sizeof("Enter Course Id to delete: "));
	read(STDIN_FILENO, &courseId, sizeof(courseId));

	write(sock, &courseId, sizeof(courseId));
	read(sock, &isValid, sizeof(isValid));
	if(!isValid) {
		write(STDOUT_FILENO, "\nUnable to Remove Course at the momemt, please try after sometime...", sizeof("Unable to Remove Course at the momemt, please try after sometime..."));
		return;
	}
	read(sock, &isExist, sizeof(isExist));

	if(!isExist) {
		write(STDOUT_FILENO, "\nCourse with the given course id doesn't exist", sizeof("\nCourse with the given course id doesn't exist"));
	}
	else {
		write(STDOUT_FILENO, "\nCourse Deleted Successfully", sizeof("\nCourse Deleted Successfully"));
	}
	return;
}

void updateCourse(int sock) {
	char courseId[5];
	int isExist, isValid;
	char intBuffer[20];
	write(STDOUT_FILENO, "Enter Course Id for Update: ", sizeof("Enter Course Id for Update: "));
	read(STDIN_FILENO, &courseId, sizeof(courseId));

	write(sock, &courseId, sizeof(courseId));
	read(sock, &isValid, sizeof(isValid));
	if(!isValid) {
		write(STDOUT_FILENO, "\nUnable to Update Course at the momemt, please try after sometime...", sizeof("Unable to Remove Course at the momemt, please try after sometime..."));
		return;
	}
	read(sock, &isExist, sizeof(isExist));

	if(!isExist) {
		write(STDOUT_FILENO, "\nCourse with the given course id doesn't exist", sizeof("\nCourse with the given course id doesn't exist"));
		return;
	}

	struct Courses course;
	read(sock, &course, sizeof(course));

	char courseName[30];
	printf("\nEnter Course Name (%s): ", course.name);
	scanf(" %s", courseName);

	if(strlen(courseName) > 1) {
		strcpy(course.name, courseName);
	}

	char courseDepartment[20];
	printf("\nEnter Department Name (%s): ", course.department);
	scanf(" %s", courseDepartment);

	if(strlen(courseDepartment) > 1) {
		strcpy(course.department, courseDepartment);
	}

	int noOfSeats;
	printf("\nEnter No. Of Seats (%d): ", course.no_of_seats);
	scanf(" %d", &noOfSeats);

	if(noOfSeats >= 0) {
		course.no_of_seats = noOfSeats;
	}

	int noOfAvailableSeats;
	printf("\nEnter No. Of Available Seats (%d): ", course.no_of_available_seats);
	scanf(" %d", &noOfAvailableSeats);

	if(noOfAvailableSeats >= 0) {
		course.no_of_available_seats = noOfAvailableSeats;
	}

	int credits;
	printf("\nEnter Credits (%d): ", course.credits);
	scanf(" %d", &credits);

	if(credits >= 0) {
		course.credits = credits;
	}
	
	printf("Course name %s \n", course.name);
	write(sock, &course, sizeof(struct Courses));

	read(sock, &isValid, sizeof(isValid));
	if(!isValid) {
		write(STDOUT_FILENO, "\nUnable to Update Course at the moment, please try after sometime...", sizeof("Unable to Remove Course at the momemt, please try after sometime..."));
		return;
	}
}

void changePassword(int sock) {
	char password[PASSWORD_LENGTH];

	write(STDOUT_FILENO, "Enter New Password: ", strlen("Enter New Password: "));
	scanf(" %s", password);
	int passLen = strlen(password);

	printf("pass len: %d\n", passLen);
	// write(sock, &passLen, sizeof(passLen));
	write(sock, &password, sizeof(password));
	
	write(STDOUT_FILENO, "\nPassword Changed Successfully: ", strlen("\nPassword Changed Successfully: "));

}

void intToString(char* buffer, int value) {
    int i = 0;
    int isNegative = 0;

    if (value < 0) {
        isNegative = 1;
        value = -value;
    }

    do {
        buffer[i++] = value % 10 + '0';
        value /= 10;
    } while (value);

    if (isNegative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';

    // Reverse the string
    int length = strlen(buffer);
    for (int j = 0; j < length / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[length - j - 1];
        buffer[length - j - 1] = temp;
    }
}