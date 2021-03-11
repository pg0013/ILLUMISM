/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_Appear.cpp.
 *
 * @brief	BOSS“oê‚Ìˆ—
 */

#include"BOSS.h"
using namespace illumism;

void BOSS::Appear(Game& _game)
{
	if (m_frame_count < 680)
		m_y += 2;
	else
		m_boss_state = MOVE;

	m_center.SetPosition(m_x + m_width / 2, m_y + m_height / 2);
	m_left.SetPosition(m_x + m_width / 2 - 220, m_y + m_height / 2);
	m_right.SetPosition(m_x + m_width / 2 + 220, m_y + m_height / 2);
}