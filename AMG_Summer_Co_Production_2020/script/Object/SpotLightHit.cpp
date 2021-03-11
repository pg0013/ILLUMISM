/**
 * @file	AMG_Summer_Co_Production_2020\script\SpotLightHit.cpp.
 *
 * @brief	�X�|�b�g���C�g�p�����蔻��N���X
 */

#include "SpotLightHit.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

SpotLightHit::SpotLightHit()
{
	Init();
}

SpotLightHit::~SpotLightHit()
{
}

void SpotLightHit::Init()
{
	m_x = 0;
	m_y = 0;

	m_width = 280;
	m_height = 100;
	
	m_hit_x = 0;	
	m_hit_y = 0;
}

void SpotLightHit::Process(Game& _game)
{
	ObjectBase::Process(_game);

	SpotlightHitActivate(_game, 0, 90);
}

void SpotLightHit::SpotlightHitActivate(Game& _game, const int _startframe, const int _activetime)
{
	auto elapsed_time = m_frame_count - _startframe;	//�o�ߎ���
	if (elapsed_time < 0)//�x�����Ԓ��͉������Ȃ�
	{
		return;
	}
	else if (elapsed_time < _activetime)
	{
		//�����蔻��o����
		m_hit_w = m_width;
		m_hit_h = m_height;
	}
	else
	{
		//�L�����Ԃ��߂�����j��
		Damage(_game);
	}
}

void SpotLightHit::Damage(Game& _game)
{
	_game.m_objectserver.Delete(this);
}

void SpotLightHit::Draw(Game& _game)
{
#ifdef _DEBUG
	if (m_ishit_flag)
	{
		ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
		int x = m_x - modeGame->m_camera.GetScreenX();

		//�J���p�����蔻��\��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//�`�惂�[�h�𔼓����`��ɃZ�b�g
		//�U���̓����蔻��
		DrawBox(x + m_hit_x, m_y + m_hit_y,
			x + m_hit_x + m_hit_w, m_y + m_hit_y + m_hit_h,
			GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�s�����`��ɖ߂�
	}
#endif // _DEBUG
}