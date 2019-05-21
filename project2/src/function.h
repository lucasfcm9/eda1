/* Alunos: Lucas Fellipe Carvalho Moreira && Pedro Henrique Queiroz Mirando && Gabriel Davi Silva Pereira
   Matrículas: 16/0133394 && 15/0144474 && 170010341
Disciplina: Estruturas de Dados 1
Professor: Mateus Mendelson
 */

#ifndef FUNCTION_H
#define FUNCTION_H

int *readFile(char *path)
{

	FILE *fp = fopen(path, "r");

	if (fp == NULL)
	{
		printf("Erro ao abrir o arquivo\n");
		exit(-1);
	}
	int lines = 0, columns = 0;

	int *matrix = (int *)malloc(1025 * 1025 * sizeof(int));

	if (matrix == NULL)
	{
		printf("Falha na alocação de memória");
	}

	int number;
	char next_char;
	int i = 0, j = 0;

	while (fscanf(fp, "%d%c", &number, &next_char) != EOF)
	{
		*(matrix + i * 1025 + j) = number;
		j++;
		if (next_char == '\n')
		{
			i++;
			j = 0;
		}
	}
	fclose(fp);
	return matrix;
}

double avg(int *matrix, int initial_line, int limit_line, int initial_column, int limit_column)
{
	double sum = 0;
	for (int i = initial_line; i <= limit_line; i++)
	{
		for (int j = initial_column; j <= limit_column; j++)
		{
			sum += *(matrix + i * 1025 + j);
		}
	}
	return sum / 9;
}

int *binaryMatrix(int *matrix, double avg, int initial_line, int limit_line, int initial_column, int limit_column)
{
	int *binary = (int *)malloc(9 * sizeof(int));
	if (binary == NULL)
	{
		printf("Erro na alocação de memória!\n");
		exit(-1);
	}

	//AS VARIAVEIS I E J ACESSAM A MATRIZ, AS VARIAVEIS K E P A MATRIZ DE BINARIO
	for (int i = initial_line, k = 0; i <= limit_line; i++, k++)
	{
		for (int j = initial_column, p = 0; j <= limit_column; j++, p++)
		{

			if (*(matrix + i * 1025 + j) > avg)
			{
				*(binary + k * 3 + p) = 1;
			}
			else
			{
				*(binary + k * 3 + p) = 0;
			}
		}
	}
	return binary;
}

int convertBinary(int *binary)
{

	int count = 9;
	int sum = 0;
	for (int i = 0; i < 9; i++)
	{
		count--;
		sum += *(binary + i) * pow(2, count);
	}
	return sum;
}

int getLowestBinary(int binary[9])
{

	int lowest = 0;			//Variável a ser retornada com o menor número
	int count = 9;			//Variável para decrementar em cada numero binario para calcular o valor do binario em inteiro
	int temp = 0;			// variavel temporária que carrega o valor do bit mais a direita do binário
	int temp_vector[9];		// vetor temporário que carrega o binário resultante após a rotação
	int take_allInteger[9]; // vetor que carrega o valor inteiro de todos os binários

	//For que vai calcular os 9 bits inteiros
	for (int i = 0; i < 9; i++)
	{

		//FOR para calcular o valor do binário e passar para 1 Inteiro
		for (int j = 0; j < 9; j++)
		{
			count--;
			if ((binary[j] * pow(2, count)) > 0)
			{
				lowest += binary[j] * pow(2, count);
			}
		}

		// Da um "Refresh" nas variáveis/ passa o valor inteiro para o vetor com todos os inteiros
		// e variavel temporária pega ultimo valor do vetor binary
		count = 9;
		temp = binary[8];
		take_allInteger[i] = lowest;
		lowest = 0;

		//loop para alocar os valores do proximo binario (Shift right) dentro do vetor temporário
		for (int k = 0; k < 9; k++)
		{

			//IF ELSE para trabalhar com o primeiro e último valor (valor a se substituir pela rotação)
			if (k == 8)
			{
				temp_vector[k] = binary[k - 1];
			}
			else
			{
				//IF ELSE para pegar o bit anterior do vetor binary e salvar na posição atual do vetor temporário
				if (k == 0)
				{
					temp_vector[0] = temp;
				}
				else
				{
					temp_vector[k] = binary[k - 1];
				}
			}
		}

		//FOR para passa os valores do vetor temporário ao vetor binário inicial
		for (int p = 0; p < 9; p++)
		{
			binary[p] = temp_vector[p];
		}
	}

	int testValue = take_allInteger[0]; //Variavel que se inicia pelo primeiro valor do vetos de inteiros

	/* LOOP que testa se a variavel test é menor que os outros valores do vetor e se for ela pega esse menor valor*/
	for (int z = 0; z < 9; z++)
	{

		if (testValue < take_allInteger[z])
		{
			lowest = testValue;
		}
		else
		{
			testValue = take_allInteger[z];
		}
	}

	return lowest;
}

