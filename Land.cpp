/*
* @fichier: Land.h
* @auteurs:
* @date:
* @description: Le template Land represente le pays que l'on va explorer, il va contenir les differents elements de jeu
*/
#include "Land.h"
template<typename T>
Land<T>::Land(string nomFichier) {
	ifstream fichier(nomFichier);
	if (!fichier.is_open()) {
		cout << "Error opening file";
		exit(-1);
	}

	// Dresseur
	string nomDresseur;

	// Objet magique
	string nomObjet, bonus;

	// Creature
	string nomCreature, attaque, defense, pointDeVie, energie;

	// Pouvoir
	string nomPouvoir, nombreDeDegat, manaNecessaire;

	string type;
	while (!fichier.eof()) {

		getline(fichier, type, '\t');

		switch (stoi(type)) {
		case DRESSEUR:
			getline(fichier, nomDresseur, '\t');
			getline(fichier, nomObjet, '\t');
			getline(fichier, bonus);
			// if est pour lire le fichier sous Mac et retire le \r à la fin de la ligne
			if (bonus[bonus.size() - 1] == '\r') {
				bonus.resize(bonus.size() - 1);
			}
			*this += make_shared<Dresseur>(nomDresseur, nomObjet, stoi(bonus));
			cout << "Le dresseur " << nomDresseur << " a bien ete ajoute!\n";
			break;

		case CREATURE:
			getline(fichier, nomCreature, '\t');
			getline(fichier, attaque, '\t');
			getline(fichier, defense, '\t');
			getline(fichier, pointDeVie, '\t');
			getline(fichier, energie, '\t');
			getline(fichier, nomPouvoir, '\t');
			getline(fichier, nombreDeDegat, '\t');
			getline(fichier, manaNecessaire);
			// if est pour lire le fichier sous Mac et retire le \r à la fin de la ligne
			if (manaNecessaire[manaNecessaire.size() - 1] == '\r')
				manaNecessaire.resize(manaNecessaire.size() - 1);
			*this += make_shared<Creature>(nomCreature, stoi(attaque), stoi(defense), stoi(pointDeVie), stoi(energie),
				Pouvoir(nomPouvoir, stoi(nombreDeDegat), stoi(manaNecessaire)));
			cout << "La creature " << nomCreature << " a bien ete ajoute!\n";
			break;

		default:
			break;
		}
	}
}

//TODO: Utiliser le foncteur FoncteurGenerateurNombresAlea
template <typename T>
shared_ptr<Dresseur> Land<T>::choisirDresseurAleatoire() {
	if (dresseurs_.size() > 0) {
		auto foncteur = FoncteurGenerateurNombresAlea();
		unsigned int indice = foncteur();
		unsigned int count = 0;
		for (auto it = dresseurs_.begin(); it != dresseurs_.end(); it++) {
			if (count == indice) {
				return *it;
			}
			count++;
		}
	}
	else {
		return nullptr;
	}
}

//TODO: Utiliser le foncteur FoncteurGenerateurNombresAlea
template <typename T>
shared_ptr<Creature> Land<T>::choisirCreatureAleatoire() {
	if (creatures_.size() > 0) {
		auto foncteur = FoncteurGenerateurNombresAlea();
		unsigned int indice = foncteur();
		unsigned int count = 0;
		for (auto it = creatures_.begin(); it != creatures_.end(); it++) {
			if (count == indice) {
				return *it;
			}
			count++;
		}
	}
	else {
		return nullptr;
	}
}

//TODO: Utiliser le foncteur FoncteurGenerateurNombresAlea
template <typename T>
shared_ptr<Dresseur> Land<T>::choisirDresseurAleatoire(unsigned int min, unsigned int max) {
	if (dresseurs_.size() > 0) {
		auto foncteur = FoncteurGenerateurNombresAlea(min, max);
		unsigned int indice = foncteur();
		unsigned int count = 0;
		for (auto it = dresseurs_.begin(); it != dresseurs_.end(); it++) {
			if (count == indice) {
				return *it;
			}
			count++;
		}
	}
	else {
		return nullptr;
	}
}

