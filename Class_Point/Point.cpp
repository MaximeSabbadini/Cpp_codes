//
//  main.cpp
//  Ex2
//
//  Created by Maxime Sabbadini on 07/03/2021.
//

#include <iostream>
#include <math.h>

using namespace std;

// -----------------------------------------------------------
//                     Déclaration de la classe
// -----------------------------------------------------------

class Complexe{
    static int nb;
    double x, y;
public:
    // Constructeurs :
    Complexe(double=0, double=0);
    Complexe(const Complexe &);
    
    // Destructeur :
    ~Complexe();
    
    // Les setters :
    void set_x(double);
    void set_y(double);
    
    // Les getters :
    double get_x();
    double get_y();
    
    // Surcharge des opérateurs avec un Complexe :
    
    Complexe operator + (const Complexe &);
    Complexe operator - (const Complexe &);
    Complexe operator * (const Complexe &);
    Complexe operator / (const Complexe &);
    void operator += (const Complexe &);
    void operator -= (const Complexe &);
    void operator *= (const Complexe &);
    void operator /= (const Complexe &);
    void operator = (const Complexe &);
    bool operator == (const Complexe &);
    bool operator != (const Complexe &);
    
    // Surcharge des opérateurs avec un double (Réel pur) :
    
    Complexe operator + (double);
    Complexe operator - (double);
    Complexe operator * (double);
    Complexe operator / (double);
    void operator += (double);
    void operator -= (double);
    void operator *= (double);
    void operator /= (double);
    void operator = (double);
    bool operator == (double);
    bool operator != (double);
    
    // Méthodes sans option friend
    
    double module();
    double argument();
    Complexe conjugue();
    Complexe inverse();
    
    // Fonctions avec l'option friend
    
    friend double distance(const Complexe &, const Complexe &);
    friend ostream& operator << (ostream &, const Complexe &);
    friend istream& operator >> (istream &, Complexe &);
    
    // Fonction statique
    
    static void nb_objets(){cout<<"--------- Vous avez "<<nb<<" point(s) dans le programme ---------"<<endl;};
    
    
};

// -----------------------------------------------------------
//             Déclaration des méthodes de la classe
// -----------------------------------------------------------

// Les Constructeurs :

Complexe::Complexe(double a, double b){
    // Constructeur avec 2 arguments, avec valeur par défaut
    x = a;
    y = b;
    nb++;
    Complexe::nb_objets();
}

Complexe::Complexe(const Complexe &c){
    // Constructeur par recopie
    x = c.x;
    y = c.y;
    nb++;
    Complexe::nb_objets();
}

// Le destructeur :

Complexe::~Complexe(){
    cout<<"Instance détruite"<<endl;
    nb--;
    Complexe::nb_objets();
}

// Les setters :

void Complexe::set_x(double a){
    x = a;
}

void Complexe::set_y(double a){
    y = a;
}

// Les getters :

double Complexe::get_x(){
    return x;
}

double Complexe::get_y(){
    return y;
}

// Surcharge des opérateurs avec un Complexe :

Complexe Complexe::operator + (const Complexe &c){
    Complexe R;
    R.x = x + c.x;
    R.y = y + c.y;
    return R;
}

Complexe Complexe::operator - (const Complexe &c){
    Complexe R;
    R.x = x - c.x;
    R.y = y - c.y;
    return R;
}

Complexe Complexe::operator * (const Complexe &c){
    Complexe R;
    R.x = x*c.x-y*c.y;
    R.y = c.y*x + c.x*y;
    return R;
}

Complexe Complexe::operator / (const Complexe &c){
    Complexe R;
    R.x = (x*c.x+y*c.y)/(pow(c.x, 2)+pow(c.y, 2));
    R.y = (c.x*y- c.y*x)/(pow(c.x, 2)+pow(c.y, 2));
    return R;
}

void Complexe::operator += (const Complexe &c){
    x += c.x;
    y += c.y;
}

void Complexe::operator -= (const Complexe &c){
    x -= c.x;
    y -= c.y;
}

void Complexe::operator *= (const Complexe &c){
    x *= c.x;
    y *= c.y;
}

void Complexe::operator /= (const Complexe &c){
    x /= c.x;
    y /= c.y;
}

void Complexe::operator = (const Complexe &c){
    x = c.x;
    y = c.y;
}

bool Complexe::operator == (const Complexe &c){
    if(x==c.x && y==c.y)
        return true;
    else
        return false;
}

