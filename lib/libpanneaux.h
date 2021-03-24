#ifndef LIBPANNEAUX_H
#define LIBPANNEAUX_H
#include <QList>
#include "panneau.h"
#include "plaque.h"
#include "lib/libalgorythm.h"
#include "QMessageBox"

class Calculs
{
public:
    Calculs(QList<Panneau *> *listePanneaux , Plaque* formats, double ep_trait_de_scie=10.0, QWidget *parent=0);

    void createPlaque(int numplaque);
    bool optimiser(QList<Panneau *> *listePanneaux);
    bool testFormats();
    bool optimiser_2();


    void TrierPanneaux(QList<Panneau *> *listePanneaux);
    void TrierPlaques(QList<Plaque *> *listePlaques);

    int getNombrePlaques();
    int search(int largeur,int longueur);

    Panneau* getPanneauMini();

    QList<Panneau *> *getListePanneaux();

    ~Calculs();

private:

    int nbreplaques;
    double ep_scie;
    double largformat,longformat,epformat;
    QList<Plaque *> *listplaques;
    QList<Plaque *> *listchuttes;
    QList<Panneau *> *listpanneaux;
    QWidget *wg;
    Plaque *formatdefaut;


};

#endif // LIBPANNEAUX_H
