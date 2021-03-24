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

import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Dialog {
    title:"Format des pièces brutes"
    id:brut_dialog
    modal:true
    height: 250
    property double largeur
    property double longueur


    onAccepted: {
        largeur=txt_largeur.text;
        longueur=txt_longueur.text;
    }
    onRejected: {

    }

    ColumnLayout{
        anchors.fill: parent
        anchors.margins:5
        RowLayout{
            Layout.fillWidth: true
            ColumnLayout{
                Text {
                    text:"Largeur"
                }
                TextField{
                    ///TODO regexp seulement accepter un double
                    id:txt_largeur
                }
            }
            ColumnLayout{
                Text{
                    text: "Longueur"
                }
                TextField{
                    id:txt_longueur
                }
            }
        }

    }
    footer: ColumnLayout{
        RowLayout{
            Layout.fillWidth:true
            Layout.preferredHeight: 40
            Layout.margins: 5

            Item {Layout.fillWidth: true}

            Button{
                text: "OK"
                icon.name: "dialog-ok"
                onClicked:accept()

            }
            Button{
                text: "Annuler"
                icon.name: "dialog-cancel"
                onClicked: reject()
            }
        }
    }

}
