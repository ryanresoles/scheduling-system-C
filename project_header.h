/*-----------------------------------------------------\
| 													   |				
|	Header file for project.						   |
|	Includes all functions, structure definitions,	   |
|	file implementations, etc.						   |
|	Ryan Nathaniel B. Resoles						   |
\_____________________________________________________*/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>


// structure for all appointments
typedef struct allAppointments{
	int appointment_id[11];
	int hour, minute, day, month, year;
	// for adding another node
	struct allAppointments *nextAppointment;
	struct allAppointments *prevAppointment;
}appointment;


// structure for all employees
typedef struct allEmployees{
	char employee_num[11];
	char first_name[50];
	char last_name[20];
	int age;
	char position [25];
	char date_hired[11];
	// for adding another node
	struct allEmployees *nextEmployee;
	struct allEmployees *prevEmployee;
	// pointer to all appointments
	struct allAppointments *appointmentPtr;	
}employee;

void save(employee** head) {
	FILE* fw = fopen("employees.txt", "w");
	employee* temp = *head;
	//saves per node
	while (temp != NULL) {
		fprintf(fw, "%s", temp->employee_num);
		fprintf(fw, "%s", temp->first_name);
		fprintf(fw, "%s", temp->last_name);
		fprintf(fw, "%d", temp->age);
		fprintf(fw, "%s", temp->position);
		fprintf(fw, "%s", temp->date_hired);
		appointment* appt = temp->appointmentPtr;
		while (appt != NULL) {
			fprintf(fw, "%s");
			appt = appt->nextAppointment;
		}
		temp = temp->nextEmployee;
	}
	fclose(fw);

}

int mainMenu(){
	//stores choice value
	system("cls");
	int choice;

	printf("\t************************************************\n");
	printf("\t* S P A   &&   M A S S A G E   E M P L O Y E E *\n");
	printf("\t*  a n d   S C H E D U L I N G   S Y S T E M   *\n");
	printf("\t************************************************\n");
	printf("\n");
	printf("\t*---------------------------------------------*\n");
	printf("\t* [1] Add Employee                            *\n");
	printf("\t* [2] Edit Employee                           *\n");
	printf("\t* [3] Delete Employee                         *\n");
	printf("\t* [4] View Employee                           *\n");
	printf("\t* [5] Add Appointment                         *\n");	
	printf("\t* [6] Edit Appointment                        *\n");
	printf("\t* [7] Delete Appointment                      *\n");
	printf("\t* [0] EXIT                                    *\n");
	printf("\t*---------------------------------------------*\n");
	printf("\n");
	printf("\t Enter your choice :");
	scanf("%d", &choice);

	return choice;
}

//prints positions
void printPositions(){
	printf("\t\t[1] aesthetician\n");
	printf("\t\t[2] hair stylist\n");
	printf("\t\t[3] massage therapist\n");
	printf("\t\t[4] nail technician\n");
	printf("\t\t[5] salon services attendant\n");
	printf("\t\t[6] spa attendant\n");
	printf("\t\t[7] spa management\n");
	printf("\t\t[8] spa receptionist\n");
}

//function for returning position string value
const char *pos(int choice){
	static char *positions[] = {"aesthetician", "hair stylist", "massage therapist", "nail technician", "salon services attendant", "spa attendant", "spa management", "spa receptionist"};
	switch(choice){
		case 1: return positions[choice-1];
		case 2: return positions[choice-1];
		case 3: return positions[choice-1];
		case 4: return positions[choice-1];
		case 5: return positions[choice-1];
		case 6: return positions[choice-1];
		case 7: return positions[choice-1];
		case 8: return positions[choice-1];
	}
}


void printDetails(employee *temp){
	printf("\n");
	printf("\tEmployee number : %s\n", temp->employee_num);
	printf("\tName : %s %s\n", temp->first_name, temp->last_name);
	printf("\tAge : %d\n", temp->age);
	printf("\tDate employed : %s \n", temp->date_hired);
	printf("\tPosition : %s\n", temp->position);
}


