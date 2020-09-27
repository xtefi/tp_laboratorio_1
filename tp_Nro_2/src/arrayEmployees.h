/*
 * employee.h
 *
 *  Created on: 26 sep. 2020
 *      Author: 54113
 */

#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_

#define NAME_SIZE 51
#define LASTNAME_SIZE 51

typedef struct
{
	int id;
	char name[NAME_SIZE];
	char lastName[LASTNAME_SIZE];
	float salary;
	int sector;
	int isEmpty;
}Employee;

int initEmployees(Employee* array, int len);
int findEmptySlot(Employee* array, int len);
int addEmployees(Employee* array, int len, int* id, int index);
int printEmployees(Employee* array, int len);
void printOneEmployee(Employee* array);
int findEmployeeById(Employee* array, int len, int value);
int removeEmployee(Employee* array, int len, int id);
int sortArray(Employee* array, int len);
int salaryInfo(Employee* array ,int len);
int sortByName(Employee* array,int len);
int updateEmployeeInformation(Employee* array, int len, int value);
int forceArray(Employee* array,int len, int index, int* id,char* name,char* lastName, float salary ,int sector);

#endif /* ARRAYEMPLOYEES_H_ */
