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

#include "calculs.h"
#include <QDebug>


Calculs::Calculs(QList<Debit *> *listeDebits, Brut *formats, double ep_trait_de_scie)
{
    m_listeDebits=new QList<Debit *>;
    m_listeBruts=new QList<Brut *>;
    m_listeChuttes=new QList<Brut *>;
    m_DebitsCalcules=new ListeDebits;

}

void Calculs::createBrut(int numBrut)
{    
    Brut *pl=new Brut(m_largFormat,m_longFormat,m_epFormat);
    //pl=formatDefaut;
    pl->setCoord_X(0);
    pl->setCoord_Y(0);

    m_listeChuttes->append(pl);
    m_listeChuttes->at(m_listeChuttes->count()-1)->setNumBrut(numBrut);
    m_listeChuttes->at(m_listeChuttes->count()-1)->setLongueur(formatDefaut->getLongueur());
    ///ajout à la liste de plaque
    m_listeBruts->append(pl);

}

int Calculs::optimiser(ListeDebits *listeDbx)
{
    qDebug()<<"Calculs::optimiser";
    ////TODO
    /// utiliser setData de Liste Debit
    /// créer les setData
    ///return error:
    /// 1 : pas de format par défaut
    /// 2: panneaux exèdent le format de base


    if(formatDefaut == nullptr){return 1;}
    m_listeDebits->clear();

    *m_listeDebits<<*listeDbx->getListe();
    ///reset des optimisations
    qDebug()<<"nbre de pièces"<<m_listeDebits->count();
    for(int i=0;i<m_listeDebits->count();i++){m_listeDebits->at(i)->setOptimise(false);}
    ///vidage de la liste de pièces brutes
    m_listeBruts->clear();
    ///vidage de la liste des chutes
    m_listeChuttes->clear();
    ///TEST des panneaux excedant le format de base
    if(!testFormats()){return 2;}
    qDebug()<<"formats OK";

    m_nbreBruts=1;
    int x=0;
    int y=0;

    if(!m_listeDebits->isEmpty())///on vérifie que la liste de débits est remplie
    {
        ///création de la première plaque
        createBrut(m_nbreBruts);

        ///les débits sont triés par largeur et longueurs décroissantes
        trierDebits();
        qDebug()<<"tris débits OK";

        bool all_optimise=false;
        bool deuxieme_part=false;
        bool match_brut=false;


       do///tant que tous les débits ne sont pas optimisés
       {
            int no_deb=-1;
           // qDebug()<<"Plaque "<<nbreplaques<<" reste :"<<m_listeChuttes->at(0)->getLong()<<"mm";


         ///triage des bout de pieces brutes restants par ordre croissant
            trierChuttes();
            qDebug()<<"liste des plaques";
            for(int z=0;z<m_listeChuttes->count();z++){
                qDebug()<<m_listeChuttes->at(z)->getLargeur()<<"x"<<m_listeChuttes->at(z)->getLongueur()<<m_listeChuttes->at(z)->getCoord_X()<<"|"<<m_listeChuttes->at(z)->getCoord_Y();
            }

            do///tant que le débit ne rentre pas dans une chutte de pièce brute
            {

                 match_brut=false;


                ///si le test dépasse le nombre de chutes de plaques, création d'une nouvelle plaque
                if(m_listeChuttes->isEmpty()){m_nbreBruts++;createBrut(m_nbreBruts);deuxieme_part=false;}

                ///on teste s'il reste de la matière
                if(m_listeChuttes->at(0)->getLongueur()>0)
                {
                ///Recherche d'un débit qui peut rentrer dans la chutte
                no_deb=rechercher(m_listeChuttes->at(0)->getLargeur(),m_listeChuttes->at(0)->getLongueur());
                }

                if(no_deb != -1)/// si un débit peut passer
                {
                    match_brut=true;
                    qDebug()<<"---------"<<m_listeDebits->at(no_deb)->getNom()<<"passe dans "<<m_listeChuttes->at(0)->getLargeur()<<m_listeChuttes->at(0)->getLongueur();
                }
                ///sinon on supprime la chutte de la liste
                else
                {
                    //qDebug()<<"chutte "<<m_listeChuttes->at(0)->getLarg()<<" x "<<m_listeChuttes->at(0)->getLong()<<" plaque"<<m_listeChuttes->at(0)->getNumPlaque()<<" supprimé";
                    m_listeChuttes->removeFirst();
                }


            }while(!match_brut);




           if(match_brut)/// s'il y a une pièce brute qui correspond à l'un des deux cas
           {

               ///phase de positionnement(nécessaire au dessin panneau/plaques)

               ///création des coordonnées du panneau dans la plaque

                m_listeDebits->at(no_deb)->setPosX(m_listeChuttes->at(0)->getCoord_X());
                m_listeDebits->at(no_deb)->setPosY(m_listeChuttes->at(0)->getCoord_Y());
                qDebug()<<"Panneau "<<m_listeDebits->at(no_deb)->getNom()<<" X:"<<m_listeDebits->at(no_deb)->getPosX()<<"|Y:"<<m_listeDebits->at(no_deb)->getPosY();
                //qDebug()<<m_listeDebits->at(no_pan)->getLarg()<<" x "<<m_listeDebits->at(no_pan)->getLong();



                ///phase de découpe/////////////


                ///si la largeur/longueur du panneau est inf à la plaque
                ///
                if(m_listeDebits->at(no_deb)->getLargeur()<=m_listeChuttes->at(0)->getLargeur())
                {

                    ///découpe en deux partie

                    ///on crée les coordonnées de l'emplacement libre
                    //x=m_listeChuttes->at(0)->getCoord_X()+m_listeDebits->at(no_pan)->getLargeur()+m_ep_scie;
                    //y=m_listeDebits->at(no_pan)->getPosY();
                    x=m_listeDebits->at(no_deb)->getPosX();
                    y=m_listeChuttes->at(0)->getCoord_Y()+m_listeDebits->at(no_deb)->getLongueur()+m_ep_scie;



                    ///on modifie l'emplacement libre du brut
                    //double largPlaque=m_listeChuttes->at(0)->getLargeur()-m_listeDebits->at(no_pan)->getLargeur()-m_ep_scie;
                    //double longPlaque=m_listeDebits->at(no_pan)->getLongueur();
                    double largPlaque= m_listeDebits->at(no_deb)->getLargeur();
                    double longPlaque=m_listeChuttes->at(0)->getLongueur()-m_listeDebits->at(no_deb)->getLongueur()-m_ep_scie;
                    qDebug()<<"modif emplacement libre"<<largPlaque<<"x"<<longPlaque;


                    int no_plaque=m_listeChuttes->at(0)->getNumBrut();

                    Brut *pl=new Brut(largPlaque,longPlaque,0,no_plaque);
                    pl->setCoord_X(x);
                    pl->setCoord_Y(y);



                    ///on modifie le format de la plaque du bas


                    //y=m_listeChuttes->at(0)->getCoord_Y()+m_listeDebits->at(no_pan)->getLongueur()+m_ep_scie;
                    //m_listeChuttes->at(0)->setCoord_Y(y);
                    x=m_listeChuttes->at(0)->getCoord_X()+m_listeDebits->at(no_deb)->getLargeur()+m_ep_scie;
                    m_listeChuttes->at(0)->setCoord_X(x);

                   // m_listeChuttes->at(0)->setCoord_X(m_listeChuttes->at(0)->getCoord_X());

                    /// Màj 2021 : on modifie seulement si le brut n'a jamais été coupé
                    if(m_listeChuttes->at(0)->getLongueur() == formatDefaut->getLongueur())
                    {
                       // qDebug()<<"plaque "<<m_listeChuttes->at(0)->getNumBrut()<<m_listeChuttes->at(0)->getLargeur()<<"x"<<m_listeChuttes->at(0)->getLongueur();
                       // m_listeChuttes->at(0)->setLongueur(m_listeChuttes->at(0)->getLongueur()-longPlaque-m_ep_scie);
                        m_listeChuttes->at(0)->setLargeur(m_listeChuttes->at(0)->getLargeur()-largPlaque-m_ep_scie);
                    }

                    qDebug()<<"plaque "<<m_listeChuttes->at(0)->getNumBrut()<<m_listeChuttes->at(0)->getLargeur()<<"x"<<m_listeChuttes->at(0)->getLongueur()<<m_listeChuttes->at(0)->getCoord_X()<<";"<<m_listeChuttes->at(0)->getCoord_Y();



                    ///suppression de la plaque existante et ajout de la nouvelle chutte créée

                    if(m_listeChuttes->at(0)->getLongueur() != m_longFormat){
                        m_listeChuttes->removeFirst();
                    }

                    m_listeChuttes->append(pl);

                    deuxieme_part=true;
                    qDebug()<<"plaque "<<pl->getNumBrut()<<pl->getLargeur()<<"x"<<pl->getLongueur()<<pl->getCoord_X()<<";"<<pl->getCoord_Y();
                }



                if(!deuxieme_part)///si on est en pleine plaque
                {
                    ///on soustrait la longueur du panneau à la plaque + épaisseur du trait de scie

                    y=m_listeChuttes->at(0)->getCoord_Y()+m_listeDebits->at(no_deb)->getLongueur()+m_ep_scie;
                    m_listeChuttes->at(0)->setCoord_X(m_listeChuttes->at(0)->getCoord_X());
                    m_listeChuttes->at(0)->setCoord_Y(y);

                    double nouvelleLong=0.0;
                    nouvelleLong=m_listeChuttes->at(0)->getLongueur()-m_listeDebits->at(no_deb)->getLongueur()-m_ep_scie;
                    m_listeChuttes->at(0)->setLongueur(nouvelleLong);
                    qDebug()<<"Plaque après découpe:"<<m_listeChuttes->at(0)->getNumBrut()<<"Lg :"<<m_listeChuttes->at(0)->getLongueur();
                }



                ///atribution n° plaque au panneau
                m_listeDebits->at(no_deb)->setNumBrut(m_listeChuttes->at(0)->getNumBrut());
                m_listeDebits->at(no_deb)->setOptimise(true);

                ///si l'épaisseur du trait de scie donne une valeur négative, on ramène la valeur à 0
             /*   if(m_listeChuttes->at(0)->getLongueur()<=0)
                {
                    m_listeChuttes->at(0)->setLongueur(0);
                }*/

           }


           for(int i=0;i<m_listeDebits->count();i++)
           {
               if(!m_listeDebits->at(i)->getOptimise())
               {
                    all_optimise=false;
                   break;
               }
               else{all_optimise=true;}
           }

        }while(!all_optimise);

    }
    //// pour finir on réinjecte les valeur dans la liste abstraite "communication QML"

    for (int i=0;i<m_listeDebits->count();i++) {
        qDebug()<<m_listeDebits->at(i)->getNumBrut();
    }

    listeDbx->setListe(m_listeDebits);


    return 0;
}



