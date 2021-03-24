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

#ifndef BRUT_H
#define BRUT_H


class Brut
{
public:
    Brut(double larg=0, double lg=0, double ep=0, int num=1);

    double getLargeur() const;
    void setLargeur(double largeur);

    double getLongueur() const;
    void setLongueur(double longueur);

    double getEpaisseur() const;
    void setEpaisseur(double epaisseur);

    double getNumBrut() const;
    void setNumBrut(double numBrut);

    double getCoord_X() const;
    void setCoord_X(double coord_X);

    double getCoord_Y() const;
    void setCoord_Y(double coord_Y);

    double getRebus() const;
    void retraitRebus(double surface);


private:
    double m_largeur,m_longueur,m_epaisseur,m_numBrut,m_coord_X,m_coord_Y,m_rebus;
};

#endif // BRUT_H
