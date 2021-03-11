/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_Move.cpp.
 *
 * @brief	BOSSÇÃà⁄ìÆèàóù
 */

#include"BOSS.h"
#include"../Game.h"
using namespace illumism;

void BOSS::Move(Game& _game)
{
	if (once_flag)
	{
		m_start_frame = m_frame_count;
		once_flag = false;
	}

	if (m_frame_count - m_start_frame < 60 * 12)
	{
		m_y = -200 + static_cast<int>(150 * sinf(DX_PI_F / 180.0f * ((m_frame_count - m_start_frame) % 360)));

		m_x += m_speed_x;
		if (m_x + m_hit_x < STAGE_WIDTH_LEFT)
			m_speed_x = 5;
		if (m_x + m_hit_x + m_hit_w >= STAGE_WIDTH_RIGHT)
			m_speed_x = -5;

		m_center.SetPosition(m_x + m_width / 2, m_y + m_height / 2);
		m_left.SetPosition(m_x + m_width / 2 - 220, m_y + m_height / 2);
		m_right.SetPosition(m_x + m_width / 2 + 220, m_y + m_height / 2);

		return;
	}

	once_flag = true;
}