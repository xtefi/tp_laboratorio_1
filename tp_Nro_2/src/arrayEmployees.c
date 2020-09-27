/*
 * employee.c
 *
 *  Created on: 26 sep. 2020
 *      Author: 54113
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_SIZE 51
#define LASTNAME_SIZE 51
#define MAX_SALARY 1000000
#define MIN_SALARY 1
#define MAX_SECTOR 20
#define MIN_SECTOR 1
#define QTY_EMPLOYEE 1000
#include "utn.h"
#include "arrayEmployees.h"


/** \brief To indicate that all position in the array are empty,
* this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param array Employee* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int initEmployees(Employee* array, int len)
{
	int retorno = -1;
	if(array != NULL && len>0)
	{
		for(int i=0; i< len; i++)
		{
			array[i].isEmpty=1;
			retorno=0;
		}
		printf("Array inicializado correctamente");
	}
	return retorno;
}

/** \brief get one empty slot from de array
*
* \param array Employee* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - or empty position if Ok
*
*/
int findEmptySlot(Employee* array, int len)
{
	int retorno=-1;
	if(array != NULL && len >0)
	{
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].isEmpty==1)
			{
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}

/** \brief add in a existing list of employees the values received as parameters
* in the first empty position
* \param list employee*
* \param len int
* \param id int
* \param name[] char
* \param lastName[] char
* \param salary float
* \param sector int
* \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space]
*
*/
int addEmployees(Employee* array, int len, int* id, int index)
{
	int retorno=-1;
	Employee buffer;
	index=findEmptySlot(array, len);
	if(array != NULL && len > 0 && id != NULL && index >=0 && index <= len)
	{
		if(utn_getDescripcion(buffer.name, NAME_SIZE ,"Ingrese nombre: ", "\nError, tiene un reintento: ", 1) == 0 &&
		   utn_getDescripcion(buffer.lastName, LASTNAME_SIZE,"Ingrese apellido: ", "\nError, tiene un reintento: ", 1) == 0 &&
		   utn_getNumeroFlotante(&buffer.salary, "Ingrese salario, entre $1 y $1000000: ", "\nError, esta fuera del rango, tiene un reintento: ", MIN_SALARY, MAX_SALARY,1) == 0 &&
		   utn_getNumero(&buffer.sector, "Ingrese numero de sector, entre 1 y 20: ", "\nError, esta fuera del rango, reintente: ", MIN_SECTOR, MAX_SECTOR, 1) == 0)
		{
			retorno=0;
			buffer.isEmpty=0;
			buffer.id=(*id);
			array[index]=buffer;
			(*id)++;
		}
	}
	return retorno;
}

/** \brief print one employee
*
* \param array Employee*
*\return void
*/
void printOneEmployee(Employee* array)
{
	if(array != NULL)
	{
		printf("%-4i |%-15s |%-15s |$%-8.2f |%-6i\n", array->id, array->name, array->lastName, array->salary, array->sector);
	}
}

