import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import RadialBar 1.0
import QtGraphicalEffects 1.0

RowLayout {
    LinearGradient {
        anchors.fill: parent
        start: Qt.point(0, 0)
        end: Qt.point(800, 0)
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#040a1b" }
            GradientStop { position: 1.0; color: "#09184b" }
        }
    }

    RadialBar {
        objectName: "radial_cpu"
        penStyle: Qt.FlatCap
        dialType: RadialBar.FullDial
        progressColor: "#e2801d"
        backgroundColor: "#000040"
        foregroundColor: "#a9a9a9"
        dialWidth: 10
        startAngle: 0
        spanAngle: 360
        minValue: 0
        maxValue: 100
        value: 56
        textFont {
            family: "Consolas"
            italic: false
            pointSize: 32
        }
        suffixText: "%\nCPU"
        textColor: "#ffffff"
    }


    RadialBar {
        objectName: "radial_ram"
        penStyle: Qt.FlatCap
        dialType: RadialBar.FullDial
        progressColor: "#e2801d"
        backgroundColor: "#000040"
        foregroundColor: "#a9a9a9"
        dialWidth: 10
        startAngle: 0
        spanAngle: 360
        minValue: 0
        maxValue: 100
        value: 30
        textFont {
            family: "Consolas"
            italic: false
            pointSize: 32
        }
        suffixText: "%\nRAM"
        textColor: "#ffffff"
    }

    RadialBar {
        objectName: "radial_disk"
        penStyle: Qt.FlatCap
        dialType: RadialBar.FullDial
        progressColor: "#008000"
        backgroundColor: "#000040"
        foregroundColor: "#a9a9a9"
        dialWidth: 10
        startAngle: 0
        spanAngle: 360
        minValue: 0
        maxValue: 100
        value: 10
        textFont {
            family: "Consolas"
            italic: false
            pointSize: 32
        }
        suffixText: "%\nDisk"
        textColor: "#ffffff"
    }
}

//RadialBar{
//    objectName: "radial_bar"
//    penStyle: Qt.FlatCap
//    dialType: RadialBar.NoDial
//    progressColor: "#e2801d"
//    backgroundColor: "#000040"
//    dialWidth: 10
//    startAngle: 30
//    spanAngle: 300
//    minValue: 0
//    maxValue: 100
//    value: 100
//    textFont {
//        family: "Consolas"
//        italic: false
//        pointSize: 32
//    }
//    suffixText: "% \nCPU"
//    textColor: "#FFFFFF"
//}
