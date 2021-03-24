#ifndef PANNEAU_H
#define PANNEAU_H
#include "QString"
#include "QList"


class Panneau
{
public:    
    Panneau(QString nom_panneau="", double larg=0, double lg=0, double ep=0,bool opti=false,int numplaque=0);
    void setNom(QString nom_panneau);
    void setLarg(double larg);
    void setLong(double lg);
    void setEp(double ep);
    void setOptimise(bool opti);
    void setError(bool err);

    void setNumPlaque(int numplaque);
    void setPos(double x,double y);
    void setRot(bool rot);

    QString getNom();
    double getLarg() ;
    double getLong() ;
    double getEp();
    bool isOptimise();
    bool isError();
    int getNumPlaque();
    int getPosX();
    int getPosY();
    bool isRotate();
    double getSurface();

double longueur;


private:
    double largeur,epaisseur;
    QString nom;
    bool optimise,rotation,erreur;
    int noplaque,posX,posY;

};

class Ensemble_Panneaux
{
public:
    Ensemble_Panneaux(QList<Panneau *> *liste);
private:
    QList <Panneau *> *listePanneaux;
};

#endif // PANNEAU_H
