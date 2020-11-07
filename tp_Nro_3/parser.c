#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	char auxId[5000];
	char auxNombre[5000];
	char auxSueldo[5000];
	char auxJornada[5000];
	Employee* pEmpleado;

	if(pArrayListEmployee != NULL && pFile != NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxNombre,auxSueldo,auxJornada);
		do
		{
			fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxNombre,auxSueldo,auxJornada);
			pEmpleado = employee_newParametros(auxId, auxNombre,auxJornada,auxSueldo);

			if(pEmpleado != NULL)
			{
				retorno = 0;
				ll_add(pArrayListEmployee,pEmpleado);
			}
		}while(!feof(pFile));
	}
    return retorno;
}

/** \brief Parsea los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	Employee* pEmpleado;
	int lectura;

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		printf("ID   |Nombre          |Salario  |Horas trabajadas\n");
		do
		{
			pEmpleado=employee_new();
			lectura=fread(pEmpleado,sizeof(Employee),1,pFile); //1 porque leo una sola vez
			if(lectura == 1)
			{
				ll_add(pArrayListEmployee, pEmpleado);
				printf("%-4d |%-15s |$%-7d |%-3d\n", pEmpleado->id, pEmpleado->nombre, pEmpleado->sueldo, pEmpleado->horasTrabajadas);
				retorno = 0;
			}
			else
			{
				employee_delete(pEmpleado);
			}
		}while(!feof(pFile));
	}
    return retorno;
}
