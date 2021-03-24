#ifndef PLAQUE_H
#define PLAQUE_H

#include<QtGlobal>



class Plaque
{
public:
    Plaque(double larg=0,double lg=0,double ep=0,int noplaque=1);
    void setLarg(double larg);
    void setLong(double lg);
    void setEp(double ep);
    void setCoord(double x,double y);
    void setNumPlaque(int noplaque);
    void soustraitPerte(double surface);


    double getLarg();
    double getLong();
    double getEp();
    int getNumPlaque();
    double get_X();
    double get_Y();
    double getPerte();
    double getSurface();

private:
    double largeur,longueur,epaisseur,numPlaque,coord_x,coord_y,rebus;


};

#endif // PLAQUE_H
