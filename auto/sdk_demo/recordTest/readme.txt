720p_recordTest.yuv  格式是NV21,10帧，1280*720


测试1：输入yuv序列，输出h264
1.把720p_recordTest.yuv片源放到/extp/目录下(目前默认就应该有，没有的话自己做一个或者找售后要)
运行：
source  /qt5.9.sh
/recordTest

执行完毕后，会在/extp/下生成recode_out.h264

上面的测试，只是一个硬件编码的例子，输入yuv,输出编码后生成的视频裸数据h264。
------------------------------------------------------------------------------------------------------------------
测试2：输入yuv序列，输出mp4
与上面的单独编码例子不一样的地方是：此测试是编码+打包,多了打包这一步，把视频裸数据打包成TS格式的MP4,则需要进行如下操作：
1.把720p_recordTest.yuv片源放到/extp/目录下(目前默认就应该有，没有的话自己做一个或者找售后要)
2.修改recordTest.cpp，把TEST_H264_OUTPUT宏注释掉，编译后放到机器中
3.插入TF卡(必须！！！)
执行如下命令：
source  /qt5.9.sh
/recordTest

PS:此测试输出的mp4仅有视频，没有音频。

