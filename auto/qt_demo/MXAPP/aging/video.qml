import QtQuick 2.7
import QtQuick.Controls 2.1
import QtMultimedia 5.9
import mvideooutput 1.0
import Qt.labs.settings 1.0
import QtQuick.Dialogs 1.2
import Qt.labs.folderlistmodel 2.2
import QtQuick.Layouts 1.3

Rectangle{
    anchors.fill: parent
    color: "green"
	
    Settings
    {
        id: settings
        property var videosrc: "file:///usr/share/myir/Video/ST2297_visionv34.mp4"
    }


    //视频输出到背景
    MVideoOutput {
        width: parent.width
        height: parent.height
        source: video
    }

    //视频播放器
    MediaPlayer {
        id: video
        autoLoad: true
        autoPlay: true
        source: "file:///usr/share/myir/Video/ST2297_visionv34.mp4"
        onPlaybackStateChanged: //1:playing, 2:pause, 0:stop
        {
            if( video.playbackState === MediaPlayer.StoppedState ) //播放完成自动停止
            {
                console.log("video stop")
                video.stop()
				video.source=""
                video.source="file:///usr/share/myir/Video/ST2297_visionv34.mp4"
				video.play()
            }
        }
    }
}
