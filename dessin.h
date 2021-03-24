#ifndef DESSIN_H
#define DESSIN_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QList>
#include <QTransform>
#include "panneau.h"
#include "plaque.h"


class Dessin : public QGraphicsScene
{
public:
    Dessin(int nbrePlaques, Plaque *plaqueRef);

   void  drawPanneaux(QList<Panneau *> *panneaux);
private:
    QList<QGraphicsRectItem *> *plaque;
};

#endif // DESSIN_H
