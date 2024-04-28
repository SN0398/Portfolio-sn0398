#pragma once
#include "Component/MeshInterface/MeshInterface.h"
#include <unordered_map>
#include "DxLib.h"
#include <cassert>

const int OC_INSIDE = 0;	// 0000 0000
const int OC_LEFT = 1;		// 0000 0001
const int OC_RIGHT = 2;		// 0000 0010
const int OC_BOTTOM = 4;	// 0000 0100
const int OC_TOP = 8;		// 0000 1000
const int OC_NEAR = 16;		// 0001 0000
const int OC_FAR = 32;		// 0010 0000

bool operator==(const Vertex& lhs, const Vertex& rhs);

struct VertexHash
{
	size_t operator()(const Vertex& v) const
	{
		// ハッシュ値を計算するロジックを記述する
		// 例えば、各座標のハッシュ値を組み合わせる
		size_t h1 = hash<double>()(v.x);
		size_t h2 = hash<double>()(v.y);
		size_t h3 = hash<double>()(v.z);
		size_t h4 = hash<double>()(v.w);
		return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
	}
};

Vertex Interpolate(Vertex v1, Vertex v2, float t);

int ComputeOutCode(Vertex v);

bool CohenSutherlandLineClip(Vertex& v1, Vertex& v2);

// ポリゴンのクリッピング
Mesh PolygonClipping(const Mesh& input);