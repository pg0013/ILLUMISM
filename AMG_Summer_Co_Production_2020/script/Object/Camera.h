/**
 * @file	AMG_Summer_Co_Production_2020\script\Camera.h.
 *
 * @brief	�Q�[���V�[���̃J��������
 * @author	Takuya Fujisawa
 */

#pragma once

namespace illumism
{
	class Game;//��d�C���N���[�h�h�~

	/**
	 * @class	Camera
	 *
	 * @brief	�Q�[���V�[���̃J�����N���X
	 *
	 */
	class Camera
	{
	public:
		Camera();
		~Camera();

		/**
		 * @fn	void Camera::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Camera::SetScreenPosition();
		 *
		 * @brief	��ʓ��ɕ\������ʒu��ݒ�
		 * @detail	�e�v���C���[��x���W�̒��S�ɃJ�������ݒ肳���
		 *
		 */
		void SetScreenPosition();

		/**
		 * @brief	�v���C���[��_���[�W���̉�ʃu������
		 */
		void ScreenVibration();
		/**
		 * @fn	const int Camera::GetScreenX()
		 *
		 * @brief	�J������x���W��Ԃ�
		 *
		 * @returns	x���W
		 */
		const int GetScreenX() { return m_scr_x; }

		/**
		 * @fn	const int Camera::GetScreenY()
		 *
		 * @brief	�J������y���W��Ԃ�
		 *
		 * @returns	y���W
		 */
		const int GetScreenY() { return m_scr_y; }

		/**
		 * @fn	void Camera::SetPlayerPosX(int _player_num, int _player_x)
		 *
		 * @brief	�v���C���[��x���W��ݒ�
		 *
		 * @param 	_player_num	�v���C���[�ԍ�
		 * @param 	_player_x  	x���W
		 */
		void SetPlayerPosX(int _player_num, int _player_x) { m_player_posx[_player_num] = _player_x; }

		/**
		 * @fn	void Camera::SetScreenY(int _y)
		 *
		 * @brief	�J������y���W��ݒ�
		 *
		 * @param 	_y		y���W
		 */
		void SetScreenY(int _y) { m_scr_y = _y; }

		/**
		 * @brief	��ʃu�����Ԃ�ݒ�.
		 * 
		 * @param _count�@��ʃu���L���t���[��
		 */
		void SetVibrationCount(int _count) { m_count = _count; }

		/**
		 * @brief�@�J�����ړ���������
		 * 
		 */
		void CameraLimit();

	private:
		int m_scr_x, m_scr_y;//!<	�J�������W
		int m_player_posx[2] = { 0 }; //!< �v���C���[���W
		double m_camera_speed;  //!< �J�����ړ����x
		int m_count;	//!<��ʃu���p�J�E���^
	};
}