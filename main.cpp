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


#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>

#include "debit.h"
#include "brut.h"
#include "lib/passerelle.h"
#include "lib/calculs.h"

int main(int argc, char ** argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    app.setOrganizationName("Optimisation-Bois");
    app.setOrganizationDomain("Wood&Co");

    QQmlApplicationEngine engine;


    ///insertion des listes dans la partie QML
    ListeDebits *lstdbt=new ListeDebits;
    engine.rootContext()->setContextProperty("listeDebits",QVariant::fromValue(lstdbt));

    ///création de l'objet import
    Passerelle *p=new Passerelle(lstdbt);
    engine.rootContext()->setContextProperty("outil_importer",p);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
