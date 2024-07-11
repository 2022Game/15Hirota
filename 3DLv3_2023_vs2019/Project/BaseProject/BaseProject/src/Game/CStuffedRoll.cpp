#include "CStuffedRoll.h"
#include "CText.h"
#include "CImage.h"
#include "CFont.h"
#include "CGameManager.h"
#include "CTaskManager.h"
#include "CPlayer.h"

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
	{"Game Title\n \nDemon Adventure", 3.0f},
	{"Producerdirector\n \nTanaka Taro", 7.0f},
	{"Director\n \nTanaka Taro", 11.0f},
	{"Designer\n \nTanaka Taro", 15.0f},
	{"Programmer\n \nTanaka Taro", 19.0f},
	{"Creator\n \nTanaka Taro", 23.0f},
	{"Debugger\n \nTanaka Taro", 27.0f},
	{"Homeroom Teacher\n \nNamizashi Shota\n \nTakahashi Shinobu", 24.0f},
	{"�X�^�b�t4", 31.0f},
	{"�X�^�b�t5", 35.0f},
	{"�X�^�b�t6", 39.0f},
	{"Thank you for playing this game!", 43.0f},
};

// �R���X�g���N�^
CStuffedRoll::CStuffedRoll()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eDefault)
	, mStaffRollTime(0.0f)
{
	spInstance = this;

	// ���S�̃t�H���g�f�[�^�𐶐�
	mpFont = new CFont("res\\Font\\toroman.ttf");
	mpFont->SetFontSize(70);
	mpFont->SetAlignment(FTGL::TextAlignment::ALIGN_CENTER);
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

	pText->SetPos(CVector2(0.0f, yPos));

	CDebugPrint::Print("Text Position: %f, %f\n", pText->GetPos().X(), pText->GetPos().Y());
	CDebugPrint::Print("yPos: %f\n", yPos);
}

// �`�揈��
void CStuffedRoll::Render()
{
	int size = ARRAY_SIZE(STAFF_DATA);
	for (int i = 0; i < size; i++)
	{
		const StafData& data = STAFF_DATA[i];
		if (mStaffRollTime < data.startTime) continue;
		if (mStaffRollTime > data.startTime + 13.0f) continue;

		mStuffedRolls[i]->SetText(data.stuffName.c_str());
		// �X�N���[������
		ScrollTextUp(mStuffedRolls[i], mTextYPositions[i], 1.0f);
		mStuffedRolls[i]->SetColor(1.0f, 1.0f, 0.0f);
		mStuffedRolls[i]->SetFontSize(42);
		mStuffedRolls[i]->Render();
	}
}