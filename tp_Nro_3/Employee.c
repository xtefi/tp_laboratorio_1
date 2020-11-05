
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Employee.h"

/** \brief reserva un espacio de memoria
 *
 * \param void
 * return Retorna el elemento si reserva memoria sino NULL
 *
 */
Employee* employee_new()
{
	return (Employee*) malloc(sizeof(Employee));

	/*Modo Disney
    Employee* this;
    this=malloc(sizeof(Employee));
    if(this!=NULL)
    {
        return this;
    }
    else
    {
        return NULL;
    }
	 */
}

/**
*\brief Realiza el alta de un elemento desde consola
*\param idStr cadena para ID
*\param nombreStr cadena para nombre
*\param horasTrabajadasStr cadena para horasTrabajadas
*\param sueldoStr cadena para sueldo
*\return Retorna el elemento creado
*/
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* this;
	this = employee_new;

    int idClienteInt = atoi(idStr);
    int horasTrabajadasInt = atoi(horasTrabajadasStr);
    int sueldoInt = atoi(sueldoStr);

	if(!employee_setIdTxt(this, idStr) &&
	   !employee_setNombre(this,nombreStr) &&
	   !employee_setSueldoTxt(this, sueldoStr) &&
	   !employee_setHorasTrabajadasTxt(this,horasTrabajadasStr))
	{
		return this;
	}

}

Employee* employee_newParametrosBin(Employee this)
{
	Employee* auxiliarEmpleado;
	auxiliarEmpleado=employee_new();
	if(auxiliarEmpleado != NULL && this != NULL)
	{
	    employee_setId(auxiliarEmpleado, this.id);
	    employee_setNombre(auxiliarEmpleado, this.nombre);
	    employee_setHorasTrabajadas(auxiliarEmpleado, this.horasTrabajadas);
	    employee_setSueldo(auxiliarEmpleado, this.sueldo);
	}
	return auxiliarEmpleado;
}

/** \brief libera un espacio de memoria ocupado por un elemento
 *
 * \param this es el elemento
 * \return void
 *
 */
void employee_delete(Employee* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

//int employee_setId(Employee* this,int id)
//int employee_getId(Employee* this,int* id)

//int employee_setNombre(Employee* this,char* nombre)
//int employee_getNombre(Employee* this,char* nombre)

//int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
//int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)

//int employee_setSueldo(Employee* this,int sueldo)
//int employee_getSueldo(Employee* this,int* sueldo)
