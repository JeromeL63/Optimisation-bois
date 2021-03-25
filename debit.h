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
#include <QHash>
#include <QByteArray>
#include <QObject>
#include <QAbstractListModel>


class Debit
{
    //Q_OBJECT
    //Q_PROPERTY(QString nom READ getNom WRITE setNom)

public:
    Debit(QString nom_debit="",double larg=0, double lg=0, double ep=0,bool opti=false,int numBrut=0,bool erreur=false);

 /*   enum DebitRoles{
        nomRole=Qt::UserRole,
        largeurRole=Qt::UserRole +1,
        longueurRole=Qt::UserRole +2,
        epaisseurRole=Qt::UserRole +3,
        optimiseRole=Qt::UserRole +4,
        numBrutRole=Qt::UserRole +5
    };*/



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


class ListeDebits : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<Debit*> *liste READ getListe WRITE setListe NOTIFY listeChanged)
public:
       enum DebitRoles{
           nomRole=Qt::UserRole,
           largeurRole=Qt::UserRole +1,
           longueurRole=Qt::UserRole +2,
           epaisseurRole=Qt::UserRole +3,
           optimiseRole=Qt::UserRole +4,
           numBrutRole=Qt::UserRole +5,
           erreurRole=Qt::UserRole +6
       };

    ListeDebits(QObject *parent=nullptr);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index,const QVariant &value, int role = Qt::EditRole);

    void append(Debit* d);
    Q_INVOKABLE int getNumBrut(int index);
    Q_INVOKABLE int getPosX(int index);
    Q_INVOKABLE int getPosY(int index);
    Q_INVOKABLE QString getNom(int index);
    Q_INVOKABLE double getLargeur(int index);
    Q_INVOKABLE double getLongueur(int index);


    Q_INVOKABLE QList<Debit *> *getListe() const;
    void setListe(QList<Debit *> *liste);

signals:
    void listeChanged();

protected:
    QHash<int, QByteArray> roleNames() const;

private :
    QList<Debit *> *m_liste;

};


#endif // DEBIT_H
