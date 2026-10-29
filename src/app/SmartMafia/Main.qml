import QtQuick
import QtQuick.Controls.Material
import QtQuick.Window
import QtQuick.Layouts

import MafiaPlayer


ApplicationWindow {
    width: 740
    height: 580
    visible: true


    title: qsTr("Smart Home System")
    Material.theme: Material.Dark
    Material.background: "#001219"
    color: Material.background

    ColumnLayout {
           id: columnLayout
           anchors.centerIn: parent
           anchors.fill: parent
           property int defMargin: 10
           spacing: defMargin / 2

    MafiaPlayer {
        id: mafia_player
    }

    SmartMafiaGui {
        id: mafia_gui
        onMafiaAction: (action) => { mafia_player.onMafiaAction(action) }
    }
}
}
