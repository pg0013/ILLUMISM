/**
 * @file	AMG_Summer_Co_Production_2020\script\Camera.cpp.
 *
 * @brief	ゲームシーンのカメラクラス
 */

#include"Camera.h"
#include"../Game.h"
using namespace illumism;

Camera::Camera()
{
	m_scr_x = 0;
	m_scr_y = 0;
	m_camera_speed = 0.5;
	m_count = 0;
}

Camera::~Camera() {}

void Camera::Process(Game& _game)
{
	m_count--;

	SetScreenPosition();
	CameraLimit();
	ScreenVibration();
}

void Camera::SetScreenPosition()
{
	int player_middle = 0;

	//各プレイヤー座標の中心をカメラ座標に設定
	if (m_player_posx[0] >= m_player_posx[1])
	{
		player_middle = m_player_posx[1] + (m_player_posx[0] - m_player_posx[1]) / 2;
	}
	else if (m_player_posx[1] > m_player_posx[0])
	{
		player_middle = m_player_posx[0] + (m_player_posx[1] - m_player_posx[0]) / 2;
	}

	m_scr_x = static_cast<int>((player_middle - (SCREEN_WIDTH / 2) + 8) * m_camera_speed);
	m_scr_y = 0;
}

void Camera::CameraLimit()
{
	if (m_scr_x < -240) { m_scr_x = -240; }
	if (m_scr_x > 240) { m_scr_x = 240; }
}

void Camera::ScreenVibration()
{
	if (m_count < 0)
		return;

	m_scr_x -= (15 - GetRand(25));
	m_scr_y -= (15 - GetRand(25));
}