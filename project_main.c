/*-----------------------------------------------------\
| 													   |				
|	Main C file for project.						   |
|	Includes all function calls	  					   |
|							 						   |
|	Ryan Nathaniel B. Resoles						   |
\_____________________________________________________*/

#include "project_header.h"


int main(){
	int choice;

	// file initialization

	// main pointer to the linked list
	employee *employeePtr = NULL;

	do{
		choice = mainMenu();
		switch(choice){
			case 1:
				// Function that adds employee 
				addEmployee(&employeePtr);
				break;
			case 2: 
				// function for editing inndividual emplyee
				editEmployee(&employeePtr);
				break;
			case 3: 
				// function for deleting selected employee
				deleteEmployee(&employeePtr);
				break;
			case 4: 
				// function that displays employee(s)
				viewEmployee(employeePtr);
				break;
			case 5: 
				// adds appointment to selected employee
				addAppointment(&employeePtr);
				break;
			case 6: 
				// edits selected employee
				editAppointment(&employeePtr);
				break;
			case 7: 
				// deletes selected employee
				deleteAppointment(&employeePtr);
				break;
			case 0:
				// saves current data to file
				exitProgram(&employeePtr);
				printf("\n"); 
				printf("\tProgram exits . . .\n");
				sleep(2);
				system("cls");
				save(&employeePtr);
				break;
			default:
				printf("\n");
				printf("\tInvalid choice!\n");
				break;
		}
	}while(choice != 0);
}