void addEmployee(employee **employeePtr){
	// temporarily holds data inputs
	employee *temp;
	int choice=0;

	//node to be inserted
	temp = (employee *) malloc (sizeof(employee));

	// user prompt for adding employee
	printf("\n");
	printf("\n");
	printf("\t\t= = A D D  E M P L O Y E E = =\n");
	printf("\n");
	// code for getting string input
	printf("\tEnter 8-digit employee number: ");
	getchar();
	scanf("%[^\n]%*c", temp->employee_num);
	printf("\tEnter employee's first name: ");
	scanf("%[^\n]%*c", temp->first_name);
	printf("\tEnter employee's last name: ");
	scanf("%[^\n]%*c", temp->last_name);
	printf("\tEnter the date employee was hired [mm/dd/yyyy]: ");
	scanf("%[^\n]%*c", temp->date_hired);

	// asks user for a number input then copies its string equivalent
	printf("\tWhat is  your position? \n");
	printf("\t\tSELECT FROM THE FOLLOWING POSITIONS :\n");
	printPositions();
	printf("\n");

	// loop for asking choice of user (should be within 1-8 bounds)
	while(choice < 1 || choice > 8){	
		printf("\tEnter your choice: ");
		scanf("%d", &choice);
	}
	strcpy(temp->position, pos(choice));

	printf("\tEnter employee's age: ");
	scanf("%d", &temp->age);

	temp->nextEmployee = NULL;
	temp->prevEmployee = NULL; 

	if(*employeePtr == NULL){
		// only executes if linked list is still empty
		// temp serves as the node to be inserted at head
		// adds employee to the head
		*employeePtr = temp;
		printf("\n");
		printf("\tEmployee was added successfully!\n");
	}
	else{
		// initially points to the first node
		employee *temp2 = *employeePtr;

		// traverses through the list
		while(temp2->nextEmployee != NULL && strcmp(temp2->nextEmployee->last_name, temp->last_name) < 0){
			temp2 = temp2->nextEmployee;
		}
		//already has a duplicate
		if(strcmp(temp2->employee_num, temp->employee_num) == 0){
			printf("\n");
			printf("\tEmployee already in the database!\n");
		}
		//there's no duplicate, can still add to list
		//sorted adding
		else{
			if(strcmp(temp2->last_name, temp->last_name) < 0 || (strcmp(temp2->last_name, temp->last_name) == 0 && strcmp(temp2->first_name, temp->first_name) < 0)){
				if(temp2->nextEmployee != NULL){
					temp->nextEmployee = temp2->nextEmployee;
					temp2->nextEmployee->prevEmployee = temp;
					temp->prevEmployee = temp2;
					temp2->nextEmployee = temp;
					printf("\tEmployee added successfully!\n");					
				}
				else{
					temp2->nextEmployee = temp;
					temp->prevEmployee = temp2;
					printf("\tEmployee added successfully!\n");	
				}
			}
			else if(strcmp(temp2->last_name, temp->last_name) > 0 || (strcmp(temp2->last_name, temp->last_name) == 0 && strcmp(temp2->first_name, temp->first_name) > 0)){
				if(temp2 = *employeePtr){
					temp->nextEmployee = temp2;
					temp2->prevEmployee = temp;
					*employeePtr = temp;
					printf("\tEmployee added successfully!\n");					
				}
				else{
					temp->nextEmployee = temp2;
					temp2->prevEmployee->nextEmployee = temp;
					temp->prevEmployee = temp2->prevEmployee;
					temp2->prevEmployee = temp;
					printf("\tEmployee added successfully!\n");	
				}
			}
		}
	}
	sleep(2);
}

