/**
 * @file	AMG_Summer_Co_Production_2020\script\TouchObjectController.h.
 *
 * @brief	�^�b�`�I�u�W�F�N�g�̏o�����Ǘ�����N���X
 *
 * @detail	����BPM�Ń^�b�`�I�u�W�F�N�g����ʏ�ɐ�������
 * @author	Takuya Fujisawa
 */

#pragma once
#include"DxLib.h"

namespace illumism
{
	class Game;//< ��d�C���N���[�h�h�~

	namespace
	{
		constexpr int MINUTES = 3600;
	}

	/**
	 * @class	TouchObjectController
	 *
	 * @brief	�^�b�`�I�u�W�F�N�g�̏o�����Ǘ�����N���X
	 */
	class TouchObjectController
	{
	public:
		TouchObjectController();
		~TouchObjectController();

		void Process(Game& _game);

	private:
		int m_bpm_counter_6;	//!< BPM�̌o�߉񐔂��J�E���g
		int m_bpm_counter_45;   //!< BPM�̌o�߉񐔂��J�E���g

		int m_time; //!< BGM�Đ�������̌o�ߎ���
	};
}