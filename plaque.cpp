#include "plaque.h"

Plaque::Plaque(double larg, double lg, double ep, int noplaque)
{
    largeur=larg;longueur=lg;epaisseur=ep;numPlaque=noplaque;
    coord_x=0;coord_y=0;rebus=100.0;
}

void Plaque::setLarg(double larg){largeur=larg;}
void Plaque::setLong(double lg){longueur=lg;}
void Plaque::setEp(double ep){epaisseur=ep;}

void Plaque::setCoord(double x, double y)
{
    coord_x=x;coord_y=y;
}


void Plaque::setNumPlaque(int noplaque)
{
    numPlaque=noplaque;
}

void Plaque::soustraitPerte(double surface)
{
    double d;
    d=(100.0*surface)/(largeur*longueur);
    rebus=rebus-d;
}



double Plaque::getLarg(){return largeur;}
double Plaque::getLong(){return longueur;}
double Plaque::getEp(){return epaisseur;}

int Plaque::getNumPlaque()
{
    return numPlaque;
}

double Plaque::get_X()
{
    return coord_x;
}

double Plaque::get_Y()
{
    return coord_y;
}

double Plaque::getPerte()
{
    return rebus;
}

double Plaque::getSurface()
{
    return largeur*longueur;
}
