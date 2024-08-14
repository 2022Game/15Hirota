#include "CStuffedRoll.h"
#include "CText.h"
#include "CImage.h"
#include "CFont.h"
#include "CGameManager.h"
#include "CTaskManager.h"
#include "CPlayer.h"
#include "CStageManager.h"
#include "CInput.h"
#include "CSceneManager.h"

const CStuffedRoll::StafData CStuffedRoll::STAFF_DATA[] =
{
	// �e�L�X�g��									// �J�n����		// X���W	R		G		B
	{"Game Title\n \nDemon Adventure",				3.0f,			450.0f,		1.0f,	0.0f,	0.0f},
	{"Producer\n \nTanaka Taro",					10.0f,			450.0f,		0.0f,	1.0f,	0.0f},
	{"Director\n \nTanaka Taro",					16.0f,			450.0f,		0.0f,	0.0f,	1.0f},
	{"Designer\n \nTanaka Taro",					22.0f,			450.0f,		1.0f,	1.0f,	0.0f},
	{"Programmer\n \nTanaka Taro",					28.0f,			450.0f,		1.0f,	0.0f,	1.0f},
	{"Creator\n \nTanaka Taro",						34.0f,			450.0f,		1.0f,	1.0f,	1.0f},
	{"Debugger\n \nTanaka Taro",					40.0f,			450.0f,		0.0f,	1.0f,	1.0f},
	{"Homeroom Teacher\n \nABCDEFG\n \nHIJKLMN",	46.0f,			450.0f,		1.0f,	0.0f,	0.0f},
	{"�X�^�b�t4",									52.0f,			450.0f,		1.0f,	0.0f,	0.0f},
	{"�X�^�b�t5",									58.0f,			450.0f,		1.0f,	0.0f,	0.0f},
	{"�X�^�b�t6",									64.0f,			450.0f,		1.0f,	0.0f,	0.0f},
	{"Thank you for Playing this Game!",			75.0f,			250.0f,		1.0f,	0.0f,	0.0f},
};

// �R���X�g���N�^
CStuffedRoll::CStuffedRoll()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eDefault)
	, mStaffRollTime(0.0f)
	, mXPos(0.0f)
{
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
	for (CText* text : mStuffedRolls)
	{
		text->Update();
	}

	if (CInput::Key(VK_UP))
	{
		mStaffRollTime += Time::DeltaTime() * 2.0f;
	}
	else
	{
		mStaffRollTime += Time::DeltaTime();
	}

	if (mStaffRollTime >= 90.0f)
	{
		CSceneManager::Instance()->LoadScene(EScene::eTitle);
	}

	//CDebugPrint::Print("mTime:%f\n", mStaffRollTime);
}

// �e�L�X�g���ړ������鏈��
void CStuffedRoll::ScrollTextUp(CText* pText, float& yPos, float speed)
{
	if (mStaffRollTime >= 82.0f)
	{
		return;
	}

	// ��L�[��������Ă���ꍇ�A2.0�{�̑����ŃX�N���[��
	if (CInput::Key(VK_UP))
	{
		yPos -= speed * 2.0f;
	}
	else
	{
		yPos -= speed;
	}

	pText->SetPos(CVector2(mXPos, yPos));

	//CDebugPrint::Print("Text Position: %f, %f\n", pText->GetPos().X(), pText->GetPos().Y());
	//CDebugPrint::Print("yPos: %f\n", yPos);
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
		// �Ō�̗v�f�łȂ��ꍇ�ɂ̂�16.0f�̐�����K�p
		if (i < mStuffedRolls.size() - 1 && mStaffRollTime > data.startTime + 16.0f) continue;

		mStuffedRolls[i]->SetText(data.stuffName.c_str());
		// �X�N���[������
		ScrollTextUp(mStuffedRolls[i], mTextYPositions[i], 1.0f);
		mStuffedRolls[i]->SetColor(data.r, data.g, data.b);
		mStuffedRolls[i]->SetFontSize(42);
		mStuffedRolls[i]->Render();
	}
}