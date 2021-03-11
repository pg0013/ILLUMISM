/**
 * @file	AMG_Summer_Co_Production_2020\script\TouchObjectController.cpp.
 *
 * @brief	�^�b�`�I�u�W�F�N�g�̏o�����Ǘ�����N���X
 * 				45BPM��6BPM�ŃI�u�W�F�N�g����ʏ�ɐ���
 */

#include"TouchObjectController.h"
#include"../Object/TouchObject.h"
#include"../Game.h"
#include"../Mode/ModeGame.h"
#include"DxLib.h"
using namespace illumism;

TouchObjectController::TouchObjectController()
{
	m_time = 0;
	m_bpm_counter_6 = 1;
	m_bpm_counter_45 = 3;
}

TouchObjectController::~TouchObjectController()
{
}

void TouchObjectController::Process(Game& _game)
{
	//BGM�Đ�����̌o�ߎ��Ԃ𑪒肷��
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	m_time = modeGame->GetModeCount();

	//45BPM�Ń^�b�`�I�u�W�F�N�g�𐶐�����
	if (m_time >= MINUTES / 45 * m_bpm_counter_45)
	{
		TouchObject* touch_object = new TouchObject(GetRand(11) + 1);

		touch_object->SetPosition(SCREEN_WIDTH * /*(GetRand(3) + 1)*/3 / 5, -220);

		//�v���C���[���O�ɕ`�悳��Ȃ����߂ɁA�C���T�[�g���g��
		_game.m_objectserver.Insert(touch_object);

		m_bpm_counter_45++;
	}

	//6BPM�Ń^�b�`�I�u�W�F�N�g�𐶐�����
	if (m_time >= MINUTES / 6 * m_bpm_counter_6)
	{
		TouchObject* touch_object = new TouchObject(GetRand(1) + 1);

		touch_object->SetPosition(SCREEN_WIDTH * (GetRand(1) + 1) / 3, -220);

		//�v���C���[���O�ɕ`�悳��Ȃ����߂ɁA�C���T�[�g���g��
		_game.m_objectserver.Insert(touch_object);

		m_bpm_counter_6++;
	}
}