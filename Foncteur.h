/*
* @fichier: Foncteur.h
* @auteurs:
* @date:
* @description: Les foncteurs
*/
#pragma once

#include <string>
#include <stdlib.h>

#include "Dresseur.h"
#include "Creature.h"

#define RAND_MIN_DEFAUT 0
#define RAND_MAX_DEFAUT 5

// TODO VERIFIED 

class FoncteurComparerDresseur {
public:
	FoncteurComparerDresseur() {};
	~FoncteurComparerDresseur() {};
	bool operator()(const shared_ptr<Dresseur> &dresseur1, const shared_ptr<Dresseur>& dresseur2) {
		return (dresseur1->obtenirNom() < dresseur2->obtenirNom());
	}
};

class FoncteurComparerCreature {
public:
	FoncteurComparerCreature() {};
	~FoncteurComparerCreature() {};
	bool operator()(const shared_ptr<Creature>& creature1, const shared_ptr<Creature>& creature2) {
		return (creature1->obtenirNom() < creature2->obtenirNom());
	}
};

class FoncteurGenerateurNombresAlea {
public:
	FoncteurGenerateurNombresAlea() : FoncteurGenerateurNombresAlea(0, 6) {}
	FoncteurGenerateurNombresAlea(int borne1, int borne2) :borneInf_(borne1), borneSupp_(borne2) {}
	int operator() () {
		return (rand() % (borneSupp_ - borneInf_ + 1)) + borneInf_;
	}
private:
	int borneInf_;
	int borneSupp_;
};