int *function_random_numbers()
{

	int *array;
	array = (int *)malloc(50 * sizeof(int));

	if (array == NULL)
	{
		printf("Falha na alocação de memória!\n");
		exit(-1);
	}
	for (int i = 0; i < 50; i++)
	{
		array[i] = i;
	}

	for (int i = 0; i < 50; i++)
	{
		int temp = array[i];
		int random_index = rand() % 50;

		array[i] = array[random_index];
		array[random_index] = temp;
	}
	return array;
}

int *ILBP(int *matrix, int initial_line, int limit_line, int initial_column, int limit_column)
{

	int *ILBP;
	ILBP = (int *)calloc(512, sizeof(int));

	if (ILBP == NULL)
	{
		printf("Falha na alocação de memória!\n");
		exit(-1);
	}

	double average;
	int *binary_matrix, j_temp = 0;
	int binary_vector[9];

	while (limit_line <= 1024)
	{
		while (limit_column <= 1024)
		{

			average = avg(matrix, initial_line, limit_line, initial_column, limit_column);
			binary_matrix = binaryMatrix(matrix, average, initial_line, limit_line, initial_column, limit_column);

			for (int i = 0; i < 3; i++)
			{
				j_temp = 0;
				for (int j = 0; j < 3; j++)
				{
					binary_vector[i * 3 + j_temp] = *(binary_matrix + i * 3 + j);
					j_temp++;
				}
			}
			int binary_sum = convertBinary(binary_matrix);

			initial_column++;
			limit_column++;

			ILBP[getLowestBinary(binary_vector)]++;
		}
		initial_line++;
		limit_line++;
		initial_column = 0;
		limit_column = 2;
	}
	return ILBP;
}

double *features_generator(int *a, int *b, int *c, int *d, int *e, int *f, int *g, int *h)
{

	int i, j;
	double *features = (double *)calloc(24, sizeof(double));

	if (features == NULL)
	{
		printf("Falha na alocação de memória!\n");
		exit(-1);
	}
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 256; j++)
		{
			//Calculo de energia
			features[0] += pow(*(a + i * 256 + j), 2);
			features[1] += pow(*(b + i * 256 + j), 2);
			features[2] += pow(*(c + i * 256 + j), 2);
			features[3] += pow(*(d + i * 256 + j), 2);
			features[4] += pow(*(e + i * 256 + j), 2);
			features[5] += pow(*(f + i * 256 + j), 2);
			features[6] += pow(*(g + i * 256 + j), 2);
			features[7] += pow(*(h + i * 256 + j), 2);

			//Calculo de contraste
			features[8] += pow(abs(i - j), 2) * (*(a + i * 256 + j));
			features[9] += pow(abs(i - j), 2) * (*(b + i * 256 + j));
			features[10] += pow(abs(i - j), 2) * (*(c + i * 256 + j));
			features[11] += pow(abs(i - j), 2) * (*(d + i * 256 + j));
			features[12] += pow(abs(i - j), 2) * (*(e + i * 256 + j));
			features[13] += pow(abs(i - j), 2) * (*(f + i * 256 + j));
			features[14] += pow(abs(i - j), 2) * (*(g + i * 256 + j));
			features[15] += pow(abs(i - j), 2) * (*(h + i * 256 + j));

			//Calculo de homogeniedade
			features[16] += *(a + i * 256 + j) / (1 + abs(i - j));
			features[17] += *(b + i * 256 + j) / (1 + abs(i - j));
			features[18] += *(c + i * 256 + j) / (1 + abs(i - j));
			features[19] += *(d + i * 256 + j) / (1 + abs(i - j));
			features[20] += *(e + i * 256 + j) / (1 + abs(i - j));
			features[21] += *(f + i * 256 + j) / (1 + abs(i - j));
			features[22] += *(g + i * 256 + j) / (1 + abs(i - j));
			features[23] += *(h + i * 256 + j) / (1 + abs(i - j));
		}
	}

	return features;
}

