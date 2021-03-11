/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Appear.cpp.
 *
 * @brief	�v���C���[�o�ꎞ�̏���
 */

#include"Player.h"
#include"../Game.h"
using namespace illumism;

void Player::Appear(Game& _game)
{
	//��������
	m_y -= m_falling_speed;
	m_falling_speed -= 1;

	//�n�ʂɐڒn���Ă���ꍇ�́AY���W�����Z�b�g�E�����x���O�ɂ��A�j���[�V�������I��
	if (m_y >= (GROUND - m_height))
	{
		m_y = GROUND - m_height;
		m_falling_speed = 0;
		m_animation_running_flag = false;
	}

	m_graph = m_wait_graph[(m_frame_count / 2) % 30];

	if (m_frame_count > START_TIME)
		m_player_state = JUMP;
}