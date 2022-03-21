/*
* @fichier: Land.h
* @auteurs:
* @date:
* @description: Le template Land represente le pays que l'on va explorer, il va contenir les differents elements de jeu
*/
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <map>

#include "Dresseur.h"
#include "Creature.h"
#include "Pouvoir.h"
#include "Foncteur.h"

using namespace std;

const int DRESSEUR = 0, CREATURE = 1;

template <typename T>
class Land {
public:
	Land() = default;
	Land(string fichier);

	shared_ptr<Dresseur> choisirDresseur(string nom);
	shared_ptr<Creature> choisirCreature(string nom);

	shared_ptr<Dresseur> choisirDresseurAleatoire();
	shared_ptr<Creature> choisirCreatureAleatoire();

	shared_ptr<Dresseur> choisirDresseurAleatoire(unsigned int min, unsigned int max);
	shared_ptr<Creature> choisirCreatureAleatoire(unsigned int min, unsigned int max);

	list<shared_ptr<Dresseur>>& obtenirDresseurs(); // modification de vector a list -sam
	list<shared_ptr<Creature>>& obtenirCreatures(); // modification de vector a list -sam

	bool attraperCreature(const shared_ptr<Dresseur>& dresseur, const shared_ptr <Creature>& creature);
	bool relacherCreature(shared_ptr<Dresseur>& dresseur, const  shared_ptr<Creature>& creature);

	//Land<T>& operator=(Land<T>& land);
	Land& operator=(Land& land);
	Land& operator+=(const shared_ptr<Dresseur>& dresseur);
	Land& operator-=(const shared_ptr<Dresseur>& dresseur);
	Land& operator+=(const shared_ptr<Creature>& creature);
	Land& operator-=(const shared_ptr<Creature>& creature);

	
	friend ostream& operator<<(ostream& os, const Land& land) {
		os << "Voici la liste des dresseurs: " << endl;
		for (auto&& i : land.dresseurs_) {
			os << *i;
		}
		os << endl;
		os << "Voici la liste des creatures: " << endl;
		for (auto&& i : land.creatures_) {
			os << *i;
		}
		return os;
	};

private:
	// TODO: Modifier les types de dresseurs_ et creatures_ de vector a List 
	// !!!!! Cette modification impactera le retour et l'implementation de certaines fonctions!
	list<shared_ptr<Dresseur>> dresseurs_;
	list<shared_ptr<Creature>> creatures_;
	// TODO: ajouter polydex une map de shared_ptr<Creature>
	map<string, shared_ptr<Creature>> polydex_; // string est la key

};