/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_Laserattack.cpp.
 *
 * @brief	BOSS�̃v���C���[�Ɍ��������[�U�[�U������
 */

#include"BOSS.h"
#include"LaserAttack.h"
#include"../Mode/ModeGame.h"
#include"../Game.h"
using namespace illumism;

void BOSS::LaserAttack(Game& _game)
{
	if (once_flag)
	{
		m_start_frame = m_frame_count;
		once_flag = false;
	}

	//�\������
	if (m_frame_count - m_start_frame < 90)
		return;

	//18�b�ԍU��
	if (m_frame_count - m_start_frame < 60 * 18)
	{
		if ((m_frame_count - m_start_frame) % 60 == 0)
		{
			GenerateLaserAttack(_game);
		}

		//9�b�ォ��͈ړ����Ȃ��烌�[�U�[�U�����s��
		if (m_frame_count - m_start_frame > 60 * 9)
		{
			m_y = -200 + static_cast<int>(150 * sinf(DX_PI_F / 180 * ((m_frame_count - m_start_frame) % 360)));

			m_x += m_speed_x;
			if (m_x + m_hit_x < STAGE_WIDTH_LEFT)
				m_speed_x = 5;
			if (m_x + m_hit_x + m_hit_w >= STAGE_WIDTH_RIGHT)
				m_speed_x = -5;

			m_center.SetPosition(m_x + m_width / 2, m_y + m_height / 2);
			m_left.SetPosition(m_x + m_width / 2 - 220, m_y + m_height / 2);
			m_right.SetPosition(m_x + m_width / 2 + 220, m_y + m_height / 2);
		}
		return;
	}

	once_flag = true;
	m_boss_state = MOVE;
}

void BOSS::GenerateLaserAttack(Game& _game)
{
	int player_count = 0;
	ModeGame* modeGame = (ModeGame*)_game.m_modeserver->Get("Game");

	for (auto iter = _game.m_objectserver.List()->begin(); iter != _game.m_objectserver.List()->end(); iter++)
	{
		//�v���C���[�Ɍ����ă��[�U�[������
		if ((*iter)->GetType() == ObjectBase::OBJECT_TYPE::PLAYER ||
			(*iter)->GetType() == ObjectBase::OBJECT_TYPE::FLY)
		{
			player_count++;

			::LaserAttack* laserattack = new ::LaserAttack(m_x + m_width / 2 + 25, m_y + m_height / 2 + 25,
				(*iter)->GetPosX() + (*iter)->GetWidth() / 2, (*iter)->GetPosY() + (*iter)->GetHeight() / 2 - 50, 15);

			_game.m_objectserver.Add(laserattack);

			//2�����˂���邪�ASE�͈�x�����Đ����邩��
			//�v���C���[�����Ȃ��Ƃ���SE�𗬂��Ȃ�
			if (player_count == 1)
				PlaySE("resource/se/laser.wav", _game);
		}
	}
}