/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeOverlay.h.
 *
 * @brief	��ʑJ�ڃ��[�h
 * 				�L���v�`�����t�F�[�h�����w�肵�ĉ�ʑJ�ڂ��s��
 * 				�L���v�`���ł́A�\����ʂ̏ォ��I�[�o�[���C�\��
 * 				�t�F�[�h�ł́A��ʂ��Ó]������
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"

namespace illumism
{
	namespace
	{
		constexpr int FADE_IN = 0;
		constexpr int FADE_OUT = 1;
	}

	/**
	 * @class	ModeOverlay
	 *
	 * @brief	�I�[�o�[���C�ŉ�ʑJ�ڂ��s���N���X
	 *
	 */
	class ModeOverlay :
		public ModeBase
	{
	public:
		/**
		 * @fn	virtual bool ModeOverlay::Initialize(Game& g);
		 *
		 * @brief	����������
		 * @detail	ModeServer�ڑ����Ɉ�x�����Ă΂��
		 *
		 * @param [in,out]	_game	Game�N���X�̎Q��
		 *
		 * @returns	�����������̉�
		 */
		virtual bool Initialize(Game& g);

		/**
		 * @fn	virtual bool ModeOverlay::Terminate(Game& g);
		 *
		 * @brief	�I������
		 * @detail	ModeServer����폜�����ہA��x�����Ă΂��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	�I�����������̉�
		 */
		virtual bool Terminate(Game& g);

		/**
		 * @fn	virtual bool ModeOverlay::Process(Game& g);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	���Z���������̉�
		 */
		virtual bool Process(Game& g);

		/**
		 * @fn	virtual bool ModeOverlay::Draw(Game& g);
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	�`�揈�������̉�
		 */
		virtual bool Draw(Game& g);

		/**
		 * @fn	void ModeOverlay::Capture(int fadecnt);
		 *
		 * @brief	���ݕ\������Ă��郂�[�h���L���v�`�����āA��ʑJ�ڂ��s��
		 *
		 * @param 	fadecnt	�t�F�[�h����
		 */
		void Capture(int fadecnt);

		/**
		 * @fn	void ModeOverlay::Fade(int fadecount, int fadetype);
		 *
		 * @brief	�t�F�[�h�C�� : �Ó]���疾�邭�Ȃ�
		 * 				�t�F�[�h�A�E�g : ���邢��ʂ��珙�X�ɈÓ]
		 *
		 * @param 	fadecount	�t�F�[�h����
		 * @param 	fadetype 	�t�F�[�h�C�� : 0
		 * 									�t�F�[�h�A�E�g : 1
		 */
		void Fade(int fadecount, int fadetype);

	private:
		int m_graph;
		int m_count;	//!< �t�F�[�h����
		int m_all;  //!< �t�F�[�h���ԋL�^�p�ϐ�
		int m_fade_type;	//!< �t�F�[�h�̎��
	};
}