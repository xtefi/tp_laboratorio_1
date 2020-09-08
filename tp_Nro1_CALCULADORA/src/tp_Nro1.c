/*
 ============================================================================
 Name        : tp_Nro1.c
 Author      : Estefania
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "calculos.h"
#include "utn.h"

int main(void) {
	setbuf(stdout,NULL);

	int menu;
	char subMenuCalculos;
	int auxSuma, auxResta, auxMulti, auxDivide, auxFactorial1, auxFactorial2;
	int verificaNro1=-1;
	int verificaNro2=-1;

	float primerNumero=0;
	float segundoNumero=0;
	float rdoSuma, rdoResta, rdoMulti, rdoDivide;
	int rdoFactorial1, rdoFactorial2;


	do
	{

		printf("\n*** OPCIONES DEL MENU ***\n"
				"1. Ingrese primer operando: %.2f\n"
				"2. Igrese segundo operando: %.2f\n"
				"3. Calcular operaciones\n"
				"4. Informar resultado\n"
				"5. salir\n", primerNumero, segundoNumero);
		scanf("%d", &menu);
		fflush(stdin);

		switch(menu)
		{
			case 1:
				if(!utn_getNumeroFlotante(&primerNumero,"Ingrese el primer operando: ", "\nError, debe ser un numero Real, reintente:",-50000000000, 50000000000, 1 ))
				{
					verificaNro1=0;
				}
				break;

			case 2:
				if(!utn_getNumeroFlotante(&segundoNumero,"Ingrese el segundo operando: ", "\nError, debe ser un numero Real, reintente:",-50000000000, 50000000000, 1 ))
				{
					verificaNro2=0;
				}
				break;

			case 3:
				do
				{
					printf("\nElija operaciones a calcular:\n"
							"a. Suma\n"
							"b. Resta\n"
							"c. Multiplicacion\n"
							"d. Division\n"
							"e. Factoriales\n"
							"f. Voler al menu anterior\n");
					scanf("%c", &subMenuCalculos);
					fflush(stdin);

					switch(subMenuCalculos)
					{
					case 'a':
						if(verificaNro1 == 0 && verificaNro2 ==0)
						{
							auxSuma=calc_Suma(primerNumero, segundoNumero, &rdoSuma);
							printf("Suma calculada\n");

						}
						else printf("No hay suficientes numeros ingresados para calcular, ingrese numeros\n");
						break;

					case 'b':
						if(verificaNro1 == 0 && verificaNro2 ==0)
						{
							auxResta=calc_Resta(primerNumero, segundoNumero, &rdoResta);
							printf("Resta calculada\n");

						}
						else printf("No hay suficientes numeros ingresados para calcular, ingrese numeros\n");

						break;
					case 'c':
						if(verificaNro1 == 0 && verificaNro2 ==0)
						{
							auxMulti=calc_Multiplica(primerNumero, segundoNumero, &rdoMulti);
							printf("Multiplicacion efectuada\n");

						}
						else printf("No hay suficientes numeros ingresados para calcular, ingrese numeros\n");
						break;
					case 'd':
						if(verificaNro1 == 0 && verificaNro2==0)
						{
							auxDivide=calc_Divide(primerNumero, segundoNumero, &rdoDivide);

							if(auxDivide == 0)
							{
							printf("Division efectuada\n");
							}
							else if(auxDivide != 0) printf("Error, no se puede dividir por cero\n");
						}

						else printf("No hay suficientes numeros ingresados para calcular, ingrese numeros\n");
						break;
					case 'e':
						if(verificaNro1 == 0 && verificaNro2 == 0)
						{
							auxFactorial1=calc_Factorial(primerNumero, &rdoFactorial1);
							auxFactorial2=calc_Factorial(segundoNumero, &rdoFactorial2);

							if(auxFactorial1 == 0 && auxFactorial2 == 0)
							{
								printf("Factoriales efectuados\n");
							}
						}
						else printf("No hay suficientes numeros ingresados para calcular, ingrese numeros\n");
						break;

					case 'f':
						break;
					}
				}while(subMenuCalculos!='f');

				break;

			case 4:
			{
				if(verificaNro1 == 0 && verificaNro2 ==0)
				{
					if(auxSuma==0) printf("a. El resultado de %.2f + %.2f es: %.2f \n", primerNumero, segundoNumero, rdoSuma);
					else if(auxMulti==0) printf("c. El resultado de %.2f x %.2f es: %.2f \n", primerNumero, segundoNumero, rdoMulti);
					else if(auxResta==0) printf("b. El resultado de %.2f - %.2f es: %.2f \n", primerNumero, segundoNumero, rdoResta);
					else if(auxDivide==0) printf("d. El resultado de %.2f / %.2f es: %.2f \n", primerNumero, segundoNumero, rdoDivide);
					else if(auxFactorial1 == 0 && auxFactorial2 == 0 ) printf("e. El factorial de %.0f ! es: %i y el factorial de %.0f ! es: %i\n", primerNumero, rdoFactorial1, segundoNumero, rdoFactorial2);

				}
				else printf("Error, no hay calculos realizados para informar.\n");
				break;
			}
			case 5:
				break;
		}

	}while(menu!=5);



	return EXIT_SUCCESS;
}