double *GLCM(int *matrix)
{

	int *array_pixel_above, *array_pixel_below, *array_pixel_right, *array_pixel_left,
		*array_pixel_above_diag_right, *array_pixel_above_diag_left, *array_pixel_below_diag_right,
		*array_pixel_below_diag_left;
	double *features;
	array_pixel_above = (int *)calloc(256 * 256, sizeof(int));
	array_pixel_below = (int *)calloc(256 * 256, sizeof(int));
	array_pixel_right = (int *)calloc(256 * 256, sizeof(int));
	array_pixel_left = (int *)calloc(256 * 256, sizeof(int));
	array_pixel_above_diag_right = (int *)calloc(256 * 256, sizeof(int));
	array_pixel_above_diag_left = (int *)calloc(256 * 256, sizeof(int));
	array_pixel_below_diag_left = (int *)calloc(256 * 256, sizeof(int));
	array_pixel_below_diag_right = (int *)calloc(256 * 256, sizeof(int));

	if (array_pixel_above == NULL || array_pixel_below == NULL || array_pixel_right == NULL || array_pixel_left == NULL ||
			array_pixel_above_diag_right == NULL || array_pixel_above_diag_left == NULL || array_pixel_below_diag_left == NULL ||
			array_pixel_above_diag_right == NULL)
	{
		printf("Falha na alocação de memória!\n");
		exit(-1);
	}

	int i, j;
	for (i = 0; i < 1025; i++)
	{
		for (j = 0; j < 1025; j++)
		{

			//Acima
			if (i > 0)
			{
				*((array_pixel_above + (*(matrix + i * 1025 + j) * 256)) + (*(matrix + ((i - 1) * 1025) + j))) += 1;
			}

			//Abaixo
			if (i < 1024)
			{
				*((array_pixel_below + (*(matrix + i * 1025 + j) * 256)) + (*(matrix + ((i + 1) * 1025) + j))) += 1;
			}

			//Lado direito
			if (j < 1024)
			{
				*((array_pixel_right + (*(matrix + i * 1025 + j) * 256)) + (*(matrix + i * 1025 + (j + 1)))) += 1;
			}

			//Lado esquerdo
			if (j > 0)
			{
				*((array_pixel_left + (*(matrix + i * 1025 + j) * 256)) + (*(matrix + i * 1025 + (j - 1)))) += 1;
			}

			//Diagonal superior direita
			if (i > 0 && j < 1024)
			{
				*((array_pixel_above_diag_right + (*(matrix + i * 1025 + j) * 256)) + (*(matrix + ((i - 1) * 1025) + (j + 1)))) += 1;
			}

			//Diagonal superior esquerda
			if (i > 0 && j > 0)
			{
				*((array_pixel_above_diag_left + (*(matrix + i * 1025 + j) * 256)) + (*(matrix + ((i - 1) * 1025) + (j - 1)))) += 1;
			}

			//Diagonal inferior esquerda
			if (j > 0 && i < 1024)
			{
				*((array_pixel_below_diag_left + (*(matrix + i * 1025 + j) * 256)) + (*(matrix + ((i + 1) * 1025) + (j - 1)))) += 1;
			}

			//Diagonal inferior direita
			if (i < 1024 && j < 1024)
			{
				*((array_pixel_below_diag_right + (*(matrix + i * 1025 + j) * 256)) + (*(matrix + ((i + 1) * 1025) + (j + 1)))) += 1;
			}
		}
	}

	features = features_generator(array_pixel_above, array_pixel_below, array_pixel_right, array_pixel_left,
			array_pixel_above_diag_right, array_pixel_above_diag_left, array_pixel_below_diag_left,
			array_pixel_below_diag_right);
	free(array_pixel_above);
	free(array_pixel_below);
	free(array_pixel_right);
	free(array_pixel_left);
	free(array_pixel_above_diag_left);
	free(array_pixel_above_diag_right);
	free(array_pixel_below_diag_left);
	free(array_pixel_below_diag_right);

	return features;
}

