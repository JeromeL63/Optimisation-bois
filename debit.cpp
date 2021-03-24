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

#include "debit.h"

Debit::Debit(QString nom_debit, double larg, double lg, double ep, bool opti, int numplaque)
{
    m_nom=nom_debit;
    m_largeur=larg;
    m_longueur=lg;
    m_epaisseur=ep;
    m_optimise=opti;
    m_numBrut=numplaque;

}

QString Debit::getNom() const{return m_nom;}
void Debit::setNom(const QString &nom){m_nom = nom;}

double Debit::getLargeur() const{return m_largeur;}
void Debit::setLargeur(double largeur){m_largeur = largeur;}

double Debit::getEpaisseur() const{return m_epaisseur;}
void Debit::setEpaisseur(double epaisseur){m_epaisseur = epaisseur;}

double Debit::getLongueur() const{return m_longueur;}
void Debit::setLongueur(double longueur){m_longueur = longueur;}

bool Debit::getOptimise() const{return m_optimise;}
void Debit::setOptimise(bool optimise){m_optimise = optimise;}

bool Debit::getRotation() const{return m_rotation;}
void Debit::setRotation(bool rotation){m_rotation = rotation;}

bool Debit::getErreur() const{return m_erreur;}
void Debit::setErreur(bool erreur){m_erreur = erreur;}

int Debit::getNumBrut() const{return m_numBrut;}
void Debit::setNumBrut(int numBrut){m_numBrut = numBrut;}

int Debit::getPosX() const{return m_posX;}
void Debit::setPosX(int posX){m_posX = posX;}

int Debit::getPosY() const{return m_posY;}
void Debit::setPosY(int posY){m_posY = posY;}
