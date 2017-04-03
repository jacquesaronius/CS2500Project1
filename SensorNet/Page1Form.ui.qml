import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: item1
    x: 0
    width: 640
    height: 480
    z: 2
    rotation: 0
    opacity: 0.9

    Text {
        id: text1
        text: qsTr("N:")
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 22
        font.pixelSize: 12
    }

    Button {
        id: btnCreate
        x: 400
        width: 100
        text: qsTr("Create sensor net")
        spacing: -2
        anchors.top: parent.top
        anchors.topMargin: 20
        opacity: 0.9
        anchors.right: parent.right
        anchors.rightMargin: 140
    }

    SpinBox {
        id: spinBox
        stepSize: 50
        to: 500
        from: 50
        value: 50
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: parent.top
        anchors.topMargin: 20
    }

    Button {
        id: btnRun
        x: 532
        y: 20
        text: qsTr("Run Simulation")
        spacing: -3
    }

    Connections {
        target: btnCreate
        onClicked: controller.create(spinBox.value)
    }
 }
