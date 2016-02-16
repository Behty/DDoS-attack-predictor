#include "stdafx.h"
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	smatch match;
	string IP[100];
	int Xi[100];
	double Pxni[100], Pxi[100], PRPxi = 1, PRPxni = 1;
	string input;
	string n;
	string g;
	int Y = 0;
	regex reg("([0-9]{1,3}[\.]){3}[0-9]{1,3}");
	cin >> n;
	cin.ignore();
	ifstream fin(n);
	for (int i = 0; i <= 100; i++)
	{
		Xi[i] = 1;
		Pxi[i] = 0;
		Pxni[i] = 0;
	}
	if (!fin.is_open())
		cout << "Файл не может быть открыт!\n";
	else
	{
		while (getline(fin, g))
		{
			fin >> g;
			if (regex_search(g, match, reg))
			{
				IP[Y] = match[0];
				Y++;
			}
		}
		fin.close(); //считали IP
		int Ys = Y-1;
		for (int i = 0; i <= Ys; i++)
		{
			for (int j = i + 1; j <= Ys; j++)
			{
				if (IP[j] != "0")
				{
					if (IP[i] == IP[j])
					{
						Xi[i]++;
						for (int g = j; g <= Ys - 1; g++)
						{
							IP[g] = IP[g + 1];
						}
						j--;
						Ys = Ys - 1;
					}
				}
			}
		}//посчитали частоту для каждого IP
		int X = 0, Xn = 0;
		for (int i = 0; i <= Ys; i++)
		{
			if (Xi[i] >= 3)//тип сотка
			{
				X = X + Xi[i];
			}
			else
			{
				Xn = Xn + Xi[i];
			}
		}
		int s = 1, sn = 1;
		double Xs = X + Xn;
		for (int i = 0; i <= Ys; i++)
		{
			if (Xi[i] >= 3)
			{
				Pxi[s] = Xi[i] / Xs;
				PRPxi = PRPxi*Pxi[s];
				s++;
			}
			else
			{
				Pxni[sn] = Xi[i] / Xs;
				PRPxni = PRPxni*Pxni[sn];//НЕ считает (Скорее всего не хватает точности после запятой)
				sn++;
			}
		}
		cout << "mas: ";
		for (int i = 0; i < 100; i++)
		{
			cout << Pxni[i] << " ";
		}
		cout << endl << "PRPxi = " << PRPxi << endl << "PRPxni = " << PRPxni << endl;
		double v = s, b = sn;
		double P = 0;
		P = v / (v + b)*PRPxi + b / (v + b)*PRPxni;
		cout << "P = " << P << endl;
		double BAYES = 0;
		BAYES = (PRPxi*v / (v + b)) / P;
		cout << "BAYES = " << BAYES << endl;
	}
	system("pause");
	return 0;
}