bool Calculs::testFormats()
{
    ///recherche des formats excédant le format de plaque par défaut, et pointage de ceux ci
    /// renvoi TRUE s'il n'y a pas d'erreur
    ///
        double laform,lgform;
        laform=formatDefaut->getLargeur();
        lgform=formatDefaut->getLongueur();
        bool sortie= true;

        qDebug()<<"TEST des formats :"<<laform<<"x"<<lgform;
        for(int i=0;i<m_listeDebits->count();i++)
        {
            double lapan,lgpan;
            lapan=m_listeDebits->at(i)->getLargeur();
            lgpan=m_listeDebits->at(i)->getLongueur();

            if(lapan>laform || lgpan>lgform)
            {
                QString t;
                if(lapan>laform){t.append("La largeur du panneau ");}
                else{t.append("La longueur du panneau ");}
                t.append(m_listeDebits->at(i)->getNom()+" ("+QString().setNum(lapan)+"x"+QString().setNum(lgpan)+"mm)");
                ///depassement de dimension
                t.append(" dépasse le format de la plaque \n Faut-il le retourner ?");
                qDebug()<<t;
              /*  int decision=0;
                switch (decision) {
                case 1:
                    m_listeDebits->at(i)->setLargeur(lgpan);
                    m_listeDebits->at(i)->setLongueur(lapan);
                    testFormats();
                    break;

                case 0:
                    m_listeDebits->at(i)->setErreur(true);
                    break;

                default:
                    m_listeDebits->at(i)->setErreur(true);
                    break;
                }*/
            }

        }

        for(int i=0;i<m_listeDebits->count();i++){
            if(m_listeDebits->at(i)->getErreur()){sortie=false;}
            //qDebug()<<m_listeDebits->at(i)->getErreur()<<m_listeDebits->at(i)->getLargeur()<<m_listeDebits->at(i)->getLongueur();
        }

        return sortie;
}

