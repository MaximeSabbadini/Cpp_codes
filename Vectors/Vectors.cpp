// Codé par Maxime Sabbadini, sous environnement OSX, xCode.

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

//-------------------------------------------------------------------------
class Vehicule
{
    protected:
    int m_prix;  //Chaque véhicule a un prix

    public:
    Vehicule(int a){m_prix=a;}
    virtual void affiche() const;
    virtual void get_infos(int *, int*, double *) const{};
    virtual int nbrRoues()  const = 0;  //Affiche une description du Vehicule
    virtual~Vehicule(){cout << "Appel du destructeur véhicule" << endl;};
};

void informations(Vehicule*);

//-------------------------------------------------------------------------

class Voiture : public Vehicule //Une Voiture EST UN Vehicule
{
    int m_portes;

    public:
    Voiture(int a, int b) : Vehicule(a){ m_portes=b;}
    virtual void affiche() const;
    virtual void get_infos(int *, int*, double *) const;
    virtual int nbrRoues() const;
    virtual ~Voiture(){cout << "Appel du destructeur voiture" << endl;};
};

//-------------------------------------------------------------------------

class Moto : public Vehicule  //Une Moto EST UN Vehicule
{
    double m_vitesse;

    public:
        Moto(int a, double b): Vehicule(a){ m_vitesse=b;}
    virtual void affiche() const;
    virtual int nbrRoues() const;
    virtual void get_infos(int *, int*, double *) const;
    virtual ~Moto (){cout << "Appel du destructeur moto" << endl;};
};

//-------------------------------------------------------------------------

class Garage{
private:
    vector<Vehicule*> listeVehicule;
public:
    void fill_file(string);
    void entrer_vehicule(int);
    void voir_tous_vehicules();
    void supprimer_vehicule(int);
    void save_file(string);
    int get_size();
    ~Garage();
};



//-------------------------------------------------------------------------
//                      Définition des méthodes
//-------------------------------------------------------------------------

// ---------- Pour la classe Véhicule -----------

void Vehicule::affiche() const
{
    cout << "Ceci est un vehicule." << endl;
}

/*
int Vehicule::nbrRoues() const
{
    
}
*/

// ---------- Pour la classe Voiture -----------

void Voiture::affiche() const
{
    cout << "Ce véhicule est une voiture." << endl;
    cout << "Son prix est : "<<m_prix<<endl;
    cout << "Son nombre de portes est : "<<m_portes<<endl;
}

int Voiture::nbrRoues() const
{
    return 4;
}

void Voiture::get_infos(int* prix, int* portes, double* vitesse) const{
    // Procédure qui renvoie par pointeurs le prix et le nombre de portes de la voiture. La vitesse vaut -1 car ce n'est pas une propriété de la voiture.
    *prix = m_prix;
    *portes = m_portes;
    *vitesse = -1.0;
}

// ---------- Pour la classe Moto -----------

void Moto::affiche() const
{
    cout << "Ce véhicule est une moto." << endl;
    cout << "Son prix est : "<<m_prix<<endl;
    cout<<"Sa vitesse max est : "<<m_vitesse<<endl;
}

int Moto::nbrRoues() const
{
    return 2;
}

void Moto::get_infos(int* prix, int* portes, double* vitesse) const{
    // Procédure qui renvoie par pointeur le prix et la vitesse max de la moto. Le nombre de portes est de -1 car ce n'est pas une caractéristique de la moto.
    *prix = m_prix;
    *portes = -1;
    *vitesse = m_vitesse;
}

// ---------- Pour la classe Garage -----------

void Garage::fill_file(string fp){
    // Procédure qui remplit le vecteur listeVehicule a partir d'un fichier spécifié par un utilisateur
    ifstream infile(fp);
    int choix, prix, portes;
    double vmax;
    
    while(infile>>choix){
        if(choix==1){
            infile>>prix>>portes;
            listeVehicule.push_back(new Voiture(prix, portes));
        }
        else{
            infile>>prix>>vmax;
            listeVehicule.push_back(new Moto(prix, vmax));
        }
    }
}

void Garage::save_file(string fp){
    // Procédure qui sauvegarde les infos de notre vecteur dans un fichier
    int prix, portes;
    double vmax;
    // cout<<fp<<endl;
    for(int i=0; i<listeVehicule.size(); i++){
        ofstream file(fp, ios::app);
        listeVehicule[i]->get_infos(&prix, &portes, &vmax);
        if(listeVehicule[i]->nbrRoues()==4){ // On filtre si le véhicule est une moto ou une voiture car
            // On ne rentre pas les mêmes paramètres dans le fichier.
            file<<1<<"\t"<<prix<<"\t"<<portes<<endl;
        }
        else{
            file<<2<<"\t"<<prix<<"\t"<<vmax<<endl;
        }
    }
}