double *concatenation_vector(int *ILBP_vector, double *GLCM_vector)
{
	double *reallocation_of_memory;
	int i, j, x, k;
	double *concatenation_ILBP_GLCM;
	concatenation_ILBP_GLCM = (double *)malloc(536 * sizeof(double));

	if (concatenation_ILBP_GLCM == NULL)
	{
		printf("Falha na alocação de memória!\n");
		exit(-1);
	}

	for (x = 0; x < 512; x++)
	{
		concatenation_ILBP_GLCM[x] = ILBP_vector[x];
	}
	for (i = 512, j = 0; i < 536; i++, j++)
	{
		concatenation_ILBP_GLCM[i] = GLCM_vector[j];
	}

	return concatenation_ILBP_GLCM;
}

double *n_vector(double *c_vector)
{
	double min=0.0, max=1.0;
	double normalization = 0.0;

	for (int i = 0; i < 536; i++)
	{

		if (c_vector[i] > max)
		{
			max = c_vector[i];
		}
		if (c_vector[i] < min)
		{
			min = c_vector[i];
		}
	}

	for (int i = 0; i < 536; i++)
	{
		c_vector[i] = (c_vector[i] - min) / (max - min);
	}

	return c_vector;
}

double *normalized_sum(double *vector, double *sum_concatenated_vector)
{

	if (sum_concatenated_vector == NULL)
	{
		printf("Falha na alocação de memória!\n");
		exit(-1);
	}

	int i;
	for (i = 0; i < 536; i++)
	{
		*(sum_concatenated_vector + i) += *(vector + i);
	}

	return sum_concatenated_vector;
}

double *normalized_average(double *vector)
{
	int i;
	double sum = 0.0;

	for (i = 0; i < 536; i++)
	{
		vector[i] /= 25;
	}

	return vector;
}

double *final_result_training(char f, int *random_numbers)
{
	char txt[][50] = {"01.txt", "02.txt", "03.txt", "04.txt", "05.txt", "06.txt", "07.txt", "08.txt", "09.txt", "10.txt", "11.txt",
		"12.txt", "13.txt", "14.txt", "15.txt", "16.txt", "17.txt", "18.txt", "19.txt", "20.txt", "21.txt", "22.txt",
		"23.txt", "24.txt", "25.txt", "26.txt", "27.txt", "28.txt", "29.txt", "30.txt", "31.txt", "32.txt", "33.txt",
		"34.txt", "35.txt", "36.txt", "37.txt", "38.txt", "39.txt", "40.txt", "41.txt", "42.txt", "43.txt", "44.txt",
		"45.txt", "46.txt", "47.txt", "48.txt", "49.txt", "50.txt"};

	int count = 0;
	int *matrix;
	int *ILBP_vector;
	double *GLCM_vector;
	double *concatenation_ILBP_GLCM;
	double *normalized_vector;
	double *sum_normalized;
	double *average_normalized;
	int initial_line = 0, limit_line = 2;
	int initial_column = 0, limit_column = 2;

	double *sum_concatenated_vector = (double *)calloc(536, sizeof(double));

	while (count < 25)
	{
		char name_asphalt[70] = "DataSet/asphalt/asphalt_";
		char name_grass[70] = "DataSet/grass/grass_";
		if (f == 'a')
		{
			strcat(name_asphalt, txt[*(random_numbers + count)]);
			printf("%s\n", name_asphalt);

			matrix = readFile(name_asphalt);
		}

		if (f == 'g')
		{
			strcat(name_grass, txt[*(random_numbers + count)]);
			printf("%s\n", name_grass);
			matrix = readFile(name_grass);
		}
		ILBP_vector = ILBP(matrix, initial_line, limit_line, initial_column, limit_column);
		GLCM_vector = GLCM(matrix);
		concatenation_ILBP_GLCM = concatenation_vector(ILBP_vector, GLCM_vector);
		normalized_vector = n_vector(concatenation_ILBP_GLCM);
		sum_normalized = normalized_sum(normalized_vector, sum_concatenated_vector);
		free(GLCM_vector);
		free(ILBP_vector);
		free(concatenation_ILBP_GLCM);
		free(matrix);
		count++;
	}
	average_normalized = normalized_average(sum_normalized);
	return average_normalized;
}

