#pragma once
#include "MyLib.h"
#include <vector>

using Vertex = Vector4f;

// 頂点インデックスバッファ構造体
struct VertexIndexBuffer
{
	unsigned short num;                    // ポリゴンの頂点数
	std::vector<unsigned short> index;     // 頂点インデックス
};

// メッシュ的な構造体
struct Mesh
{
	int vertNum;							// 頂点の数
	std::vector<Vertex> VB;					// 頂点の座標
	int polyNum;							// ポリゴン数
	std::vector<VertexIndexBuffer> IB;		// ポリゴン情報(頂点インデックス)
};