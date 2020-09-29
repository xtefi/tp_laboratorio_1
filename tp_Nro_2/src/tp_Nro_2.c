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
#include "arrayEmployees.h"


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

	forceArray(array,QTY_EMPLOYEE, 0,&auxId,"Monrgomery","Scott", 430, 17);
	forceArray(array,QTY_EMPLOYEE, 2,&auxId,"Leonard","McCoy", 2522, 4);
	forceArray(array,QTY_EMPLOYEE, 3,&auxId,"Hikaru","Sulu", 200, 2);
	forceArray(array,QTY_EMPLOYEE, 4,&auxId,"James Tiberuis","Kirk", 340, 4);
	forceArray(array,QTY_EMPLOYEE, 5,&auxId,"Leonard","Nimoy", 1359, 1);

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
							if(updateEmployeeInformation(array, QTY_EMPLOYEE, auxId)==0)
								{
									printf("Empleado modificado correctamente");
								}
							else if(updateEmployeeInformation(array, QTY_EMPLOYEE, auxId)!=0)
								{
									printf("Error, ID invalido");
								}
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
						sortArray(array, QTY_EMPLOYEE);
						printEmployees(array, QTY_EMPLOYEE);
						salaryInfo(array, QTY_EMPLOYEE);
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


