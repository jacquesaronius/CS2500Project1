import QtQuick 2.7
import QtQuick.Controls 2.0
Page1Form {
    Canvas{
        id: myCanvas
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: 252
        height: 252
        onPaint: {


            const DILATION = 5;
            console.log("Onpaint got called!")
            var ctx = getContext("2d")
            var count = controller.count;
            ctx.reset();
            ctx.lineWidth = 1
            ctx.strokeStyle = "black"
            ctx.rect(0,0,252,252)
            ctx.stroke();
            ctx.save();

            for(var i = 0; i < count; i++) {
                var sensor = controller.get_sensor(i)
                var x = sensor.x * DILATION;
                var y = sensor.y * DILATION;
                ctx.restore();
                ctx.beginPath();
                ctx.strokeStyle = "red";
                ctx.moveTo(x - 4, y);
                ctx.lineTo(x + 4, y);

                ctx.moveTo(x, y - 4);
                ctx.lineTo(x, y + 4);
                ctx.stroke();
                if (sensor.active)
                {

                    ctx.beginPath();
                    ctx.strokeStyle = "green";
                    ctx.arc(x, y, RADIUS * DILATION, 0, 360, false);
                    ctx.stroke();

                }
            }

        }
    }
    objectName: "page1"

    Component.onCompleted: {
        console.log("Completed")
        myCanvas.requestPaint()
    }

    signal create(int n);

    Connections {
        target: controller
        onUpdate: {
            myCanvas.requestPaint();
            txtRounds.text = controller.rounds;
            txtStatus.text = controller.status;

        }

    }


}
