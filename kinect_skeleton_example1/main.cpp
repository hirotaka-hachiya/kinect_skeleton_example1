//main.cpp Kinect����E�㔼�g�̊֐߈ʒu���擾���A���i����`�悷��v���O����
#include "myKinect.h"
#include <tchar.h>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
 //Kinect�ɐڑ�
 if(!connectKinect()) return 1;
    
 //�e�t���[���ł̑S�����̍��i���i�X�P���g���j�Ȃǂ��i�[�����\����
 NUI_SKELETON_FRAME SkeletonFrame;

 //�L�['q'���������܂Ń��[�v
 while (true)
 {    
  //--------
  // �E�㔼�g�̍��i�\���p��OpenCv�s����쐬
  cv::Mat img = cv::Mat::zeros(300, 500, CV_8UC3);
  //--------
 
  //���̃t���[���̍��i�����擾
  NuiSkeletonGetNextFrame(0, &SkeletonFrame); 

  //�P�l�ڂ̍��i����ǐՂł��Ă��邩�A�܂��́A�֐߈ʒu�����擾�ł��Ă��邩�H
  if(SkeletonFrame.SkeletonData[0].eTrackingState==NUI_SKELETON_TRACKED
	  || SkeletonFrame.SkeletonData[0].eTrackingState==NUI_SKELETON_POSITION_ONLY)
  {      
   //�E�㔼�g�̊֐߈ʒu���̎擾
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
  
   //�E���𒆐S�Ƃ����A���ΓI�ȉE���x, y, z���W��W���o��
   std::cout<<"Right Hand:"<<hand_r.x - shoulder_r.x<<", \\
	   "<<hand_r.y-shoulder_r.y<<", "<<hand_r.z-shoulder_r.z<<std::endl;

   //�֐ߊԂ��q������`��
   drawLine(img, wrist_r,  hand_r);
   drawLine(img, elbow_r,  wrist_r);
   drawLine(img, shoulder_r,  elbow_r);
   drawLine(img, shoulder_c,  shoulder_r);
   drawLine(img, head,  shoulder_c);
   drawLine(img, shoulder_c,  spine);
   
   //�E��̈ʒu�Ɋۂ�`��
   drawPoint(img, hand_r);

   //�s���\��
   cv::imshow("�E�㔼�g�̊֐߈ʒu", img);
  
   //�L�['q'�������ꂽ�烋�[�v���~
   int key = cv::waitKey(10);
   if(key == 'q'){
    break;
   }

   // ���i����A���ɕω�����悤�ɕϊ�
   NuiTransformSmooth(&SkeletonFrame,NULL);
  }        
 }

 return 0;
}
