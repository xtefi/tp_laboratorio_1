/*
 ============================================================================
 Name        : tp_Nro_2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_SIZE 51
#define LASTNAME_SIZE 51
#define QTY_EMPLOYEE 1000
#include "utn.h"
#include "employee.h"


int main(void) {
	setbuf(stdout,NULL);

	int menu;
	int informes;
	int flag=1;
	Employee array[QTY_EMPLOYEE];
	int auxId;
	int auxIndex;

	if(initEmployees(array, QTY_EMPLOYEE)==0)
	{
		printf("Array inicializado correctamente\n");
	}

	forceArray(array,QTY_EMPLOYEE, 0,&auxId,"Juan Alfredo","Johnson", 430, 17);
	forceArray(array,QTY_EMPLOYEE, 2,&auxId,"Lina","Parker", 2522, 4);
	forceArray(array,QTY_EMPLOYEE, 3,&auxId,"Alba","Frisco", 200, 2);
	forceArray(array,QTY_EMPLOYEE, 4,&auxId,"Caleb","Bush", 340, 4);
	forceArray(array,QTY_EMPLOYEE, 5,&auxId,"Juan Alfredo","Smith", 1359, 1);

	do
	{
		if(!utn_getNumero(&menu, "\n**Ingrese una opcion del menu**\n"
										"1. Altas\n"
										"2. Modificar\n"
										"3. Bajas\n"
										"4. Informar\n"
										"5. Salir\n", "Error, opcion invalida, reintente: \n", 1, 5, 3))
		{
			switch(menu)
			{
				case 1:
					auxIndex=findEmptySlot(array,QTY_EMPLOYEE);
					if(addEmployees(array, QTY_EMPLOYEE, &auxId, auxIndex)==0)
					{
						printf("Empleado cargado correctamente\n");
						flag=0;
					}
					break;

				case 2:
					if(flag == 0)
					{
						printEmployees(array, QTY_EMPLOYEE);
						if(!utn_getNumero(&auxId, "Ingrese ID del empleado a modificar: \n", "Error, solo numeros: \n", 0, QTY_EMPLOYEE,1))
						{
							updateEmployeeInformation(array, QTY_EMPLOYEE, auxId);
						}
					}
					else
					{
						printf("Error, no hay empleados cargados. Intente con la opcion 1 del menu\n");
					}
					break;

				case 3:
					if(flag == 0)
					{
						printEmployees(array, QTY_EMPLOYEE);
						if(!utn_getNumero(&auxId, "Ingrese ID de empleado para dar de baja: ", "Error, no esta dentro del rango, reintente", 0, 999, 2))
						{
							if(removeEmployee(array, QTY_EMPLOYEE, auxId)==0)
							{
								printf("Empleado dado de baja");
							}
						}
					}
					else
					{
						printf("Error, no hay empleados cargados. Intente con la opcion 1 del menu\n");
					}
				break;

				case 4:
					if(flag == 0)
					{
						if(!utn_getNumero(&informes,"Que informacion desea ver?\n"
								"1. Listado de los empleados ordenados alfabéticamente por Apellido y Sector. \n"
								"2. Total y promedio de los salarios, y cuántos empleados superan el salario promedio. \n","Error, esa opcion no esta en el menu, reintente: \n", 1, 2, 1))
						{
							switch(informes)
							{
								case 1:
									sortArray(array, QTY_EMPLOYEE);
									printEmployees(array, QTY_EMPLOYEE);
									break;
								case 2:
									salaryInfo(array, QTY_EMPLOYEE);
									break;
							}//switch informes
						}//if get informes
					}//if flag menu 4
					else
					{
						printf("Error, no hay empleados cargados. Intente con la opcion 1 del menu\n");
					}
					break;
				}// switch menu
		}//if get menu

	}while(menu != 5);

	return EXIT_SUCCESS;
}


