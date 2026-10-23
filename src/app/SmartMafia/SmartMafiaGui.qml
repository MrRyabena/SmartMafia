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
            Repeater {
                model: [
                    {name: "Low Background", type: MafiaActions.DECREASE_BACKGROUND},
                    {name: "Raise Background", type: MafiaActions.INCREASE_BACKGROUND}
                ]

                Button {
                    Layout.fillWidth: true
                    text: modelData.name
                    onClicked: root.mafiaAction(modelData.type)
                }
            }
        }

        ColumnLayout {

            Repeater {
                model: [
                    {name: "City Sleep", type: MafiaActions.CITY_SLEEP},
                    {name: "Mafia S Maniac WU", type: MafiaActions.MAFIA_SLEEP_MANIAC_WU},
                    {name: "Maniac S Doctor WU", type: MafiaActions.MANIAC_SLEEP_DOCTOR_WU},
                    {name: "Doctor S Sherif WU", type: MafiaActions.DOCTOR_SLEEP_SHERIF_WU},
                    {name: "Sherif S Bitch WU", type: MafiaActions.SHERIF_SLEEP_BITCH_WU},
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

            Repeater {
                model: [
                    {name: "Mafia Sleep", type: MafiaActions.MAFIA_SLEEP},
                    {name: "Maniac WU", type: MafiaActions.MANIAC_WU},
                    {name: "Maniac Sleep", type: MafiaActions.MANIAC_SLEEP},
                    {name: "Doctor WU", type: MafiaActions.DOCTOR_WU},
                    {name: "Doctor Sleep", type: MafiaActions.DOCTOR_SLEEP},
                    {name: "Sherif WU", type: MafiaActions.SHERIF_WU},
                    {name: "Sherif Sleep", type: MafiaActions.SHERIF_SLEEP},
                    {name: "Bitch WU", type: MafiaActions.BITCH_WU},
                    {name: "Bitch Sleep", type: MafiaActions.BITCH_SLEEP}
                ]
                Button {
                    text: modelData.name
                    onClicked: root.mafiaAction(modelData.type)
                }
            }
        }

        ColumnLayout {

            Repeater {
                model: [
                    {name: "Mafia", type: MafiaActions.MAFIA_SLEEP}, 
                    {name: "Maniac", type: MafiaActions.MANIAC_SLEEP}, 
                    {name: "Doctor", type: MafiaActions.DOCTOR_SLEEP}, 
                    {name: "Sherif", type: MafiaActions.SHERIF_SLEEP},
                    {name: "Townsman 1", type: MafiaActions.TOWNSMAN_1_SLEEP},
                    {name: "Townsman 2", type: MafiaActions.TOWNSMAN_2_SLEEP},
                    {name: "Murder", type: MafiaActions.MURDER}]
                Button {
                    Layout.fillWidth: true
                    text: modelData.name
                    onClicked: root.mafiaAction(modelData.type)
                }
            }
        }
 
    }
}
