/**
 * @file	AMG_Summer_Co_Production_2020\script\SpotlightController.h.
 *
 * @brief	�X�|�b�g���C�g�̏o�����Ǘ�����N���X
 * @author	Takuya Fujisawa
 */

#pragma once
#include"DxLib.h"

namespace illumism
{
	class Game; //<	��d�C���N���[�h�h�~

	/**
	 * @class	SpotlightController
	 *
	 * @brief	�X�|�b�g���C�g�o�����Ǘ�����N���X
	 */
	class SpotlightController
	{
	public:
		SpotlightController();
		~SpotlightController();

		void Process(Game& _game);

	private:
		int m_start_time;	//!< BGM�Đ����̃X�^�[�g�^�C��
		int m_now_time;	//!< ���݂̃^�C��
		int m_time;			//!< BGM�Đ�������̌o�ߎ���[ms]
		int m_interval;		//!< �X�|�b�g���C�g�̊Ԋu
		int m_count;			//!< �t���[���J�E���g
		bool once_flag;
	};
}