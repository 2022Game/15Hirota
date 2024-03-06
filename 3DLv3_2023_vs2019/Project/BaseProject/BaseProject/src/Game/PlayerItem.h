#ifndef PLAYERITEM_H
#define PLAYERITEM_H

// �v���C���[�̃A�C�e���̎��(����)
struct PlayerItem
{
	std::string name;
	int PowerBonus;
	int DefenseBonus;
	int HealAmount;
};

// �A�C�e���̍ő吔
#define ITEM_COUNT_MAX 100

// �A�C�e�����Ƃ̏����Ǘ�����e�[�u��
extern const PlayerItem ITEM_TABLE[ITEM_COUNT_MAX];
#endif