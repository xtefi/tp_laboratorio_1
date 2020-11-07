#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "controller.h"
#include "utn.h"
#include "parser.h"
#define NOMBRE_LEN 128

/** \brief devuelve un ID disponible de la lista.
 *
 * \param pArrayListEmployee LinkedList*
 * \return posicion disponible. Int
 */
int controller_buscaIdLibre(LinkedList* pArrayListEmployee)
{
	int len = ll_len(pArrayListEmployee);
	int position = len + 1;
	Employee* empleado;
	Employee* auxEmpleado = employee_new();
	for(int i = 1; i < len - 1 ; i++)
	{
		empleado = ll_get(pArrayListEmployee, i+1);
		auxEmpleado = ll_get(pArrayListEmployee, i);
		if(!( (auxEmpleado)->id+1 == (empleado)->id ))
		{
			position = (auxEmpleado)->id+1;
			break;
		}
		else
		{
			position = (empleado)->id+1;
		}
	}
	return position;
}
/** \brief Ordenamiento de Empleados por ID
 *
 * \param void* pEmployeeA
 * \param void* pEmployeeB
 * \return 0
 *
 */
int controller_ordenaId(void* pEmployeeA, void* pEmployeeB)
{
    if(((Employee*)pEmployeeA)->id > ((Employee*)pEmployeeB)->id)
    {
        return 1;
    }
    if(((Employee*)pEmployeeA)->id < ((Employee*)pEmployeeB)->id)
    {
        return -1;
    }
    return 0;
}
/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	FILE* pFile;
	pFile= fopen(path, "r+");
	if(!parser_EmployeeFromText(pFile, pArrayListEmployee))
	{
		retorno =0;
		printf("\nLista de empleados cargada con exito");
	}
	fclose(pFile);
	return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	FILE* pFile= fopen(path, "r+");
	if(!parser_EmployeeFromBinary(pFile,pArrayListEmployee))
	{
		retorno = 0;
		printf("\nLista en binario cargada con exito.\n");

	}
	else printf("\nNo se pudo cargar la lista en binario.\n");
	fclose(pFile);
    return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	Employee* auxEmpleado=NULL;
	int id;
	int horasTrabajadas;
	int sueldo;
	char nombre[128];
	if(pArrayListEmployee !=NULL)
	{
		auxEmpleado=employee_new();
		ll_sort(pArrayListEmployee, controller_ordenaId, 1);
		if(auxEmpleado!=NULL)
		{
			id=controller_buscaIdLibre(pArrayListEmployee);
			if(!utn_getNombre(nombre,125,"\nIngrese nombre: ","\nError solo letras, reintente: ",2) &&
			   !utn_getNumero(&horasTrabajadas,"\nIngrese horas trabajadas entre 0hs y 720hs: ","\nError, solo numeros, reintente: ",0,720,2) &&
			   !utn_getNumero(&sueldo,"\nIngrese sueldo: ","\n Error, solo numeros, reintente: ",0,999999,2))
			{
				employee_setId(auxEmpleado, id);
				employee_setNombre(auxEmpleado,nombre);
				employee_setSueldo(auxEmpleado,sueldo);
				employee_setHorasTrabajadas(auxEmpleado,horasTrabajadas);
				retorno=0;
				ll_add(pArrayListEmployee,auxEmpleado);
			}
		}
	}
	return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	int limite=ll_len(pArrayListEmployee);
	int auxId;
	int sueldo;
	int jornada;
	int opciones;
	Employee* auxEmpleado;

	if(pArrayListEmployee!=NULL && limite>0 &&
			!utn_getNumero(&auxId,"\nIngrese el ID del Empleado a modificar: ", "\nError, reintente: ", 0,limite,2))
	{
		auxEmpleado = ll_get(pArrayListEmployee, auxId-1);
		if(!employee_getId(auxEmpleado, &auxId))
		{
			do
			{
				utn_getNumero(&opciones,"\nElija opcion a modificar"
										"\n1. Nombre"
										"\n2. Salario"
										"\n3. Horas trabajadas"
										"\n4. Volver al menu anterior\n", "\nError, reintente:", 1, 4, 2);
				switch(opciones)
				{
					case 1:
						utn_getDescripcion(auxEmpleado->nombre, NOMBRE_LEN, "\nIngrese nombre del empleado: ", "Error, reintente: \n", 1);
					break;
					case 2:
						utn_getNumero(&sueldo, "\nIngrese nuevo salario: ", "Error, reintente", 0, 999999, 1);
						employee_setSueldo(auxEmpleado, sueldo);
					break;
					case 3:
						utn_getNumero(&jornada, "\nIngrese horas trabajadas entre 0hs y 720hs ", "Error, reintente", 0, 720, 1);
						employee_setHorasTrabajadas(auxEmpleado,sueldo);
					break;
				}//switch
			}while(opciones!=4);
		}
		else
		{
			printf("Error, ID no encontrado");
		}
	}//PRIMER IF
	else
	{
		printf("Error, no hay clientes cargados");
	}
    return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return (-1) si hubo ERROR
 * 			(0) si funciono correctamente
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int auxId;
	int respuesta;
	int len=ll_len(pArrayListEmployee);
	Employee* auxEmpleado;
	Employee* empleado;
	if(!utn_getNumero(&auxId,"\n\nIngrese ID del empleado a eliminar: ","\nError verifique los datos ingresados",0,999999,2))
	{
		auxEmpleado=ll_get(pArrayListEmployee, auxId-1);
	    for(int i=0; i<=len; i++)
	    {
	        empleado = ll_get(pArrayListEmployee, i);
	        if((auxEmpleado)->id == (*empleado).id)
	        {
				utn_getNumero(&respuesta, "Desea eliminar?"
									"\nIngrese 1 para proceder "
									"\nIngrese 2 para cancelar ", "\nError, reintente", 1,2,1);
				if(respuesta == 1)
				{
					employee_delete(empleado);
					ll_remove(pArrayListEmployee, auxId-1);
					printf("\nEmpleado eliminado con exito\n");
					retorno=0;
					break;
				}
				else if(respuesta==2)
				{
					printf("Se cancela eliminacion del ID %i\n", auxId);
					break;
				}
	        }
	    }
	}
	return retorno;
}
/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int i;
    int limite=ll_len(pArrayListEmployee);
    Employee* auxEmpleado;
    auxEmpleado = employee_new();
    if(pArrayListEmployee!=NULL && limite>0)
    {
		printf("\n\nID   |Nombre          |Salario  |Horas trabajadas");
		for(i= 0; i < limite; i++)
		{
			auxEmpleado=ll_get(pArrayListEmployee, i);
			if(auxEmpleado->id > 0)
			{
				printf("\n%-4d |%-15s |$%-7d |%-3d", auxEmpleado->id, auxEmpleado->nombre, auxEmpleado->sueldo, auxEmpleado->horasTrabajadas);
			}
		}
    }
    else
    {
    	printf("Error, no hay clientes cargados");
    }
    return 0;
}
/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	if(pArrayListEmployee != NULL)
	{
		if(!ll_sort(pArrayListEmployee,employee_ordenaNombre,1))
		{
			retorno = 0;
			printf("\nLista ordenada con exito.\n");
			controller_ListEmployee(pArrayListEmployee);
		}
		else printf("\nError, la lista no se pudo ordenar\n");
	}
	return retorno;
}
/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	Employee* auxEmpleado;
	FILE* pFile;
	pFile = fopen(path, "w+");
	if(pFile != NULL)
	{
		fprintf(pFile, "%s,%s,%s,%s\n", "id", "nombre", "horasTrabajadas" , "sueldo");
		for(int i=0; i < ll_len(pArrayListEmployee); i++)
		{
			auxEmpleado = (Employee*)ll_get(pArrayListEmployee, i);
			fseek(pFile, 0L, SEEK_END);
			fprintf(pFile, "%i,%s,%i,%i\n", auxEmpleado->id, auxEmpleado->nombre, auxEmpleado->horasTrabajadas, auxEmpleado->sueldo);
		}
	}
	ll_clear(pArrayListEmployee);
	printf("\nArchivo Guardado en modo texto.");
	fclose(pFile);
	return 1;
}
/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	FILE *pFile;
	int retorno =-1;
	int len=ll_len(pArrayListEmployee);
	Employee* auxEmpleado;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		pFile=fopen(path,"w+");
		if(pFile != NULL)
		{
			retorno=0;
			for(int i=0;i<len;i++)
			{
				auxEmpleado=(Employee*)ll_get(pArrayListEmployee, i);
				fwrite(auxEmpleado, sizeof(Employee), 1, pFile);
			}
		}
	}
	fclose(pFile);
    return retorno;
}
