#include "Clipping.h"

bool operator==(const Vertex& lhs, const Vertex& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

Vertex Interpolate(Vertex v1, Vertex v2, float t)
{
	Vertex v;
	v.x = v1.x + t * (v2.x - v1.x);
	v.y = v1.y + t * (v2.y - v1.y);
	v.z = v1.z + t * (v2.z - v1.z);
	v.w = v1.w + t * (v2.w - v1.w);
	return v;
}

int ComputeOutCode(Vertex v)
{
	int code = OC_INSIDE;

	if (v.x < -v.w) code |= OC_LEFT;	// x = -w の面より左にある
	if (v.x > v.w) code |= OC_RIGHT;	// x =  w の面より右にある
	if (v.y < -v.w) code |= OC_BOTTOM;	// y = -w の面より下にある
	if (v.y > v.w) code |= OC_TOP;		// y =  w の面より上にある
	if (v.z < -v.w) code |= OC_NEAR;	// z = -w の面より手前にある
	if (v.z > v.w) code |= OC_FAR;		// z =  w の面より奥にある

	return code;
}

bool CohenSutherlandLineClip(Vertex& v1, Vertex& v2)
{
	int outcode0 = ComputeOutCode(v1);
	int outcode1 = ComputeOutCode(v2);
	bool accept = false;

	while (true)
	{
		// 線分は内側にある
		if (!(outcode0 | outcode1))
		{
			accept = true;
			break;
		}
		// 線分は外側にある
		else if (outcode0 & outcode1)
		{
			accept = false;
			break;
		}
		// どちらかの頂点が内側にあり外側にある
		else
		{
			float t;
			Vertex v;
			int outcodeOut = outcode1 > outcode0 ? outcode1 : outcode0;

			if (outcodeOut & OC_NEAR)
			{
				// 線形補間の比率
				t = (-v1.w - v1.z) / (v2.z - v1.z + v2.w - v1.w);
				// 比率が0~1の範囲外なら交点を計算しない
				if (t <= 0.0f || t >= 0.99999f) { accept = false;break; }
				v = Interpolate(v1, v2, t);
			}
			else if (outcodeOut & OC_FAR)
			{
				t = (v1.w - v1.z) / (v2.z - v1.z - v2.w + v1.w);
				if (t <= 0.0f || t >= 0.99999f) { accept = false;break; }
				v = Interpolate(v1, v2, t);
			}
			else if (outcodeOut & OC_BOTTOM)
			{
				t = (-v1.w - v1.y) / (v2.y - v1.y + v2.w - v1.w);
				if (t <= 0.0f || t >= 0.99999f) { accept = false;break; }
				v = Interpolate(v1, v2, t);
			}
			else if (outcodeOut & OC_TOP)
			{
				t = (v1.w - v1.y) / (v2.y - v1.y - v2.w + v1.w);
				if (t <= 0.0f || t >= 0.99999f) { accept = false;break; }
				v = Interpolate(v1, v2, t);
			}
			else if (outcodeOut & OC_LEFT)
			{
				t = (-v1.w - v1.x) / (v2.x - v1.x + v2.w - v1.w);
				if (t <= 0.0f || t >= 0.99999f) { accept = false;break; }
				v = Interpolate(v1, v2, t);
			}
			else if (outcodeOut & OC_RIGHT)
			{
				t = (v1.w - v1.x) / (v2.x - v1.x - v2.w + v1.w);
				if (t <= 0.0f || t >= 0.99999f) { accept = false;break; }
				v = Interpolate(v1, v2, t);
			}

			if (outcodeOut == outcode0)
			{
				v1 = v;
				outcode0 = ComputeOutCode(v1);
			}
			else
			{
				v2 = v;
				outcode1 = ComputeOutCode(v2);
			}
		}
	}

	return accept;
}

Mesh PolygonClipping(const Mesh& input)
{
	Mesh result = {};
	result.vertNum = 0;
	result.VB = {};
	result.polyNum = 0;
	result.IB = {};

	//const auto AddVert = [&](VertexIndexBuffer* out, const Vertex& v)
	//	{
	//		// 頂点を追加
	//		result.VB.push_back(v);
	//		// ポリゴンのインデックス番号に登録
	//		// ついでに頂点数インクリメント
	//		out->index.push_back(result.vertNum++);
	//		// ポリゴンの頂点数をインクリメント
	//		out->num++;
	//	};

	// 頂点の重複回避にunordered_mapを使う
	// 頂点座標で頂点インデックスの索引を行う
	unordered_map<Vertex, unsigned short, VertexHash> VIB;

	const auto AddVert = [&](VertexIndexBuffer* out, const Vertex& v)
		{
			// ※mapはデフォルト値が0で頂点インデックス0と重複するので
			// 値は+1されている
			auto& index = VIB[v];
			/*
			返ってきた値がデフォルト値
			である場合は頂点が重複していないので
			そのまま追加する
			*/
			if (index == 0)
			{
				// 頂点を追加
				result.VB.push_back(v);
				// ポリゴンのインデックス番号に登録
				out->index.push_back(result.vertNum);
				// 頂点数インクリメント
				result.vertNum++;
				// 頂点のインデックスを設定
				index = result.vertNum;
				// ポリゴンの頂点数をインクリメント
				out->num++;
				return;
			}
			/*
			デフォルト値でない場合は
			頂点が重複しているので
			取得した値を頂点インデックスとして
			そのまま追加するだけ
			*/
			// ポリゴンのインデックス番号に登録
			out->index.push_back(index - 1);
			// ポリゴンの頂点数をインクリメント
			out->num++;

			return;
		};

	/*
	* AddVert(temp, v);	// 重複しない頂点なら追加し重複する頂点なら頂点インデックス
	*/

	// ポリゴンの数繰り返し
	for (int i = 0; i < input.polyNum;i++)
	{
		// ポリゴン情報一時保管用
		VertexIndexBuffer temp;
		temp.num = 0;
		temp.index = {};

		// ポリゴンが持つ頂点数だけ繰り返し
		for (int j = 0; j < input.IB[i].num - 1; j++)
		{
			// j番目のインデックスとj番目の次のインデックスを取得
			int curindex = j;
			int nextindex = (j + 1) % input.IB[i].num; // (j + 1 >= result.IB[i].num)なら0になる

			// 繋がっている頂点を取得
			Vertex v1 = input.VB[input.IB[i].index[curindex]];
			Vertex v2 = input.VB[input.IB[i].index[nextindex]];

			if (CohenSutherlandLineClip(v1, v2))
			{
				AddVert(&temp, v1);
				AddVert(&temp, v2);
			}
		}
		// 頂点が一つ以上あるポリゴンになったら追加する
		if (temp.num)
		{
			//printf("ポリゴンを追加できる\n");
			result.IB.push_back(temp);
			result.polyNum++;
		}
	}

	return result;
}