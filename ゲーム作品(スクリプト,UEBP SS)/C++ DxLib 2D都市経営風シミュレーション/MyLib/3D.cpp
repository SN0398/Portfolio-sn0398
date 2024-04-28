#include "../MyLib.h"
#include <math.h>

// ベクトルの大きさを得る
float GetMagnitude3D(Vector3D pos)
{
	// 平方根
	return sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
}

// 3Dベクトルの正規化
Vector3D Normalize_3D(Vector3D pos)
{
	// ベクトルの長さ取得
	float Length = GetMagnitude3D(pos);
	// ベクトルの長さが０（計算不能な値）なら計算せずに抜ける
	if (Length <= 0.00001f) { return pos; }
	// リザルト
	return Vector3D
	{
		pos.x / Length,
		pos.y / Length,
		pos.z / Length,
	};
}