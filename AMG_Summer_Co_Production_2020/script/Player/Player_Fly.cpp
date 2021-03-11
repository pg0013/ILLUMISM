/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Fly.cpp.
 *
 *	@brief	��s���[�h�����iLT�j
 */

#include"Player.h"
#include"../Effect/Particle.h"
#include"../Utility/Utility.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void Player::Fly(Game& _game)
{
	//L�g���K�[��������Ă���A����s�\���ԓ�
	if (_game.m_xinput_state[PLAYER_NUM - 1].LeftTrigger == 255 &&
		m_fly_frame < m_fly_time)
	{
		m_fly_frame++;

		m_ishit_flag = false;
		m_fly_flag = true;
		m_move_flag = false;

		m_animation_running_flag = true;	//�A�j���[�V������L��
		m_graph = m_lightball_graph;

		m_speed = FLY_SPEED;	//��s���͈ړ����x�������Ȃ�
		m_falling_speed = 0;		//��s�����ɋ}�������Ȃ����߂ɏ�����

		//�g���K�[����
		if (m_fly_trigger_flag == false && m_fly_flag == true)
		{
			//FLY�I�u�W�F�N�g�Ƃ��Ĉ����A�v���C���[�̓����蔻��𖳌��ɂ���
			SetType(ObjectBase::OBJECT_TYPE::FLY);

			PlaySE("resource/se/fly.wav", _game);
			m_se.Fade(0.0f, 0.6f);
		}

		//�v���C���[�ړ�
		if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_UP)
			m_y -= static_cast<int>(m_speed * _game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX);
		if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_DOWN)
			m_y -= static_cast<int>(m_speed * _game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX);
		if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_LEFT)
			m_x += static_cast<int>(m_speed * _game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX);
		if (_game.m_gkey[PLAYER_NUM - 1] & PAD_INPUT_RIGHT)
			m_x += static_cast<int>(m_speed * _game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX);

		//��s�ړ�����PAN��ݒ�
		ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");
		m_se.Pan(m_x + m_width / 2 - modeGame->m_camera.GetScreenX());

		for (int i = 0; i < 3; i++)
			GenerateFlyParticle(_game);
	}
	else
	{
		//�����蔻����v���C���[�ɖ߂�
		SetType(ObjectBase::OBJECT_TYPE::PLAYER);

		//��s���Ԃ��g���؂�����AMAX�܂ŉ񕜂���܂Ŏg���Ȃ�
		if (m_fly_frame >= m_fly_time)
		{
			m_fly_time = 0;
		}

		//��s���Ԃ���
		m_fly_frame--;
		//�񕜂����������s���Ԃ�MAX��
		if (m_fly_frame < 0)
		{
			m_fly_frame = 0;
			m_fly_time = FLY_TIME;
		}

		// LT�������ςȂ�����Jump�֐������s����Ȃ��̂ŁA�����ŗ����������s��
		m_y -= m_falling_speed;
		m_falling_speed -= 1;

		if (m_y >= (GROUND - m_height))
		{
			m_y = GROUND - m_height;
			m_falling_speed = 0;
			m_animation_running_flag = false;
		}

		if (m_falling_speed < 0)
			m_graph = m_jump_graph[((m_frame_count - m_jump_frame) / 2) % 27];

		m_ishit_flag = true;
		m_speed = MOVE_SPEED;
		m_animation_running_flag = false;
		m_fly_flag = false;

		m_touch_flag = false;
		m_player_state = TOUCH;
	}
	//�O�t���[���̏�Ԃ�ۑ�
	m_fly_trigger_flag = m_fly_flag;
}

void Player::GenerateFlyParticle(Game& _game)
{
	//��s���̃v���C���[�ԍ����ʗp�p�[�e�B�N��
	Particle* particle_player = new Particle("resource/object/fly_test_13.png", static_cast<double>(m_x + 50.0), static_cast<double>(m_y + 100.0), 0, 0, 25);
	if (PLAYER_NUM == 1)
		particle_player->SetBright(95, 3, 69);
	else
		particle_player->SetBright(24, 84, 83);
	_game.m_objectserver.Add(particle_player);

	//���F�p�[�e�B�N��
	double vx = static_cast<double>(GetRand(15) - 6.0) / 10.0;
	double vy = static_cast<double>(GetRand(15) - 6.0) / 10.0;
	Particle* particle = new Particle("resource/object/fly_test_13.png", static_cast<double>(m_x + 50.0), static_cast<double>(m_y + 100.0), vx, vy, 30);

	int* rainbow;
	if (PLAYER_NUM == 1)
		rainbow = utility::GetColorHSV(static_cast<float>((6 * m_frame_count) % 360), 1.0f, 1.0f);
	else
		rainbow = utility::GetColorHSV(static_cast<float>(360 - (6 * m_frame_count) % 360), 1.0f, 1.0f);
	particle->SetBright(rainbow[0], rainbow[1], rainbow[2]);
	_game.m_objectserver.Add(particle);
}