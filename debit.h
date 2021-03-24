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

#ifndef DEBIT_H
#define DEBIT_H

#include <QString>
#include <QList>


class Debit
{
public:
    Debit(QString nom_debit="",double larg=0, double lg=0, double ep=0,bool opti=false,int numplaque=0);

    QString getNom() const;
    void setNom(const QString &nom);

    double getLargeur() const;
    void setLargeur(double largeur);

    double getEpaisseur() const;
    void setEpaisseur(double epaisseur);

    double getLongueur() const;
    void setLongueur(double longueur);

    bool getOptimise() const;
    void setOptimise(bool optimise);

    bool getRotation() const;
    void setRotation(bool rotation);

    bool getErreur() const;
    void setErreur(bool erreur);

    int getNumBrut() const;
    void setNumBrut(int numBrut);

    int getPosX() const;
    void setPosX(int posX);

    int getPosY() const;
    void setPosY(int posY);

private:
    QString m_nom;
    double m_largeur,m_epaisseur,m_longueur;
    bool m_optimise,m_rotation,m_erreur;
    int m_numBrut,m_posX,m_posY;
};

#endif // DEBIT_H
