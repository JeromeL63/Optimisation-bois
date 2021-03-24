#include "libpasserelle.h"

#include "QDebug"

Passerelle::Passerelle()
{
    tab=new QTableWidget;

}

QList<QTableWidgetItem *> Passerelle::addLine(Panneau *panneau)
{
    QList<QTableWidgetItem *> list;
    list.clear();
    QString opt;

    QTableWidgetItem *n=new QTableWidgetItem();
    n->setData(Qt::DisplayRole,panneau->getNom());


    QTableWidgetItem *larg=new QTableWidgetItem(QString().setNum(panneau->getLarg()));

    larg->setData(Qt::DisplayRole,panneau->getLarg());

    QTableWidgetItem *lg=new QTableWidgetItem(QString().setNum(panneau->getLong()));


    if(panneau->isOptimise())
    {
        opt.append("oui");
    }
    else{opt.append("non");}
    QTableWidgetItem *opti=new QTableWidgetItem(opt);
    if(panneau->isOptimise()){opti->setBackgroundColor(QColor(Qt::green));}


    QTableWidgetItem *noplaque=new QTableWidgetItem(QString().setNum(panneau->getNumPlaque()));


    if(panneau->isError())
    {
        n->setBackgroundColor(QColor(Qt::red));
        larg->setBackgroundColor(QColor(Qt::red));
        lg->setBackgroundColor(QColor(Qt::red));
    }

    list.append(n);
    list.append(larg);
    list.append(lg);
    list.append(opti);
    list.append(noplaque);

    return list;
}

QList<Panneau *> Passerelle::import(QString file)
{
    ///ouverture et ecriture des lignes du fichier dans une string list
    /// le fichier doit ce présenter comme ça :
    ///  numéro LC ; nbre panneaux ; largeur ; longueur
    QFile fichier(file);
    QStringList tampon;tampon.clear();
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&fichier);
    do{
        tampon<<in.readLine();

    }while(!in.atEnd());

    QList<Panneau *> list;
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
             Panneau *p=new Panneau(t.at(0),QString(t.at(2)).toDouble(),QString(t.at(3)).toDouble());
                     list.append(p);
             }
         }
     }
     return list;

}



