#include "CBGMData.h"

// BGM�f�[�^�̃e�[�u��
const BGMData BGM_DATA[] =
{
	//BGM�̎��			���\�[�X�p�X					�x�[�X����	���[�v	���[�v�J�n	���[�v�I��
	{ EBGMType::eTitle,	"Sound\\BGM\\title.wav",		0.1f,		true,	0,			0		},
	{ EBGMType::eClear,	"Sound\\BGM\\Clear.wav",		1.25f,		true,	0,			0		},
	{ EBGMType::eMap,	"Sound\\BGM\\menu.wav",			0.25f,		true,	0,			0		},
	{ EBGMType::eStage1,"Sound\\BGM\\nature.wav",		0.25f,		true,	0,			0		},
	{ EBGMType::eStage2,"Sound\\BGM\\Pops.wav",			0.25f,		true,	0,			0		},
	{ EBGMType::eStage3,"Sound\\BGM\\Ska.wav",			0.25f,		true,	0,			0		},
	{ EBGMType::eGame,	"Sound\\BGM\\Pops_01.wav",		0.1f,		true,	0,			2801203	},
	{ EBGMType::eMenu,	"Sound\\BGM\\menu.wav",			0.25f,		true,	0,			0		},
	{ EBGMType::eResult,"Sound\\BGM\\Shooting.wav",		0.25f,		true,	0,			0		},
	{ EBGMType::eEnding,"Sound\\BGM\\kinematic.wav",	0.25f,		true,	0,			0		},
};

// BGM�f�[�^��
const int BGM_DATA_COUNT = ARRAY_SIZE(BGM_DATA);