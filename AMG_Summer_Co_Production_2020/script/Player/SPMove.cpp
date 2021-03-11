/**
 * @file	AMG_Summer_Co_Production_2020\script\SPMove.cpp
 *
 * @brief	�K�E�Z�I�u�W�F�N�g�̏���
 */

#include "SPMove.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
using namespace illumism;

SPMove::SPMove(int _num)
{
	m_player_num = _num;

	//�v���C���[���ƂɈقȂ�F�̉摜��I��
	if (_num == 1)
		m_graph = ResourceServer::LoadGraph("resource/object/spmove1.png");
	if (_num == 2)
		m_graph = ResourceServer::LoadGraph("resource/object/spmove2.png");
	GetGraphSize(m_graph, &m_width, &m_height);

	Init();
}

SPMove::~SPMove()
{
}

void SPMove::Init()
{
	m_x = 0;
	m_y = 0;

	m_hit_x = 95;
	m_hit_y = 75;
	m_hit_w = 0;
	m_hit_h = 0;
}

void SPMove::Process(Game& _game)
{
	ObjectBase::Process(_game);

	SPMoveActivate(_game, 0, 80);
}

void SPMove::SetDirection(Game& _game, int _num, bool _turn_flag)
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

	//�j���[�g������Ԃ̎��͉摜�̌����ɍ��킹�Č��������߂�
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

void SPMove::SPMoveActivate(Game& _game, const int _startframe, const int _activetime)
{
	auto elapsed_time = m_frame_count - _startframe;	//�o�ߎ���

	if (elapsed_time < 0)//�x�����Ԓ��͉������Ȃ�
	{
		return;
	}
	else if (elapsed_time < _activetime)
	{
		//����o����
		m_hit_w = m_width - m_hit_x * 2;
		m_hit_h = m_height - m_hit_y * 2;
	}
	else
	{
		//�L�����Ԃ��߂�����j��
		Damage(_game);
	}
}

void SPMove::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	SetDrawBlendMode(DX_BLENDMODE_ADD, 175);
	//�摜�̌����𔽓]����
	if (m_turn_flag == true)
		DrawTurnGraph(x, m_y, m_graph, TRUE);
	else
		DrawGraph(x, m_y, m_graph, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG
	if (m_ishit_flag)
	{
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

void SPMove::Damage(Game& _game)
{
	_game.m_objectserver.Delete(this);
}