bool Complexe::operator != (const Complexe &c){
    if(x!=c.x || y!=c.y)
        return true;
    else
        return false;
}

// Surcharge des opérateurs avec un double (Réel pur) :

Complexe Complexe::operator + (double a){
    Complexe R;
    R.x = x + a;
    R.y = y;
    return R;
}

Complexe Complexe::operator - (double a){
    Complexe R;
    R.x = x - a;
    R.y = y;
    return R;
}

Complexe Complexe::operator * (double a){
    Complexe R;
    R.x = x*a;
    R.y = y*a;
    return R;
}

Complexe Complexe::operator / (double a){
    Complexe R;
    R.x = x/a;
    R.y = y/a;
    return R;
}

void Complexe::operator += (double a){
    x += a;
}

void Complexe::operator -= (double a){
    x -= a;
}

void Complexe::operator *= (double a){
    x *= a;
    y *= a;
}

void Complexe::operator /= (double a){
    x /= a;
    y /= a;
}

void Complexe::operator = (double a){
    x = a;
    y = 0;
}

bool Complexe::operator == (double a){
    if(x==a && y==0)
        return true;
    else
        return false;
}

bool Complexe::operator != (double a){
    if(x!=a || y!=0)
        return true;
    else
        return false;
}

// Définition des méthodes de la classe

double Complexe::module(){
    return sqrt(pow(x, 2) + pow(y, 2));
}

double Complexe::argument(){
    return atan(y/x);
}

Complexe Complexe::conjugue(){
    Complexe R;
    R.x = x;
    R.y = -y;
    return R;
}

Complexe Complexe::inverse(){
    Complexe R;
    R.x = x/(pow(x, 2) + pow(y, 2));
    R.y = -y/(pow(x, 2) + pow(y, 2));
    return R;
}

// Fonctions friend

double distance(const Complexe &c1, const Complexe &c2){
    return sqrt(pow(c1.x-c2.x, 2) + pow(c1.y-c2.y, 2));
}

ostream& operator <<(ostream &os, const Complexe &c){
    os<<c.x<<" + ("<<c.y<<")i"<<endl;
    return os;
}

istream& operator >> (istream &is, Complexe &c)
{
    cout << "Donnez un nombre complexe sous la forme x+iy"<<endl;
    cout << "x : ";
    is >> c.x;
    cout << "y : ";
    is >> c.y;
    return is;
}

int Complexe::nb=0;

int main() {
    
    double d;
    Complexe c1(1, 2);
    Complexe c2(3, -1);
    Complexe c3(c1+c2);
    Complexe c4(c1-c2);
    Complexe c5(c1*c2);
    Complexe c6(c1/c2);
    cout<<c1<<" + "<<c2<<" = "<<c3<<endl;
    cout<<c1<<" - ("<<c2<<") = "<<c4<<endl;
    cout<<c1<<" * ("<<c2<<") = "<<c5<<endl;
    cout<<c1<<" / ("<<c2<<") = "<<c6<<endl;
    cout<<"c1 avant (+=) : "<<c1<<endl;
    c1 += c2;
    cout<<"c1 après (+=) : "<<c1<<endl;
    cout<<"c1 avant (-=) : "<<c1<<endl;
    c1 -= c2;
    cout<<"c1 après (-=) : "<<c1<<endl;
    cout<<"c1 avant (*=) : "<<c1<<endl;
    c1 *= c2;
    cout<<"c1 après (*=) : "<<c1<<endl;
    cout<<"c1 avant (/=) : "<<c1<<endl;
    c1 /= c2;
    cout<<"c1 après (/=) : "<<c1<<endl;
    Complexe c7(1, 2);
    Complexe c8(2, 1);
    if(c7==c8)
        cout<<c7<<" et "<<c8<<" sont égaux"<<endl;
    else
        cout<<c7<<" et "<<c8<<" sont différents"<<endl;
    
    d = distance(c1, c2);
    cout<<"La distance entre "<<c1<<" et "<<c2<<" est : "<<d<<endl;
    d = c1.module();
    cout<<"Le Module de "<<c1<< " est : "<<d<<endl;
    d = c1.argument();
    cout<<"L'argument de "<<c1<< " est : "<<d<<endl;
    Complexe c9(c1.inverse());
    cout<<"L'inverse de "<<c1<<" est :"<<c9<<endl;
    Complexe c11;
    cin>>c11;
    cout<<"Nouveau complexe : "<<c11<<endl;
    return 0;
}
