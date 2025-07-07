import QtQuick
import QtQuick.Controls
import an.example 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello GUI frontend state remains synchronized with the backend")
    Worker {
        id: id_worker
        // onWorkStarted: {
        //     console.log("Work started")
        //     id_userButton.text = "startedWorking..."
        //     console.log("Work started..text should changed")
        //     //id_busyIndicator.running = true
        // }
        //Connections
        // onWorkFinished: success => {
        //                     id_busyIndicator.running = false
        //                     if (success) {
        //                         console.log("Work finished successfully")
        //                         id_userButton.text = "Task Completed/Start Work"
        //                     } else {
        //                         console.log("Work failed")
        //                         id_userButton.text = "Task Failed"
        //                     }
        //                     id_userButton.enabled = true
        //                 }
    }

    Column {
        anchors.centerIn: parent
        spacing: 20

        Button {
            id: id_button01
            text: "Hello"
            onClicked: {
                console.log("Hello successfully")
                //id_userButton.enabled = false
                id_button01.text = "ByeBye"
            }
        }
        Button {
            id: id_userButton
            text: "Start Work"
            onClicked: {
                console.log("button clicked...")
                //id_userButton.enabled = false
                id_userButton.text = "Working..."
                id_worker.doWork()
            }
            BusyIndicator {
                //Note: The indicator is only visible when running property is set to true.
                id: id_busyIndicator
                running: false //The default value is true
                anchors.fill: parent
            }
        }
        Button {
            id: id_userOnetimeButton
            text: "Start id_userOnetimeButton Work"
            onClicked: {
                console.log("id_userOnetimeButton clicked...")
                id_userOnetimeButton.text = "id_userOnetimeButton Working..."
                id_userOnetimeButton.enabled = false
                id_busyIndicator4id_userOnetimeButton.running = true
                id_worker.doWorkWithNewThread()
            }
            BusyIndicator {
                //Note: The indicator is only visible when running property is set to true.
                id: id_busyIndicator4id_userOnetimeButton
                running: false //The default value is true
                anchors.fill: parent
            }
        }
        Button {
            id: id_syncButton
            text: "Start id_syncButton Work"
            onClicked: {
                console.log("id_syncButton clicked...")
                id_userOnetimeButton.text = "id_syncButton Working..."
                id_userOnetimeButton.enabled = false
                id_worker.doWorkSync()
            }
        }
    }
    Connections {
        target: id_worker
        function onWorkStarted() {
            id_userButton.enabled = false //without disable but with runing check also work --eton@250707
            id_userButton.text = "Working..."
            id_busyIndicator.running = true
        }

        function onWorkFinished(success) {
            id_busyIndicator.running = false
            id_userButton.enabled = true
            if (success) {
                console.log("Work finished successfully")
                id_userButton.text = "Task Completed"
            } else {
                id_userButton.text = "Task Failed"
                console.log("Work failed")
            }
        }
    }
    //this make id_userOnetimeButton and id_userButton both connect to id_worker's signal. --eton@250707
    Connections {
        target: id_worker
        function onWorkFinished(success) {
            id_busyIndicator4id_userOnetimeButton.running = false
            id_userOnetimeButton.enabled = true
            if (success) {
                console.log("id_userOnetimeButton Work finished successfully")
                id_userOnetimeButton.text = "Task Completed"
            } else {
                id_userOnetimeButton.text = "Task Failed"
                console.log("id_userOnetimeButton Work failed")
            }
        }
    }
}
