#pragma once
#include <vector>
#include <string>

using namespace std;

namespace MyLib
{
	// マップクラス
	class MapChip
	{
	public:
		MapChip() = delete;
		MapChip(const std::vector<std::vector<int>>& _map) : Chip(_map)
		{
			height = Chip.size();
			width = Chip.front().size();
		}
		MapChip(const int Width, const int Height, const int fillNum = 0)
		{
			// 初期化
			width = Width;
			height = Height;
			// 行の領域確保
			Chip.reserve(height);
			// 列の領域確保と初期化
			for (int i = 0; i < height; i++)
			{
				vector<int> tmp;	// 追加用
				tmp.reserve(width);	// 領域確保
				tmp.resize(width);	// 要素追加
				std::fill(tmp.begin(), tmp.end(), fillNum);	// 初期化
				Chip.push_back(tmp);	// 追加
			}
		}

	public:
		bool Export(string _path);
		bool Import(string _path);

	public:
		vector<vector<int>> Chip;
		int height;
		int width;

	};

	// 2Dのベクトル構造体
	typedef struct _Vector2D
	{
		double x;
		double y;

	}Vector2D;

	// 2Dのベクトル構造体
	typedef struct _Position2D
	{
		int x;
		int y;

	}Position2D;

	// 2D処理関係
	Vector2D GetVec2D(float X, float Y);	// 指定した2Dベクトルを得る
	Vector2D AddVec2D(Vector2D VecA, Vector2D VecB);	// 二つの2Dベクトルを合成した2Dベクトルを得る
	Vector2D SubVec2D(Vector2D VecA, Vector2D VecB);	// 二つの2Dベクトルを減算した2Dベクトルを得る
	Vector2D MulVec2D(Vector2D Vec, float Multiplier);	// 2Dベクトルを乗算したベクトルを得る
	int CheckHitBoxToBox2D(Vector2D StartPosA, Vector2D EndPosA, Vector2D StartPosB, Vector2D EndPosB);	// 矩形同士の当たり判定
	int CheckHitBoxToPoint2D(Vector2D StartPos, Vector2D EndPos, Vector2D Point);	// 矩形と点との当たり判定
	Vector2D Normalize_2D(Vector2D pos);	// 2Dベクトルの正規化
	Vector2D GetDirection(Vector2D pos, Vector2D target);	// 方向ベクトルを得る
	float GetDistance_2D(Vector2D VecA, Vector2D VecB);	// 2点間の距離を取得する
	float GetMagniture2D(float x, float y);	// ベクトルの大きさを得る
	void MoveProcess(Vector2D* pos, double MoveSpeed);	//汎用移動処理
}