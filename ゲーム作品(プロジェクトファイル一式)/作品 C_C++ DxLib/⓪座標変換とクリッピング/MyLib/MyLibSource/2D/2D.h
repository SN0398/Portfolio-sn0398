#pragma once
#include <vector>
#include <string>

using namespace std;

namespace MyLib
{
	// �}�b�v�N���X
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
			// ������
			width = Width;
			height = Height;
			// �s�̗̈�m��
			Chip.reserve(height);
			// ��̗̈�m�ۂƏ�����
			for (int i = 0; i < height; i++)
			{
				vector<int> tmp;	// �ǉ��p
				tmp.reserve(width);	// �̈�m��
				tmp.resize(width);	// �v�f�ǉ�
				std::fill(tmp.begin(), tmp.end(), fillNum);	// ������
				Chip.push_back(tmp);	// �ǉ�
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

	// 2D�̃x�N�g���\����
	typedef struct _Vector2D
	{
		double x;
		double y;

	}Vector2D;

	// 2D�̃x�N�g���\����
	typedef struct _Position2D
	{
		int x;
		int y;

	}Position2D;

	// 2D�����֌W
	Vector2D GetVec2D(float X, float Y);	// �w�肵��2D�x�N�g���𓾂�
	Vector2D AddVec2D(Vector2D VecA, Vector2D VecB);	// ���2D�x�N�g������������2D�x�N�g���𓾂�
	Vector2D SubVec2D(Vector2D VecA, Vector2D VecB);	// ���2D�x�N�g�������Z����2D�x�N�g���𓾂�
	Vector2D MulVec2D(Vector2D Vec, float Multiplier);	// 2D�x�N�g������Z�����x�N�g���𓾂�
	int CheckHitBoxToBox2D(Vector2D StartPosA, Vector2D EndPosA, Vector2D StartPosB, Vector2D EndPosB);	// ��`���m�̓����蔻��
	int CheckHitBoxToPoint2D(Vector2D StartPos, Vector2D EndPos, Vector2D Point);	// ��`�Ɠ_�Ƃ̓����蔻��
	Vector2D Normalize_2D(Vector2D pos);	// 2D�x�N�g���̐��K��
	Vector2D GetDirection(Vector2D pos, Vector2D target);	// �����x�N�g���𓾂�
	float GetDistance_2D(Vector2D VecA, Vector2D VecB);	// 2�_�Ԃ̋������擾����
	float GetMagniture2D(float x, float y);	// �x�N�g���̑傫���𓾂�
	void MoveProcess(Vector2D* pos, double MoveSpeed);	//�ėp�ړ�����
}