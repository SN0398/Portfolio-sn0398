#include "2D.h"
#include "MyLibSource/Input/Keyboard/Keyboard.h"

#include "DxLib.h"
#include <math.h>
#include <fstream>

using namespace MyLib;

// 指定した2Dベクトルを得る
Vector2D MyLib::GetVec2D(float X, float Y)
{
	return Vector2D{ X,Y };
}

// 二つの2Dベクトルを合成した2Dベクトルを得る
Vector2D MyLib::AddVec2D(Vector2D VecA, Vector2D VecB)
{
	return Vector2D{ VecA.x + VecB.x, VecA.y + VecB.y };
}

// 二つの2Dベクトルを減算した2Dベクトルを得る
Vector2D MyLib::SubVec2D(Vector2D VecA, Vector2D VecB)
{
	return Vector2D{ VecA.x - VecB.x, VecA.y - VecB.y };
}

// 2Dベクトルを乗算したベクトルを得る
Vector2D MyLib::MulVec2D(Vector2D Vec, float mult)
{
	return Vector2D{ Vec.x * mult, Vec.y * mult };
}

// 矩形同士の当たり判定
int MyLib::CheckHitBoxToBox2D(Vector2D StartPosA, Vector2D EndPosA, Vector2D StartPosB, Vector2D EndPosB)
{
	return ((StartPosA.x > StartPosB.x && StartPosA.x < EndPosB.x) ||
		(StartPosB.x > StartPosA.x && StartPosB.x < EndPosA.x)) &&
		((StartPosA.y > StartPosB.y && StartPosA.y < EndPosB.y) ||
			(StartPosB.y > StartPosA.y && StartPosB.y < EndPosA.y));
}

// 矩形と点との当たり判定
int MyLib::CheckHitBoxToPoint2D(Vector2D StartPos, Vector2D EndPos, Vector2D pos)
{
	return (pos.y >= StartPos.y && pos.y <= EndPos.y &&
		pos.x >= StartPos.x && pos.x <= EndPos.x);
}

// 2Dベクトルの正規化
Vector2D MyLib::Normalize_2D(Vector2D pos)
{
	float X = pos.x;
	float Y = pos.y;
	float L = sqrt(X * X + Y * Y);

	if (L <= 0.00001f) { return pos; }

	X /= L;
	Y /= L;
	
	return Vector2D{ X,Y };
}

// 方向ベクトルを得る
Vector2D MyLib::GetDirection(Vector2D pos, Vector2D target)
{
	return Vector2D
	{
		target.x - pos.x,
		target.y - pos.y
	};
}

// 2点間の距離を取得する
float MyLib::GetDistance_2D(Vector2D pos1, Vector2D pos2)
{
	// 方向ベクトル
	double x = pos1.x - pos2.x;
	double y = pos1.y - pos2.y;
	// ベクトルの大きさを求める
	return sqrt(x * x + y * y);
}

// 2Dベクトルの大きさを得る
float MyLib::GetMagniture2D(float x, float y)
{
	return sqrt(x * x + y * y);
}

// 十字キーでの2D移動ベクトル処理
void MyLib::MoveProcess(Vector2D* pos, double MoveSpeed)
{
	// 1フレームの移動ベクトル
	float VecX = 0;
	float VecY = 0;

	// 右移動
	if (Keyboard_Get(KEY_INPUT_RIGHT) >= 1 || Keyboard_Get(KEY_INPUT_D) >= 1)
	{
		VecX += 1;
	}
	// 左移動
	if (Keyboard_Get(KEY_INPUT_LEFT) >= 1 || Keyboard_Get(KEY_INPUT_A) >= 1)
	{
		VecX -= 1;
	}
	// 下移動
	if (Keyboard_Get(KEY_INPUT_DOWN) >= 1 || Keyboard_Get(KEY_INPUT_S) >= 1)
	{
		VecY += 1;
	}
	// 上移動
	if (Keyboard_Get(KEY_INPUT_UP) >= 1 || Keyboard_Get(KEY_INPUT_W) >= 1)
	{
		VecY -= 1;
	}
	// 移動ベクトルの正規化
	Vector2D move = Normalize_2D(GetVec2D(VecX, VecY));
	// 座標に移動ベクトル*速度を加算代入する
	*pos = AddVec2D(*pos, MulVec2D(move, MoveSpeed));

	return;
}

bool MyLib::MapChip::Export(string _path)
{
	// ファイルを開く
	std::ofstream ofs(_path);
	if (!ofs) return false; // 開けなかったらfalseを返す

	// Chipの内容を書き出す
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			ofs << Chip[i][j] << " "; // 空白区切りで書き出す
		}
		ofs << "\n"; // 改行する
	}

	// ファイルを閉じる
	ofs.close();
	return true; // 成功したらtrueを返す
}

bool MyLib::MapChip::Import(string _path)
{
	// ファイルを開く
	std::ifstream ifs(_path);
	if (!ifs) return false; // 開けなかったらfalseを返す

	// Chipの内容を読み込む
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			ifs >> Chip[i][j]; // 空白区切りで読み込む
		}
	}

	// ファイルを閉じる
	ifs.close();
	return true; // 成功したらtrueを返す
}
