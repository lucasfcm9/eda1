#include <bits/stdc++.h>

using namespace std;

template<typename T>
void print(const vector<T>& xs)
{
	for(size_t i = 0; i < xs.size(); i++)
		cout << xs[i] << (i+1 == xs.size() ? '\n' : ' ');
}

template<typename T>
int *recebe_notas(const vector<T>& NOTAS, int *APR)
{
	for(size_t i = 0; i < NOTAS.size(); i++)
	{
		if(NOTAS[i] >= 6.0)
			APR[i] = 1;
		else
			APR[i] = 0;
	}

	return APR;
}

pair<int, int> conta_notas(int *APR, int approved, int reproved)
{
	for(size_t i = 0; i < 10; i++)
	{
		if(APR[i] == 1)
			approved++;
		else
			reproved++;
	}

	return make_pair(approved, reproved);
}

bool percent_aprov(pair<int, int>& students)
{
	if(students.first >= 5)
		return true;
	return false;
}

int main()
{
	vector<double> NOTAS;
	int APR[10];
	int approved, reproved;
	approved = reproved = 0;

	cout << "Digite a nota dos 10 alunos: " << endl;
	for(int i = 0; i < 10; i++)
	{
		double aux; cin >> aux;
		NOTAS.push_back(aux);
	}

	print(NOTAS);

	auto received_notes = recebe_notas(NOTAS, APR);
	for(size_t i = 0; i < 10; i++)
		cout << "Aluno " << i+1 << ": " <<  received_notes[i] << endl;

	auto students = conta_notas(APR, approved, reproved);
	cout << "Aprovados: " << students.first << endl;
	cout << "Reprovados: " << students.second << endl;
	
	auto solve = percent_aprov(students);
	cout << (solve ? "Mais da metade da turma foi aprovada" : "Menos da metade da turma foi aprovada") << endl;

	return 0;
}
