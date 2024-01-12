import QtQuick 2.7
import QtQuick.Controls 2.1

Item {
    width: parent.width
    height: parent.height

    BusyIndicator{
        id:busyIndicator
        anchors.centerIn: parent;
        running: true;
    }
    Label{
        anchors.top: busyIndicator.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: qsTr("开发中......");
        font.family: "Microsoft YaHei";
        font.pointSize: 18;
        color: "#828385";
        verticalAlignment:Label.AlignVCenter;
        horizontalAlignment: Label.AlignHCenter;
    }
}
