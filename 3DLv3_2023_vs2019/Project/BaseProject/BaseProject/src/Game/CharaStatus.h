#ifndef CHARASTATUS_H
#define CHARASTATUS_H

//�L�����N�^�[�̃X�e�[�^�X
struct CharaStatus
{
	int level;			// ���x��
	int hp;				// HP
	int power;			// �U����
	int defense;		// �h���
	int stamina;		// �X�^�~�i
	int baria;			// �o���A
	float moveSpeed;	// �ړ����x
};

// �v���C���[�̍ő僌�x��
#define PLAYER_LEVEL_MAX 100
// �v���C���[�̃��x�����Ƃ̃X�e�[�^�X�̃e�[�u��
extern const CharaStatus PLAYER_STATUS[PLAYER_LEVEL_MAX];

// �G�̍ő僌�x��
#define ENEMY_LEVEL_MAX 5
// �G�̃��x�����Ƃ̃X�e�[�^�X�̃e�[�u��
extern const CharaStatus ENEMY_STATUS[ENEMY_LEVEL_MAX];

// �G�̍ő僌�x��
#define PICOCHAN_LEVEL_MAX 5
// �G�̃��x�����Ƃ̃X�e�[�^�X�̃e�[�u��
extern const CharaStatus PICOCHAN_STATUS[PICOCHAN_LEVEL_MAX];


// ���@���K�[�h�̍ő僌�x��
#define VANGUARD_LEVEL_MAX 5
// ���@���K�[�h���Ƃ̃X�e�[�^�X�̃e�[�u��
extern const CharaStatus VANGUARD_STATUS[VANGUARD_LEVEL_MAX];
#endif