#include "CCollisionManager.h"
#include "CCollider.h"

// �R���W�����}�l�[�W���̃C���X�^���X
CCollisionManager* CCollisionManager::mpInstance = nullptr;

// �C���X�^���X���擾
CCollisionManager* CCollisionManager::Instance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CCollisionManager();
	}
	return mpInstance;
}

// �C���X�^���X�̔j��
void CCollisionManager::ClearInstance()
{
	delete mpInstance;
	mpInstance = nullptr;
}

// �R���X�g���N�^
CCollisionManager::CCollisionManager()
{
}

// �f�X�g���N�^
CCollisionManager::~CCollisionManager()
{
}

// �w�肵���R���C�_�[�����X�g�ɒǉ�
void CCollisionManager::Add(CCollider* col)
{
	// ���Ƀ��X�g�ɒǉ�����Ă�����A�ǉ����Ȃ�
	auto it = std::find(mColliderList.begin(), mColliderList.end(), col);
	if (it != mColliderList.end()) return;

	// ���X�g�̍Ō���ɒǉ�
	mColliderList.push_back(col);
}

// �w�肵���R���C�_�[�����X�g�����菜��
void CCollisionManager::Remove(CCollider* col)
{
	mColliderList.remove(col);
}

// �w�肵��2�̃R���C�_�[�̏Փˏ������s��
void CCollisionManager::Collision(CCollider* col0, CCollider* col1)
{
	// �w�肵���R���C�_�[���L���łȂ���΁A�Փ˔�����s��Ȃ�
	if (col0 == nullptr || col1 == nullptr) return;
	if (!col0->IsEnable() || !col1->IsEnable()) return;
	// ���R���C�_�[�Ɏ����傪���݂��Ȃ��ꍇ�́A�Փ˔�����s��Ȃ�
	if (col0->Owner() == nullptr && col1->Owner() == nullptr) return;

	// �Փ˔�����s���R���C�_�[�łȂ���΁A�Փ˔�����s��Ȃ�
	if (!col0->IsCollision(col1)) return;

	// �Փ˔�����s��
	CVector adjust;
	bool collision = CCollider::Collision(col0, col1, &adjust);
	// �Փ˂��Ă��Ȃ���΁A�Փˏ������s��Ȃ�
	if (!collision) return;

	// �e�R���C�_�[�̎�����ɏՓ˂������Ƃ�`����
	if (col0->Owner() != nullptr)
		col0->Owner()->Collision(col0, col1, adjust);
	if (col1->Owner() != nullptr)
		col1->Owner()->Collision(col1, col0, adjust);
}

// �w�肵���R���C�_�[�Ƒ��̑S�ẴR���C�_�[�Ƃ̏Փˏ������s��
void CCollisionManager::Collision(CCollider* col)
{
	// �w�肵���R���C�_�[���L���łȂ���΁A�Փ˔���͍s��Ȃ�
	if (col == nullptr) return;
	if (!col->IsEnable()) return;

	// �R���C�_�[���X�g���̑S�ăR���C�_�[�ƏՓˏ������s��
	for (auto& other : mColliderList)
	{
		// 2�̃R���C�_�[�̏Փˏ������s��
		Collision(col, other);
	}
}

// �S�ẴR���C�_�[�̏Փˏ������s��
void CCollisionManager::CollisionAll()
{
	// ���X�g�̐擪���珇�ԂɏՓˏ������s��
	auto it = mColliderList.begin();
	auto end = mColliderList.end();
	for (; it != end; ++it)
	{
		CCollider* current = *it;

		// current�̎��̃R���C�_�[���珇�ԂɏՓˏ������s��
		// �icurrent���O�̃R���C�_�[�Ƃ͊��ɏՓˏ������s���Ă��邽�߁j
		auto nextIt = it;
		nextIt++;
		for (; nextIt != end; ++nextIt)
		{
			CCollider* next = *nextIt;
			// 2�̃R���C�_�[�̏Փˏ������s��
			Collision(current, next);
		}
	}
}

// �S�R���C�_�[��`��
void CCollisionManager::Render()
{
	// ���X�g���̑S�ẴR���C�_�[��`��
	for (auto& col : mColliderList)
	{
		col->Render();
	}
}