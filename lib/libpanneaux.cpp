#include "libpanneaux.h"
#include "QDebug"
//#define precision_tri 50 //nombre de passes pour trier les listes


Calculs::Calculs(QList<Panneau *> *listePanneaux, Plaque *formats, double ep_trait_de_scie, QWidget *parent)
{
    listpanneaux=new QList<Panneau*>;
   listplaques=new QList<Plaque*>;
   listchuttes=new QList<Plaque*>;
   formatdefaut=new Plaque;
   *formatdefaut=*formats;
    ep_scie=ep_trait_de_scie;
    wg= new QWidget(parent);
}

void Calculs::createPlaque(int numplaque)
{
    Plaque *pl=new Plaque;
    *pl=*formatdefaut;
    pl->setCoord(0,0);
    listchuttes->append(pl);
    listchuttes->at(listchuttes->count()-1)->setNumPlaque(numplaque);
    listchuttes->at(listchuttes->count()-1)->setLong(formatdefaut->getLong());
    ///ajout à la liste de plaque
    listplaques->append(pl);
}

bool Calculs::optimiser_2()
{

}

bool Calculs::optimiser(QList<Panneau *> *listePanneaux)
{
    //qDebug()<<"DEBUT Optimiser";
    ///RAZ des optimisations
    *listpanneaux=*listePanneaux;
    for(int i=0;i<listpanneaux->count();i++){listpanneaux->at(i)->setOptimise(false);}
    listplaques->clear();

    ///TEST des panneaux exédant le format de base

    if(testFormats()){return false;}


   // qDebug()<<"Fin des RAZ et des tests";

    nbreplaques=1;  
    int x=0;
    int y=0;

    ///vidage de la liste de chuttes de plaques
    listchuttes->clear();

    if(!listpanneaux->isEmpty())///on vérifie que la liste de panneaux est remplie
    {
        ///création de la première plaque
        createPlaque(nbreplaques);

        ///les panneaux sont triés par et longueurs décroissantes
        TrierPanneaux(listpanneaux);

        bool all_optimise=false;
        bool deuxieme_part=false;
        bool match_plaque=false;


       do///tant que tous les panneaux ne sont pas optimisés
       {
            int no_pan=-1;
           // qDebug()<<"Plaque "<<nbreplaques<<" reste :"<<listchuttes->at(0)->getLong()<<"mm";


 ///triage des bout de plaques restant par ordre croissant
    TrierPlaques(listchuttes);

            do///tant que le panneau ne rentre pas dans une chutte de plaque
            {                 

                 match_plaque=false;


                ///si le test dépasse le nombre de chutes de plaques, création d'une nouvelle plaque
                if(listchuttes->isEmpty()){nbreplaques++;createPlaque(nbreplaques);deuxieme_part=false;}

                ///on teste s'il reste de la matière
                if(listchuttes->at(0)->getLong()>0)
                {
                ///Recherche d'un panneau qui peut rentrer dans la chutte
                no_pan=search(listchuttes->at(0)->getLarg(),listchuttes->at(0)->getLong());
                }

                if(no_pan != -1)/// si un panneau peut passer
                {
                    match_plaque=true;
                }
                ///sinon on supprime la chutte de la liste
                else
                {
                    //qDebug()<<"chutte "<<listchuttes->at(0)->getLarg()<<" x "<<listchuttes->at(0)->getLong()<<" plaque"<<listchuttes->at(0)->getNumPlaque()<<" supprimé";
                    listchuttes->removeFirst();
                }


            }while(!match_plaque);



           if(match_plaque)/// s'il y a une plaque qui passe dans l'un des deux cas
           {

               ///phase de positionnement(nécessaire au dessin panneau/plaques)

               ///création des coordonnées du panneau dans la plaque

                listpanneaux->at(no_pan)->setPos(listchuttes->at(0)->get_X(),listchuttes->at(0)->get_Y());
                //qDebug()<<"Panneau "<<listpanneaux->at(no_pan)->getNom()<<" X:"<<listpanneaux->at(no_pan)->getPosX()<<"|Y:"<<listpanneaux->at(no_pan)->getPosY();
                //qDebug()<<listpanneaux->at(no_pan)->getLarg()<<" x "<<listpanneaux->at(no_pan)->getLong();



                ///phase de découpe/////////////

                ///si la largeur du panneau est inf à la plaque
                ///découpe en deux partie
                if(listpanneaux->at(no_pan)->getLarg()<listchuttes->at(0)->getLarg())
                {


                    ///on crée les coordonnées de la plaque de droite
                    x=listchuttes->at(0)->get_X()+listpanneaux->at(no_pan)->getLarg()+ep_scie;
                    y=listpanneaux->at(no_pan)->getPosY();



                    ///on crée une plaque à droite
                    double largPlaque=listchuttes->at(0)->getLarg()-listpanneaux->at(no_pan)->getLarg()-ep_scie;

                    double longPlaque=listpanneaux->at(no_pan)->getLong();
                    int no_plaque=listchuttes->at(0)->getNumPlaque();

                    Plaque *pl=new Plaque(largPlaque,longPlaque,0,no_plaque);
                    pl->setCoord(x,y);


                    ///on modifie la longueur de la plaque du bas
                    y=listchuttes->at(0)->get_Y()+listpanneaux->at(no_pan)->getLong()+ep_scie;
                    listchuttes->at(0)->setCoord(listchuttes->at(0)->get_X(),y);
                    listchuttes->at(0)->setLong(listchuttes->at(0)->getLong()-longPlaque-ep_scie);
                    //qDebug()<<"longueur restante "<<listchuttes->at(0)->getLong();

                    ///ajout de la plaque de droite dans la liste de chuttes
                    listchuttes->append(pl);
                    deuxieme_part=true;
                }



                if(!deuxieme_part)///si on est en pleine plaque
                {
                    ///on soustrait la longueur du panneau à la plaque + épaisseur du trait de scie

                    y=listchuttes->at(0)->get_Y()+listpanneaux->at(no_pan)->getLong()+ep_scie;
                    listchuttes->at(0)->setCoord(listchuttes->at(0)->get_X(),y);
                    double nouvelleLong=0.0;
                    nouvelleLong=listchuttes->at(0)->getLong()-listpanneaux->at(no_pan)->getLong()-ep_scie;
                    listchuttes->at(0)->setLong(nouvelleLong);
                    //qDebug()<<"Plaque après découpe:"<<listchuttes->at(0)->getNumPlaque()<<"Lg :"<<listchuttes->at(0)->getLong();
                }                



                ///atribution n° plaque au panneau
                listpanneaux->at(no_pan)->setNumPlaque(listchuttes->at(0)->getNumPlaque());
                listpanneaux->at(no_pan)->setOptimise(true);

                ///si l'épaisseur du trait de scie donne une valeur négative, on ramène la valeur à 0
                if(listchuttes->at(0)->getLong()<=0)
                {
                    listchuttes->at(0)->setLong(0);}

           }          


           for(int i=0;i<listpanneaux->count();i++)
           {          
               if(!listpanneaux->at(i)->isOptimise())
               {
                    all_optimise=false;
                   break;
               }
               else{all_optimise=true;}
           }


        }while(!all_optimise);

    }
    return true;

}

