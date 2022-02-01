import QtQuick 2.12

Canvas{
    id:rendu
    renderStrategy: Canvas.Cooperative
    renderTarget: Canvas.FramebufferObject
    onWidthChanged:{ markDirty();}
    onCanvasSizeChanged: markDirty()
    property variant ctx
    property variant ctx2
    property var coul_bruts: Qt.rgba(100/255,220/255,80/255,1)
    property var coul_debits: Qt.rgba(1.0,0,0,0.4)
    property int offset_value:100
    property int margins: 5
    property int h_text:12
    property double ech: 20


    onPainted: {}
    onPaint: {


        ctx= rendu.getContext("2d");
        ctx.reset();
        ctx.fillStyle = 'grey'
        ctx.fillRect(0, 0, width, height)
        var offset=0;



        ///dimension du brut
        var lx= calculs.getFormatDefautLargeur();
        var ly= calculs.getFormatDefautLongueur();

        ///réglage l'echelle du dessin

        if(lx<ly){
            ech = ly/(width - (margins *2))
        }
        else{
            ech = ly/(width - margins *2)
        }
        lx= lx/ ech;
        ly = ly /ech;

//traçage des axes X(rouge) Y(vert)
        ctx.beginPath()
        ctx.lineWidth = 3;
        ctx.moveTo(width/2,height/2)
        ctx.strokeStyle = "red"
        ctx.lineTo((width/2) +150,height/2)
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(width/2,height/2)
        ctx.strokeStyle = "green"
        ctx.lineTo(width/2,(height/2)+ 150)
        ctx.stroke();

        for(var i=0;i<calculs.getNbreBruts();i++)
        {
             //reglage offset
            offset=offset+(offset_value/ech)
            //reglage couleur
            ctx.beginPath();
            ctx.strokeStyle = "black"
            ctx.fillStyle = coul_bruts
            ctx.lineWidth = 1;
            //deplacement du point de départ
            if(lx<ly){
                //dessin pièce brute
                ctx.fillRect(margins,offset,ly,lx);
                ctx.stroke();
                //recherche de débit contennus dans le brut
                for(var j=0;j<listeDebits.rowCount();j++){
                    if(listeDebits.getNumBrut(j) === i+1){

                        var ldx=listeDebits.getLargeur(j)/ech;
                        var ldy=listeDebits.getLongueur(j)/ech;
                        var px=listeDebits.getPosX(j)/ech;
                        var py=listeDebits.getPosY(j)/ech;

                        //réduction du format pour passer dans le brut
                        py=py+margins/2
                        px=px+margins/2
                        ldx=ldx-margins
                        ldy=ldy-margins

                        ctx.beginPath();
                        ctx.fillStyle = coul_debits
                        ctx.fillRect(py+margins,px+offset,ldy,ldx)
                        ctx.stroke()

                        //numérotation et longueur du débit
                        ctx.beginPath();
                        var txtx=py+(ldy/2);
                        var txty=px+(ldx/2) + offset;
                        //ctx.text("N° "+listeDebits.getNom(j)+" débit: "+listeDebits.getLongueur(j),txtx,txty+margins)
                        ctx.text("N° "+listeDebits.getNom(j),txtx,txty+margins)
                        ctx.stroke();
                        ctx.beginPath();
                        ctx.text(" débit: "+listeDebits.getLongueur(j),txtx,txty+margins+h_text)
                        ctx.stroke();
                    }
                }
                //reglage du prochain offset
                offset=offset + lx + margins

            }
            else{
                ///TODO
                /// appliquer la methode de traçage précédente en inversant x et Y
                //reglage du prochain offset
                offset=offset + ly + margins
                ctx.fillRect(0,0,lx,ly);
            }
            //création de la pièce brute


        }
    }
}