void Calculs::trierDebits()
{
    QList<Debit *> *list=new QList<Debit *>;
    *list<<*m_listeDebits;


    Algorythm *alg=new Algorythm;
    ///creation d'une liste de _2values
    QList<_2values*> *tableau=new QList<_2values*>;

    ///envoie des valeurs largeur et longueur dans un _2values
    for(int i=0;i<list->count();i++)
    {
        _2values *val=new _2values(i);
        val->set1(list->at(i)->getLargeur());
        val->set2(list->at(i)->getLongueur());
        tableau->append(val);
    }
    ///envoie de la liste dans l'algorythme de tri
    alg->setValues(tableau);
    QList<int> indexs=alg->Trier();///recupération des index du tableau une fois trié
    m_listeDebits->clear();
    ///mise en ordre de la liste suivant les index de tableau fournit
    for(int i=0;i<indexs.count();i++){m_listeDebits->append(list->at(indexs.at(i)));}
}


void Calculs::trierChuttes()
{
     QList<Brut *> *list=new QList<Brut *>;
     *list<<*m_listeChuttes;

     Algorythm *alg=new Algorythm;
     ///creation d'une liste de _2values
     QList<_2values*> *tableau=new QList<_2values*>;


     ///envoie des valeurs largeur et longueur dans un _2values
     for(int i=0;i<list->count();i++)
     {
         _2values *val=new _2values(i);
         val->set1(list->at(i)->getLargeur());
         val->set2(list->at(i)->getLongueur());
         tableau->append(val);
     }
     ///envoie de la liste dans l'algorythme de tri
     alg->setValues(tableau);
     QList<int> indexs=alg->Trier(false);///recupération des index du tableau une fois trié

     m_listeChuttes->clear();
     ///mise en ordre de la liste suivant les index de tableau fournit
     for(int i=0;i<indexs.count();i++){m_listeChuttes->append(list->at(indexs.at(i)));}


     ///suppression des plaque avec longueur 0
     if(m_listeChuttes->at(0)->getLongueur()<=0.0){m_listeChuttes->removeFirst();}
}



