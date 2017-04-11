import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: item1
    x: 0
    width: 640
    height: 480
    property alias btnTopDown: btnTopDown
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

    ToolBar {
        id: toolBar
        y: 71
        leftPadding: -2
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8

        ToolButton {
            id: btnAllActive
            x: 0
            y: 0
            width: 158
            text: qsTr("All Active")
            spacing: 1
            autoExclusive: true
            checked: true
            opacity: 0.9
            checkable: true
        }

        ToolButton {
            id: btnTopDown
            x: 156
            y: 0
            width: 156
            text: qsTr("Top Down")
            autoExclusive: true
            checked: false
            checkable: true
        }

        ToolButton {
            id: btnBottomUp
            x: 312
            y: 0
            width: 156
            text: qsTr("Bottom Up")
            autoExclusive: true
            checked: false
            checkable: true
        }

        ToolButton {
            id: btnGreedy
            x: 468
            y: 0
            width: 156
            text: qsTr("Greedy Algorithm")
            autoExclusive: true
            checked: false
            checkable: true
        }
    }

    Text {
        id: text2
        x: 22
        y: 457
        text: qsTr("Rounds:")
        font.pixelSize: 12
    }

    Text {
        id: txtRounds
        x: 72
        y: 457
        width: 50
        text: qsTr("")
        font.pixelSize: 12
    }

    Text {
        id: text3
        x: 128
        y: 457
        text: qsTr("Status:")
        font.pixelSize: 12
    }

    Text {
        id: txtStatus
        x: 171
        y: 457
        width: 300
        text: qsTr("Not Started")
        font.pixelSize: 12
    }

    Text {
        id: text4
        x: 186
        y: 20
        text: qsTr("Delay:")
        font.pixelSize: 12
    }

    SpinBox {
        id: spinDelay
        x: 232
        y: 20
        stepSize: 100
        to: 2000
    }

    Connections {
        target: btnCreate
        onClicked: txtStatus.text = "Sensor network created."
    }

    Connections {
        target: spinDelay
        onValueChanged: controller.delay = spinDelay.value
    }

    Connections {
        target: btnAllActive
        onClicked: controller.mode = ALL_ACTIVE
    }

    Connections {
        target: btnBottomUp
        onClicked: controller.mode = BOTTOM_UP_RANDOM
    }

    Connections {
        target: btnTopDown
        onClicked: controller.mode = TOP_DOWN_RANDOM
    }

    Connections {
        target: btnGreedy
        onClicked: controller.mode = GREEDY
    }

    Connections {
        target: btnRun
        onClicked: controller.run()
    }
}
