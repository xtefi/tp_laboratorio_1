#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "utn.h"
#define NOMBRE_LEN 128

static int esDescripcion(char* cadena,int longitud);
static int esNumerica(char* cadena, int limite);
/**
 * \brief Verifica si la cadena ingresada es una descripcion valida
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 */
static int esDescripcion(char* cadena,int longitud)
{
	int retorno = 1;
	if(cadena != NULL && longitud > 0)
	{
		for(int i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if(cadena[i] != '.' && cadena[i] != ' ' && (cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ) && (cadena[i] < '0' || cadena[i] > '9' ) )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es numerica
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es numerica, 0 (falso) si no lo es y -1 en caso de error
 */
static int esNumerica(char* cadena, int limite)
{
	int retorno = -1;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1;
		for(int i=0;i<limite && cadena[i] != '\0';i++)
		{
			if(i==0 && (cadena[i] == '+' || cadena[i] == '-'))
			{
				continue;
			}
			if(cadena[i] < '0'||cadena[i] > '9')
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/** \brief reserva un espacio de memoria
 *
 * \param void
 * return Retorna el elemento si reserva memoria sino NULL
 *
 */
Employee* employee_new(void)
{
	return (Employee*) malloc(sizeof(Employee));
}
/**
*\brief Se realiza el alta de un elemento desde consola
*\param pArrayListEmployee Es el array para ingresar elemento
*\return Retorna 0 si logra agregar elemento sino retorna -1
*/
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* this = NULL;
	this = employee_new();

	if(this!= NULL && idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL && sueldoStr != NULL)
	{
		employee_setIdTxt(this, idStr) ;
		employee_setNombre(this,nombreStr);
		employee_setSueldoTxt(this, sueldoStr);
		employee_setHorasTrabajadasTxt(this,horasTrabajadasStr);
	}
	return this;
}

Employee* employee_newParametrosBin(Employee this)
{

	Employee* auxEmpleado;
	auxEmpleado = employee_new();
	employee_setId(auxEmpleado, this.id);
	employee_setNombre(auxEmpleado, this.nombre);
	employee_setHorasTrabajadas(auxEmpleado, this.horasTrabajadas);
    employee_setSueldo(auxEmpleado, this.sueldo);

	    return auxEmpleado;
}


/** \brief libera un espacio de memoria ocupado por un elemento
 *
 * \param void
 * \return void
 *
 */
void employee_delete(Employee* this)
{
	if( this != NULL)
	{
		free(this);
	}
}
//------------------------------------------NOMBRE-------------------------------

/**
*\brief Se setea el nombre del elemento
*\param this Es el elemento
*\param nombre Es el nombre para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int employee_setNombre(Employee* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		if(esDescripcion(nombre, NOMBRE_LEN))
		{
			strncpy(this->nombre, nombre, NOMBRE_LEN);
			retorno = 0;
		}
	}
	return retorno;
}

/**
*\brief Se obtiene el nombre del elemento
*\param this Es el elemento
*\param nombre Es el nombre que se obtiene
*\return Retorna 0 si obtiene elemento sino retorna -1
*/
int employee_getNombre(Employee* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		retorno = 0;
		strncpy(nombre, this->nombre, NOMBRE_LEN);
	}
	return retorno;
}

//------------------------------------------ID-------------------------------

/**
*\brief Se setea el ID del elemento
*\param this Es el elemento
*\param id Es el ID para setear
*\return Retorna 0 si setea sino -1
*/
int employee_setId(Employee* this,int id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
			retorno = 0;
			this->id=id;
	}
	return retorno;
}
/**
*\brief Se setea el ID del elemento como texto
*\param this Es el elemento
*\param id Es el ID para setear
*\return Retorna 0 si setea sino -1
*/
int employee_setIdTxt(Employee* this,char* id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
		if(esNumerica(id,50))
		{
			retorno = 0;
			this->id= atoi(id);
		}
	}
	return retorno;
}
/**
*\brief Se obtiene el ID del elemento
*\param this Es el elemento
*\param id Es el ID que se obtiene
*\return Retorna 0 si obtiene sino retorna -1
*/
int employee_getId(Employee* this,int* id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
			retorno = 0;
			(*id)=this->id;
	}
	return retorno;
}
/**
*\brief Se obtiene el ID del elemento como texto
*\param this Es el elemento
*\param id Es el ID que se obtiene
*\return Retorna 0 si obtiene sino retorna -1
*/
int employee_getIdTxt(Employee* this,char* id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
		retorno = 0;
		sprintf(id,"%d",this->id);
	}
	return retorno;
}

