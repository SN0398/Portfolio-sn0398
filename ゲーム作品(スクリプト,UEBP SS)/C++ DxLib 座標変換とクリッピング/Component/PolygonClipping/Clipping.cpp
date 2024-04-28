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

	if (v.x < -v.w) code |= OC_LEFT;	// x = -w �̖ʂ�荶�ɂ���
	if (v.x > v.w) code |= OC_RIGHT;	// x =  w �̖ʂ��E�ɂ���
	if (v.y < -v.w) code |= OC_BOTTOM;	// y = -w �̖ʂ�艺�ɂ���
	if (v.y > v.w) code |= OC_TOP;		// y =  w �̖ʂ���ɂ���
	if (v.z < -v.w) code |= OC_NEAR;	// z = -w �̖ʂ���O�ɂ���
	if (v.z > v.w) code |= OC_FAR;		// z =  w �̖ʂ�艜�ɂ���

	return code;
}

bool CohenSutherlandLineClip(Vertex& v1, Vertex& v2)
{
	int outcode0 = ComputeOutCode(v1);
	int outcode1 = ComputeOutCode(v2);
	bool accept = false;

	while (true)
	{
		// �����͓����ɂ���
		if (!(outcode0 | outcode1))
		{
			accept = true;
			break;
		}
		// �����͊O���ɂ���
		else if (outcode0 & outcode1)
		{
			accept = false;
			break;
		}
		// �ǂ��炩�̒��_�������ɂ���O���ɂ���
		else
		{
			float t;
			Vertex v;
			int outcodeOut = outcode1 > outcode0 ? outcode1 : outcode0;

			if (outcodeOut & OC_NEAR)
			{
				// ���`��Ԃ̔䗦
				t = (-v1.w - v1.z) / (v2.z - v1.z + v2.w - v1.w);
				// �䗦��0~1�͈̔͊O�Ȃ��_���v�Z���Ȃ�
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
	//		// ���_��ǉ�
	//		result.VB.push_back(v);
	//		// �|���S���̃C���f�b�N�X�ԍ��ɓo�^
	//		// ���łɒ��_���C���N�������g
	//		out->index.push_back(result.vertNum++);
	//		// �|���S���̒��_�����C���N�������g
	//		out->num++;
	//	};

	// ���_�̏d�������unordered_map���g��
	// ���_���W�Œ��_�C���f�b�N�X�̍������s��
	unordered_map<Vertex, unsigned short, VertexHash> VIB;

	const auto AddVert = [&](VertexIndexBuffer* out, const Vertex& v)
		{
			// ��map�̓f�t�H���g�l��0�Œ��_�C���f�b�N�X0�Əd������̂�
			// �l��+1����Ă���
			auto& index = VIB[v];
			/*
			�Ԃ��Ă����l���f�t�H���g�l
			�ł���ꍇ�͒��_���d�����Ă��Ȃ��̂�
			���̂܂ܒǉ�����
			*/
			if (index == 0)
			{
				// ���_��ǉ�
				result.VB.push_back(v);
				// �|���S���̃C���f�b�N�X�ԍ��ɓo�^
				out->index.push_back(result.vertNum);
				// ���_���C���N�������g
				result.vertNum++;
				// ���_�̃C���f�b�N�X��ݒ�
				index = result.vertNum;
				// �|���S���̒��_�����C���N�������g
				out->num++;
				return;
			}
			/*
			�f�t�H���g�l�łȂ��ꍇ��
			���_���d�����Ă���̂�
			�擾�����l�𒸓_�C���f�b�N�X�Ƃ���
			���̂܂ܒǉ����邾��
			*/
			// �|���S���̃C���f�b�N�X�ԍ��ɓo�^
			out->index.push_back(index - 1);
			// �|���S���̒��_�����C���N�������g
			out->num++;

			return;
		};

	/*
	* AddVert(temp, v);	// �d�����Ȃ����_�Ȃ�ǉ����d�����钸�_�Ȃ璸�_�C���f�b�N�X
	*/

	// �|���S���̐��J��Ԃ�
	for (int i = 0; i < input.polyNum;i++)
	{
		// �|���S�����ꎞ�ۊǗp
		VertexIndexBuffer temp;
		temp.num = 0;
		temp.index = {};

		// �|���S���������_�������J��Ԃ�
		for (int j = 0; j < input.IB[i].num - 1; j++)
		{
			// j�Ԗڂ̃C���f�b�N�X��j�Ԗڂ̎��̃C���f�b�N�X���擾
			int curindex = j;
			int nextindex = (j + 1) % input.IB[i].num; // (j + 1 >= result.IB[i].num)�Ȃ�0�ɂȂ�

			// �q�����Ă��钸�_���擾
			Vertex v1 = input.VB[input.IB[i].index[curindex]];
			Vertex v2 = input.VB[input.IB[i].index[nextindex]];

			if (CohenSutherlandLineClip(v1, v2))
			{
				AddVert(&temp, v1);
				AddVert(&temp, v2);
			}
		}
		// ���_����ȏ゠��|���S���ɂȂ�����ǉ�����
		if (temp.num)
		{
			//printf("�|���S����ǉ��ł���\n");
			result.IB.push_back(temp);
			result.polyNum++;
		}
	}

	return result;
}