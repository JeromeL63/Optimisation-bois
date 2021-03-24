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
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as Separate

Window {
    id:main_window
    visible: true
    width: 800
    height: 600
    title: qsTr("Optimisation")

    RowLayout{
        anchors.fill: parent
        ColumnLayout{
            Separate.TableView{
                Layout.preferredWidth: main_window.width/2
                Separate.TableViewColumn{
                    title:"N° prod"
                    width:75
                }
                Separate.TableViewColumn{
                    title:"largeur"
                    width:75
                }
                Separate.TableViewColumn{
                    title:"longueur"
                    width:75
                }
                Separate.TableViewColumn{
                    title:"Optimisé"
                    width:75
                }
                Separate.TableViewColumn{
                    title:"N° brute"
                    width:75
                }
            }
            Button{
                text:"Ajouter un débit"
            }
            Button{
                text:"Importer une liste de Débits"
            }
            Button{
                text:"Optimiser"
            }


        }
        Item {
            id: name
        }
    }
}
