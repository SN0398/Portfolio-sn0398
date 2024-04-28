#pragma once
#include "MyLib.h"
#include "GameObject/3DModel/3DModel.h"
#include <vector>

// カメラ情報
struct CameraData
{
	Vector cameraPos;	// カメラ座標
	Vector lookAtPos;	// 注視点
	Vector upVector;	// 上方向ベクトル
};

// 投影情報
struct ProjectionData
{
	float FoV;			// 視野
	float aspectRatio;	// アスペクト比
	float nearPlane;	// 近クリップ面
	float farPlane;		// 遠クリップ面
};

// スクリーン矩形情報
struct ScreenRect
{
	float Height;		// 縦幅
	float Width;		// 横幅
	float OffsetX;
	float OffsetY;
};

class Renderer : public Component
{
public:
	struct RendererBuffer
	{
		Matrix world;
		Matrix view;
		Matrix proj;
		Matrix screen;
	};
	
	enum class ProjectionType
	{
		Perspective,	// 透視投影
		//Orthogonal		// 平行投影
	};

public:
	Renderer();
	~Renderer();

public:
	void Update() override {}

	void Draw() override {}

	Mesh ClipCoordinate(const Mesh& buff);

	Mesh NormalizedDeviceCoordinate(const Mesh& buff);

	Mesh ScreenCoordinate(const Mesh& buff);

	void Render(const Mesh& buff, COLOR_U8 color);

	// 座標変換した結果のクリップ座標系を返す
	Vertex Transformed(const Vertex& v);

	// 描画用の行列を更新
	void UpdateRendererConfig();

	// モデル行列を取得
	void GetModelMatrix(ModelData model);

	// カメラ情報を変更
	void UpdateCameraData(CameraData _camera) { camera = _camera; }
	
	// 投影情報を変更
	void UpdateProjectionData(ProjectionData _proj) { proj = _proj; }
	
	// スクリーン情報を変更
	void UpdateScreenRect(ScreenRect _window) { window = _window; }
	
	// 投影変換の方法を切り替え
	void SwitchProjectionType(ProjectionType _projType) { projType = _projType; }

public:
	RendererBuffer renderer;		// 	
	CameraData camera;				// 
	ProjectionData proj;			// 
	ScreenRect window;				// 
	ProjectionType projType;		// 

};