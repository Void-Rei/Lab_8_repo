/*Приветствую, unreg_user
Автор программы: Исаков, гр.#9309
Задание #5 версия 1.0.6
Начата: 6 октября
Закончена: tbd */
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
const int N = 10;
char in(float ***b, int *m, int *k, int *siz)
{
	ifstream in;
	int i = 1, j = 0, lmin = 100, cmin = 100, cycle = 1;
	char s;
	float t; 
	in.open("in5.txt");
	if(in.is_open())
	{
		if (cycle) in >> *m >> *k;
		else in >> skipws >> *m >> *k;
		while(i <= N)
		{
			in >> noskipws >> s;
			if ((s == '0')||(s == '1')||(s == '2')||(s == '3')||(s == '4')||(s == '5')||(s == '6')||(s == '7')||(s == '8')||(s == '9'))
			{
				in.putback(s);
				in >> skipws >> t;
				if (!cycle) 
				{
					*b[i][j] = t;
					cout << *b[i][j] << endl;
				}
				j++;
			}
			else switch (s)
			{
				case '\n': 
					if((i == 1)&&(j == 0))
					{
						break;	
					}
					else 
					{
						if (cycle) {if (j < cmin) cmin = j;} // mimum of colums 
						i++;
						if (cycle) lmin = i; // minimum of lines
						j = 0;
						break;
					}
				default: 
					if (in.eof())
					{
						if (cycle)
						{
							cout << lmin << 'x' << cmin << endl;
							if (cmin > lmin) cmin = lmin;
							else if (lmin > cmin) lmin = cmin;
							else if (cmin == 100) 
							{
								return 'e'; // empty input file case
								in.close();
							}
							*siz = cmin;
							in.close();
							cmin ++;
							cout << "before creation" << endl;
							*b = new float*[cmin];
							cout << "right after" << endl;
							if (*b == NULL) 
							{
								cout << "memory_1 error occured" << endl;
								return 'm'; // memory error  
							}
							for (i = 1; i < cmin; i++) 
							{
								*(b)[i] = new float[cmin];
								cout << "submass created" << endl;
								if (*(b)[i] == NULL) 
								{
									cout << "memory_2 error occured" << endl;
									cout << i << endl;
									return 'm'; // memory error
								}
							}
							cout << "after creation" << endl;
							cycle = 0;
							break;
						}
						else 
							{
								in.close();
								return 'r'; //right ending
							}
					}
	 		}
		}
	}
	else 
	{
		in.close();
		cout << "input error occured" << endl;
		return 'i'; // input error
	}
}
char out(ofstream *f, float ***b, int *m, int *k, int *siz, char *inerr, char *res)
{
		int i = 1, j = 1;
		switch (*inerr)
		{
			case 'm': 
				*f << "Memory error occured";
				cout << "Memory error occured";
				return 'e';
			case 'e':
				*f << "No matrix elements detected";
				cout << "No matrix elements detected";
				return 'e';
			case 'i':
				*f << "Could not open input file";
				cout << "Could not open input file";
				return 'e';
			case 'r':
				*f << "Additional parameters:" << endl << "m = " << *m << "  " << " k = " << *k << endl;
				*f << "Size of sqare matrix: " << *siz << 'x' << *siz << endl;
				for (i = 1; i <= *siz; i++)
				{
					for (j = 1; j <= *siz; j++)
					{
						if (j == *siz) 
						{
							*f << *(*(*b+i)+j) << endl;
						}
						else 
						{
							*f << *(*(*b+i)+j) << ' ';
						}
					}
				}
				return 'g';
			default:
				*f << "Maximum value is " << *res;
				return 'c';
		}	
	}
float proc(float ***b, int *m, int *k, int *siz)
{
	float max;
	int i = *siz, j = 1;
	do
	{
		if (j == 1) max = *(*(*b+i)+j);
		else if (*(*(*b+i)+j) > max) max = *(*(*b+i)+j); // diagonal check
		i--; j++;
	}
	while ((i >= 1)&&(j <= *siz));
	i = *siz; j = *m;
	do
	{
		if (*(*(*b+i)+j) > max) max = *(*(*b+i)+j); // m column check
		i--;
	}
	while (i <= j);
	i = *k; j = *siz;
	do
	{
		if (*(*(*b+i)+j) > max) max = *(*(*b+i)+j); // k line check
		j--;
	}
	while (j <= i);
	return max;
}
int main(void)
{
	int i, j;
	float **b;
	int m, k, siz;
	char inerr;
	char res = 'n';
	ofstream f;
	f.open("out5.txt",ios::out);
	if (f.is_open())
	{
		inerr = in(&b , &m, &k, &siz);
		out(&f, &b, &m, &k, &siz, &inerr, &res);
		/*for (i = 1; i <= siz; i++)
				{
					for (j = 1; j <= siz; j++)
					{
						if (j == siz - 1) 
						{
							f << *(*(b+i)+j) << endl;
							cout << *(*(b+i)+j) << endl;
						}
						else 
						{
							f << *(*(b+i)+j) << ' ';
							cout << *(*(b+i)+j) << ' ';
						}
					}
				}*/
		if ((inerr == 'm')||(inerr == 'e')||(inerr == 'i')) return 0;
		res = proc(&b, &m, &k, &siz);
		out(&f, &b, &m, &k, &siz, &inerr, &res);
	}
	else cout << "Output file error" <<endl;
	for (i = 1; i <= siz; i++) 
	{
		for (j = 1; j <= siz; j++)
			{
				delete[]b[i];
			}
	}
	delete[] *b; b = NULL;
	f.close();
}
