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
#include <QDebug>

Debit::Debit(QString nom_debit, double larg, double lg, double ep, bool opti, int numBrut)
{
    m_nom=nom_debit;
    m_largeur=larg;
    m_longueur=lg;
    m_epaisseur=ep;
    m_optimise=opti;
    m_numBrut=numBrut;

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




ListeDebits::ListeDebits(QObject *parent)
{
    Q_UNUSED(parent)
    m_liste=new QList<Debit *>;

}

///utilisé pour le model QML
QHash<int, QByteArray> ListeDebits::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[nomRole] = "nom";
    roles[largeurRole] = "largeur";
    roles[longueurRole] = "longueur";
    roles[epaisseurRole] = "epaisseur";
    roles[optimiseRole] = "optimise";
    roles[numBrutRole] = "num_brut";
    roles[erreurRole] ="erreur";

    return roles;
}





int ListeDebits::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_liste->count();

}

QVariant ListeDebits::data(const QModelIndex &index, int role) const
{

    QVariant value;
        if (index.isValid()) {
            if (role < Qt::UserRole) {
                qDebug()<<"role inférieur à Qt::userrole";
            } else {
                const Debit *d= m_liste->at(index.row());
                switch(role){
                default:
                    break;

                case nomRole:
                    value=d->getNom();
                    break;
                case largeurRole:
                    value=d->getLargeur();
                    break;
                case longueurRole:
                    value=d->getLongueur();
                    break;
                case epaisseurRole:
                    value=d->getEpaisseur();
                    break;
                case optimiseRole:
                    value=d->getOptimise();
                    break;
                case numBrutRole:
                    value=d->getNumBrut();
                    break;
                case erreurRole:
                    value=d->getErreur();
                    break;

                }
            }
        }
        return value;
}

bool ListeDebits::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.row()<0 || index.row() > m_liste->count()){return false;}
    if(role == Qt::EditRole){

        ///TODO

        emit dataChanged(index,index,{role});
        return true;
    }
    else return false;

}


QList<Debit *> *ListeDebits::getListe() const
{
    return m_liste;
}


void ListeDebits::setListe(QList<Debit *> *liste)
{
    ///vidage du model
    this->beginRemoveRows(QModelIndex(),0,rowCount());
    m_liste->clear();
    this->endRemoveRows();
    ///insertion des nouvelles lignes
    this->beginInsertRows(QModelIndex(),0,liste->count());
    m_liste = liste;
    this->endInsertRows();
    ///information au QML que le model a changé
    emit dataChanged(QModelIndex(),QModelIndex());
}



void ListeDebits::append(Debit *d)
{
/*
    m_liste->append(d);

*/
}
