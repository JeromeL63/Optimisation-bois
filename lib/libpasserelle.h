#ifndef PASSERELLE_H
#define PASSERELLE_H
#include "QTableWidgetItem"
#include "QList"
#include "panneau.h"
#include "QFile"
#include "QTextStream"





class Passerelle
{
public:
    Passerelle();
    QList <QTableWidgetItem *> addLine(Panneau *panneau);
    QList <Panneau *> import(QString file);
private:
    QTableWidget *tab;
};

#endif // PASSERELLE_H