int dist_euclidiana(int *random_numbers, double *final_grass, double *final_asphalt, int n, char type)
{
	char txt[][50] = {"01.txt", "02.txt", "03.txt", "04.txt", "05.txt", "06.txt", "07.txt", "08.txt", "09.txt", "10.txt", "11.txt",
		"12.txt", "13.txt", "14.txt", "15.txt", "16.txt", "17.txt", "18.txt", "19.txt", "20.txt", "21.txt", "22.txt",
		"23.txt", "24.txt", "25.txt", "26.txt", "27.txt", "28.txt", "29.txt", "30.txt", "31.txt", "32.txt", "33.txt",
		"34.txt", "35.txt", "36.txt", "37.txt", "38.txt", "39.txt", "40.txt", "41.txt", "42.txt", "43.txt", "44.txt",
		"45.txt", "46.txt", "47.txt", "48.txt", "49.txt", "50.txt"};
	int initial_line = 0, limit_line = 2;
	int initial_column = 0, limit_column = 2;
	int *ILBP_vector;
	double *GLCM_vector;
	double *concatenation_ILBP_GLCM;
	double *normalized_vector;
	int *matrix;
	double sum_dist_asphalt = 0;
	double sum_dist_grass = 0;
	double root_result_grass;
	double root_result_asphalt;
	int result;

	char name_asphalt[70] = "DataSet/asphalt/asphalt_";
	char name_grass[70] = "DataSet/grass/grass_";
	if (type == 'a')
	{
		strcat(name_asphalt, txt[*(random_numbers + n)]);
		printf("%s\n", name_asphalt);
		matrix = readFile(name_asphalt);
	}

	if (type == 'g')
	{
		strcat(name_grass, txt[*(random_numbers + n)]);
		printf("%s\n", name_grass);
		matrix = readFile(name_grass);
	}

	ILBP_vector = ILBP(matrix, initial_line, limit_line, initial_column, limit_column);
	GLCM_vector = GLCM(matrix);
	concatenation_ILBP_GLCM = concatenation_vector(ILBP_vector, GLCM_vector);
	normalized_vector = n_vector(concatenation_ILBP_GLCM);

	for (int i = 0; i < 536; i++)
	{
		sum_dist_grass += pow(fabs(*(normalized_vector + i) - *(final_grass + i)), 2);
		sum_dist_asphalt += pow(fabs(*(normalized_vector + i) - *(final_asphalt + i)), 2);
	}
	root_result_asphalt = sqrt(sum_dist_grass);
	root_result_grass = sqrt(sum_dist_asphalt);

	printf("TYPE: %c\n",type);
	printf("ASPHALT: %.10lf\n",root_result_asphalt );
	printf("GRASS: %.10lf\n",root_result_grass );

	if (type == 'a' && root_result_asphalt < root_result_grass)
	{
		result = 0; //Taxa de acerto
	}
	if (type == 'g' && root_result_asphalt > root_result_grass)
	{
		result = 0; //Taxa de acerto
	}
	if (type == 'a' && root_result_asphalt > root_result_grass)
	{
		result = 1; //Taxa de falsa aceitação
	}
	if (type == 'g' && root_result_asphalt < root_result_grass)
	{
		result = 2; //Taxa de falsa rejeição
	}

	free(GLCM_vector);
	free(ILBP_vector);
	free(concatenation_ILBP_GLCM);
	free(matrix);

	return result;
}
#endif
