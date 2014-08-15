#include "myKinect.h"

//connectKinect�@Kinect�ɐڑ�
//�@�o�́@�������Ftrue�A���s���Ffalse
bool connectKinect()
{
  HRESULT hr= NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);
  if(FAILED(hr))
  {
    std::cout<<"Kinect�ɂ͐ڑ��ł��܂���ł����BKinect�̏�Ԃ��m�F���Ă��������B"<<std::endl;
    return false;
  }
  return true;
}

// drawPoint�@�����摜��Ɋۂ�`�悷��֐�
// image		: OpenCV�̍s��
// position		: �ۂ�`�悷��R�������W
void drawPoint( cv::Mat& image, Vector4 position )
{
	// �R�������W����Q�����̋����摜��̍��W�ɕϊ�
	FLOAT depthX = 0, depthY = 0;
	::NuiTransformSkeletonToDepthImage(position, &depthX, &depthY, CAMERA_RESOLUTION);

	// �����摜��̍��W����RGB�摜��̍��W�ɕϊ�
	LONG colorX = 0;
	LONG colorY = 0;
	::NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION, CAMERA_RESOLUTION, 0,(LONG)depthX, (LONG)depthY, 0, &colorX, &colorY );
	
	// RGB�摜��̍��W�Ɋۂ�`��
	cv::circle( image, cv::Point(colorX,colorY), 10, cv::Scalar( 0, 255, 0), 5);
}

// drawLine�@�����摜��ɐ�����`�悷��֐�
// image		: OpenCV�̍s��
// pos1		: �@: ���̒[�_�P
// pos2			: ���̒[�_�Q
void drawLine( cv::Mat& image, Vector4 pos1, Vector4 pos2)
{
	// �R�������W���狗���摜��̍��W�ɕϊ�
	FLOAT depthX1 = 0, depthY1 = 0;
	FLOAT depthX2 = 0, depthY2 = 0;
	::NuiTransformSkeletonToDepthImage(pos1, &depthX1, &depthY1, CAMERA_RESOLUTION);
	::NuiTransformSkeletonToDepthImage(pos2, &depthX2, &depthY2, CAMERA_RESOLUTION);

	// �����摜��̍��W����RGB�摜��̍��W�ɕϊ�
	LONG colorX1 = 0, colorY1 = 0;
	LONG colorX2 = 0, colorY2 = 0;
	::NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(
		CAMERA_RESOLUTION, CAMERA_RESOLUTION, 0, (LONG)depthX1, (LONG)depthY1, 0, &colorX1, &colorY1 );
	::NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(
		CAMERA_RESOLUTION, CAMERA_RESOLUTION, 0, (LONG)depthX2, (LONG)depthY2, 0, &colorX2, &colorY2 );
	
	// RGB�摜���W�ɐ�����`��
	cv::line(image, cv::Point(colorX1,colorY1), cv::Point(colorX2,colorY2), cv::Scalar(50,255,50), 5);	
}