bool Calculs::testFormats()
{///recherche des formats excédant le format de plaque par défaut, et pointage de ceux ci
    double laform,lgform;
    laform=formatdefaut->getLarg();
    lgform=formatdefaut->getLong();
    bool sortie= false;

    //qDebug()<<"TEST des formats :"<<laform<<"x"<<lgform;
    for(int i=0;i<listpanneaux->count();i++)
    {
        double lapan,lgpan;
        lapan=listpanneaux->at(i)->getLarg();
        lgpan=listpanneaux->at(i)->getLong();

        if(lapan>laform || lgpan>lgform)
        {
            QString t;
            if(lapan>laform){t.append("La largeur du panneau ");}
            else{t.append("La longueur du panneau ");}
            t.append(listpanneaux->at(i)->getNom()+" ("+QString().setNum(lapan)+"x"+QString().setNum(lgpan)+"mm)");
            t.append(" dépasse le format de la plaque \n Faut-il le retourner ?");
            int decision=QMessageBox::warning(wg,"Erreur",t,QMessageBox::Yes,QMessageBox::No);
            switch (decision) {
            case QMessageBox::Yes:
                listpanneaux->at(i)->setLarg(lgpan);
                listpanneaux->at(i)->setLong(lapan);
                testFormats();
                break;

            case QMessageBox::No:
                listpanneaux->at(i)->setError(true);
                break;

            default:
                listpanneaux->at(i)->setError(true);
                break;
            }
        }

    }

    for(int i=0;i<listpanneaux->count();i++){if(listpanneaux->at(i)->isError()){sortie=true;}}

    return sortie;
}