void editEmployee(employee **employeePtr){
	char en[11];
	int choice;
	employee *temp = *employeePtr;	

	//nothing to be edited
	if(*employeePtr == NULL) printf("\tThere are no employees yet. Add some.\n");
	//executes if pointer is not empty
	else{
		printf("\n");
		printf("\t\t= = E D I T  E M P L O Y E E = =\n");
		printf("\n");
		printf("\tEnter 8-digit employee number of employee to be modified: ");
		getchar();
		scanf("%[^\n]%*c", en);

		while(temp != NULL && strcmp(temp->employee_num, en) != 0){
			temp = temp->nextEmployee;
		}
		if(temp == NULL) printf("\tEmployee not found.\n");
		else{
			printf("\tEnter new first name: ");
			scanf("%[^\n]%*c", temp->first_name);
			printf("\tEnter new last name: ");
			scanf("%[^\n]%*c", temp->last_name);
			printf("\tEnter new age: ");
			scanf("%d", &temp->age);
			printf("\tSelect from the following positions: \n");
			printPositions();
			printf("\tEnter new position: ");
			scanf("%d", &choice);
			strcpy(temp->position, pos(choice));

			printf("\tEmployee successfully modified!\n");
			printf("\n");
		}		
	}
	sleep(2);
}

void deleteEmployee(employee **employeePtr){
	int choice = 0, YorN;
	employee *temp = *employeePtr, *temp2 = *employeePtr;
	char en[11];

	if(*employeePtr == NULL){
		printf("\n");
		printf("\tThere are no employees yet. Nothing to delete.\n\n");
	} 
	else{
		printf("\n");
		printf("\t\t= = D E L E T E  E M P L O Y E E = =\n");
		printf("\n");
		printf("\t[1] Delete an employee\n");
		printf("\t[2] Delete ALL employees\n");
		printf("\n");

		while(choice != 1 || choice !=2){
			printf("\tWhich functionality do you wish to access :");
			scanf("%d", &choice);

			//prints all existing employees and asks who to delete
			if(choice == 1){
				printf("\tCURRENTLY VIEWING ALL EMPLOYEES: \n");
				while(temp != NULL){
					printDetails(temp);

					temp = temp->nextEmployee;
				}

				printf("\tEnter 8-digit employee number of person to be deleted: ");
				getchar();
				scanf("%[^\n]%*c", en);
				printf("\n");

				//traverses through list to look for a match
				while(temp2 != NULL && strcmp(temp2->employee_num, en) != 0){
					temp2 = temp2->nextEmployee;
				}
				//prits if there is no match found
				if(temp2 == NULL) printf("\tNo match.\n\n");
				//executes if there is a match
				else{
					if(temp2->appointmentPtr != NULL) printf("\tEmployee has appointments. Can't delete.\n");
					else{
						printf("\tAre you sure you want to delete employee? [1=Yes / 0=No]: ");
						scanf("%d", &YorN);
						if(YorN == 1){
							//second confirmation
							printf("\tAre you really really sure?  [1=Yes / 0=No]: ");
							scanf("%d", &YorN);
							if(YorN == 1){
								//deletes at head
								if(temp2 == (*employeePtr)){
									if(temp2->nextEmployee == NULL){
										free(temp2);
										*employeePtr = NULL;
										printf("\tEmployee successfully deleted!\n");
									}
									else{
										temp2->nextEmployee->prevEmployee = NULL;
										*employeePtr = temp2->nextEmployee;
										free(temp);
										printf("\tEmployee successfully deleted!\n");
									}
								}
								//deletes at tail
								else if(temp2->nextEmployee == NULL){
									temp2->prevEmployee->nextEmployee = NULL;
									free(temp2);
									printf("\tEmployee successfully deleted!\n");
								}
								//deletes at middle
								else{
									temp2->prevEmployee->nextEmployee = temp2->nextEmployee;
									temp2->nextEmployee->prevEmployee = temp2->prevEmployee;
									free(temp2);
									printf("\tEmployee successfully deleted!\n");
								}
								printf("\n");
							}
							else if(YorN == 0) printf("\tDeletion cancelled.");
							else printf("\tInvlaid choice.\n");
						}
						else if(YorN == 0) printf("\tDeletion cancelled.");
						else printf("\tInvlaid choice.\n");
					}
					break;
				}
			}
			//deletes all nodes
			else if(choice == 2){
				int YorN;
				//confirmation
				printf("\tNOTE: This only deletes all employees without existing appointments.\n");
				printf("\tAre you sure you want to delete all employees? [1=Yes / 0=No]: ");
				scanf("%d", &YorN);
				if(YorN == 1){
					//second confirmation
					printf("\tAre you really really sure?  [1=Yes / 0=No]: ");
					scanf("%d", &YorN);
					//deletes everything
					if(YorN == 1){
						while(temp != NULL){
							temp2 = temp;
							temp = temp->nextEmployee;
							if(temp2->appointmentPtr == NULL){
								if(temp2 = (*employeePtr)){
									(*employeePtr) = (*employeePtr)->nextEmployee;
									free(temp2);
								}
								else{
									temp->prevEmployee->nextEmployee = temp->nextEmployee;
									temp->nextEmployee->prevEmployee = temp->prevEmployee;
									free(temp2);

								}
							}
							else continue;
						}
						printf("\n\tDeletion complete!\n\n");
					}
					else if(YorN == 0) printf("\n\tDeletion cancelled.");
					else printf("\n\tInvlaid choice.\n");
				}
				else if(YorN == 0) printf("\n\tDeletion cancelled.");
				else printf("\n\tInvlaid choice.\n");
				break;
			}
		}		
	}
	sleep(2);
}

