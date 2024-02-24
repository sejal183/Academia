/*
Author: 	Sejal Khandelwal
Roll No.: 	MT2023069
*/

#include "../macros.h"
// #include "../database/database.h"

void addStudent(int sock);
void addFaculty(int sock);
void viewStudents(int sock);
void viewFaculty(int sock);
void activateStudent(int sock);
void blockStudent(int sock);
void updateStudentDetails(int sock);
void updateFacultyDetails(int sock);

int adminMenu(int opt,int  sock){//used in client.c
	printf("\n_________Admin Menu_________\n");
	printf("1. Add Student\n");
	printf("2. View Student Details \n");
	printf("3. Add Faculty\n");
	printf("4. View Faculty Details\n");
	printf("5. Activate Student\n");
	printf("6. Block Student\n");
	printf("7. Modify Student Details\n");
	printf("8. Modify Faculty Details\n");
	printf("9. Logout and Exit\n");

	int choice;
	printf("Enter Your Choice: ");
	scanf("%d", &choice);
	write(sock, &choice, sizeof(choice));

	switch(choice) {
		case 1: addStudent(sock);
		break;

		case 2: viewStudents(sock);
		break;

		case 3: addFaculty(sock);
		break;
		
		case 4: viewFaculty(sock);
		break;
		
		case 5: activateStudent(sock);
		break;
		
		case 6: blockStudent(sock);
		break;
		
		case 7: updateStudentDetails(sock);
		break;
		
		case 8: updateFacultyDetails(sock);
		break;
		
		case 9: return -1;
	}
}

void addStudent(int sock) {
	struct Student student;

	printf("Enter Student Name: \n");
	scanf("%s", student.name);
	printf("Enter You Age: \n");
	scanf("%d", &student.age);
	printf("Enter You Address: \n");
	scanf("%s", student.address);
	printf("Enter Password: \n");
	scanf("%s", student.password);
	printf("Enter You Email Address: \n");
	scanf("%s", student.email);
	
	write(sock, &student, sizeof(struct Student));
}

void addFaculty(int sock) {
	struct Faculty faculty;
	int count = 0;
	struct flock lock;
	printf("_________________Enter Faculty Details___________________\n");
	printf("Name: ");
	scanf("%s", faculty.name);
	printf("Age: ");
	scanf("%d", &faculty.age);
	printf("Address: ");
	scanf("%s", faculty.address);
	printf("Password: ");
	scanf("%s", faculty.password);
	printf("Email Address: ");
	scanf("%s", faculty.email);
	
	write(sock, &faculty, sizeof(struct Faculty));
}

void viewStudents(int sock){
	char id[10];
	printf("Enter Student ID: ");
	scanf("%s",id);
	write(sock,&id,sizeof(id));
	int status;
	struct Student student;
	read(sock,&status,sizeof(status));
	if(status){
		read(sock,&student,sizeof(student));
		printf("__________________Student Details___________________\n");
		printf("ID : %s \n",student.login_id);
		printf("Name :%s \n",student.name);
		printf("Age : %d \n",student.age);
		printf("Email : %s \n",student.email);
		printf("Address: %s \n",student.address);
		printf("Sudent Status: %d \n",student.isActive);
		printf("Course Enrolled: %d \n", student.courseCount);
		// printf("Course Enrolled are: [: ");
		// for(int i = 0; i < student.courseCount; i++) {
		// 	printf(" %s", student.courses_enrolled[i]);
		// }
		// printf(" ]");
	}else{
		printf("-----------------  Invalid Student ID  ---------------\n");
	}

}


void viewFaculty(int sock){
	char id[10];
	printf("Enter Faculty ID: ");
	scanf("%s",id);
	write(sock,&id,sizeof(id));
	int status;
	struct Faculty faculty;
	read(sock,&status,sizeof(status));
	printf("Status is %d\n",status);
	if(status){
		read(sock,&faculty,sizeof(faculty));
		printf("___________________Faculty Details___________________\n");
		printf("ID : %s \n",faculty.login_id);
		printf("Name :%s \n",faculty.name);
		printf("Age : %d \n",faculty.age);
		printf("Email : %s \n",faculty.email);
		printf("Address: %s \n",faculty.address);
		
	}else{
		printf("-----------------  Invalid Faculty ID  ---------------\n");
	}

}

void activateStudent(int sock){
	char id[10];
	printf("Enter Student ID: ");
	scanf("%s",id);
	write(sock,&id,sizeof(id));	
	int format_status;
	read(sock,&format_status,sizeof(format_status));
	if(format_status==0){
		printf("------------ Invalid Format  ------------ \n");
		
	}
	else{
		int count_flag;
		read(sock,&count_flag,sizeof(count_flag));
		if(count_flag==0){
			printf("------------ Student Dosen't Exists ------------\n");
			return ;
		}
		printf("Student Activated\n");
	}
}

void blockStudent(int sock){
	char id[10];
	printf("Enter Student ID: ");
	scanf("%s",id);
	write(sock,&id,sizeof(id));	
	int format_status;
	read(sock,&format_status,sizeof(format_status));
	if(format_status==0)
		printf("------------ Invalid Format  ------------ \n");
	else{
		int count_flag;
		read(sock,&count_flag,sizeof(count_flag));
		if(count_flag==0){
			printf("------------ Student Dosen't Exists ------------\n");
			return ;
		}
		printf("Student Blocked\n");
	}
	
}


void updateStudentDetails(int sock){
	char id[10];
	printf("Enter Student ID: ");
	scanf("%s",id);
	write(sock,&id,sizeof(id));

	printf("1. Change Name\n");
	printf("2. Change Age \n");
	printf("3. Change Address\n");
	printf("4. Change Email\n");
	printf("5. Change All Details\n");
	int choice;
	scanf("%d",&choice);
	write(sock,&choice,sizeof(choice));
	switch (choice)
	{
	case 1:
		char name[30];
		printf("Enter Name: ");
		scanf("%s",name);
		write(sock,&name,sizeof(name));
		break;
	case 2:
		int age;
		printf("Age: ");
		scanf("%d",&age);
		write(sock,&age,sizeof(age));
		break;
	case 3:
		char Address[50];
		printf("Enter Address : ");
		scanf("%s",Address);
		write(sock,&Address,sizeof(Address));
		break;
	case 4:
		char email[30];
		printf("Enter Email: ");
		scanf("%s",email);
		write(sock,&email,sizeof(email));
		break;
	case 5:
		
		break;
	default:
		break;
	}
}

void updateFacultyDetails(int sock){
	char id[10];
	printf("Enter Faculty ID: ");
	scanf("%s",id);
	write(sock,&id,sizeof(id));

	printf("1. Change Name\n");
	printf("2. Change Age \n");
	printf("3. Change Address\n");
	printf("4. Change Email\n");
	int choice;
	scanf("%d",&choice);
	write(sock,&choice,sizeof(choice));
	switch (choice)
	{
	case 1:
		char name[30];
		printf("Enter Name: ");
		scanf("%s",name);
		write(sock,&name,sizeof(name));
		break;
	case 2:
		int age;
		printf("Age: ");
		scanf("%d",&age);
		write(sock,&age,sizeof(age));
		break;
	case 3:
		char Address[50];
		printf("Enter Address : ");
		scanf("%s",Address);
		write(sock,&Address,sizeof(Address));
		break;
	case 4:
		char email[30];
		printf("Enter Email: ");
		scanf("%s",email);
		write(sock,&email,sizeof(email));
		break;
	case 5:
		
		break;
	default:
		break;
	}
}