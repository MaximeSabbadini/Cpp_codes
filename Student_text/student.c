#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min_year 2007  // Année minimale considérée pour accepter l'inscription

// Définition des structures date de naissance et étudiant

typedef struct{
    int jour;
    int mois;
    int annee;
}ddn;


typedef struct{
    char nom[20];
    char prenom[20];
    ddn datedenaissance;
    float n1;
    float n2;
    float n3;
    float m;
}etudiant;

// Définition des fonctions

int bissextile(int y)
{
    // Fonction qui détermine si l'annöe est bissextile ou pas
    // Si l'année est bissextile, retourne 1 sinon retourne 0
    if(((y%4==0) && (y%100!=0)) || (y%400==0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_date(int d, int m, int y)
{
    // Fonction qui vérifie la validité de la date de naissance inscrite
    if(d<0||d>31)
    {
        printf("Date incorrecte\n");
        return 0;
    }
    if(m<0||m>12)
    {
        printf("Date incorrecte\n");
        return 0;
    }
    if(y>min_year)
    {
        printf("Date incorrecte\n");
        return 0;
    }
    if(m==2)
    {
        if(bissextile(y)==1)
        {
            if(d>29)
            {
                printf("Date incorrecte\n");
                return 0;
            }
            else
                return 1;
        }
        else
        {
            if(d>28)
            {
                printf("Date incorrecte\n");
                return 0;
            }
            else
                return 1;
        }
    }
    if((m==2)||(m==4)||(m==6)||(m==9)||(m==11))
    {
        if(d>30)
        {
            printf("Date incorrecte\n");
            return 0;
        }
        else
            return 1;
    }
    else
        return 1;
}

etudiant saisir_1_etudiant()
{
    etudiant e;
    //int number;
    printf("Entrez le nom : ");
    scanf("%s", &e.nom);
    printf("Entrez le prénom : ");
    scanf("%s", &e.prenom);
    printf("Date de naissance ?\n");
    do{
        printf("Jour : ");
        scanf("%d", &e.datedenaissance.jour);
        printf("Mois : ");
        scanf("%d", &e.datedenaissance.mois);
        printf("Annee : ");
        scanf("%d", &e.datedenaissance.annee);
    }while(check_date(e.datedenaissance.jour, e.datedenaissance.mois, e.datedenaissance.annee) != 1);
    do{
        printf("Entrez la note 1 : ");
        scanf("%f", &e.n1);
    }while(e.n1<0||e.n1>20);
    
    do{
        printf("Entrez la note 2 : ");
        scanf("%f", &e.n2);
    }while(e.n2<0||e.n2>20);
    
    do{
        printf("Entrez la note 3 : ");
        scanf("%f", &e.n3);
    }while(e.n3<0||e.n3>20);
    
    e.m = (e.n1+e.n2+e.n3)/3;
    return e;
}

void saisir_n_etudiant(int n, etudiant *e)
{
    int i;
    for(i=0;i<n;i++)
    {
        (*(e+i)) = saisir_1_etudiant();
    }
}

void trait(void)
{
    printf("\n---------------------------------");
}

void titre(char t[50])
{
    trait();
    printf("\n\t\t %s", t);
    trait();
    printf("\n");
}

void afficher_1_etudiant(etudiant e)
{
    titre("Fiche Etudiant");
    printf("\t Nom : %s\n", e.nom);
    printf("\t Prénom : %s\n", e.prenom);
    printf("\t Date de naissance : %d/%d/%d\n", e.datedenaissance.jour, e.datedenaissance.mois, e.datedenaissance.annee);
    printf("\t Moyenne : %f\n", e.m);
}

void afficher_n_etudiant(int n, etudiant *e)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("Fiche %i\n", i+1);
        afficher_1_etudiant((*(e+i)));
    }
}

int saisir_n()
{
    int n;
    do{
        printf("Entrez n : \n");
        scanf("%d", &n);
    }while(n<0);
    return n;
}

int Search_in_File(char *fname, char *str, int print)
{
    // Fonction de recherche d'un string dans le fichier. Si la suite de caractère n'apparait pas, elle retourne 0.
    // Fonction inspirée de https://www.codingunit.com/c-tutorial-searching-for-strings-in-a-text-file
    
    FILE *fp;
    int line_num = 1;
    int find_result = 0;
    char temp[512]; //Chaine de caractère destinée à stocker le contenu de la ligne qui est lue
    
    if((fp = fopen(fname, "r")) == NULL)
    {
        // Erreur dans l'ouverture du fichier
        return(-1);
    }

    while(fgets(temp, 512, fp) != NULL) {
        if((strstr(temp, str)) != NULL) {
            if(print==1){
                printf("\n%s\n", temp);
            }
            find_result++;
        }
        line_num++;
    }

    if(find_result == 0 && print==1) {
        printf("\nSorry, couldn't find a match.\n");
    }
 
    if(fp)
    {
        // Si le fichier n'est pas clos, le fermer.
        fclose(fp);
    }
    return find_result;
}

void enregistrer(int n, etudiant *e, char *fp)
{
    // Fonction qui enregistre l'étudiant saisi dans le fichier texte.
    
    int i;
    char nom[50], prenom[20];
    FILE *file;
    
    file = fopen(fp, "a+"); //Ici on ouvre puis ferme le fichier pour nous assurer que celui-ci existe déjà. S'il n'existe pas, il est automatiquement créé.
    fclose(file);
    for(i=0;i<n;i++)
    {
        strcpy(nom, (e+i)->nom);
        strcpy(prenom, (e+i)->prenom);
        strcat(nom, "\t");
        strcat(nom, prenom);
        
        // Pour chaque enregistrement, il nous faut tout d'abord vérifier que celui-ci n'existe pas déjà. Pour cela, Je recompose un string comme il est censé être écrit dans le fichier texte, avec une tabulation entre le nom et le prénom.
        // Nous cherchons alors dans le fichier texte si un enregistrement n'existe pas déjà, cela grâce à la fonction Search_in_File. Si celle-ci retourne 0, cela veut dire que l'étudiant n'existe pas déjà nous pouvons donc l'enregistrer. L'enregistrement est validé avec une phrase dans le terminal. Si l'étudiant existait déjà, L'utilisateur en est informé et rien n'est fait.
        
        if(Search_in_File(fp, nom, 0) == 0)
        {
            file = fopen(fp, "a+");
            fprintf(file, "%s\t", (e+i)->nom);
            fprintf(file, "%s\t", (e+i)->prenom);
            fprintf(file, "%d/%d/%d\t", (e+i)->datedenaissance.jour,(e+i)->datedenaissance.mois, (e+i)->datedenaissance.annee);
            fprintf(file, "%f\n", (e+i)->m);
            fclose(file);
            printf("Enregistrement au nom %s réussi\n", nom);
        }
        else
        {
            printf("Un enregistrement au nom %s existe déjà\n", nom);
        }
    }
}

void afficher_tous_etudiants(char *fname)
{
    // Fonction qui permet d'afficher tous les étudiants présents dans le fichier texte.
    
    FILE *fp;
    char temp[512]; //Chaine de caractère destinée à stocker le contenu de la ligne qui est lue
    etudiant e;
    if((fp = fopen(fname, "r")) == NULL)
    {
        printf("Erreur dans l'ouverture du fichier");
    }

    while(fgets(temp, 512, fp) != NULL)
        {
            // Pour chaque ligne, on sépare chaque champ du fichier texte pour les stocker dans une structure etudiant. Il ne nous suffit plus qu'à afficher cet étudiant grâce à la fonction prévue à cet effet.
            
            sscanf(temp, "%s  %s  %d/%d/%d  %f", e.nom, e.prenom, &e.datedenaissance.jour, &e.datedenaissance.mois, &e.datedenaissance.annee, &e.m);
            afficher_1_etudiant(e);
        }

    if(fp){
        fclose(fp);
    }
}

void rechercher(char *fname, char nom[20], char prenom[20], float m)
{
    // Fonction qui recherche un étudiant par son nom ou son prénom ou sa moyenne.
    
    FILE *fp;
    int counter = 0;
    char temp[512];
    etudiant e;
    
    if((fp = fopen(fname, "r")) == NULL)
    {
        printf("Erreur dans l'ouverture du fichier");
    }

    while(fgets(temp, 512, fp) != NULL)
        {
            sscanf(temp, "%s  %s  %d/%d/%d  %f", e.nom, e.prenom, &e.datedenaissance.jour, &e.datedenaissance.mois, &e.datedenaissance.annee, &e.m);
            // On stocke chaque champ dans une structure étudiant.
            if(strcmp(nom, e.nom)==0 || strcmp(prenom, e.prenom)==0 || m == e.m)
            {
                // Ici on compare les noms/prénoms/moyennes de chaque enregistrement du fichier avec les noms/prénoms/moyennes entrés par l'utilisateur puis on affiche le ou les résultats qui correspondent.
                afficher_1_etudiant(e);
                counter++;
            }
        }
    if(counter==0)
    {
        // S'il n'y a aucun résultat, la variable counter reste à la valeur 0 et on indique à l'utilisateur que aucun résultat n'a öté trouvé
        printf("Aucun résultat trouvé\n");
    }
    if(fp){
        fclose(fp);
    }
}

int main()
{
    int n, saisie, saisie2; // n : Nombre d'enregistrements que l'utilisateur va saisir, saisie : Choix de l'utilisateur dans le menu principal, saisie2 : Choix de l'utilisateur pour la recherche d'un étudiant.
    char *file_path = "/Users/maximesabbadini/Desktop/etudiant.txt"; //Chemin amenant au fichier txt
    char nom[20], prenom[20];
    float moyenne;
    
    while(1) //Boucle infinie qui ne se termine que si l'utilisateur quitte le menu en entrant le chiffre 4.
    {
        titre("Menu Principal");
        printf("1 : Saisir des étudiants\n");
        printf("2 : Afficher tous les étudiants enregistrés\n");
        printf("3 : Recherche d'un étudiant\n");
        printf("4 : Quitter\n");
    
        do{
            printf("Votre choix : ");
            scanf("%d", &saisie);
        }while(saisie<0 || saisie>4);
    
    
        if(saisie==1)
        {
            // system("cls")
            // Faire la saisie des étudiants
            printf("Saisir des étudiants\n");
            n = saisir_n();
            etudiant *e;
            e = (etudiant *)malloc(n*sizeof(etudiant));
            saisir_n_etudiant(n, e);
            enregistrer(n, e, file_path);
            free(e);
            //Mettre la fonction system qui attend l'action de l'utilisateur pour afficher le reste
        }
        else
        {
            if(saisie==2)
            {
                // L'utilisateur veut consulter tous les étudiants présents dans le fichier texte
                titre("Affichage de tous les étudiants du fichier txt");
                afficher_tous_etudiants(file_path); // On appelle la fonction qui affiche tous les étudiants
            }
            else
            {
                if (saisie==3)
                {
                    // L'utilisateur veut effectuer une recherche d'étudiant
                    titre("Recherche d'étudiants");
                    printf("1 : Recherche par nom\n");
                    printf("2 : Recherche par prénom\n");
                    printf("3 : Recherche par moyenne\n");
                    printf("4 : Retour au menu\n");
                    do{
                        printf("Votre choix : ");
                        scanf("%d", &saisie2);
                    }while(saisie2<0 || saisie2>4);
                    
                    if(saisie2==1)
                    {
                        // L'utilisateur recherche un étudiant par son nom
                        //system("cls");
                        printf("Entrez le nom : ");
                        scanf("%s", nom);
                        rechercher(file_path, nom, "", -1);
                        // Ici on recherche un étudiant par son nom, nous ne connaissons pas son prénom ni sa moyenne. Le fait que les conditions pour trouver un match dans le fichier soient séparées par des "||" montre qu'une seule des 3 conditions doit être réunie. J'ai décidé de mettre -1 dans le champ de la moyenne pour être sûr que nous ne tombions pas malencontreusement sur une personne que nous ne cherchons pas.
                    }
                    else
                    {
                        if(saisie2==2)
                        {
                            // L'utilisateur recherche un étudiant par son prénom
                            //system("cls");
                            printf("Entrez le prénom : ");
                            scanf("%s", prenom);
                            rechercher(file_path, "", prenom, -1);
                            // Ici même principe qu'en haut
                        }
                        else
                        {
                            if(saisie2==3)
                            {
                                // L'utilisateur recherche un étudiant par sa moyenne
                                //system("cls");
                                printf("Entrez la moyenne : ");
                                scanf("%f", &moyenne);
                                rechercher(file_path, "", "", moyenne);
                                // Ici même principe qu'en haut
                            }
                        }
                    }
                }
                else
                {
                    if(saisie==4)
                    {
                        // Si l'utilisateur saisit 4, le programme prend fin.
                        return 0;
                    }
                }
            }
        }
    }
}