void Calculs::TrierPanneaux(QList<Panneau *> *listePanneaux)
{
    QList<Panneau *> *list=new QList<Panneau *>;
    *list<<*listePanneaux;


    Algorythm *alg=new Algorythm;
    ///creation d'une liste de _2values
    QList<_2values*> *tableau=new QList<_2values*>;

    ///envoie des valeurs largeur et longueur dans un _2values
    for(int i=0;i<list->count();i++)
    {
        _2values *val=new _2values(i);
        val->set1(list->at(i)->getLarg());
        val->set2(list->at(i)->getLong());
        tableau->append(val);
    }
    ///envoie de la liste dans l'algorythme de tri
    alg->setValues(tableau);
    QList<int> indexs=alg->Trier();///recupération des index du tableau une fois trié
    listpanneaux->clear();
    ///mise en ordre de la liste suivant les index de tableau fournit
    for(int i=0;i<indexs.count();i++){listpanneaux->append(list->at(indexs.at(i)));}
}

void Calculs::TrierPlaques(QList<Plaque *> *listePlaques)
{    
     QList<Plaque *> *list=new QList<Plaque *>;
     *list<<*listePlaques;

     Algorythm *alg=new Algorythm;
     ///creation d'une liste de _2values
     QList<_2values*> *tableau=new QList<_2values*>;

     ///envoie des valeurs largeur et longueur dans un _2values
     for(int i=0;i<list->count();i++)
     {
         _2values *val=new _2values(i);
         val->set1(list->at(i)->getLarg());
         val->set2(list->at(i)->getLong());
         tableau->append(val);
     }
     ///envoie de la liste dans l'algorythme de tri
     alg->setValues(tableau);
     QList<int> indexs=alg->Trier(false);///recupération des index du tableau une fois trié

     listplaques->clear();
     ///mise en ordre de la liste suivant les index de tableau fournit
     for(int i=0;i<indexs.count();i++){listplaques->append(list->at(indexs.at(i)));}

     ///suppression des plaque avec longueur 0
     if(listplaques->at(0)->getLong()<=0.0){listplaques->removeFirst();}
}


int Calculs::getNombrePlaques()
{
    return nbreplaques;
}

int Calculs::search(int largeur, int longueur)
{
  //  qDebug()<<"FONCTION SEARCH";
    int num=-1;
    for(int i=0;i<listpanneaux->count();i++)
    {
        ///on cherche le premier panneau qui passe dans les cotes données       
        if((listpanneaux->at(i)->getLarg()<=largeur) && (listpanneaux->at(i)->getLong()<=longueur))
        {
           /// on vérifie qu'il ne soit pas optimisé
            if(!listpanneaux->at(i)->isOptimise())
            {
                num=i;              
                return num;
            }
        }
    }
    /// on essai en retournant les panneaux
    if(num==-1)
    {
        for(int i=0;i<listpanneaux->count();i++)
        {
            ///on cherche le premier panneau qui passe dans les cotes données
            if((listpanneaux->at(i)->getLarg()<=longueur) && (listpanneaux->at(i)->getLong()<=largeur))
            {
                /// on vérifie qu'il ne soit pas optimisé
                if(!listpanneaux->at(i)->isOptimise())
                {
                    ///on retourne le panneau
                    num=i;listpanneaux->at(i)->setRot(true);
                    double b,h;
                    b=listpanneaux->at(i)->getLarg();
                    h=listpanneaux->at(i)->getLong();
                    listpanneaux->at(i)->setLarg(h);
                    listpanneaux->at(i)->setLong(b);
                   // qDebug()<<"le panneau "<<listpanneaux->at(i)->getNom()<<" a été retourné";
                   // qDebug()<<"format demandé"<<largeur<<" x "<<longueur;
                }
            }
        }
    }

    ///le cas échéant la fonction retourne -1
    return num;
}

QList<Panneau *> *Calculs::getListePanneaux(){return listpanneaux;}

Calculs::~Calculs()
{
    delete listpanneaux;
    delete listplaques;
}


