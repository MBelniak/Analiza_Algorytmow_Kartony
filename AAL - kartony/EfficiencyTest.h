/*
Klasa wykonuj¹ca testy wydajnoœciowe dla algorytmu pakowania z klasy MPacking.
Micha³ Belniak grupa 5I3, prowadz¹cy: £ukasz Skonieczny
Projekt: AAL-11-LS kartony
*/

#ifndef EFFICIENCY_TEST
#define EFFICIENCY_TEST
#include "Graph.h"
#include "MPacking.h"
#include <chrono>
#include <math.h>
typedef std::chrono::high_resolution_clock Clock;


class EfficiencyTest
{
public:
	EfficiencyTest(int portions, int complexities[], int c_count);
	EfficiencyTest(int complexities[], int c_count, bool hardCases);
	EfficiencyTest() {};
};

EfficiencyTest::EfficiencyTest(int portions, int complexities[], int c_count)
{
	std::chrono::duration<double>** duration = new std::chrono::duration<double>*[c_count];	//do konkretnych pomiarów
	for (int i = 0; i < c_count; i++)
	{
		duration[i] = new std::chrono::duration<double>[portions];
		std::cout << "Results for " << complexities[i] << " elements: \n";

		for (int k = 0; k < portions; k++)
		{
			MPacking test(complexities[i], true);
			if (test.isCreated())
			{
				auto t1 = Clock::now();
				test.findBestPaths();
				auto t2 = Clock::now();
				duration[i][k] = t2 - t1;
			}
			std::cout << duration[i][k].count() << "s\n" << std::endl;
			
		}
		delete[] duration[i];
	}
	delete[] duration;
}

EfficiencyTest::EfficiencyTest(int complexities[], int c_count, bool hardCases)
{
	std::chrono::duration<double>* duration = new std::chrono::duration<double>[c_count];	//do konkretnych pomiarów
	std::cout << "******Algorytm z asymptota O(n^3)******" << std::endl;
	std::cout << "n\t\tt(n)[ms]\t\tq(n)\n";
	for (int i = 0; i < c_count; i++)
	{
		MPacking test(complexities[i], hardCases);
		if (test.isCreated())
		{
			auto t1 = Clock::now();
			test.findBestPaths();
			auto t2 = Clock::now();
			duration[i] = t2 - t1;
		}
	}

	float Tn;
	float tn;
	if (c_count & 1)
	{
		Tn = pow(complexities[c_count / 2+1], 3);
		tn = duration[c_count / 2+1].count() * 1000;
	}
	else
	{
		Tn = pow((complexities[c_count / 2] + complexities[c_count / 2 + 1]) / 2, 3);
		tn = ((duration[c_count / 2].count() + duration[c_count / 2 + 1].count()) * 1000) / 2;
		
	}

	float qn;
	for (int i = 0; i < c_count; i++)
	{
		qn = (duration[i].count() * 1000 * Tn) / (pow(complexities[i], 3)*tn);
		std::cout << complexities[i] << "\t\t" << duration[i].count() * 1000 << "\t\t" << qn <<"\n";
	}
	delete[] duration;
}
#endif 