#pragma once
#include "MyLib.h"
#include <vector>

using Vertex = Vector4f;

// ���_�C���f�b�N�X�o�b�t�@�\����
struct VertexIndexBuffer
{
	unsigned short num;                    // �|���S���̒��_��
	std::vector<unsigned short> index;     // ���_�C���f�b�N�X
};

// ���b�V���I�ȍ\����
struct Mesh
{
	int vertNum;							// ���_�̐�
	std::vector<Vertex> VB;					// ���_�̍��W
	int polyNum;							// �|���S����
	std::vector<VertexIndexBuffer> IB;		// �|���S�����(���_�C���f�b�N�X)
};