/** \brief print the content of employees array
*
* \param array Employee*
* \param len int
* \return int
*
*/
int printEmployees(Employee* array, int len)
{
	if(array != NULL && len>0)
	{
		printf("ID   |NAME            |LAST NAME       |SALARY    |SECTOR\n");
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].isEmpty==0)
			{
				printOneEmployee(&array[i]);
			}
		}
	}
	return 0;
}
/** \brief find an Employee by Id and returns the index position in array.
*
* \param list Employee*
* \param len int
* \param id int
* \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
*
*/
int findEmployeeById(Employee* array, int len, int value)
{
	int retorno=-1;
	value=utn_getNumero(&value, "Ingrese ID a buscar: \n", "Error, solo numeros, tiene un reintento \n", 0,QTY_EMPLOYEE-1, 1);
	if(array != NULL && len >0)
	{
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].id==value)
			{
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}
/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
*
* \param array Employee*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
*
*/
int removeEmployee(Employee* array, int len, int id)
{
	int retorno=-1;
	if(array != NULL && len > 0)
	{
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].id == id && array[i].isEmpty==0)
			{
				array[i].isEmpty=1;
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief sort the array first by name and then by sector
* \param array Employee*
* \param len int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
*
 */
int sortArray(Employee* array, int len)
{
	int flagSwap;
	int retorno=-1;
	Employee buffer;

	if(array != NULL && len > 0)
	{
		do
		{
			flagSwap = 0;
			for(int i=0;i<len-1;i++)
			{
				if(array[i].isEmpty==1 || array[i+1].isEmpty==1)
					{
						continue;
					}
					if(strncmp(array[i].name,array[i+1].name,NAME_SIZE) > 0)
					{
						flagSwap = 1;
						buffer = array[i];
						array[i] = array[i+1];
						array[i+1]=buffer;
					}
					else if(strncmp(array[i].name,array[i+1].name,NAME_SIZE) == 0)
					{
						if(array[i].sector > array[i+1].sector)
						{
							flagSwap = 1;
							buffer = array[i];
							array[i] = array[i+1];
							array[i+1]=buffer;
						}
					}
			}
			len--;
		}while(flagSwap);
	}
	return retorno;
}
/**
 * \brief sort the array by name
* \param array Employee*
* \param len int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
*
 */
int sortByName(Employee* array,int len)
{
	int retorno = -1;
	int flagSwap;
	Employee buffer;
	if(array != NULL && len > 0)
	{
		do
		{
			flagSwap = 0;
			for(int i=0;i<len-1;i++)
			{
				if(array[i].isEmpty==1 || array[i+1].isEmpty==1)
				{
					continue;
				}
				if(strncmp(array[i].name,array[i+1].name,NAME_SIZE) > 0)
				{
					flagSwap = 1;
					buffer = array[i];
					array[i] = array[i+1];
					array[i+1]=buffer;
				}
			}
			len--;
		}while(flagSwap);
		retorno=0;
	}
	return retorno;
}
/**
 * \brief information about salary
* \param array Employee*
* \param len int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't find a employee] - (0) if Ok
*
 */
int salaryInfo(Employee* array ,int len)
{
	int acumuladorDeuda=0;
	float total;
	float average;
	int counter=0;
	int retorno = -1;
	int maxSalaryCounter=0;

	if(array != NULL && len >= 0)
	{
		retorno = 0;
		for(int i=0;i<len;i++)
		{
			if(array[i].isEmpty==1) // 1 o 0?
			{
				continue;
			}
			acumuladorDeuda+=(array[i].salary);
			counter++;
		}
	}
	total=(float)acumuladorDeuda;
	average=total/counter;

	for(int j=0; j<len; j++)
	{
		if(average < array[j].salary && array[j].isEmpty==0)
		{
			maxSalaryCounter++;
		}
	}
	printf("\nSuma total de salarios: $%.2f\n", total);
	printf("Salario promedio: $%.2f\n", average);
	printf("Cantidad de empleados que superan el salario promedio: %d\n", maxSalaryCounter);
	return retorno;
}
/** \brief update an array position
*
* \param list Employee*
* \param len int
* \param value int
* \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
*
*/
int updateEmployeeInformation(Employee* array, int len, int value)
{
	int retorno=-1;
	int update;
	Employee buffer;

	if(array != NULL && len>=0)
	{
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].id == value && array[i].isEmpty == 0 && !utn_getNumero(&update, "Ingrese opcion a modificar:\n"
															"1. Nombre\n"
															"2. Apellido\n"
															"3. Sector\n"
															"4. Salario\n"
															"5. Salir\n", "Error, no esta dentro del rango, reintente: \n", 1, 5, 1))
			{
				switch(update)
				{
				case 1:
					if(!utn_getDescripcion(buffer.name, NAME_SIZE, "Reingrese nombre: \n", "Error, no esta dentro del rango, reintente: \n", 1))
					{
						strcpy(buffer.lastName,array[i].lastName);
						buffer.salary=array[i].salary;
						buffer.sector=array[i].sector;
						buffer.id=array[i].id;
						array[i]=buffer;
						array[i].isEmpty=0;
						retorno=0;
						printf("Nombre modificado correctamente\n");
					}
					break;

				case 2:
					if(!utn_getDescripcion(buffer.lastName, NAME_SIZE, "Reingrese apellido: \n", "Error, no esta dentro del rango, reintente: \n", 1))
					{
						strcpy(buffer.name,array[i].name);
						buffer.salary=array[i].salary;
						buffer.sector=array[i].sector;
						buffer.id=array[i].id;
						array[i]=buffer;
						array[i].isEmpty=0;
						retorno=0;
						printf("Apellido modificado correctamente\n");
					}
					break;

				case 3:
					if(!utn_getNumero(&buffer.sector, "Reingrese sector, del 1 al 20 \n", "Error, no esta dentro del rango, reintente: ", MIN_SECTOR, MAX_SECTOR, 1))
					{
						strcpy(buffer.name,array[i].name);
						strcpy(buffer.lastName,array[i].lastName);
						buffer.salary=array[i].salary;
						buffer.id=array[i].id;
						array[i]=buffer;
						array[i].isEmpty=0;
						retorno=0;
						printf("Sector modificado correctamente\n");
					}
					break;

				case 4:
					if(!utn_getNumeroFlotante(&buffer.salary,"Reingrese salario: \n", "Error, no esta dentro del rango, reintente: \n", MIN_SALARY, MAX_SALARY, 1))
					{
						strcpy(buffer.name,array[i].name);
						strcpy(buffer.lastName,array[i].lastName);
						buffer.sector=array[i].sector;
						buffer.id=array[i].id;
						array[i]=buffer;
						array[i].isEmpty=0;
						retorno=0;
						printf("Salario modificado correctamente\n");
					}
					break;
				}//switch
				break;
			}//if
		}//for

	}
	return retorno;
}
/** \brief upload information for testing
*
* \param list Employee*
* \param len int
* param index int
* \param id int
* param name char
* param lastName char
* param salary float
* param sector int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
*
*/
int forceArray(Employee* array,int len, int index, int* id,char* name,char* lastName, float salary ,int sector)
{
	int retorno = -1;
	Employee bufferEmployee;

	if(array != NULL && len > 0 && index < len && index >= 0 && id != NULL)
	{
			strncpy(bufferEmployee.name,name,NAME_SIZE);
			strncpy(bufferEmployee.lastName,lastName,LASTNAME_SIZE);
			bufferEmployee.sector = sector;
			bufferEmployee.salary = salary;
			retorno = 0;
			bufferEmployee.id = *id;
			bufferEmployee.isEmpty = 0;
			array[index] = bufferEmployee;
			(*id)++;
	}
	return retorno;
}
