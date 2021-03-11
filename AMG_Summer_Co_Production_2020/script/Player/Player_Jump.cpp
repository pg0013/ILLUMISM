/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Jump.cpp
 *
 * @brief	�W�����v�����iA�{�^���j
 */

#include"Player.h"
#include"../Effect/LandingParticle.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void Player::Jump(Game& _game)
{
	//��s���̓W�����v�֎~
	if (m_fly_flag)
		return;

	int pre_falling = m_falling_speed;

	//��������
	m_y -= m_falling_speed;
	m_falling_speed -= 1;

	//�n�ʂɐڒn���Ă���ꍇ�́AY���W�����Z�b�g�E�����x���O�ɂ��A�j���[�V�������I��
	if (m_y >= (GROUND - m_height))
	{
		m_y = GROUND - m_height;
		m_falling_speed = 0;
		m_animation_running_flag = false;

		if (pre_falling != 0 && m_falling_speed == 0)
		{
			ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
			int x = m_x + m_width / 2 - modeGame->m_camera.GetScreenX();
			LandingParticle* landing_effect = new LandingParticle(x, m_y + m_height / 2, 30);
			_game.m_objectserver.Add(landing_effect);
		}
	}

	//�n�ʂ�A�{�^���������ꂽ��W�����v
	if ((_game.m_trigger_key[PLAYER_NUM - 1] & PAD_INPUT_1) &&
		m_y == (GROUND - m_height))
	{
		m_falling_speed = JUMP_HEIGHT;
		m_animation_running_flag = true;
		m_jump_frame = m_frame_count;

		PlaySE("resource/se/jump.wav", _game);
	}

	//�W�����v����SHOOT���s�����Ƃ��ɉ摜��SHOOT�摜�ɂ���
	if (_game.m_xinput_state[PLAYER_NUM - 1].RightTrigger == 255 &&
		m_player_state == SHOOT &&
		((m_y < (GROUND - m_height)) || m_falling_speed != 0))
	{
		if (floor((_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX) * 10) / 10 == 0 &&
			_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY/THUMB_MAX > ANALOG_MIN)//��
			m_graph = m_shoot_up_graph[m_frame_count / 2 % 5];
		if (floor((_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX) * 10) / 10 == 0 &&
			_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY/THUMB_MAX < -ANALOG_MIN)//��
			m_graph = m_shoot_downleft_graph[m_frame_count / 2 % 5];
		else if (floor((_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX) * 10) / 10 != 0 &&
			_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY/THUMB_MAX > ANALOG_MIN)//����
			m_graph = m_shoot_upleft_graph[m_frame_count / 2 % 5];
		else if (floor((_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX) * 10) / 10 != 0 &&
			_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY/THUMB_MAX < -ANALOG_MIN)//����
			m_graph = m_shoot_downleft_graph[m_frame_count / 2 % 5];

		return;
	}

	//�W�����v���̓W�����v�摜�ɐݒ�
	// ���ݐ؂��Ă��璸�_�܂�
	if (m_falling_speed > 0)
		m_graph = m_jump_graph[((m_frame_count - m_jump_frame) / 2) % 14];
	//���_���痎��
	if (m_falling_speed < 0)
		m_graph = m_jump_graph[13 + ((m_frame_count - m_jump_frame) / 2) % 13];
}