void viewEmployee(employee *employeePtr){
	employee *temp, *temp2;
	int choice = 0, choice2;
	char en[11];
	temp = employeePtr;
	temp2 = employeePtr;

	//user menu
	printf("\n");
	printf("\n");
	printf("\t\t= = V I E W  E M P L O Y E E = =\n");
	printf("\n");
	printf("\t[1] View an employee by employee number\n");
	printf("\t[2] View all employees\n");
	printf("\t[3] View employees of a specific position\n");
	printf("\n");

	while(choice < 1 || choice > 3){
		printf("\tWhich functionality do you wish to access :");
		scanf("%d", &choice);

		//prints employee with a match
		if(choice == 1){
			temp = employeePtr;
			printf("\tEnter employee number: ");
			getchar();
			scanf("%[^\n]%*c", en);
			printf("%s\n", en);

			//traverses through list of all employees
			while(temp != NULL){
				if(strcmp(temp->employee_num, en) == 0){
					printDetails(temp);
					break;
				}
				temp = temp->nextEmployee;
			}
			if(temp == NULL){		
				printf("\tEmployee not found.\n");
			}
			break;
		} 
			//prints all employees
		else if(choice == 2){
			if(temp == NULL) printf("\n\tThere are no employees yet. Add some.\n");
			else if(temp != NULL){
				printf("\tCURRENTLY VIEWING ALL EMPLOYEES\n");
				printf("\n");
				//traverses through the list and prints each node
				while(temp != NULL){
					printDetails(temp);

					temp = temp->nextEmployee;
				}						
			}
			printf("\n");
			break;				
		} 

		//prints employees depending on the position
		else if(choice == 3){
			printf("\tChoose a position :\n");
			printPositions();
			printf("\n");

			while(choice2 < 1 || choice2 > 8){
				printf("\tWhich position: ");
				scanf("%d", &choice2);
			}
			while(temp != NULL){
				if(strcmp(temp->position, pos(choice2)) == 0){
					printDetails(temp);
				}		
				temp = temp->nextEmployee;	
			}
			printf("\n");
		}
	}
	sleep(5);
}


