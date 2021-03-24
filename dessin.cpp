#include "dessin.h"
#include <QDebug>

#define ech 7.5
#define larg_rot_mini 500.0


QColor coul_plaques(100,220,80);
QColor coul_panx(200,160,79);



Dessin::Dessin(int nbrePlaques, Plaque *plaqueRef)
{
    this->clear();
    int longplaque=plaqueRef->getLong()/ech;
    int offset=0;   

    /// DESSIN des plaques/barres
     plaque=new QList<QGraphicsRectItem *>;
     int lx,ly;
     lx=plaqueRef->getLarg()/ech;
     ly=plaqueRef->getLong()/ech;
    for(int i=0;i<nbrePlaques;i++)
    {
        offset=offset+(50/ech);

        QGraphicsRectItem *pl=new QGraphicsRectItem(0,0,lx,ly);
        pl->setPos(0,offset);
        pl->setBrush(QBrush(coul_plaques));
        if(lx<ly){pl->setRotation(-90);}
        plaque->append(pl);

        this->addItem(plaque->at(i));
        ///reglage des marges entre plaques/barres
        double hauteur_dessin=0;
        if(lx<ly){hauteur_dessin=lx;}
        else{hauteur_dessin=ly;}
        offset=offset+hauteur_dessin+(250/ech);

    }


}

///dessin des panneaux
void Dessin::drawPanneaux(QList<Panneau *> *panneaux)
{

    for(int i=0;i<panneaux->count();i++)
    {


        double x,y,larg,lg;


        if(panneaux->at(i)->isOptimise())
        {
            int num_plaque=0;
            num_plaque=panneaux->at(i)->getNumPlaque()-1;

            x=panneaux->at(i)->getPosX()/ech;
            y=panneaux->at(i)->getPosY()/ech;
            larg=panneaux->at(i)->getLarg()/ech;
            lg=panneaux->at(i)->getLong()/ech;
            QGraphicsRectItem *pan=new QGraphicsRectItem(0,0,larg,lg,plaque->at(num_plaque));
            ///disposition suivant la plaque dans laquelle le panneau est débité
            pan->mapToParent(0,0,larg,lg);
            pan->setPos(x,y);


            QGraphicsTextItem *nom=new QGraphicsTextItem(pan);

            nom->setHtml("<b>"+panneaux->at(i)->getNom()+"</b> "+QString().setNum(panneaux->at(i)->getLarg())+"x"+QString().setNum(panneaux->at(i)->getLong()));

            nom->setDefaultTextColor(Qt::black);



            //rotation du text
            if(panneaux->at(i)->getLarg()<larg_rot_mini)
            {
                nom->moveBy(ech*2.5,0);
                nom->setRotation(90);
            }
            nom->mapToParent(0,0);



            pan->setBrush(QBrush(coul_panx ));



        }

    }

}


