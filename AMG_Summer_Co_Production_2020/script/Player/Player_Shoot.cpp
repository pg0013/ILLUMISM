/**
 * @file	AMG_Summer_Co_Production_2020\script\Player_Shoot.cpp
 *
 * @brief	�e�ۂ𔭎˂���U������(RT)
 */

#include"Player.h"
#include"../Game.h"
#include"../Mode/ModeGame.h"
#include"../Object/Bullet.h"
using namespace illumism;

void Player::Shoot(Game& _game)
{
	//R�g���K�[�������ꂽ
	if (m_RT_flag)
	{
		m_animation_running_flag = true;

		//todo
		if (m_RT_flag == true && m_oldRT_flag == false)
		{
			//2�x�������Ԃ̊�ƂȂ�t���[�����L�^
			if (m_pushRT_count == 0)
				m_pushRT_frame = m_frame_count;
			//�͂��߂ĉ����ꂽ��J�E���^��1
			m_pushRT_count++;

			//2��ډ����ꂽ�Ƃ���
			if (m_pushRT_count == 2)
			{
				//�����o�߃t���[������x�������e�͈͓����n�ʂȂ��
				//�ړ������Ɍ����ăJ�E���^�����Z�b�g
				if (m_frame_count - m_pushRT_frame < 20 &&
					m_y + m_height == GROUND)
				{
					m_move_flag = true;
					m_inertia = 0;
					m_pushRT_count = 0;
				}
				//2��ڂȂ̂�2�x�������e���Ԃ��߂��Ă�����A
				// �{�^���񐔂�1�x�ڂɂ��āA�t���[�����L�^���L�^�������r����
				else
				{
					m_pushRT_count = 1;
					m_pushRT_frame = m_frame_count;
				}
			}
		}

		//�{�^���������ꂽ�Ƃ��ɒe���˃t���[�����J�E���g
		m_bullet_frame_count++;

		int bullet_count = 0;
		//�e�I�u�W�F�N�g���J�E���g
		for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
		{
			if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::BULLET)
				bullet_count++;
		}
		clsDx();
		//���������͈͓��ł����
		if (bullet_count < BULLET_MAX)
		{
			ObjectBase* bullet = new Bullet(PLAYER_NUM);

			bullet->SetDirection(_game, PLAYER_NUM, m_turn_flag);

			// �e�I�u�W�F�N�g�̊J�n�ʒu���v���C���[�ʒu�ƕ�������Z�o
			if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX < -ANALOG_MIN)
			{
				//��
				bullet->SetPosition(m_x - 180 - bullet->GetWidth() * 2 / 3, m_y - 70 + m_height / 2 - bullet->GetHeight() / 2);
			}
			else if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX > ANALOG_MIN)
			{
				//�E
				bullet->SetPosition(m_x + 50 + m_width - bullet->GetWidth() / 3, m_y - 70 + m_height / 2 - bullet->GetHeight() / 2);
			}
			else
			{
				//�j���[�g�����̏ꍇ
				if (m_direction_x == LEFT)
				{
					bullet->SetPosition(m_x - 180 - bullet->GetWidth() * 2 / 3, m_y - 70 + m_height / 2 - bullet->GetHeight() / 2);
				}
				if (m_direction_x == RIGHT)
				{
					bullet->SetPosition(m_x + 50 + m_width - bullet->GetWidth() / 3, m_y - 70 + m_height / 2 - bullet->GetHeight() / 2);
				}
			}

			//SHOOT�摜��؂�ւ�
			// �E�͍��𔽓]����̂ŏ����Ă��Ȃ�
			if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX == 0 &&
				_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX > ANALOG_MIN)//��
			{
				m_graph = m_shoot_up_graph[m_frame_count / 2 % 5];
			}
			else if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX == 0 &&
				_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX < -ANALOG_MIN)//��
			{
				m_graph = m_shoot_downleft_graph[m_frame_count / 2 % 5];
			}
			else if (m_move_flag && _game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX > ANALOG_MIN)//����
			{
				m_graph = m_shoot_upleft_graph[m_frame_count / 2 % 5];
			}
			else if (m_move_flag && _game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX < -ANALOG_MIN)//����
			{
				m_graph = m_shoot_downleft_graph[m_frame_count / 2 % 5];
			}
			else if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX == 0 || m_move_flag)//��
			{
				m_graph = m_shoot_graph[m_frame_count / 2 % 5];
			}
			else if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX != 0 &&
				_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX > ANALOG_MIN)//����Ȃ��獶��
			{
				m_graph = m_dashshoot_upleft_graph[m_frame_count / 2 % 20];
			}
			else if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX != 0 &&
				_game.m_xinput_state[PLAYER_NUM - 1].ThumbLY / THUMB_MAX < -ANALOG_MIN)//����Ȃ��獶��
			{
				m_graph = m_dashshoot_downleft_graph[m_frame_count / 2 % 20];
			}
			else if (_game.m_xinput_state[PLAYER_NUM - 1].ThumbLX / THUMB_MAX != 0)//����Ȃ��獶
			{
				m_graph = m_dashshoot_graph[m_frame_count / 2 % 20];
			}

			//1�b��5��e�𔭎�
			if (m_bullet_frame_count % 10 == 0 || m_bullet_frame_count == 1)
			{
				PlaySE("resource/se/bullet.wav", _game);
				m_se.RandomPitch(0.1f);

				_game.m_objectserver.Add(bullet);
			}
			else
			{
				delete bullet;
			}
		}
	}
	else
	{
		//�{�^���������ꂽ��e���˃t���[���̃J�E���^�����������A�ړ������̉���
		m_bullet_frame_count = 0;
		m_move_flag = false;
	}
}