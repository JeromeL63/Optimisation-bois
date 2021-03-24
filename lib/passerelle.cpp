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

#include "passerelle.h"
#include <QDebug>

Passerelle::Passerelle(ListeDebits *liste, QObject *parent)
{
    m_liste=liste;
}

void Passerelle::import(QUrl file)
{
    ///import d'un fichier .csv de débits sous la forme:
    /// Numéro de production ; Qté ; largeur ; longueur

    QFile fichier(file.toLocalFile());
    QStringList tampon;tampon.clear();
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&fichier);
    do{
        tampon<<in.readLine();

    }while(!in.atEnd());

    QList<Debit *> list;
     for(int i=0;i<tampon.count();i++)
     {
         QString ligne=tampon.at(i);
         QStringList t=ligne.split(';');
         if(t.count()==4)
         {
             QString nombre(t.at(1));/// récupération du nombre de panneaux
             int nbre=nombre.toInt();/// cast en int

             for(int j=0;j<nbre;j++)
             {
                 ///insertion des panneaux dans la liste
             Debit *p=new Debit(t.at(0),QString(t.at(2)).toDouble(),QString(t.at(3)).toDouble());
                     list.append(p);
             }
         }
     }
     //return list;
     m_liste->setListe(list);
     qDebug()<<m_liste->rowCount();
}


