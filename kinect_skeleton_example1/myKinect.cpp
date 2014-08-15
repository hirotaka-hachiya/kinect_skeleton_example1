#include "myKinect.h"

//connectKinect　Kinectに接続
//　出力　成功時：true、失敗時：false
bool connectKinect()
{
  HRESULT hr= NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);
  if(FAILED(hr))
  {
    std::cout<<"Kinectには接続できませんでした。Kinectの状態を確認してください。"<<std::endl;
    return false;
  }
  return true;
}

// drawPoint　距離画像上に丸を描画する関数
// image		: OpenCVの行列
// position		: 丸を描画する３次元座標
void drawPoint( cv::Mat& image, Vector4 position )
{
	// ３次元座標から２次元の距離画像上の座標に変換
	FLOAT depthX = 0, depthY = 0;
	::NuiTransformSkeletonToDepthImage(position, &depthX, &depthY, CAMERA_RESOLUTION);

	// 距離画像上の座標からRGB画像上の座標に変換
	LONG colorX = 0;
	LONG colorY = 0;
	::NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION, CAMERA_RESOLUTION, 0,(LONG)depthX, (LONG)depthY, 0, &colorX, &colorY );
	
	// RGB画像上の座標に丸を描画
	cv::circle( image, cv::Point(colorX,colorY), 10, cv::Scalar( 0, 255, 0), 5);
}

// drawLine　距離画像上に線分を描画する関数
// image		: OpenCVの行列
// pos1		: 　: 線の端点１
// pos2			: 線の端点２
void drawLine( cv::Mat& image, Vector4 pos1, Vector4 pos2)
{
	// ３次元座標から距離画像上の座標に変換
	FLOAT depthX1 = 0, depthY1 = 0;
	FLOAT depthX2 = 0, depthY2 = 0;
	::NuiTransformSkeletonToDepthImage(pos1, &depthX1, &depthY1, CAMERA_RESOLUTION);
	::NuiTransformSkeletonToDepthImage(pos2, &depthX2, &depthY2, CAMERA_RESOLUTION);

	// 距離画像上の座標からRGB画像上の座標に変換
	LONG colorX1 = 0, colorY1 = 0;
	LONG colorX2 = 0, colorY2 = 0;
	::NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(
		CAMERA_RESOLUTION, CAMERA_RESOLUTION, 0, (LONG)depthX1, (LONG)depthY1, 0, &colorX1, &colorY1 );
	::NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(
		CAMERA_RESOLUTION, CAMERA_RESOLUTION, 0, (LONG)depthX2, (LONG)depthY2, 0, &colorX2, &colorY2 );
	
	// RGB画像座標に線分を描画
	cv::line(image, cv::Point(colorX1,colorY1), cv::Point(colorX2,colorY2), cv::Scalar(50,255,50), 5);	
}
