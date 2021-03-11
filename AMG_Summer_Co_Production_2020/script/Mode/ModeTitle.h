/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeTitle.h.
 *
 * @brief	�^�C�g���\�����[�h
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"
#include"../Sound/PlayWAVE.h"

namespace illumism
{
	/**
 * @class	ModeTitle
 *
 * @brief	�^�C�g���\�����[�h
 *
 */
	class ModeTitle : public ModeBase
	{
	public:
		/**
		 * @fn	virtual bool ModeTitle::Initialize(Game& _game);
		 *
		 * @brief	����������
		 * @detail	ModeServer�ڑ����Ɉ�x�����Ă΂��
		 *
		 * @param [in,out]	_game	Game�N���X�̎Q��
		 *
		 * @returns	�����������̉�
		 */
		virtual bool Initialize(Game& _game);

		/**
		 * @fn	virtual bool ModeTitle::Terminate(Game& _game);
		 *
		 * @brief	�I������
		 * @detail	ModeServer����폜�����ہA��x�����Ă΂��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	�I�����������̉�
		 */
		virtual bool Terminate(Game& _game);

		/**
		 * @fn	virtual bool ModeTitle::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	���Z���������̉�
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeTitle::Draw(Game& _game);
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	�`�揈�������̉�
		 */
		virtual bool Draw(Game& _game);

	private:

		/**
		 * @fn	void ModeTitle::Init();
		 *
		 * @brief	�����o�ϐ��̏�����
		 *
		 */
		void Init();

		/**
		 * @fn	void ModeTitle::Input(Game& _game);
		 *
		 * @brief	�R���g���[���[������͂����m���A���C�����j���[���[�h�ֈڍs
		 *
		 * @param [in,out]	_game	The game.
		 */
		void Input(Game& _game);

		/**
		 * @fn	void ModeTitle::NextMode(Game& _game);
		 *
		 * @brief	���C�����j���[���[�h�ֈڍs
		 *
		 * @param [in,out]	_game	The game.
		 */
		void NextMode(Game& _game);

		/**
		 * @fn	void ModeTitle::PlayBGM(Game& _game);
		 *
		 * @brief	BGM���Đ�
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void PlayBGM(Game& _game);

	private:
		int m_graph;	//!< �摜�n���h��
		int m_press_graph;
		int m_press_count;  //!< <�{�^����������Ă���̌o�ߎ��ԃJ�E���^
		bool m_once_flag;   //!< <��x�̂ݍs���鏈���p�t���O
		float m_freq;   //!< EQ�p�Ւf���g��
	};
}