import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
	id: root

	implicitWidth: 300
	implicitHeight: 360

	property bool connected: false
	property bool spotOn: false
	property bool fanOn: false
	property int fanPower: fanOn ? 255 : 0
	property int fanMode: 0
	property real temperature: 0
	property color spotColor: "#f6c453"

	signal spotPowerRequested(bool enabled)
	signal fanRequested(bool enabled, int power, int mode)
	signal colorRequested(color color)

	readonly property var colorPresets: [
		{name: "Warm white", color: "#f6c453"},
		{name: "Cool white", color: "#d8ecff"},
		{name: "Red", color: "#ef476f"},
		{name: "Orange", color: "#f78c45"},
		{name: "Yellow", color: "#ffd166"},
		{name: "Green", color: "#52b788"},
		{name: "Cyan", color: "#4cc9f0"},
		{name: "Blue", color: "#4895ef"},
		{name: "Violet", color: "#9b5de5"}
	]

	Rectangle {
		anchors.fill: parent
		radius: 12
		color: "#10232b"
		border.color: "#29434d"
		border.width: 1

		ColumnLayout {
			anchors.fill: parent
			anchors.margins: 16
			spacing: 14

			RowLayout {
				Layout.fillWidth: true

				ColumnLayout {
					Layout.fillWidth: true
					spacing: 2

					Label {
						text: qsTr("Smart spot")
						font.pixelSize: 20
						font.bold: true
					}

					Label {
						text: connected ? qsTr("Connected") : qsTr("Disconnected")
						color: connected ? "#75d69c" : "#e88989"
						font.pixelSize: 12
					}
				}

				Rectangle {
					implicitWidth: 14
					implicitHeight: 14
					radius: width / 2
					color: connected ? "#75d69c" : "#e88989"
					border.color: "#10232b"
					border.width: 3
				}
			}

			Rectangle {
				Layout.fillWidth: true
				implicitHeight: 1
				color: "#29434d"
			}

			RowLayout {
				Layout.fillWidth: true

				ColumnLayout {
					Layout.fillWidth: true
					spacing: 2

					Label {
						text: qsTr("Spot")
						font.bold: true
					}

					Label {
						text: root.spotOn ? qsTr("On") : qsTr("Off")
						color: root.spotOn ? "#f6c453" : "#90a4ae"
						font.pixelSize: 12
					}
				}

				Switch {
					checked: root.spotOn
					text: qsTr("Power")
					onToggled: {
						root.spotOn = checked
						root.spotPowerRequested(checked)
					}
				}
			}

			RowLayout {
				Layout.fillWidth: true

				ColumnLayout {
					Layout.fillWidth: true
					spacing: 2

					Label {
						text: qsTr("Cooling")
						font.bold: true
					}

					Label {
						text: root.fanOn ? qsTr("Fan running") : qsTr("Fan off")
						color: root.fanOn ? "#4cc9f0" : "#90a4ae"
						font.pixelSize: 12
					}
				}

				Switch {
					checked: root.fanOn
					text: qsTr("Fan")
					onToggled: {
						root.fanOn = checked
						root.fanPower = checked ? 255 : 0
						root.fanRequested(checked, root.fanPower, root.fanMode)
					}
				}
			}

			RowLayout {
				Layout.fillWidth: true

				Label {
					text: qsTr("Temperature")
					font.bold: true
				}

				Item { Layout.fillWidth: true }

				Label {
					text: Number(root.temperature).toFixed(1) + " °C"
					color: root.temperature >= 40 ? "#ef476f" : "#d8ecff"
					font.pixelSize: 18
					font.bold: true
				}
			}

			Label {
				text: qsTr("Color")
				font.bold: true
			}

			GridLayout {
				Layout.fillWidth: true
				columns: 5
				rowSpacing: 8
				columnSpacing: 8

				Repeater {
					model: root.colorPresets

					Button {
						id: colorButton
						Layout.fillWidth: true
						implicitWidth: 38
						implicitHeight: 30
						padding: 0
						display: AbstractButton.IconOnly
						icon.color: modelData.color
						icon.source: ""
						ToolTip.visible: hovered
						ToolTip.text: modelData.name

						background: Rectangle {
							radius: 7
							color: modelData.color
							border.width: root.spotColor === modelData.color ? 3 : 1
							border.color: root.spotColor === modelData.color ? "#ffffff" : "#526b74"
						}

						onClicked: {
							root.spotColor = modelData.color
							root.colorRequested(modelData.color)
						}
					}
				}
			}
		}
	}
}
