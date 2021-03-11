/**
 * @file	AMG_Summer_Co_Production_2020\script\BOSS_CENTER.h.
 *
 * @brief	�{�X�����p�[�c���Ǘ�
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
 * @class	BOSS_CENTER
 *
 * @brief	�{�X�����p�[�c���Ǘ�
 *
 */
	class BOSS_CENTER : public ObjectBase
	{
	public:
		BOSS_CENTER();
		~BOSS_CENTER();

		/**
		 * @fn	virtual OBJECT_TYPE BOSS_CENTER::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::BOSS; }

		/**
		 * @fn	void BOSS_CENTER::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void BOSS_CENTER::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void BOSS_CENTER::Draw(Game& _game) override;
		 *
		 * @brief	�{�X�����p�[�c��`��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void BOSS_CENTER::Damage(Game& _game) override;
		 *
		 * @brief	�_���[�W�摜��`��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Damage(Game& _game) override;

		/**
		 * @fn	void BOSS_CENTER::DrawHand(Game& _game,int _state,bool damage);
		 *
		 * @brief	�r�̃A�j���[�V������`��
		 *
		 * @param [in,out]	_game 		�Q�[���N���X�̎Q��.
		 * @paam				  	_state		�{�X�̍U�����
		 * @param 		  		damage		�_���[�W���󂯂���
		 */
		void DrawHand(Game& _game, int _state, bool damage);

		/**
		 * @fn	void BOSS_CENTER::SwithEyeGraph(Game& _game, int _state, bool damage);
		 *
		 * @brief	�ڂ̉摜��؂�ւ��鏈��
		 *
		 * @param [in,out]	_game 		�Q�[���N���X�̎Q��.
		 * @paam				  	_state		�{�X�̍U�����
		 * @param 		  		damage		�_���[�W���󂯂���
		 */
		void SwithEyeGraph(Game& _game, int _state, bool damage);

	private:

		int m_pyram_up_graph[2];	//!< �摜�n���h��
		int m_pyram_down_graph[2];
		int m_gear_graph[2];
		int m_eye_graph[9];
		int m_scrap_graph[2];
		int m_righthand_graph[2];
		int m_lefthand_graph[2];
		int m_fallhand_graph[13];
		int m_groundhand_graph[11];

		int m_startanim_frame;  //!< �A�j���[�V�����J�n�t���[�����L�^
		int eye;	//!<	�`�悷��ڂ̎�ނ�ۑ�
		bool once_flag; //!< ��Ԉڍs���̏����������p�t���O
	};
}