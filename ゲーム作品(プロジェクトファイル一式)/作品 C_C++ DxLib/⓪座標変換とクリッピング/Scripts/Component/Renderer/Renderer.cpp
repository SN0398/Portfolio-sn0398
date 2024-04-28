#include "Renderer.h"
#include "Component/PolygonClipping/Clipping.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::UpdateRendererConfig()
{
	if (projType == ProjectionType::Perspective)
	{
		renderer.proj =
			Matrix::MakePerspectiveMatrix
			(
				proj.FoV,
				proj.aspectRatio,
				proj.nearPlane,
				proj.farPlane
			);
	}
	//else
	//{
	//	renderer.proj =
	//		Matrix::MakeOrthogonalMatrix
	//		(
	//			window.Width,
	//			window.Height,
	//			proj.nearPlane,
	//			proj.farPlane
	//		);
	//}
	renderer.view =
		Matrix::MakeViewMatrix
		(
			camera.cameraPos,
			camera.lookAtPos,
			camera.upVector
		);
	// �X�N���[�����W�n
	renderer.screen = Matrix::MakeViewportMatrix
	(
		window.OffsetX, window.OffsetY,
		window.Width, window.Height,
		0.0f, 1.0f
	);
}

Mesh Renderer::ClipCoordinate(const Mesh& buff)
{
	Mesh result = buff;
	for (Vertex& v : result.VB)
	{
		v = Transformed(v);
	}
	return result;
}

Mesh Renderer::NormalizedDeviceCoordinate(const Mesh& buff)
{
	Mesh result = buff;
	for (Vertex& v : result.VB)
	{
		// ���K���f�o�C�X���W�n
		v.x = v.x / v.w;
		v.y = v.y / v.w;
		v.z = v.z / v.w;
		v.w = v.w / v.w;
	}
	return result;
}

Mesh Renderer::ScreenCoordinate(const Mesh& buff)
{
	Mesh result = buff;
	for (Vertex& v : result.VB)
	{
		// �X�N���[�����W�n
		v = Vector4Transform(renderer.screen, v);
	}
	return result;
}

void Renderer::Render(const Mesh& buff, COLOR_U8 color)
{
	// �|���S���̕`��
	for (int i = 0; i < buff.polyNum; i++)
	{
		VertexIndexBuffer vib = buff.IB[i]; // ���_���ޯ���ޯ̧���擾

		// DX���C�u�����ŕ`�悷�邽�߂̍\���̒�`(���_�������z����m��)
		VERTEX2D* polygons = new VERTEX2D[vib.num];

		COLOR_U8 polygoncolor = color;    // �`�悷��F

		// �|���S���̊e���_��VERTEX2D�Ɋi�[
		for (int j = 0; j < vib.num; j++)
		{
			// �w��C���f�b�N�X�̒��_���W���擾
			Vertex pos = buff.VB[vib.index[j]];
			VECTOR v = { pos.x,pos.y }; // �ϊ�
			// �v�f�X�V
			polygons[j] = { v,1,polygoncolor,0,0 };
		}

		// ���p�`�̕`��
		DrawPrimitive2D
		(
			polygons,
			vib.num,
			DX_PRIMTYPE_LINESTRIP,
			DX_NONE_GRAPH,
			TRUE
		);
		delete[] polygons;
	}
}

Vertex Renderer::Transformed(const Vertex& v)
{
	// ���[�J�����W�n
	Vector4f pos = v;
	// ���[���h���W�n
	pos = Vector4Transform(renderer.world, pos);
	// �J�������W�n
	pos = Vector4Transform(renderer.view, pos);
	// �N���b�s���O���W�n
	pos = Vector4Transform(renderer.proj, pos);
	// �ԋp
	return pos;
}

void Renderer::GetModelMatrix(ModelData model)
{
	// ���f���ϊ��s��
	renderer.world =
		Matrix::MakeModelMatrix
		(
			model.transform.Position,
			model.transform.Rotation,
			model.transform.Scale
		);
}