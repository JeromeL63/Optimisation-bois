/*
***************************************************************************
# *   (c) Jerome Laverroux (jerome.laverroux@free.fr) 2021                  *
# *                                                                         *
# *   This file is part of Optimisation-bois development system.            *
# *                                                                         *
# *   This program is free software; you can redistribute it and/or modify  *
# *   it under the terms of the GNU Lesser General Public License (LGPL)    *
# *   as published by the Free Software Foundation; either version 2 of     *
# *   the License, or (at your option) any later version.                   *
# *   for detail see the LICENCE text file.                                 *
# *                                                                         *
# *   Optimisation-bois is distributed in the hope that it will be useful,  *
# *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
# *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
# *   GNU Lesser General Public License for more details.                   *
# *                                                                         *
# *   You should have received a copy of the GNU Library General Public     *
# *   License along with Optimisation-bois; if not,                         *
# *   write to the Free Software                                            *
# *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
# *   USA                                                                   *
# *                                                                         *
# *   Jerome Laverroux 2021                                                 *
# ***************************************************************************
*/

#ifndef CALCULS_H
#define CALCULS_H

#include <QList>
#include <QObject>
#include "debit.h"
#include "brut.h"
#include "algorythm.h"



class Calculs :public QObject
{
    Q_OBJECT
public:
    Calculs(QList<Debit*> *listeDebits=nullptr,Brut* formats=nullptr,double ep_trait_de_scie=10.0);

    void createBrut(int numBrut);
    Q_INVOKABLE bool optimiser(ListeDebits *listeDbx);
    void updateDebits();
    bool testFormats();


    void trierDebits();
    void trierChuttes();


    int getNbreBruts() const;
    void setNbreBruts(int nbreBruts);

    int rechercher(int dim_x,int dim_y);

    Debit* getDebitMini();


    QList<Debit *> *getListeDebits() const;



    Q_INVOKABLE void setFormatDefaut(Brut *value);

    Q_INVOKABLE void setEp_scie(double ep_scie);

private:
    int m_nbreBruts;
    double m_ep_scie;
    double m_largFormat,m_longFormat,m_epFormat;
    QList<Brut *> *m_listeBruts;
    QList<Brut *> *m_listeChuttes;
    QList<Debit *> *m_listeDebits;
    Brut *formatDefaut;
    ListeDebits *m_DebitsCalcules;


};

#endif // CALCULS_H
