#ifndef OPTI_PANNEAU_H
#define OPTI_PANNEAU_H

#include "panneau.h"
#include "plaque.h"
#include "lib/libpanneaux.h"
#include "dessin.h"
#include "lib/libpasserelle.h"

#include <QMainWindow>
#include <QInputDialog>
#include <QDebug>
#include <QTableWidgetItem>
#include <QPainter>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>


namespace Ui {
class opti_panneau;
}

class opti_panneau : public QMainWindow
{
    Q_OBJECT

public:
    explicit opti_panneau(QWidget *parent = 0);
    ~opti_panneau();
    void remplirTableau();


private slots:
    void on_ajouter_panneau_clicked();

    void on_optimiser_clicked();



    void on_import_liste_clicked();

private:
    Ui::opti_panneau *ui;
    QList<Panneau *> *listpanneaux;
    Plaque *plaque_defaut;


};

#endif // OPTI_PANNEAU_H