void addAppointment(employee **employeePtr){
	// temporary value holders
	char en[11];

	// for traversing in the list later on
	employee *temp;
	appointment *temp2;
	appointment *temp3;

	printf("\n");
	printf("\t\t= = A D D   A P P O I N T M E N T = =\n");
	printf("\n");
	if(*employeePtr == NULL){
		 printf("\tDatabase of employee is still empty. Add one first.\n");
		 printf("\n");
	}
	else{
		printf("\tEmployees are as follows: \n");
		printf("\n");

		// points to the first node
		temp = *employeePtr;
		// traverses and prints each node
		while(temp != NULL){
			printf("\t\t[%s] ", temp->employee_num);
			printf("%s, ", temp->last_name);
			printf("%s", temp->first_name);
			temp = temp->nextEmployee;
		}
		printf("\n");
		printf("\tWhich employee do you want to add an appointment to? : ");
		getchar();
		scanf("%s", en);
		// repoints to the first node
		temp = *employeePtr;

		// looks for an identical employee number in the list
		while(temp != NULL){
			if(strcmp(temp->employee_num, en) == 0){
				printf("\n");
				printf("\tWelcome, %s!\n", temp->first_name);
				printf("\tEmployee number : %s\n", temp->employee_num);
				printf("\n");

				//node to be inserted
				temp2 = (appointment *) malloc (sizeof(appointment));								
				//adds appointment details
				printf("\tEnter 8-digit appointment ID :");
				scanf("%d", &temp2->appointment_id);
				printf("\tAppointment date... \n");
				printf("\tEnter day of appointment: ");
				scanf("%d", &temp2->day);
				printf("\tEnter month of appointment: ");
				scanf("%d", &temp2->month);
				printf("\tEnter year of appointment: ");
				scanf("%d", &temp2->year);			
				printf("\tAppointment time...\n");
				printf("\tEnter hour of appointment: ");
				scanf("%d", &temp2->hour);
				printf("\tEnter minute of appointment: ");
				scanf("%d", &temp2->minute);								
				temp2->nextAppointment = NULL;
				temp2->prevAppointment = NULL;

				temp3 = temp->appointmentPtr;

				//adds appointment to current employee
				//adds at head
				if(temp->appointmentPtr == NULL){
					temp->appointmentPtr = temp2;
					printf("\n");
					printf("\tAppointment successfully added!\n");
				}
				//sorted adding
				else{
					while(temp3->nextAppointment != NULL && temp3->nextAppointment->year < temp2->year){
						temp3 = temp3->nextAppointment;
					}
					if(temp3->year < temp2->year || (temp3->year == temp2->year && temp3->month < temp2->month) || (temp3->year == temp2->year && temp3->month == temp2->month && temp3->day < temp2->day)){
						if(temp3->nextAppointment == NULL){
							temp3->nextAppointment = temp2;
							temp2->prevAppointment = temp3;
							printf("\n");
							printf("\tAppointment successfully added!\n");	
						}
						else{
							temp2->nextAppointment = temp3->nextAppointment;
							temp3->nextAppointment->prevAppointment = temp2;
							temp2->prevAppointment = temp3;
							temp3->nextAppointment = temp2;
							printf("\n");
							printf("\tAppointment successfully added!\n");
						}
					}
					else if(temp3->year > temp2->year || (temp3->year == temp2->year && temp3->month > temp2->month) || (temp3->year == temp2->year && temp3->month == temp2->month && temp3->day > temp2->day)){
						if(temp3 = temp->appointmentPtr){
							temp2->nextAppointment = temp3;
							temp3->prevAppointment = temp2;
							temp->appointmentPtr = temp2;
							printf("\n");
							printf("\tAppointment successfully added!\n");
						}
						else{
							temp2->nextAppointment = temp3;
							temp3->prevAppointment->nextAppointment = temp2;
							temp2->prevAppointment = temp3->prevAppointment;
							temp3->prevAppointment = temp2;
							printf("\n");
							printf("\tAppointment successfully added!\n");
						}
					}
					else printf("\tAppointment already exists!\n");
				}
				temp = temp->nextEmployee;
			}else printf("\n\tEmployee not found.\n");
		}
	printf("\n");
	}
	sleep(2);
}


