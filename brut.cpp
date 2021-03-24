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

#include "brut.h"

Brut::Brut(double larg, double lg, double ep, int num)
{
    m_largeur=larg;
    m_longueur=lg;
    m_epaisseur=ep;
    m_numBrut=num;
    m_rebus=100.0;//perte de matière -> 100%

}

double Brut::getLargeur() const{return m_largeur;}
void Brut::setLargeur(double largeur){m_largeur = largeur;}

double Brut::getLongueur() const{return m_longueur;}
void Brut::setLongueur(double longueur){m_longueur = longueur;}

double Brut::getEpaisseur() const{return m_epaisseur;}
void Brut::setEpaisseur(double epaisseur){m_epaisseur = epaisseur;}

double Brut::getNumBrut() const{return m_numBrut;}
void Brut::setNumBrut(double numBrut){m_numBrut = numBrut;}

double Brut::getCoord_X() const{return m_coord_X;}
void Brut::setCoord_X(double coord_X){m_coord_X = coord_X;}

double Brut::getCoord_Y() const{return m_coord_Y;}
void Brut::setCoord_Y(double coord_Y){m_coord_Y = coord_Y;}

double Brut::getRebus() const{return m_rebus;}

void Brut::retraitRebus(double surface){
    ///soustraction d'une surface à la perte de matière
    double d;
    d=(100.0*surface)/(m_largeur*m_longueur);
    m_rebus=m_rebus-d;
}