//------------------------------------------Sueldo-------------------------------

/**
*\brief Se setea el sueldo del elemento
*\param this Es el elemento
*\param sueldo Es el sueldo para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int employee_setSueldo(Employee* this,int sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo >= 0)
	{
		retorno = 0;
		this->sueldo=sueldo;
	}
	return retorno;
}
/**
*\brief Se setea el sueldo del elemento como texto
*\param this Es el elemento
*\param sueldo Es el sueldo para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int employee_setSueldoTxt(Employee* this,char* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo >= 0)
	{
		if(esNumerica(sueldo,50))
		{
			retorno = 0;
			this->sueldo=atoi(sueldo);
		}
	}
	return retorno;
}

/**
*\brief Se obtiene el sueldo del elemento
*\param this Es el elemento
*\param sueldo Es el sueldo que se obtiene
*\return Retorna 0 si setea elemento sino retorna -1
*/
int employee_getSueldo(Employee* this,int* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo >= 0)
	{
		retorno = 0;
		(*sueldo)=this->sueldo;
	}
	return retorno;
}

/**
*\brief Se obtiene el sueldo del elemento como texto
*\param this Es el elemento
*\param sueldo Es el sueldo que se obtiene
*\return Retorna 0 si setea elemento sino retorna -1
*/
int employee_getSueldoTxt(Employee* this,char* sueldo)
{
	int retorno = -1;

	if(this != NULL && sueldo >= 0)
	{
		retorno = 0;
		sprintf(sueldo,"%d",this->sueldo);
	}
	return retorno;
}
//------------------------------------------Horas trabajadas-------------------------------

/**
*\brief Se setea las horas trabajadas del elemento
*\param this Es el elemento
*\param horasTrabajadas Es la cantidad de horas para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas >= 0)
	{
		retorno = 0;
		this->horasTrabajadas=horasTrabajadas;
	}
	return retorno;
}
/**
*\brief Se setea las horas trabajadas del elemento
*\param this Es el elemento
*\param horasTrabajadas Es la cantidad de horas para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int employee_setHorasTrabajadasTxt(Employee* this,char* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas >= 0)
	{
			if(esNumerica(horasTrabajadas, 50) )
			{
				retorno = 0;
				this->horasTrabajadas=atoi(horasTrabajadas);
			}
	}
	return retorno;
}

/**
*\brief Se obtienen las horas trabajadas del elemento
*\param this Es el elemento
*\param horasTrabajadas Es la cantidad de horas que se obtiene
*\return Retorna 0 si setea elemento sino retorna -1
*/
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL &&  horasTrabajadas>= 0)
	{
		retorno = 0;
		(*horasTrabajadas)=this->horasTrabajadas;
	}
	return retorno;
}
/**
*\brief Se obtienen las horas trabajadas del elemento como texto
*\param this Es el elemento
*\param horasTrabajadas Es la cantidad de horas que se obtiene
*\return Retorna 0 si setea elemento sino retorna -1
*/
int employee_getHorasTrabajadasTxt(Employee* this,char* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas >= 0)
	{
		retorno = 0;
		sprintf(horasTrabajadas,"%d",this->horasTrabajadas);
	}
	return retorno;
}
/**
*\brief base para comparar el campo de dos elementos
*\param this1 primer elemento
*\param this2 segundo elemento
*\return retorna 1 si el primer elemento es mayor, -1 si el segundo elemento es mayor, caso contrario retorna 0
*/
int employee_ordenaNombre(void* this1, void* this2)
{
	int retorno = 0;
	char nombre1[128];
	char nombre2[128];
	Employee* empAux1= NULL;
	Employee* empAux2= NULL;
	if(this1 != NULL && this2!= NULL)
	{
		empAux1= (Employee*)this1;
		empAux2= (Employee*)this2;
		if(employee_getNombre(empAux1,nombre1)==0 && employee_getNombre(empAux2,nombre2)==0)
		{
			if(strcmpi(nombre1, nombre2) > 0)
			{
				retorno = 1;
			}
			if(strcmpi(nombre1, nombre2) < 0)
			{
				retorno = -1;
			}
		}
	}
	return retorno;
}