void editAppointment(employee **employeePtr){
	employee *temp = *employeePtr;
	appointment *temp2;
	char en[11];
	int aID[11];

	printf("\n");
	printf("\n");
	printf("\t\t= = E D I T   A P P O I N T M E N T = =\n");
	printf("\n");
	printf("\tEnter 8-digit employee number: ");
	getchar();
	scanf("%[^\n]%*c", en);

	//traverses through the list and looks for a match
	while(temp != NULL && strcmp(temp->employee_num, en) != 0){
		temp = temp->nextEmployee;
	}
	//proceeds to edit if a match is found
	if(strcmp(temp->employee_num, en) == 0){
		temp2= temp->appointmentPtr;

		//prints if there are no appointments yet
		if(temp2 == NULL) printf("\n\tNo appointment to edit. Add one first.\n\n");
		else{
			printf("\tEnter 8-digit appointment ID of appointment to be modified: ");
			scanf("%d", aID);

			//looks for a match in appointments
			while(temp2 != NULL && temp2->appointment_id != aID ){
				temp2 = temp2->nextAppointment;
			}
			if(temp2 == NULL) printf("\n\tAppointment not found.\n\n");
			else if(temp2->appointment_id == aID){
				printf("\tAppointment date... \n");
				printf("\tEnter modified day of appointment: ");
				scanf("%d", &temp2->day);
				printf("\tEnter modified month of appointment: ");
				scanf("%d", &temp2->month);
				printf("\tEnter modified year of appointment: ");
				scanf("%d", &temp2->year);			
				printf("\tAppointment time...\n");
				printf("\tEnter modified hour of appointment: ");
				scanf("%d", &temp2->hour);
				printf("\tEnter modified minute of appointment: ");
				scanf("%d", &temp2->minute);

				printf("\n\tAppointment successfully modified! \n\n");
			}			

		}
	}
	//exits the function if no match is found
	else printf("\n\tEmployee not found.\n\n");
	sleep(2);

}

void deleteAppointment(employee **employeePtr){
	char en[11];
	int aID[11];
	employee *temp = *employeePtr;
	appointment *temp2;

	printf("\n");
	printf("\t\t= = D E L E T E   A P P O I N T M E N T = =\n");
	printf("\n");
	printf("\tEnter employee number with appointment to be deleted: ");
	getchar();
	scanf("%s", en);

	//traverses through the list
	while(temp != NULL && strcmp(temp->employee_num, en) != 0 ){
		temp = temp->nextEmployee;
	}
	if(temp == NULL) printf("\n\tNo match found.\n");
	else{
		temp2 = temp->appointmentPtr;
		if(temp2 == NULL) printf("\tNo appointment to delete.\n");
		else{
			printf("\tEnter appointment number to be deleted: ");
			scanf("%d", aID);

			//traverses through appointments pointer
			while(temp2 != NULL && temp2->appointment_id != aID){
				temp2 = temp2->nextAppointment;
			}
			if(temp2 == NULL) printf("\tAppointment not found. Please try again.\n");
			else{
				if(temp2 == temp->appointmentPtr){
					temp->appointmentPtr = NULL;
					free(temp2);
				}
				else{
					//hold the node to be deleted
					appointment *temp3;					
					temp3 = temp2;

					if(temp2->nextAppointment != NULL){
						temp2->nextAppointment->prevAppointment = temp2->prevAppointment;
						temp2->prevAppointment->nextAppointment = temp2->nextAppointment;
						free(temp3);						
					}
					else{
						temp2->nextAppointment = NULL;
						free(temp3);
					}
				}
				printf("\tAppointment successfully deleted!\n");
			}			
		}
	}
	sleep(2);

}

void exitProgram(employee **employeePtr){
	employee *temp;
	appointment *temp2;

	//deletes the entire linked list
	if(*employeePtr != NULL){
		do{
			temp = *employeePtr;
			if(temp->appointmentPtr != NULL){
				temp2 = temp->appointmentPtr;
				while(temp2 != NULL){
					//holds node to be deleted
					appointment *temp3;
					temp3 = temp2;
					temp2 = temp2->nextAppointment;
					free(temp3);				
				}
			}
			*employeePtr = (*employeePtr)->nextEmployee;
			free(temp);

		}while(*employeePtr != NULL);		
	}
}

