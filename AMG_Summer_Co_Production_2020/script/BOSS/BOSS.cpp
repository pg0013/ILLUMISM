/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS.cpp.
 *
 * @brief	�{�X�I�u�W�F�N�g
 */

#include "BOSS.h"
#include"../Server/ResourceServer.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
using namespace illumism;

BOSS::BOSS()
{
	Init();
}

BOSS::~BOSS()
{
	m_se.Pause();
	m_se.Destroy();
}

void BOSS::Init()
{
	m_width = 1499;
	m_height = 1060;

	m_x = SCREEN_WIDTH / 2 - m_width / 2;
	m_y = -200 - 680 * 2;

	m_speed_x = 5;
	m_speed_y = 1;

	m_hit_x = m_width / 2 - 130;
	m_hit_y = 200;
	m_hit_w = 250;
	m_hit_h = 650;

	//0frame�Ń_���[�W��ԂɂȂ�Ȃ��悤�ɏ�����
	m_damage_frame = -10;
	m_damage_flag = false;

	m_params.HP = 1000;
	m_blinking_flag = false;
	m_ishit_flag = true;
	once_flag = true;
	once_death_flag = true;
	attack_random_flag = false;

	m_boss_state = APPEAR;
	m_pre_boss_state = MOVE;
}

void BOSS::Process(Game& _game)
{
	ObjectBase::Process(_game);

	//�{�X�̃p�[�c���ƂɃA�j���[�V�����𓮂���
	m_center.Process(_game);
	m_left.Process(_game);
	m_right.Process(_game);

	State(_game);

	if (m_params.HP < 0)
	{
		m_params.HP = 0;
		m_boss_state = DESTROY;
		return;
	}

	//�_���[�W���󂯂���10�t���[���_���[�W�摜��`��
	if (m_frame_count - m_damage_frame < 10)
		m_damage_flag = true;
	else
		m_damage_flag = false;
}

void BOSS::State(Game& _game)
{
	switch (m_boss_state)
	{
	case APPEAR:
		Appear(_game);
		break;
	case MOVE:
		Move(_game);
		Hit(_game);
		SelectNextAttack();
		break;
	case FALL_ATTACK:
		FallAttack(_game);
		Hit(_game);
		break;
	case GROUND_ATTACK:
		GroundAttack(_game);
		Hit(_game);
		break;
	case CROSS_LASER:
		CrossLaser(_game);
		Hit(_game);
		break;
	case LASER_ATTACK:
		LaserAttack(_game);
		Hit(_game);
		break;
	case SIMPLE_LASER:
		SimpleLaser(_game);
		Hit(_game);
		break;
	case DESTROY:
		Destroy(_game);
		break;
	}
}

void BOSS::Draw(Game& _game)
{
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	int x = m_x - modeGame->m_camera.GetScreenX();

	//DESTROY���ɓ_�ŕ`����s��
	if (m_blinking_flag && (m_frame_count / 10 % 2) == 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
	}

	if (m_damage_flag)
	{
		m_center.Damage(_game);
		m_left.Damage(_game);
		m_right.Damage(_game);
		m_center.DrawHand(_game, m_boss_state, m_damage_flag);
		m_center.SwithEyeGraph(_game, m_boss_state, m_damage_flag);
	}
	else
	{
		m_center.Draw(_game);
		m_left.Draw(_game);
		m_right.Draw(_game);
		m_center.DrawHand(_game, m_boss_state, m_damage_flag);
		m_center.SwithEyeGraph(_game, m_boss_state, m_damage_flag);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG
	if (m_ishit_flag)
	{
		//�J���p�����蔻��\��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//�`�惂�[�h�𔼓����`��ɃZ�b�g
		//�̂̓����蔻��
		DrawBox(x + m_hit_x, m_y + m_hit_y,
			x + m_hit_x + m_hit_w, m_y + m_hit_y + m_hit_h,
			GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�s�����`��ɖ߂�
	}
#endif // _DEBUG
}

void BOSS::SelectNextAttack()
{
	if (m_frame_count - m_start_frame < 60 * 12)
		return;

	//���ׂĂ̍U�����s������O��s�����U���ȊO���烉���_���őI��
	if (attack_random_flag)
	{
		do
		{
			m_boss_state = GetRand(4) + 3;
		} while (m_pre_boss_state == m_boss_state);

		//�O��̍U�����L�^
		m_pre_boss_state = m_boss_state;

		return;
	}

	//���ԂɍU�����s��
	m_boss_state = m_pre_boss_state + 1;

	//�U�����L�^
	m_pre_boss_state = m_boss_state;

	if (m_pre_boss_state == CROSS_LASER)
	{
		m_pre_boss_state = MOVE;
		attack_random_flag = true;
	}
}

void BOSS::Damage(Game& _game)
{
	m_damage_frame = m_frame_count;
}

void BOSS::PlaySE(const char* _filename, Game& _game)
{
	m_se.Load(_filename);
	m_se.SetVolume(SE_VOLUME);
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
	m_se.Pan(m_x + m_width / 2 - modeGame->m_camera.GetScreenX());
	m_se.PlayBackGround(m_se);
}