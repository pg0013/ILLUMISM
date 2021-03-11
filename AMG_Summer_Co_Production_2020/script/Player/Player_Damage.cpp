/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Damage.cpp.
 *
 *	@brief	�_���[�W���󂯂��Ƃ��̏���
 */

#include"Player.h"
#include"../Effect/HitEffect.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void Player::Damage(Game& _game)
{

	if (m_damage_frame == 0)
	{
		PlaySE("resource/se/player_damage.wav", _game);
		m_combo = -1;									//2��^�b�`������1�R���{�ɂȂ�悤�ɏ�����
		m_damage_frame = m_frame_count;	//�A�j���[�V�����̊J�n���Ԃ��L�^

		//��ʃu���ݒ�
		ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
		modeGame->m_camera.SetVibrationCount(5);

		//�q�b�g�G�t�F�N�g����
		HitEffect* hiteffect = new HitEffect(m_x+m_width/2, m_y, 16);
		hiteffect->SetPositionOffset(modeGame->GetPlayerCharactor(PLAYER_NUM), m_direction_x);
		_game.m_objectserver.Add(hiteffect);
	}

	if (m_frame_count - m_damage_frame < 30)
	{
		m_player_state = DAMAGE;
		m_hit_no_count = 30;
		m_animation_running_flag = true;

		m_move_flag = true;
		//�󒆂Ń_���[�W���󂯂��ꍇ�A���E�ړ��ł����ɗ�������
		if (m_y + m_height < GROUND)
		{
			//��������
			m_y -= m_falling_speed;
			//���������x��������
			m_falling_speed -= 2;
		}

		//�_���[�W���󂯂��Ƃ��̌ジ����
		if (m_frame_count - m_damage_frame < 10)
		{
			if (m_direction_x == LEFT)
			{
				m_x += 5;
			}
			if (m_direction_x == RIGHT)
			{
				m_x -= 5;
			}
		}

		//�A�j���[�V�����Đ�
		if (m_frame_count - m_damage_frame < 30)
			m_graph = m_damage_graph[(m_frame_count - m_damage_frame) / 2 % 15];
	}
	else
	{
		m_animation_running_flag = false;
		m_move_flag = false;

		//���[�V�������Ƀ_���[�W���󂯂��Ƃ��̂��߂ɁA���[�V�����t���O��������
		m_attack_flag = false;
		m_appeal_flag = false;
		m_touch_flag = false;
		m_spmove_flag = false;

		m_damage_frame = 0;
		m_inertia = 0;
		m_player_state = JUMP;
	}
}