/*
 * calculos.c
 *
 *  Created on: 1 sep. 2020
 *      Author: Estefania
 */
#include <stdio.h>
#include <stdlib.h>
#include "calculos.h"

/* \brief suma dos numeros ingresados por el usuario
 *
 * \param num1 primer numero
 * \param num2 segundo numero
 * \param rdo resultado de la operacion
 *
 * \return Retorna 0 (EXITO) y -1 (ERROR)
*/
int calc_Suma(float num1, float num2, float* rdo)
{
	int retorno=-1;

	if(rdo != NULL)
	{
	*rdo=num1+num2;
	retorno=0;
	}

	return retorno;
}

/* \brief resta dos numeros ingresados por el usuario
 *
 * \param num1 primer numero
 * \param num2 segundo numero
 * \param rdo resultado de la operacion
 *
 * \return Retorna 0 (EXITO) y -1 (ERROR)
*/
int calc_Resta(float num1, float num2, float* rdo)
{
	int retorno=-1;

	if(rdo != NULL)
	{
	*rdo=num1-num2;
	retorno=0;
	}

	return retorno;
}

/* \brief multiplica dos numeros ingresados por el usuario
 *
 * \param num1 primer numero
 * \param num2 segundo numero
 * \param rdo resultado de la operacion
 *
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int calc_Multiplica(float num1, float num2, float* rdo)
{
	int retorno=-1;

	if(rdo != NULL)
	{
	*rdo=num1*num2;
	retorno=0;
	}

	return retorno;
}

/* \brief divide dos numeros ingresados por el usuario
 *
 * \param num1 dividendo
 * \param num2 divisor
 * \param rdo resultado de la operacion
 * \return Retorna 0 (EXITO) y 1 (ERROR)
 */

int calc_Divide(float num1, float num2, float* rdo)
{
	float rdoDivide;
	    int huboError;

	    if(num2!=0)
	    {
	        rdoDivide = num1 / num2;

	        (*rdo)= rdoDivide;

	        huboError=0;
	    }
	    else
	    {
	        huboError=1;
	    }

	        return huboError;
}

/* \brief factoriza numeros
 *
 * \param numero para operar
 *
 * \return resultado de la factorizacion
 */
int calc_Factorial(float numero, int* rdo)
{
    int rdoFact=1;
    int retorno=-1;

    for(int i=1; i <= (int)numero ; i++)
    {
        rdoFact = (rdoFact*i);
        *rdo=rdoFact;
        retorno=0;

    }

    return retorno;
}

