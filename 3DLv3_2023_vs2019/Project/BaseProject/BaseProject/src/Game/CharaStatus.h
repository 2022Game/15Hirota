#ifndef CHARASTATUS_H
#define CHARASTATUS_H

//�L�����N�^�[�̃X�e�[�^�X
struct CharaStatus
{
	int level;			// ���x��
	int hp;				// HP
	int power;			// �U����
	int defense;		// �h���
	float moveSpeed;	// �ړ����x
};

// �v���C���[�̍ő僌�x��
#define PLAYER_LEVEL_MAX 100
// �v���C���[�̃��x�����Ƃ̃X�e�[�^�X�̃e�[�u��
extern const CharaStatus PLAYER_STATUS[PLAYER_LEVEL_MAX];
#endif