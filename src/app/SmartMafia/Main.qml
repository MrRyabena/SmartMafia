import QtQuick
import QtQuick.Controls.Material
import QtQuick.Window
import QtQuick.Layouts

ApplicationWindow {
    width: 1080
    height: 720
    visible: true


    title: qsTr("Smart Home System")
    Material.theme: Material.Dark
    Material.background: "#001219"
    color: Material.background

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        SmartMafiaGui {
            id: mafia_gui
            Layout.fillWidth: true
            Layout.fillHeight: true
            onMafiaAction: (action) => { mafiaEngine.onMafiaAction(action) }
        }

        SmartSpotGui {
            id: spot_1
            Layout.preferredWidth: implicitWidth
            Layout.fillHeight: true
            onColorRequested: (selectedColor) => {
                    mafiaEngine.setColor(
                    Math.round(selectedColor.r * 255),
                    Math.round(selectedColor.g * 255),
                    Math.round(selectedColor.b * 255))
            }
        }
    }
}
