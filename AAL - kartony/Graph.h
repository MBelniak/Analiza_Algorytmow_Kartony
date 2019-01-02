/*
Klasa Graph implementuje struktur� danych - graf skierowany wa�ony - przystosowan� do rozwi�zania problemu pakowania karton�w.
Micha� Belniak grupa 5I3, prowadz�cy: �ukasz Skonieczny
Projekt: AAL-11-LS kartony
*/

#include <vector>
#include <algorithm>
#ifndef GRAPH_H
#define GRAPH_H
class Graph {
protected:
	struct Vertice {	//struktura wierzcho�ka
		unsigned number;
		float width, length, height, volume;  //width>=length>=height
		std::vector<Vertice*> children, parents;	//wska�niki odpowiadaj�ce kraw�dziom w grafie.
		bool is_Deleted;		//flaga oznaczaj�ca, czy wierzcho�ek zosta� usuni�ty z grafu. Gdyby usuwa� wierzcho�ek z wektora wierzcho�k�w, pozosta�e wierzcho�ki mog�y by zmieni� pozycj�.
	};

	std::vector<Vertice> vertices;	
	float v_total;	//ca�kowita obj�to�� karton�w
	int findRoot();	//zwraca pozycj� w wektorze pierwszego wierzcho�ka, kt�ry jest korzeniem drzewa.
	static bool compare(Vertice first, Vertice second)
	{
		return first.volume>second.volume;
	}

public:
	void addVertice(float dims[3]);//Dodanie pude�ka o wymiarach dims[] do grafu jako wierzcho�ek.
	void findParentsAndChildren();		//Wyszukanie rodzic�w i dzieci ka�dego wierzcho�ka jeszcze raz.
};

//Dodanie wierzcho�ka do grafu.
void Graph::addVertice(float dims[3])
{
	struct Vertice v;
	v.number = vertices.size()+1;
	v.width = dims[0];
	v.length = dims[1];
	v.height = dims[2];
	v.volume = v.width*v.length*v.height;
	v.is_Deleted = false;
	vertices.push_back(v);
	v_total += v.volume;
}

int Graph::findRoot()
{
	for (unsigned i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].is_Deleted)
			continue;
		if (vertices[i].parents.size() == 0)
			return i;
	}
	return -1;
}

//Szukanie kraw�dzi w grafie. O(n^2) 
void Graph::findParentsAndChildren()
{
	std::sort(vertices.begin(), vertices.end(), &(Graph::compare)); //Presortowanie
	for (unsigned i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].is_Deleted)
			continue;
		for (unsigned k = i + 1; k < vertices.size(); k++)	//Nie musimy analizowa� pude�ek wi�kszych, bo wi�ksze analizuj� mniejsze.
		{
			if (vertices[k].is_Deleted)
				continue;
			if (vertices[k].width < vertices[i].width && vertices[k].length < vertices[i].length && vertices[k].height < vertices[i].height)
			{
				vertices[i].children.push_back(&vertices[k]);
				vertices[k].parents.push_back(&vertices[i]);
			}
		}
	}
}
#endif

