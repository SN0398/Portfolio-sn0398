#include "Renderer.h"
#include "Component/PolygonClipping/Clipping.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::UpdateRendererConfig()
{
	if (projType == ProjectionType::Perspective)
	{
		renderer.proj =
			Matrix::MakePerspectiveMatrix
			(
				proj.FoV,
				proj.aspectRatio,
				proj.nearPlane,
				proj.farPlane
			);
	}
	//else
	//{
	//	renderer.proj =
	//		Matrix::MakeOrthogonalMatrix
	//		(
	//			window.Width,
	//			window.Height,
	//			proj.nearPlane,
	//			proj.farPlane
	//		);
	//}
	renderer.view =
		Matrix::MakeViewMatrix
		(
			camera.cameraPos,
			camera.lookAtPos,
			camera.upVector
		);
	// スクリーン座標系
	renderer.screen = Matrix::MakeViewportMatrix
	(
		window.OffsetX, window.OffsetY,
		window.Width, window.Height,
		0.0f, 1.0f
	);
}

Mesh Renderer::ClipCoordinate(const Mesh& buff)
{
	Mesh result = buff;
	for (Vertex& v : result.VB)
	{
		v = Transformed(v);
	}
	return result;
}

Mesh Renderer::NormalizedDeviceCoordinate(const Mesh& buff)
{
	Mesh result = buff;
	for (Vertex& v : result.VB)
	{
		// 正規化デバイス座標系
		v.x = v.x / v.w;
		v.y = v.y / v.w;
		v.z = v.z / v.w;
		v.w = v.w / v.w;
	}
	return result;
}

Mesh Renderer::ScreenCoordinate(const Mesh& buff)
{
	Mesh result = buff;
	for (Vertex& v : result.VB)
	{
		// スクリーン座標系
		v = Vector4Transform(renderer.screen, v);
	}
	return result;
}

void Renderer::Render(const Mesh& buff, COLOR_U8 color)
{
	// ポリゴンの描画
	for (int i = 0; i < buff.polyNum; i++)
	{
		VertexIndexBuffer vib = buff.IB[i]; // 頂点ｲﾝﾃﾞｯｸｽﾊﾞｯﾌｧを取得

		// DXライブラリで描画するための構造体定義(頂点数だけ配列を確保)
		VERTEX2D* polygons = new VERTEX2D[vib.num];

		COLOR_U8 polygoncolor = color;    // 描画する色

		// ポリゴンの各頂点をVERTEX2Dに格納
		for (int j = 0; j < vib.num; j++)
		{
			// 指定インデックスの頂点座標を取得
			Vertex pos = buff.VB[vib.index[j]];
			VECTOR v = { pos.x,pos.y }; // 変換
			// 要素更新
			polygons[j] = { v,1,polygoncolor,0,0 };
		}

		// 多角形の描画
		DrawPrimitive2D
		(
			polygons,
			vib.num,
			DX_PRIMTYPE_LINESTRIP,
			DX_NONE_GRAPH,
			TRUE
		);
		delete[] polygons;
	}


	//for (auto& obj : model)
	//{
	//	// モデル行列更新
	//	GetModelMatrix(*obj);

	//	// 座標変換とクリッピング
	//	Mesh buff = obj->Model;		// コピー
	//	printfDx("クリップ座標系\n\n");
	//	for (Vertex& v : buff.VB)
	//	{
	//		// 座標変換 M->V->P
	//		v = Transformed(v);
	//		printfDx("%7.3f, %7.3f, %7.3f, %7.3f\n", v.x, v.y, v.z, v.w);
	//	}
	//	printfDx("\n");
	//	buff = PolygonClipping(buff);
	//	printfDx("\n");
	//	printfDx("クリッピング後座標\n\n");
	//	for (Vertex& v : buff.VB)
	//	{
	//		printfDx("%7.3f, %7.3f, %7.3f, %7.3f\n", v.x, v.y, v.z, v.w);
	//	}
	//	//printfDx("正規化デバイス座標系\n\n");
	//	for (Vertex& v : buff.VB)
	//	{
	//		// 正規化デバイス座標系
	//		v.x = v.x / v.w;
	//		v.y = v.y / v.w;
	//		v.z = v.z / v.w;
	//		v.w = v.w / v.w;
	//		//printfDx("%7.3f, %7.3f, %7.3f, %7.3f\n", v.x, v.y, v.z, v.w);
	//	}
	//	//printfDx("スクリーン座標系\n\n");
	//	// スクリーン座標系
	//	for (Vertex& v : buff.VB)
	//	{
	//		// スクリーン座標系
	//		v = Vector4Transform(ScreenMat, v);
	//		//printfDx("%7.3f, %7.3f, %7.3f, %7.3f\n", v.x, v.y, v.z, v.w);
	//		//printfDx("\n");
	//	}

	//	// ポリゴンの描画
	//	for (int i = 0; i < buff.polyNum; i++)
	//	{
	//		VertexIndexBuffer vib = buff.IB[i]; // 頂点ｲﾝﾃﾞｯｸｽﾊﾞｯﾌｧを取得

	//		// DXライブラリで描画するための構造体定義(頂点数だけ配列を確保)
	//		VERTEX2D* polygons = new VERTEX2D[vib.num];

	//		COLOR_U8 polygoncolor = obj->color;    // 描画する色

	//		// ポリゴンの各頂点をVERTEX2Dに格納
	//		for (int j = 0; j < vib.num; j++)
	//		{
	//			// 指定インデックスの頂点座標を取得
	//			Vertex pos = buff.VB[vib.index[j]];
	//			VECTOR v = { pos.x,pos.y }; // 変換
	//			// 要素更新
	//			polygons[j] = { v,1,polygoncolor,0,0 };
	//		}

	//		// 多角形の描画
	//		DrawPrimitive2D
	//		(
	//			polygons,
	//			vib.num,
	//			DX_PRIMTYPE_LINESTRIP,
	//			DX_NONE_GRAPH,
	//			TRUE
	//		);
	//		delete[] polygons;
	//	}
	//}
}

Vertex Renderer::Transformed(const Vertex& v)
{
	// ローカル座標系
	Vector4f pos = v;
	// ワールド座標系
	pos = Vector4Transform(renderer.world, pos);
	// カメラ座標系
	pos = Vector4Transform(renderer.view, pos);
	// クリッピング座標系
	pos = Vector4Transform(renderer.proj, pos);
	// 返却
	return pos;
}

void Renderer::GetModelMatrix(ModelData model)
{
	// モデル変換行列
	renderer.world =
		Matrix::MakeModelMatrix
		(
			model.transform.Position,
			model.transform.Rotation,
			model.transform.Scale
		);
}