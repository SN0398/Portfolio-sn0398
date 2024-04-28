#include "../Utility.h"
#include <math.h>

// 内積
float DotProduct(VECTOR pos1, VECTOR pos2)
{
	return pos1.x * pos2.x + pos1.y * pos2.y + pos1.z * pos2.z;
}

// 外積
VECTOR CrossProduct(VECTOR pos1, VECTOR pos2)
{
	VECTOR pos =
	{
		pos1.y * pos2.z - pos1.z * pos2.y,
		pos1.z * pos2.x - pos1.x * pos2.z,
		pos1.x * pos2.y - pos1.y * pos2.x,
	};
	return pos;
}

// ベクトルの大きさを得る
float GetMagnitude(VECTOR pos)
{
	// 平方根
	return sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
}

// 3Dベクトルの正規化
VECTOR Normalize_3D(VECTOR pos)
{
	// ベクトルの長さ取得
	float Length = GetMagnitude(pos);
	// ベクトルの長さが０（計算不能な値）なら計算せずに抜ける
	if (Length <= 0.000001f) { return pos; }
	// リザルト
	return VECTOR
	{
		pos.x / Length,
		pos.y / Length,
		pos.z / Length,
	};
}