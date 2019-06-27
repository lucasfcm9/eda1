/* Alunos: Lucas Fellipe Carvalho Moreira && Pedro Henrique Queiroz Mirando && Gabriel Davi Silva Pereira
   Matrículas: 16/0133394 && 15/0144474 && 170010341
   Disciplina: Estruturas de Dados 1
   Professor: Mateus Mendelson
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "function.h"

int main()
{
	srand(time(NULL));

	int *random_numbers = function_random_numbers();
	long double resut;
	long double correct = 0.0;
	long double false_positive = 0.0; //asfalto classificado como grama
	long double false_negative = 0.0; //grama como sendo asfalto
	long double *final_grass;
	long double *final_asphalt;

	final_grass = final_result_training('g', random_numbers);
	final_asphalt = final_result_training('a', random_numbers);

	for (int i = 25; i < 50; i++)
	{
		switch (dist_euclidiana(random_numbers, final_grass, final_asphalt, i, 'a'))
		{
		case 0:
			correct++;
			break;
		case 1:
			false_positive++;
			break;
		case 2:
			false_negative++;
			break;
		}

		switch (dist_euclidiana(random_numbers, final_grass, final_asphalt, i, 'g'))
		{
		case 0:
			correct++;
			break;
		case 1:
			false_positive++;
			break;
		case 2:
			false_negative++;
			break;
		}
	}

	correct = (correct / 50) * 100;
	false_positive = (false_positive / 50) * 100;
	false_negative = (false_negative / 50) * 100;

	//printf("FINAL RESULT\n");
	printf("Taxa de acerto: %.Lf %%\n", (correct));
	printf("Taxa de falsa rejeição: %.Lf %%\n", false_negative);
	printf("Taxa de falsa aceitação: %.Lf %%\n", false_positive);

	free(final_grass);
	free(final_asphalt);
	free(random_numbers);
	return 0;
}