//TODO: Utiliser le foncteur FoncteurGenerateurNombresAlea
template <typename T>
shared_ptr<Creature> Land<T>::choisirCreatureAleatoire(unsigned int min, unsigned int max) {
	if (creatures_.size() > 0) {
		auto foncteur = FoncteurGenerateurNombresAlea(min, max);
		unsigned int indice = foncteur();
		unsigned int count = 0;
		for (auto it = creatures_.begin(); it != creatures_.end(); it++) {
			if (count == indice) {
				return *it;
			}
			count++;
		}
	}
	else {
		return nullptr;
	}
}

// TODO: Utiliser un algorithme pour chercher le dresseur
//Foncteur , algorithme advance de la STL
//fonction lamda
//		 Aucune boucle for ou while/*fonction lamda implemente*/
template <typename T>
shared_ptr<Dresseur> Land<T>::choisirDresseur(string nom) {
	list<shared_ptr<Dresseur>>::iterator it = find_if(dresseurs_.begin(), dresseurs_.end(), [nom](string a) {return a == nom;});
	//it va prendre la bonne valeur
	if (it == dresseurs_.end()) {
		return nullptr;
	}
	return *it;

}

// TODO: Utiliser polydex pour retourner la creature
template <typename T>
shared_ptr<Creature> Land<T>::choisirCreature(string nom) {
	list<shared_ptr<Creature>>::iterator it = find_if(creatures_.begin(), creatures_.end(), [nom](string a) {return a == nom;});
	if (it == creatures_.end()) {
		return nullptr;
	}
	return *it;
}

//list<shared_ptr<Dresseur>> dresseurs_;
template <typename T>
list<shared_ptr<Dresseur>>& Land<T>::obtenirDresseurs() { //modification de vector a list -sam
	//return list<shared_ptr<Dresseur>> dresseurs_;
	return dresseurs_;
}

template <typename T>
list<shared_ptr<Creature>>& Land<T>::obtenirCreatures() { //modification de vector a list -sam
	return creatures_;
}

template <typename T>
bool Land<T>::attraperCreature(const shared_ptr<Dresseur>& dresseur, const shared_ptr <Creature>& creature) {
	return dresseur->ajouterCreature(creature);
}

template <typename T>
bool Land<T>::relacherCreature(shared_ptr<Dresseur>& dresseur, const  shared_ptr<Creature>& creature) {
	return dresseur->supprimerCreature(creature->obtenirNom());
}

// TODO: A implementer ***************** a revoir
template <typename T>
Land<T>& Land<T>::operator=(Land<T>& land) {
	if (this != &land) {
		dresseurs_ = land.dresseurs_;
		creatures_ = land.creatures_;
		polydex_ = land.polydex_;
	}
	return *this;
}

template <typename T>
Land<T>& Land<T>::operator+=(const shared_ptr<Dresseur>& dresseur) {
	dresseurs_.push_back(dresseur);
	return *this;
}

template <typename T>
Land<T>& Land<T>::operator-=(const shared_ptr<Dresseur>& dresseur) {
	dresseurs_.erase(std::remove(dresseurs_.begin(), dresseurs_.end(), dresseur), dresseurs_.end());
	return *this;
}

// TODO: Ajouter la creature a la map polydex
template <typename T>
Land<T>& Land<T>::operator+=(const shared_ptr<Creature>& creature) {
	polydex_.insert(creature);
	//creatures_.push_back(creature);
	return *this;
}

// TODO: Utiliser un algorithme pour retirer la creature
//		 Aucune boucle for ou while
template <typename T>
Land<T>& Land<T>::operator-=(const shared_ptr<Creature>& creature) {
	creatures_.remove_if(creatures_.begin(), creatures_.end(), creature);
	//creatures_.erase(std::remove(creatures_.begin(), creatures_.end(), creature), creatures_.end()); 
	return *this;
}

template <typename T>
ostream& operator<<(std::ostream& os, const Land<T>& land) {
	return *this;
}