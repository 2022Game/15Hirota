#include "CStuffedRoll.h"
#include "CText.h"
#include "CImage.h"
#include "CFont.h"
#include "CGameManager.h"
#include "CTaskManager.h"
#include "CPlayer.h"
#include "CStageManager.h"

// �X�^�b�t���[���N���X�̃C���X�^���X
CStuffedRoll* CStuffedRoll::spInstance = nullptr;

CStuffedRoll* CStuffedRoll::Instance()
{
	if (spInstance == nullptr)
	{
		spInstance = new CStuffedRoll();
	}
	return spInstance;
}

const CStuffedRoll::StafData CStuffedRoll::STAFF_DATA[] =
{
	// �e�L�X�g��									// �J�n����		// X���W	R		G		B
	{"Game Title\n \nDemon Adventure",				3.0f,			450.0f,		1.0f,	0.0f,	0.0f},
	{"Producer\n \nTanaka Taro",					8.0f,			450.0f,		0.0f,	1.0f,	0.0f},
	{"Director\n \nTanaka Taro",					12.0f,			450.0f,		0.0f,	0.0f,	1.0f},
	{"Designer\n \nTanaka Taro",					16.0f,			450.0f,		1.0f,	1.0f,	0.0f},
	{"Programmer\n \nTanaka Taro",					20.0f,			750.0f,		1.0f,	0.0f,	1.0f},
	{"Creator\n \nTanaka Taro",						24.0f,			750.0f,		1.0f,	1.0f,	1.0f},
	{"Debugger\n \nTanaka Taro",					28.0f,			450.0f,		0.0f,	1.0f,	1.0f},
	{"Homeroom Teacher\n \nABCDEFG\n \nHIJKLMN",	32.0f,			450.0f,		1.0f,	0.0f,	0.0f},
	{"�X�^�b�t4",									38.0f,			450.0f,		1.0f,	0.0f,	0.0f},
	{"�X�^�b�t5",									42.0f,			450.0f,		1.0f,	0.0f,	0.0f},
	{"�X�^�b�t6",									46.0f,			450.0f,		1.0f,	0.0f,	0.0f},
	{"Thank you for Playing this Game!",			50.0f,			250.0f,		1.0f,	0.0f,	0.0f},
};

// �R���X�g���N�^
CStuffedRoll::CStuffedRoll()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eDefault)
	, mStaffRollTime(0.0f)
	, mXPos(0.0f)
{
	spInstance = this;

	// ���S�̃t�H���g�f�[�^�𐶐�
	mpFont = new CFont("res\\Font\\toroman.ttf");
	mpFont->SetFontSize(70);
	//mpFont->SetAlignment(FTGL::TextAlignment::ALIGN_LEFT);
	mpFont->SetLineLength(WINDOW_WIDTH);

	// �e�L�X�g�I�u�W�F�N�g�Ə���Y�ʒu�̐ݒ�
	int size = ARRAY_SIZE(STAFF_DATA);
	for (int i = 0; i < size; i++)
	{
		CText* text = new CText
		(
			mpFont, 70,
			CVector2(0.0f, 720.0f),
			CVector2(600.0f, 600),
			CColor(1.0f, 1.0f, 0.0f, 1.0f),
			ETaskPriority::eUI,
			0,
			ETaskPauseType::eDefault,
			false, false
		);
		mStuffedRolls.push_back(text);
		mTextYPositions.push_back(720.0f);  // ����Y�ʒu
	}
}

// �f�X�g���N�^
CStuffedRoll::~CStuffedRoll()
{
	SAFE_DELETE(mpFont);
	CStageManager::RemoveTask(this);
	spInstance = nullptr;
	int size = mStuffedRolls.size();
	for (int i = 0; i < size; i++)
	{
		CText* tex = mStuffedRolls[i];
		mStuffedRolls[i] = nullptr;
		SAFE_DELETE(tex);
	}
	mStuffedRolls.clear();
	mTextYPositions.clear();
}

// �X�V����
void CStuffedRoll::Update()
{
	mStaffRollTime += Time::DeltaTime();

	for (CText* text : mStuffedRolls)
	{
		text->Update();
	}

	CDebugPrint::Print("mTime:%f\n", mStaffRollTime);
}

// �e�L�X�g���ړ������鏈��
void CStuffedRoll::ScrollTextUp(CText* pText, float& yPos, float speed)
{
	yPos -= speed;

	pText->SetPos(CVector2(mXPos, yPos));

	CDebugPrint::Print("Text Position: %f, %f\n", pText->GetPos().X(), pText->GetPos().Y());
	CDebugPrint::Print("yPos: %f\n", yPos);
}

// �e�L�X�g��X���̃|�W�V������ݒ�
void CStuffedRoll::TextXPos(const float pos)
{
	mXPos = pos;
}

// �`�揈��
void CStuffedRoll::Render()
{
	int size = ARRAY_SIZE(STAFF_DATA);
	for (int i = 0; i < size; i++)
	{
		const StafData& data = STAFF_DATA[i];
		mXPos = data.xPos;
		if (mStaffRollTime < data.startTime) continue;
		if (mStaffRollTime > data.startTime + 15.0f) continue;

		mStuffedRolls[i]->SetText(data.stuffName.c_str());
		// �X�N���[������
		ScrollTextUp(mStuffedRolls[i], mTextYPositions[i], 1.0f);
		mStuffedRolls[i]->SetColor(data.r, data.g, data.b);
		mStuffedRolls[i]->SetFontSize(42);
		mStuffedRolls[i]->Render();
	}
}