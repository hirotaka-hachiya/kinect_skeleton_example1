//main.cpp Kinectから右上半身の関節位置を取得し、骨格情報を描画するプログラム
#include "myKinect.h"
#include <tchar.h>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
 //Kinectに接続
 if(!connectKinect()) return 1;
    
 //各フレームでの全員分の骨格情報（スケルトン）などが格納される構造体
 NUI_SKELETON_FRAME SkeletonFrame;

 //キー'q'が押されるまでループ
 while (true)
 {    
  //--------
  // 右上半身の骨格表示用のOpenCv行列を作成
  cv::Mat img = cv::Mat::zeros(300, 500, CV_8UC3);
  //--------
 
  //次のフレームの骨格情報を取得
  NuiSkeletonGetNextFrame(0, &SkeletonFrame); 

  //１人目の骨格情報を追跡できているか、または、関節位置情報を取得できているか？
  if(SkeletonFrame.SkeletonData[0].eTrackingState==NUI_SKELETON_TRACKED
	  || SkeletonFrame.SkeletonData[0].eTrackingState==NUI_SKELETON_POSITION_ONLY)
  {      
   //右上半身の関節位置情報の取得
   const Vector4 hand_r = 
    SkeletonFrame.SkeletonData[0].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT];
   const Vector4 wrist_r =
    SkeletonFrame.SkeletonData[0].SkeletonPositions[NUI_SKELETON_POSITION_WRIST_RIGHT];
   const Vector4 elbow_r = 
    SkeletonFrame.SkeletonData[0].SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT];  
   const Vector4 shoulder_r = 
    SkeletonFrame.SkeletonData[0].SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_RIGHT];
   const Vector4 shoulder_c =
    SkeletonFrame.SkeletonData[0].SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_CENTER];
   const Vector4 head =
    SkeletonFrame.SkeletonData[0].SkeletonPositions[NUI_SKELETON_POSITION_HEAD];
   const Vector4 spine =
    SkeletonFrame.SkeletonData[0].SkeletonPositions[NUI_SKELETON_POSITION_SPINE];
  
   //右肩を中心とした、相対的な右手のx, y, z座標を標準出力
   std::cout<<"Right Hand:"<<hand_r.x - shoulder_r.x<<", \\
	   "<<hand_r.y-shoulder_r.y<<", "<<hand_r.z-shoulder_r.z<<std::endl;

   //関節間を繋ぐ線を描画
   drawLine(img, wrist_r,  hand_r);
   drawLine(img, elbow_r,  wrist_r);
   drawLine(img, shoulder_r,  elbow_r);
   drawLine(img, shoulder_c,  shoulder_r);
   drawLine(img, head,  shoulder_c);
   drawLine(img, shoulder_c,  spine);
   
   //右手の位置に丸を描画
   drawPoint(img, hand_r);

   //行列を表示
   cv::imshow("右上半身の関節位置", img);
  
   //キー'q'が押されたらループを停止
   int key = cv::waitKey(10);
   if(key == 'q'){
    break;
   }

   // 骨格情報を連続に変化するように変換
   NuiTransformSmooth(&SkeletonFrame,NULL);
  }        
 }

 return 0;
}
