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
#include "all_functions.h"

int main()
{
	srand(time(NULL));

	int *random_numbers = function_random_numbers();
	double resut;
	double correct = 0.0;
	double rate_false_positive = 0.0;
	double rate_false_negative = 0.0;
	double *final_grass;
	double *final_asphalt;

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
			rate_false_positive++;
			break;
		case 2:
			rate_false_negative++;
			break;
		}

		switch (dist_euclidiana(random_numbers, final_grass, final_asphalt, i, 'g'))
		{
		case 0:
			correct++;
			break;
		case 1:
			rate_false_positive++;
			break;
		case 2:
			rate_false_negative++;
			break;
		}
	}

	correct = (correct/50) * 100;
	rate_false_positive = (rate_false_positive/50) * 100;
	rate_false_negative = (rate_false_negative/50) * 100;

	printf("Hit rate: %.3lf %%\n", (correct));
	printf("False rejection rate: %.3lf %%\n", rate_false_negative);
	printf("False acceptance rate: %.3lf %%\n", rate_false_positive);

	free(final_grass);
	free(final_asphalt);
	free(random_numbers);
	return 0;
}
