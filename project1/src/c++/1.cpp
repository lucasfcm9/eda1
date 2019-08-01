#include <bits/stdc++.h>

using namespace std;

template<typename T>
void print(const vector<T>& xs)
{
	for(size_t i = 0; i < xs.size(); i++)
		cout << xs[i] << (i+1 == xs.size() ? '\n' : ' ');
}

template<typename T>
bool fneuronio(vector<T>& ENTRADA, vector<T>& PESOS, double limiar, size_t size)
{
	double SOMA_P = 0.0;
	for(size_t i = 0; i < size; i++)
	{
		SOMA_P += ENTRADA[i] * PESOS[i];
	}

	cout.precision(10);
	cout << fixed << "SOMA = " << SOMA_P << endl;

	if(SOMA_P > limiar) return true;
	return false;
}

int main()
{
	vector<double> ENTRADA, PESOS;
	cout << "Enter the 10 values of ENTRADA: " << endl;
	for(int i = 0; i < 10; i++)
	{
		double aux; cin >> aux;
		ENTRADA.push_back(aux);
	}

	print(ENTRADA);

	cout << "Enter the 10 values of PESOS: " << endl;
	for(int i = 0; i < 10; i++)
	{
		double tmp; cin >> tmp;
		PESOS.push_back(tmp);
	}
	
	print(PESOS);

	double limiar;
	cout << "Enter the value of LIMIAR: " << endl;
	cin >> limiar;

	cout << (fneuronio(ENTRADA, PESOS, limiar, ENTRADA.size()) ? "Neurônio ativado" : "Neurônio inibido") << endl;

	return 0;
}
