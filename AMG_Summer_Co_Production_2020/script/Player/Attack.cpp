/**
 * @file	AMG_Summer_Co_Production_2020\script\Attack.cpp.
 *
 * @brief	ATTACK�p�����蔻��̃N���X
 */

#include "Attack.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

Attack::Attack(int _player_num)
{
	m_player_num = _player_num;
	Init();
}

Attack::~Attack()
{
}

void Attack::Init()
{
	m_x = 0;
	m_y = 0;

	m_width = 160;
	m_height = 25;

	m_hit_x = 0;
	m_hit_y = 0;
	m_hit_w = 0;
	m_hit_h = 0;
}

void Attack::Process(Game& _game)
{
	ObjectBase::Process(_game);

	AttackActivate(_game, 0, 5);
}

void Attack::SetDirection(Game& _game, int _num, bool _turn_flag)
{
	//�����̐ݒ�
	if (_game.m_xinput_state[_num - 1].ThumbLX < 0)
	{
		m_direction_x = LEFT;
		m_turn_flag = true;
	}
	else if (_game.m_xinput_state[_num - 1].ThumbLX > 0)
	{
		m_direction_x = RIGHT;
		m_turn_flag = false;
	}

	//�j���[�g������Ԃ̎��͉摜�̌����ɍ��킹�Ēe�̌��������߂�
	if (_game.m_xinput_state[_num - 1].ThumbLX == 0 &&
		_game.m_xinput_state[_num - 1].ThumbLY == 0)
	{
		if (_turn_flag == true)
		{
			m_direction_x = LEFT;
			m_turn_flag = true;
		}
		else
		{
			m_direction_x = RIGHT;
			m_turn_flag = false;
		}
	}
}

void Attack::AttackActivate(Game& _game, const int _startframe, const int _activetime)
{
	auto elapsed_time = m_frame_count - _startframe;	//�o�ߎ���
	if (elapsed_time < 0)//�x�����Ԓ��͉������Ȃ�
	{
		return;
	}
	else if (elapsed_time < _activetime)
	{
		//ATTACK����o����
		m_hit_w = m_width;
		m_hit_h = m_height;
	}
	else
	{
		//�L�����Ԃ��߂�����j��
		Damage(_game);
	}

}

void Attack::Draw(Game& _game)
{
#ifdef _DEBUG
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	if (m_ishit_flag)
	{
		//�J���p�����蔻��\��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//�`�惂�[�h�𔼓����`��ɃZ�b�g
		//�U���̓����蔻��
		DrawBox(x + m_hit_x, m_y + m_hit_y,
			x + m_hit_x + m_hit_w, m_y + m_hit_y + m_hit_h - 50,
			GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�s�����`��ɖ߂�
	}
#endif // _DEBUG
}

void Attack::Damage(Game& _game)
{
	_game.m_objectserver.Delete(this);
}