/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Move.cpp.
 *
 * @brief	�ړ������iL�X�e�B�b�N�j
 */

#include"Player.h"
#include"../Game.h"
using namespace illumism;

void Player::Move(Game& _game)
{
	//�p�b�h���͔�������A�v���C���[���ړ�(���E��)
	if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX < -ANALOG_MIN)
	{
		m_direction_x = LEFT;
		m_turn_flag = true;

		if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_UP)
			m_direction_y = UP;
		else if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_DOWN)
			m_direction_y = DOWN;

		//�v���C���[�������X�e�B�b�N�̌X���ʂɃ}�[�W����݂���
		// �v���C���[�𓮂����Ă���X�e�B�b�N�𗣂����Ƃ��ɁA�����Ŏ~�܂�ɂ���
		if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX < -ANALOG_MIN)
		{
			//�ړ������iSHOOT�Œ茂���j
			if (m_move_flag)
				return;

			//L�X�e�B�b�N���X�����ʂ����ړ�
			//FLY���̓}�[�W�����Ƃ�Ȃ������ňړ�����
			if (m_fly_flag == false)
			{
				m_inertia = static_cast<int>(m_speed * _game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX);
				m_x += m_inertia;
			}
		}

		//�n�ʂł̂݃_�b�V���A�j���[�V����
		if (m_y == (GROUND - m_height) &&
			m_animation_running_flag == false)
		{
			m_graph = m_dash_graph[(m_frame_count / 2) % 20];
		}
	}
	else if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX > ANALOG_MIN)
	{
		m_direction_x = RIGHT;
		m_turn_flag = false;

		if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_UP)
			m_direction_y = UP;
		else if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_DOWN)
			m_direction_y = DOWN;

		//�v���C���[�������X�e�B�b�N�̌X���ʂɃ}�[�W����݂���
		// �v���C���[�𓮂����Ă���X�e�B�b�N�𗣂����Ƃ��ɁA�����Ŏ~�܂�ɂ���
		if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX > ANALOG_MIN)
		{
			//�ړ������iSHOOT�Œ茂���j
			if (m_move_flag)
				return;

			//L�X�e�B�b�N���X�����ʂ����ړ�
			//FLY���̓}�[�W�����Ƃ�Ȃ������ňړ�����
			if (m_fly_flag == false)
			{
				m_inertia = static_cast<int>(m_speed * _game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX);
				m_x += m_inertia;
			}
		}

		//�n�ʂł̂݃_�b�V���A�j���[�V����
		if (m_y == (GROUND - m_height) &&
			m_animation_running_flag == false)
		{
			m_graph = m_dash_graph[(m_frame_count / 2) % 20];
		}
	}
	else
	{
		//��s��ԂłȂ��A�����쒆�̃A�j���[�V�������Ȃ��������ҋ@���[�V����
		if (m_fly_flag == false && m_animation_running_flag == false)
			m_graph = m_wait_graph[(m_frame_count / 2) % 30];

		//�X�e�B�b�N�𗣂����Ƃ��Ɋ����ňړ�
		if (m_move_flag == false)
		{
			m_inertia = static_cast<int>(m_inertia * 0.8);
			m_x += m_inertia;
		}
	}
}