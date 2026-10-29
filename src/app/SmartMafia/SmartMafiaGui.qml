import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Item {
    id: root
    anchors.fill: parent

    signal mafiaAction(int actionType)

    GridLayout {
        anchors.fill: parent
        anchors.margins: 10
        columns: 4
        rowSpacing: 10
        columnSpacing: 10

        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            Repeater {
                model: [
                {name: "Low Background", type: MafiaActions.DECREASE_BACKGROUND},
                {name: "Raise Background", type: MafiaActions.INCREASE_BACKGROUND},
                {name: "Intro", type: MafiaActions.INTRO},
                {name: "First Night", type: MafiaActions.FIRST_NIGHT},
                {name: "Murder", type: MafiaActions.MURDER}
                ]

                Button {
                    Layout.fillWidth: true
                    text: modelData.name
                    onClicked: root.mafiaAction(modelData.type)
                }
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            Repeater {
                model: [
                {name: "City Sleep", type: MafiaActions.CITY_SLEEP},
                {name: "Mafia S Maniac WU", type: MafiaActions.MAFIA_SLEEP_MANIAC_WU},
                {name: "Maniac S Sheriff WU", type: MafiaActions.MANIAC_SLEEP_SHERIFF_WU},
                {name: "Sheriff S Doctor WU", type: MafiaActions.SHERIFF_SLEEP_DOCTOR_WU},
                {name: "Doctor S Bitch WU", type: MafiaActions.DOCTOR_SLEEP_BITCH_WU},
                {name: "Bitch Sleep", type: MafiaActions.BITCH_SLEEP},
                {name: "City WU", type: MafiaActions.CITY_WU}
                ]
                Button {
                    Layout.fillWidth: true
                    text: modelData.name
                    onClicked: root.mafiaAction(modelData.type)
                }
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            Repeater {
                model: [
                {name: "Mafia Sleep", type: MafiaActions.MAFIA_SLEEP},
                {name: "Maniac WU", type: MafiaActions.MANIAC_WU},
                {name: "Maniac Sleep", type: MafiaActions.MANIAC_SLEEP},
                {name: "Doctor WU", type: MafiaActions.DOCTOR_WU},
                {name: "Doctor Sleep", type: MafiaActions.DOCTOR_SLEEP},
                {name: "Sheriff WU", type: MafiaActions.SHERIFF_WU},
                {name: "Sheriff Sleep", type: MafiaActions.SHERIFF_SLEEP},
                {name: "Bitch WU", type: MafiaActions.BITCH_WU},
                {name: "Bitch Sleep", type: MafiaActions.BITCH_SLEEP}
                ]
                Button {
                    Layout.fillWidth: true
                    text: modelData.name
                    onClicked: root.mafiaAction(modelData.type)
                }
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            Repeater {
                model: [
                {name: "Mafia", type: MafiaActions.MAFIA},
                {name: "Maniac", type: MafiaActions.MANIAC},
                {name: "Sheriff", type: MafiaActions.SHERIFF},
                {name: "Doctor", type: MafiaActions.DOCTOR},
                {name: "Townsman 1", type: MafiaActions.TOWNSMAN_1},
                {name: "Townsman 2", type: MafiaActions.TOWNSMAN_2},
                ]
                Button {
                    Layout.fillWidth: true
                    text: modelData.name
                    onClicked: root.mafiaAction(modelData.type)
                }
            }
        }

    }
}
