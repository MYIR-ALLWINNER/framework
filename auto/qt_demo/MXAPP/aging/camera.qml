import QtQuick 2.7
import QtQuick.Controls 2.1
import QtMultimedia 5.12
import mvideooutput 1.0

Rectangle{
    anchors.fill: parent
    color: "red"
    border.width: 2
    border.color: "black"

    Camera {
        id: camera
        //相机模式
//        captureMode: Camera.CaptureStillImage       //静态照片捕捉模式
        captureMode: Camera.CaptureStillImage
        //白平衡
        imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash
        //分辨率
        viewfinder.resolution: "640x480"
        flash.mode: Camera.FlashRedEyeReduction
        //曝光
        exposure {
            exposureCompensation: +1.0
            exposureMode: Camera.ExposurePortrait
        }

        //拍照模式配置
        imageCapture {

            onImageSaved: console.log("save path:" + path);
//                    onImageCaptured: bar.img_src = preview
            onCaptureFailed: console.log("capture failed:" + message)
        }

        //录像模式配置
        videoRecorder {
//             resolution: "640x480"
             frameRate: 30              //帧率
//             audioEncodingMode: CameraRecorder.ConstantBitrateEncoding;
//             audioBitRate: 128000       //视频比特率
//             mediaContainer: "mp4"      //视频录制格式
//             outputLocation: "D:\MYIR\Capture\video_test"        //保存地址
             onRecorderStateChanged: console.log("state changed")
             onRecorderStatusChanged: console.log("status changed")
        }
        //对焦模式
//        focus {
//            focusMode: Camera.FocusAuto
//            focusPointMode: Camera.FocusPointCenter
//        }

        onError: console.log("camera err: " + errorCode + errorString);
        Component.onCompleted: console.log('StackView.onStatusChanged camera.viewfinder.resolution:', camera.viewfinder.resolution)
    }

    MVideoOutput {
//        anchors.fill: parent
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        source: camera
    }

//            ListModel {id: imagePaths}

    MouseArea{
        anchors.fill: parent

        onDoubleClicked: {
//                    loader10.sourceComponent = comp1;
            parent.scale= 1.5
            parent.z = 20

        }
    }
}
