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



import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.13
import QtQuick.Controls 2.13
import QtQuick.Controls 1.4 as Separate
import QtQuick.Dialogs 1.2


Window {
    id:main_window
    visible: true
    width: 800
    height: 600
    title: qsTr("Optimisation")

    Loader{
        id:importer
        active:false
        sourceComponent: FileDialog{
            id:f_importer

            title: "Choix du fichier .csv"
            nameFilters: {"*.csv"}

            onAccepted: {
                outil_importer.import(f_importer.fileUrl)
                importer.active=false
            }
            onRejected:{
                importer.active=false
            }

            Component.onCompleted: visible =true
        }
    }

    Loader{
        id:formats
        active: false
        sourceComponent: Format_Brut{
            id:f_formats
            visible: true
            onAccepted: {
                ///récupération du format brut
                defaut_brut.longueur=f_formats.longueur
                defaut_brut.largeur=f_formats.largeur
                /// remplissage de la partie calculs
                calculs.setFormatDefaut(defaut_brut);
                calculs.setEp_scie(10.0);


                formats.active=false
            }
            onRejected: formats.acitve=false
        }
    }

    RowLayout{
        anchors.fill: parent
        anchors.margins:5
        ColumnLayout{
            Separate.TableView{
                Layout.preferredWidth: main_window.width/2
                Layout.fillHeight: true
                model: listeDebits
                Separate.TableViewColumn{
                    title:"N° prod"
                    role:"nom"
                    width:75
                }
                Separate.TableViewColumn{
                    title:"largeur"
                    role:"largeur"
                    width:75
                }
                Separate.TableViewColumn{
                    title:"longueur"
                    role:"longueur"
                    width:75
                }
              /*  Separate.TableViewColumn{
                    title:"Optimisé"
                    role:
                    width:75
                }*/
                Separate.TableViewColumn{
                    title:"N° pièce brute"
                    role:"num_brut"
                    width:75
                }
            }
            Button{
                text:"Importer une liste de Débits"
                onClicked: importer.active=true
            }
            Button{
                text:"Ajouter un débit"
            }
            Button{
                text:"format de pièce brute"
                onClicked: formats.active=true

            }

            Button{
                text:"Optimiser"
                onClicked: {
                    var isOptimised=calculs.optimiser(listeDebits)
                    console.log(isOptimised)
                    if(isOptimised == 2){console.log(calculs.getFormatDefautLargeur(),calculs.getFormatDefautLongueur())}
                }
            }

        }
        Item {
            id: name
        }
    }
}
