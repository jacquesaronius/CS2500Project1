import QtQuick 2.7

Page1Form {
    Canvas{
        id: myCanvas
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: 252
        height: 252
        onPaint: {
            console.log("Onpaint got called!")
            var ctx = getContext("2d")
            ctx.lineWidth = 1
            ctx.strokeStyle = "black"
            ctx.rect(0,0,252,252)
            ctx.stroke();
        }

    }

    Component.onCompleted: {
        console.log("Completed")
        myCanvas.requestPaint()
    }

    signal create(int n);

    Connections {
        target: controller
        onUpdate: {
            myCanvas.requestPaint()
        }
    }


}
