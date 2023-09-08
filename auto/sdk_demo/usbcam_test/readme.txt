./csitestT5 6 0 1280 720 ./ 1 30 25
3   	/dev/video6
0   	sel
w   	1280
h   	720
./  	path_name
1   	mode
30	test_cnt
25	fps

测试方式：
1. 确定 usb camera 的分辨率，如 1920x1080
2. 确定 usb camera 生成的节点，可以通过拔插 usb camera，然后 ls /dev 看对应的是哪个 videoX
3. 键入命令回车便可

测试现象：
运行时，会出现如以下的 log
# ./csitestT5 6 0 1280 720 ./tmp/ 1 30 25
open /dev/video6 fd = 3
mCameraType = CAMERA_TYPE_UVC
format index = 0, name = YUYV 4:2:2, v4l2 pixel format = 56595559
format index = 0, name = YUYV 4:2:2, v4l2 pixel format = 56595559
format index = 0, name = YUYV 4:2:2, v4l2 pixel format = 56595559
capture format: V4L2_PIX_FMT_YUYV
 pixel format is 56595559
resolution got from sensor = 1280*720 num_planes = 0
VIDIOC_STREAMON ok
VIDIOC_STREAMOFF ok
mode 1 test done at the 0 time!!
time cost 3.744699(s)

在 log 中的 capture format 表示摄像头的输出格式，以下分几种情况：
1. YUYV：使用 RawViewer 打开便可，可以观测到画面正常且流畅
2. H.264：使用 Potplayer 打开，可以观测到画面正常且流畅
3. MPEG：使用 Potplayer 打开，可以观测到画面正常，但是只有一幅画面

注意：
1. 此 csitest 只适用于 usb camera 的调试，并不通用于其他 AHD camera 的应用
2. mode 注意无需改动，保持 1 便可
