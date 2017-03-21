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
        x: 0
        width: 100
        text: qsTr("Create sensor net")
        anchors.top: parent.top
        anchors.topMargin: 20
        opacity: 0.9
        anchors.right: parent.right
        anchors.rightMargin: 20
    }

    SpinBox {
        id: spinBox
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: parent.top
        anchors.topMargin: 20
    }
}
