#include "opti_panneau.h"
#include "ui_opti_panneau.h"

#define larg_col_nom 40
#define larg_col_larg 70
#define larg_col_long 70
#define larg_col_opti 80
#define larg_col_pla 80


opti_panneau::opti_panneau(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::opti_panneau)
{
///Init interface graphique
    ui->setupUi(this);
    listpanneaux=new QList<Panneau *>;
    listpanneaux->clear();
    ui->default_Larg->setValidator(new QDoubleValidator(0,4000,0,this));
    ui->default_Long->setValidator(new QDoubleValidator(0,4000,0,this));
    plaque_defaut=new Plaque(ui->default_Larg->text().toDouble(),ui->default_Long->text().toDouble());
    ui->tablePanneaux->setColumnWidth(0,larg_col_nom);
    ui->tablePanneaux->setColumnWidth(1,larg_col_larg);
    ui->tablePanneaux->setColumnWidth(2,larg_col_long);
    ui->tablePanneaux->setColumnWidth(3,larg_col_opti);
    ui->tablePanneaux->setColumnWidth(4,larg_col_pla);
    ui->tablePanneaux->verticalHeader()->setVisible(false);
    ui->total_plaques->setVisible(false);

    if (QApplication::arguments().size() > 1)
    {
        const QString FileName = QApplication::arguments().at(1);
        // FILENAME now contains path and name of the file to open.
        Passerelle p;
        *listpanneaux=p.import(FileName);
        remplirTableau();
        on_optimiser_clicked();

    }

}

opti_panneau::~opti_panneau(){delete ui;}

///Création du tableau contenant la liste des panneaux
void opti_panneau::remplirTableau()
{

    QStringList header;
    header<<"nom"<<"largeur"<<"Longueur"<<"optimisé"<<"N° de plaque";
    ui->total_plaques->setVisible(false);
    ui->tablePanneaux->clear();
    ui->tablePanneaux->setHorizontalHeaderLabels(header);
    for(int i=0;i<listpanneaux->count();i++)
    {

        if(i>ui->tablePanneaux->rowCount()-1){ui->tablePanneaux->insertRow(ui->tablePanneaux->rowCount());}
        Passerelle p;
        QList<QTableWidgetItem *> list(p.addLine(listpanneaux->at(i)));

        for(int j=0;j<=4;j++)
        {

            ui->tablePanneaux->setItem(i,j,list.at(j));
        }
    }
}

///Fonction d'ajout d'un panneau
void opti_panneau::on_ajouter_panneau_clicked()
{
    plaque_defaut->setLarg(ui->default_Larg->text().toDouble());
    plaque_defaut->setLong(ui->default_Long->text().toDouble());
    Panneau *p=new Panneau();

    bool ok=false;
    p->setNom(QInputDialog::getText(this,"Nom du panneau","Nom du panneau",QLineEdit::Normal,"",&ok));
    if(ok)
    {
        ok=false;
        p->setLarg( QInputDialog::getDouble(this,"largeur","largeur du panneau",0,0,plaque_defaut->getLarg(),0,&ok) );
        if(ok)
        {
            ok=false;
            p->setLong(QInputDialog::getDouble(this,"longueur","longueur du panneau",0,0,plaque_defaut->getLong(),0,&ok) );
            if(ok)
            {

               //remplissage de la liste des panneaux
               listpanneaux->append(p);
               remplirTableau();
            }
        }
    }
}

///Lance l'optimisation
void opti_panneau::on_optimiser_clicked()
{

                     ///récupération des données du tableau
    //Vidage de la liste
    listpanneaux->clear();


    for(int i=0;i<ui->tablePanneaux->rowCount();i++)
    {
        Panneau *p=new Panneau();
        p->setNom(ui->tablePanneaux->item(i,0)->text());
        p->setLarg(ui->tablePanneaux->item(i,1)->text().toDouble());
        p->setLong(ui->tablePanneaux->item(i,2)->text().toDouble());
        listpanneaux->append(p);

    }   
    plaque_defaut->setLarg(ui->default_Larg->text().toDouble());
    plaque_defaut->setLong(ui->default_Long->text().toDouble());

    Calculs *resultats=new Calculs(listpanneaux,plaque_defaut,ui->ep_scie->value(),this);
    bool test=resultats->optimiser(listpanneaux);

    //test: test si les panneaux ont des dimensions supérieurs au format de plaque donné
    if(test)
    {
    listpanneaux=resultats->getListePanneaux();

                                    ///partie dessin
    Dessin *rendu=new Dessin(resultats->getNombrePlaques(),plaque_defaut);
    rendu->drawPanneaux( listpanneaux );
    ui->dessin->setScene(rendu);
    remplirTableau();
    ui->total_plaques->setVisible(true);
    ui->total_plaques->setText("Nombre total de plaque : "+QString().setNum(resultats->getNombrePlaques()));

    }
    else
    {
        QMessageBox::warning(this,"Erreur","la liste n'a pas pu être optimisée, il y a des panneaux qui ne passent pas dans le format de plaque donnée");
        listpanneaux=resultats->getListePanneaux();
        remplirTableau();
    }



}




void opti_panneau::on_import_liste_clicked()
{
    ///import depuis liste cadwork, un fichier de réglage des colonnes dans cadwork a été réalisé pour exporter correctement
    QString emplacement(QFileDialog::getOpenFileName(this,"import de liste","D:/CloudStation/Programmation","*.csv *.lsp"));
    Passerelle p;
    *listpanneaux=p.import(emplacement);
    remplirTableau();
    qDebug()<<"done Import";
}
