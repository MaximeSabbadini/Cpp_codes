// Ecrit par Maxime Sabbadini, sous environnement OSX, xCode.

#include <iostream>

using namespace std;

// ------------------------------------------------------
// Déclaration des classes :
// ------------------------------------------------------

class Point{
protected:
    double x,y;
    
public:
    Point(double=0, double=0);
    Point(const Point &);
    void afficher();
};

// ------------------------------------------------------

class Point_3D : public Point{
protected:
    double z;
    
public:
    Point_3D(double=0, double=0, double=0);
    Point_3D(const Point &, double);
    Point_3D(const Point_3D &);
    void afficher();
};

// ------------------------------------------------------

class Couleur{
protected:
    string color;
public:
    Couleur(string="nocolor");
    Couleur(const Couleur &);
    void afficher();
};

class Point_couleur : public Point, public Couleur{
public:
    Point_couleur(double=0, double=0, string="nocolor");
    Point_couleur(const Point &, string="nocolor");
    Point_couleur(double, double, const Couleur &);
    Point_couleur(const Point &, const Couleur &);
    Point_couleur(const Point_couleur &);
    void afficher();
    
};

class Point_3D_couleur : public Point_3D, public Couleur{
public:
    Point_3D_couleur(double=0, double=0, double=0, string="nocolor");
    Point_3D_couleur(const Point_3D &, string="nocolor");
    Point_3D_couleur(double, double, double, const Couleur &);
    Point_3D_couleur(const Point_3D &, const Couleur &);
    Point_3D_couleur(const Point_3D_couleur &);
    void afficher();
};

// ------------------------------------------------------
// Déclaration des méthodes des classes
// ------------------------------------------------------

Point::Point(double a, double b){
    x = a;
    y = b;
}

Point::Point(const Point &p){
    x = p.x;
    y = p.y;
}

void Point::afficher(){
    cout<<"x : "<<x<<" ; y : "<<y<<endl;
}

// ------------------------------------------------------

Point_3D::Point_3D(double a, double b, double c):Point(a, b){z = c;}

Point_3D::Point_3D(const Point &p, double c):Point(p){z = c;}

Point_3D::Point_3D(const Point_3D &p):Point(p){z = p.z;}

void Point_3D::afficher(){
    Point::afficher();
    cout<<"z : "<<z<<endl;
}

// ------------------------------------------------------

Couleur::Couleur(string c){
    color = c;
}

Couleur::Couleur(const Couleur &c){
    color = c.color;
}

void Couleur::afficher(){
    cout<<"La couleur est : "<<color<<endl;
}

// ------------------------------------------------------

Point_couleur::Point_couleur(double a, double b, string c):Point(a, b), Couleur(c){};
Point_couleur::Point_couleur(const Point &p, string c):Point(p), Couleur(c){};
Point_couleur::Point_couleur(double a, double b, const Couleur &c):Point(a, b), Couleur(c){};
Point_couleur::Point_couleur(const Point &p, const Couleur &c):Point(p), Couleur(c){};
Point_couleur::Point_couleur(const Point_couleur &p):Point(p.x, p.y), Couleur(p.color){};
void Point_couleur::afficher(){
    Point::afficher();
    Couleur::afficher();
}

// ------------------------------------------------------

Point_3D_couleur::Point_3D_couleur(double a, double b, double c, string color):Point_3D(a, b, c), Couleur(color){};
Point_3D_couleur::Point_3D_couleur(const Point_3D &p, string color):Point_3D(p), Couleur(color){};
Point_3D_couleur::Point_3D_couleur(double a, double b, double c, const Couleur &color):Point_3D(a, b, c), Couleur(color){};
Point_3D_couleur::Point_3D_couleur(const Point_3D &p, const Couleur &color):Point_3D(p), Couleur(color){};
Point_3D_couleur::Point_3D_couleur(const Point_3D_couleur &p):Point_3D(p.x, p.y, p.z), Couleur(p.color){};
void Point_3D_couleur::afficher(){
    Point_3D::afficher();
    Couleur::afficher();
}

// ------------------------------------------------------

int main() {
    
    cout<<"-----------------------------"<<endl;
    cout<<"Test des classes Point et Couleur"<<endl;
    cout<<"-----------------------------"<<endl;
    
    
    Point p1(1, 2);
    Point_3D p2(p1, 5);
    Point_3D p3(p2);
    p1.afficher();
    p2.afficher();
    p3.afficher();
    Couleur c1("blue");
    Couleur c2;
    Couleur c3(c1);
    c1.afficher();
    c2.afficher();
    c3.afficher();
    
    cout<<"-----------------------------"<<endl;
    cout<<"Test de Point_Couleur"<<endl;
    cout<<"-----------------------------"<<endl;
    
    Point pp1(1,2);
    Couleur cp1("red");
    Point_couleur p_2_1(2,3,"blue");
    Point_couleur p_2_2(pp1, cp1);
    Point_couleur p_2_3(p2);
    p_2_1.afficher();
    p_2_2.afficher();
    p_2_3.afficher();
    
    cout<<"-----------------------------"<<endl;
    cout<<"Test de Point_3D_Couleur"<<endl;
    cout<<"-----------------------------"<<endl;
    
    Point_3D ppp1(1,2,3);
    // pp1.afficher();
    Point_3D_couleur p_3_1(3,4,5, "blue");
    //Couleur c1("red");
    Point_3D_couleur p_3_2(ppp1, "green");
    Point_3D_couleur p_3_3(ppp1, cp1);
    Point_3D_couleur p_3_4(10,11,12, cp1);
    Point_3D_couleur p_3_5(p_3_4);
    p_3_1.afficher();
    p_3_2.afficher();
    p_3_3.afficher();
    p_3_4.afficher();
    p_3_5.afficher();

    //Point_3D_couleur p1;
    

    return 0;
}