void Garage::entrer_vehicule(int n){
    // Procédure qui entre n véhicules dans le vecteur listeVéhicule
    int temp, price, nportes;
    double vmax;
    
    for(int i=1; i<=n; i++){
        cout<<"Véhicule "<<i<<endl;
        cout<<"Voiture = 1, Moto = 2"<<endl;
        do{
            cout<<"Quel type de véhicule ?"<<endl;
            cin>>temp;
        }while(temp!=1 && temp!=2);
        
        // On filtre si le véhicule est une moto ou une Voiture
        // Ensuite on remplit les caractéristiques propres au type de véhicule
        if(temp==1){
            cout<<"Le véhicule est une voiture"<<endl;
            cout<<"Entrez son prix :"<<endl;
            cin>>price;
            cout<<"Entrez son nombre de portes :"<<endl;
            cin>>nportes;
            listeVehicule.push_back(new Voiture(price, nportes));
        }
        else{
            cout<<"Le véhicule est une moto"<<endl;
            cout<<"Entrez son prix :"<<endl;
            cin>>price;
            cout<<"Entrez sa vitesse max :"<<endl;
            cin>>vmax;
            listeVehicule.push_back(new Moto(price, vmax));
        }
    }
}

void Garage::voir_tous_vehicules(){
    // Procédure qui permet de voir tous les véhicules du garage, avec leur place attitrée
    for(int i=0;i<listeVehicule.size();i++){
        cout<<"----------------------------"<<endl;
        cout<<"\tPlace de parking n°"<<i+1<<endl;
        cout<<"----------------------------"<<endl;
        informations(listeVehicule[i]);
    }
    if(listeVehicule.size()==0)
        cout<<"Il n'y a aucun véhicule dans le garage"<<endl;
}

void Garage::supprimer_vehicule(int pos){
    // Procédure qui supprime un véhicule en fonction de sa position dans le garage
    listeVehicule.erase(listeVehicule.begin()+pos);
}

int Garage::get_size(){
    //Fonction qui retourne le nombre de véhicules dans le garage
    return listeVehicule.size();
}

Garage::~Garage(){
    //Destructeur de la classe qui vide le vecteur et supprime toutes les instances
    for(int i=0; i<listeVehicule.size(); i++){
        delete listeVehicule[i];
        listeVehicule[i] = 0;
    }
    cout<<"Vecteur vidé"<<endl;
}


//-------------------------------------------------------------------------
//                      Fonction spéciale
//-------------------------------------------------------------------------


void informations (Vehicule *v){
    // Cette procédure affiche les informations du véhicule en fonction de si c'est une moto ou une voiture
    v->affiche();
    cout << "Le véhicule a "<<v->nbrRoues()<< " roues "<<endl;
}

// Les fonctions qui servent dans le main :

int saisir_n(){
    int n;
    do{
        cout<<"Entrez le nombre de véhicules : ";
        cin>>n;
    }while(n<0);
    return n;
}


//-------------------------------------------------------------------------
//                          Programme principal
//-------------------------------------------------------------------------

int main()
{
    
    // Garage g("/Users/maximesabbadini/Desktop/sortie.txt");
    Garage g;
    int choix;
    
    do{
        cout<<"Voulez-vous charger un fichier de véhicules ? "<<endl;
        cout<<"1 : Oui"<<endl<<"2 : Non"<<endl;
        cout<<"Votre choix : ";
        cin>>choix;
    }while(choix<1||choix>2);
    
    if(choix==1){
        cout<<"Entrez le chemin complet du fichier : "<<endl;
        string fp;
        cin>>fp;
        g.fill_file(fp);
    }
       
    int n, saisie;
    
    while(1){
        cout<<"------------------------------------------"<<endl;
        cout<<"\t\t\t\t Garage"<<endl;
        cout<<"------------------------------------------"<<endl;
        cout<<""<<endl;
        cout<<"1 : Saisir des véhicules"<<endl;
        cout<<"2 : Afficher les véhicules du garage"<<endl;
        cout<<"3 : Supprimer un véhicule du garage"<<endl;
        cout<<"4 : Quitter"<<endl;
        do{
            cout<<"Votre choix : ";
            cin>>saisie;
        }while(saisie<=0 || saisie >4);
        
        if(saisie==1){
            n = saisir_n();
            g.entrer_vehicule(n);
        }
        else{
            if(saisie==2){
                cout<<"Affichage de tous les véhicules du garage"<<endl;
                g.voir_tous_vehicules();
            }
            else{
                if(saisie==3){
                    cout<<"Supprimer un véhicule du garage"<<endl;
                    g.voir_tous_vehicules(); // On affiche la liste des véhicules
                    do{
                        cout<<"Quel véhicule voulez vous supprimer ? Entrez sa position : ";
                        cin>>n;
                    }while(n<1||n>g.get_size());
                    g.supprimer_vehicule(n-1); // On supprime le véhicule en position n-1 car l'indexage commence a 0.
                }
                else{
                    if(saisie==4)
                        do{
                            cout<<"Voulez-vous enregistrer les véhicules du garage dans un fichier ?"<<endl;
                            cout<<"1 : Oui"<<endl<<"2 : Non"<<endl;
                            cout<<"Votre choix : ";
                            cin>>choix;
                        }while(choix<1||choix>2);
                    if(choix==1){
                        string fp2;
                        cout<<"Entrez le chemin complet vers le fichier de sortie"<<endl;
                        cin>>fp2;
                        g.save_file(fp2);
                    }
                        return 0; // Fin du programme
                }
            }
        }
    }
}
