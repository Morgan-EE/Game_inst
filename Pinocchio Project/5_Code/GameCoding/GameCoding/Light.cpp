#include "pch.h"
#include "Light.h"
#include "SceneManager.h"
#include "FlipbookActor.h"
#include "Flipbook.h"

#include "Sprite.h"
#include "Texture.h"
#include "Room.h"
#include "stage.h"

// Scene
#include "Scene.h"
#include "GameScene.h"

Light::Light()
{
	_blackAlphaBrush = new SolidBrush(Color(_blackAlpha, 0, 0, 0));
}

Light::~Light()
{
}

void Light::Tick()
{

}

void Light::Render(HDC hdc)
{
	//((GameScene*)(GET_SINGLE(SceneManager)->GetCurrentScene()))

	Graphics graphics(hdc);

	if ((GetMyScene()->isTabToggle))
	{
		Region* stage1Rect = new Region(Rect(384 * 0, 290, 384, 260));
		Region* stage2Rect = new Region(Rect(384 * 1, 290, 384, 260));
		Region* stage3Rect = new Region(Rect(384 * 2, 290, 384, 260));
		Region* stage4Rect = new Region(Rect(384 * 3, 290, 384, 260));
		Region* stage5Rect = new Region(Rect(384 * 4, 290, 384 + 30, 260));

		Region* stageRect[5] = { stage1Rect , stage2Rect , stage3Rect , stage4Rect , stage5Rect };
		
		for (int i = 0; i < 5; i++)
		{
			if (!((GameScene*)GetMyScene())->_currentRoom->_stages[i]->isVisited)
			{
				graphics.FillRegion(_blackAlphaBrush, stageRect[i]);
			}
			delete stageRect[i];
		}
	}
	else
	{
		// GDI+ Graphics ��ü ����
		_regionRectangle = new Region(Rect(0, 240, 1920, 600));

		// �簢������ �� ���� (�� ���� �ֱ�)
		for (int32 i = 0; i < _lightVector.size(); i++)
		{
			Region regionEllipse(_lightVector[i]);
			_regionRectangle->Exclude(&regionEllipse);
		}

		// �簢�� ä���
		graphics.FillRegion(_blackAlphaBrush, _regionRectangle);

		// �� �׶��̼�(���� ȿ�� �ֱ�)

		if (_lightVector.size() == 2)
		{
			Region regionEllipse1(_lightVector[0]);
			Region regionEllipse2(_lightVector[1]);

			(&regionEllipse1)->Exclude(&regionEllipse2);
			graphics.FillRegion(_EllipseBrushVector[0], &regionEllipse1);

			Region regionEllipse3(_lightVector[0]);
			Region regionEllipse4(_lightVector[1]);

			(&regionEllipse4)->Exclude(&regionEllipse3);
			graphics.FillRegion(_EllipseBrushVector[1], &regionEllipse4);
		}
		else
		{
			for (int32 i = 0; i < _lightVector.size(); i++)
			{
				graphics.FillPath(_EllipseBrushVector[i], _lightVector[i]);
			}
		}

		//delete _regionRectangle;

		_lightVector.clear();
		_EllipseBrushVector.clear();
	}
	

// 	Vec2Int size = _sprite->GetSize();
// 	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
// 
// 
// 	BITMAP bit;
// 
// 	GetObject(GetSprite()->GetTexture()->GetHBitMap(), sizeof(BITMAP), &bit);
// 	int bx, by;
// 
// 	bx = bit.bmWidth;
// 	by = bit.bmHeight;
// 
// 	// BLENDFUNCTION ����ü
// 	BLENDFUNCTION bf;
// 	bf.AlphaFormat = AC_SRC_ALPHA; // ��Ʈ�� ������ �Ϲ� ��Ʈ���� ��� 0, 32��Ʈ ��Ʈ���� ��� AC_SRC_ALPHA
// 	bf.BlendFlags = 0; // ������ 0�̾�� �Ѵ�
// 	bf.BlendOp = AC_SRC_OVER; // ������ AC_SRC_OVER�̾�� �ϰ� ������ ��� �̹����� ��ģ�ٴ� �ǹ�
// 	bf.SourceConstantAlpha = 255; // ����(���� 0 - ������ 255)
// 
// 	Gdiplus::Image* image = Gdiplus::Image::FromFile(L"D:\\Pinocchio\\5_Project\\GameCoding\\Resources\\Sprite\\Map\\effect.png"); //�̹�����ü����
// 	Gdiplus::Graphics g(hdc); // DC�� �̿��� �׷��Ȱ�ü ����
// 	Gdiplus::Rect rect; //��ġ��
// 	rect.X = 0; //x��ǥ
// 	rect.Y = 240; //y��ǥ
// 	//rect.Width = image->GetWidth(); //���α���
// 	rect.Width = 1920; //���α���
// 	rect.Height = 600; //���α���
// 	g.DrawImage(image, rect); //�̹����׸���
// 
// 		// ������ �޸� ����
// 		delete image;

// 	//alphablend �Լ��� �����ؾߵ�
// 	::BitBlt(hdc,
// 		(int32)_pos.x - size.x / 2 - ((int32)(cameraPos.x) - GWinSizeX / 2),
// 		(int32)_pos.y - size.y / 2 - ((int32)(cameraPos.y) - GWinSizeY / 2),
// 		size.x,
// 		size.y,
// 		_sprite->GetDC(),
// 		_sprite->GetPos().x,
// 		_sprite->GetPos().y,
// 		SRCCOPY);
}

void Light::AddLight(int32 x, int32 y)
{
	GraphicsPath* path = new GraphicsPath();
	if (y != 100)
	{
		path->AddEllipse(x, y, _radius * 2, _radius * 2);
	}
	else
	{
		path->AddEllipse(x, y, 750 * 2, 750 * 2);
	}

	_lightVector.push_back(path);

	PathGradientBrush* brush = new PathGradientBrush(path);
	brush->SetCenterColor(Color(0, 255, 255, 255));

	INT colorNum = 1;
	brush->SetSurroundColors(new Color[1]{ Color(_blackAlpha, 0, 0, 0) }, &colorNum); // �ܺ� ���� ����
	if (y != 100)
	{
		brush->SetCenterPoint(Point(x + 270, y + 270)); // ���� �߽��� ����
	}
	else
	{
		brush->SetCenterPoint(Point(x + 750, y + 750)); // ���� �߽��� ����
	}
	brush->SetFocusScales(0.2f, 0.2f);

	_EllipseBrushVector.push_back(brush);
}
