import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    signal signalQml2Qt()
    signal signalParent2Child(var msg)

    Text {
        id:test
        text: "Hello"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("TEST: Qml is signaling to Qt...")
                signalQml2Qt()
            }
        }
    }

    function slotQt2Qml() {
        console.log("TEST: Qml received!")
        test.text = "World"

        signalParent2Child("Hello World")
    }
}