int Calculs::getNbreBruts() {return m_nbreBruts;}
void Calculs::setNbreBruts(int nbreBruts){m_nbreBruts = nbreBruts;}

int Calculs::rechercher(int dim_x, int dim_y)
{
    ///recherche d'un débit qui passe dans les dimensions données
    int num=-1;
    for(int i=0;i<m_listeDebits->count();i++)
    {
        ///on cherche le premier panneau qui passe dans les cotes données
        if((m_listeDebits->at(i)->getLargeur()<=dim_x) && (m_listeDebits->at(i)->getLongueur()<=dim_y))
        {
           /// on vérifie qu'il ne soit pas optimisé
            if(!m_listeDebits->at(i)->getOptimise())
            {
                num=i;
                return num;
            }
        }
    }
    /// on essai en inversant largeur longueur des débits
    if(num==-1)
    {
        for(int i=0;i<m_listeDebits->count();i++)
        {
            ///on cherche le premier panneau qui passe dans les cotes données
            if((m_listeDebits->at(i)->getLargeur()<=dim_y) && (m_listeDebits->at(i)->getLongueur()<=dim_x))
            {
                /// on vérifie qu'il ne soit pas optimisé
                if(!m_listeDebits->at(i)->getOptimise())
                {
                    ///on retourne le panneau
                    num=i;m_listeDebits->at(i)->setRotation(true);
                    double b,h;
                    b=m_listeDebits->at(i)->getLargeur();
                    h=m_listeDebits->at(i)->getLongueur();
                    m_listeDebits->at(i)->setLargeur(h);
                    m_listeDebits->at(i)->setLongueur(b);
                }
            }
        }
    }

    ///le cas échéant la fonction retourne -1
    return num;

}

QList<Debit *> *Calculs::getListeDebits() const{return m_listeDebits;}

void Calculs::setFormatDefaut(Brut *value){
    formatDefaut = value;
    m_largFormat= formatDefaut->getLargeur();
    m_longFormat=formatDefaut->getLongueur();
}

double Calculs::getFormatDefautLargeur()
{
    return m_largFormat;
}

double Calculs::getFormatDefautLongueur()
{
    return m_longFormat;

}

void Calculs::setEp_scie(double ep_scie){m_ep_scie = ep_scie;}
