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

#include "algorythm.h"

_2values::_2values(int index)
{
    ind=index;
}

double _2values::get1(){return valeur1;}
double _2values::get2(){return valeur2;}

int _2values::getIndex()
{
    return ind;
}
void _2values::set1(double value){valeur1=value;}
void _2values::set2(double value){valeur2=value;}


Algorythm::Algorythm()
{
    tab=new QList<_2values *>;

}

void Algorythm::setValues(QList<_2values *> *tableau)
{
    *tab=*tableau;
}

QList<int> Algorythm::Trier(bool decroissant)
{
    ///fonction de trie suivant deux valeurs données
    /// retourne un tableau d'index correspondant à
    /// la liste triée
    /// priorité de tri suivant le tableau de valeur val1




    int largtest=0;
    int val1_high=0;///largeur la plus grande dans le tableau
    int val1_low=0;///largeur la plus petite dans le tableau
    int ind_larg_mil=0;/// index du milieu du tableau



    /// permet d'effectuer plusieurs passes dans le tableau pour le tri
    int precision_tri=tab->count()/2;


    QList<_2values*> *list=new QList<_2values*>;///list va servir à effectuer plusieurs passes de tri

    *list=*tab;


    for(int j=0;j<=precision_tri;j++)/// on va faire x passes pour remettre la liste dans le bon ordre
    {

        QList<_2values*> *remplissage=new QList<_2values*>;///remplissage va servir de tableau de sortie en fin de passe



        for(int i=0;i<list->count();i++)
        {
            //si le tableau n'est pas vide
            if(!remplissage->isEmpty())
            {
                val1_high=remplissage->at(0)->get1();
                val1_low=remplissage->last()->get1();
                ind_larg_mil=remplissage->count()/2;
            }
            else
            {
                val1_low=0;val1_high=0;
            }

            largtest=list->at(i)->get1();

         //qDebug()<<"i="<<i<<" | largtest"<<largtest<<" | max"<<val1_high<<" | min"<<val1_low;
        // qDebug()<<"panneau "<<list->at(i)->getNom();


         ///on test si la valeur1 est plus grande que celle en tête de tableau,
         ///alors on insere l'objet en tête de liste
         if(largtest>val1_high)
         {
             if(!remplissage->isEmpty())

             {
                 remplissage->insert(i-1,list->at(i));

             }
             else
             {
                 remplissage->append(list->at(i));
             }
         }

         ///sinon on teste avec les valeur1 existantes
         else
         {

              ///deuxième phase : on teste les valeur1 identiques
                if(largtest==val1_high)
                {
                    if(!remplissage->isEmpty())
                    {
                        ///TEST des valeur2

                        ///si la valeur2 est aussi plus grande ou égale alors on le place en tête
                        if(list->at(i)->get2() >= remplissage->at(0)->get2())

                        {
                            remplissage->insert(i-1,list->at(i));
                        }
                        ///sinon
                        else
                        {
                            /// va tester la valeur1 en milieu de tableau
                            /// cela va permettre de remonter les objets à grandes valeur en fin de liste pour les retrier ensuite en deuxième passe
                            if(largtest>=remplissage->at(ind_larg_mil)->get1() && largtest>val1_low)
                            {
                                ///on teste aussi la valeur2 en milieu de tableau
                                if(list->at(i)->get2() >= remplissage->at(ind_larg_mil)->get2())

                                {
                                    remplissage->insert(ind_larg_mil,list->at(i));

                                }
                                else
                                {
                                    remplissage->insert(ind_larg_mil+1,list->at(i));

                                }
                            }

                            else
                            {
                                /// on teste si en fin de liste on a aussi la même valeur1
                                /// et si valeur2 est plus grande que celle ci
                                if(val1_high==val1_high && list->at(i)->get2() > remplissage->last()->get2())

                                {
                                    remplissage->insert(i-1,list->at(i));
                                }
                                else
                                {
                                    remplissage->insert(i,list->at(i));
                                }
                            }
                        }
                    }
                    ///si la liste est pour l'instant vide
                    else
                    {
                        remplissage->append(list->at(i));
                    }
                }


             ///si valeur1 est inférieur à la tête de liste
                else
                {
                    ///alors test de la valeur la plus petite
                    if(largtest<=val1_low)
                    {

                        ///si les valeur1 faibles sont identique
                        if(largtest==val1_low)
                        {
                            ///si valeur2 est plus grande que celle en fin de liste
                            if(list->at(i)->get2()>remplissage->last()->get2())
                            {
                                remplissage->insert(remplissage->count()-2,list->at(i));
                            }
                            ///sinon insertion en fin de tableau
                            else
                            {
                                remplissage->append(list->at(i));
                            }
                        }
                        else
                        {
                            remplissage->append(list->at(i));
                        }

                    }
                    else
                    {
                        remplissage->insert(remplissage->count()-2,list->at(i));
                    }
                }


         }// fin des tests


        }// fin de la boucle


        list->clear();
        for(int i=0;i<remplissage->count();i++)
        {
            list->append(remplissage->at(i));
        }

    }
    ///SORTIE DES INDEX de list///
    QList<int> sortie;
    for(int i=0;i<list->count();i++)
    {
        if(decroissant){sortie.append(list->at(i)->getIndex());}
        else{sortie.append(list->at(list->count()-i-1)->getIndex());}
    }

    return sortie;

}

