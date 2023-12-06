#include "CBillBoardImage.h"

// �R���X�g���N�^
CBillBoardImage::CBillBoardImage(std::string path, ETag tag, ETaskPriority prio, int sortOrder, ETaskPauseType pause)
	: CBillBoard(tag, prio, sortOrder, pause)
	, mpAnimData(nullptr)
	, mAnimNo(0)
	, mElapsedTime(0.0f)
{
	// �e�N�X�`���ǂݍ���
	mMaterial.LoadTexture("", path, false);
	CTexture* tex = mMaterial.Texture();

	CVector2 size;
	size.X(tex->Header().width / 256.0f);
	size.Y(tex->Header().height / 256.0f);
	SetSize(size);

	SetColor(CColor::white);

	// UV�ݒ�
	SetUV(CRect(0.0f, 0.0f, 1.0f, 1.0f));
}

// �f�X�g���N�^
CBillBoardImage::~CBillBoardImage()
{
}

// UV�ݒ�
void CBillBoardImage::SetUV(const CRect& uv)
{
	float l = uv.X();
	float t = uv.Y();
	float r = l + uv.W();
	float b = t + uv.H();

	mT[0].UV
	(
		CVector(r, t, 0.0f),
		CVector(l, b, 0.0f),
		CVector(r, b, 0.0f)
	);
	mT[1].UV
	(
		CVector(l, t, 0.0f),
		CVector(l, b, 0.0f),
		CVector(r, t, 0.0f)
	);
}

// �A�j���[�V�������Đ��ł��邩�ǂ���
bool CBillBoardImage::IsEnableAnim() const
{
	if (mpAnimData == nullptr) return false;
	if (mpAnimData->frames.size() == 0) return false;
	return true;
}

// �A�j���[�V�����f�[�^��ݒ�
void CBillBoardImage::SetAnimData(TexAnimData* animData)
{
	mpAnimData = animData;
	mAnimNo = 0;
	mElapsedTime = 0.0f;

	// �A�j���[�V�������L���ł���΁A
	// ��ԍŏ��̉摜��UV��ݒ�
	if (IsEnableAnim())
	{
		CRect uv = mMaterial.Texture()->CalcUV
		(
			mpAnimData->row,
			mpAnimData->col,
			0
		);
		SetUV(uv);
	}
}

// �X�V
void CBillBoardImage::Update()
{
	// �A�j���[�V�������L���ł����
	if (IsEnableAnim())
	{
		TexAnimFrameData data = mpAnimData->frames[mAnimNo];
		// ���݂̉摜�̕\�����Ԃ𒴂�����
		if (mElapsedTime >= data.time)
		{
			// ���̉摜�֐؂�ւ�
			mElapsedTime -= data.time;
			mAnimNo = (mAnimNo + 1) % mpAnimData->frames.size();
			CRect uv = mMaterial.Texture()->CalcUV
			(
				mpAnimData->row,
				mpAnimData->col,
				mAnimNo
			);
			SetUV(uv);
		}
		// �o�ߎ��Ԃ��v��
		mElapsedTime += Time::DeltaTime();
	}

	CBillBoard::Update();
}

// �`��
void CBillBoardImage::Render()
{
	CBillBoard::Render(&mMaterial);
}