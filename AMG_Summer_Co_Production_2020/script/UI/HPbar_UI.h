/**
 * @file	AMG_Summer_Co_Production_2020\script\HPbar_UI.h.
 *
 * @brief	�v���C���[��HP��\������UI
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	class Game;	//��d�C���N���[�h�h�~

	/**
	 * @class	HPbar_UI
	 *
	 * @brief	�v���C���[��HP��\������N���X
	 *
	 */
	class HPbar_UI : public ObjectBase
	{
	public:
		HPbar_UI();
		~HPbar_UI();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE HPbar_UI::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::UI; }

		/**
		 * @fn	void HPbar_UI::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void HPbar_UI::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void HPbar_UI::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void HPbar_UI::SetHP(const int _player_num, const int _hp);
		 *
		 * @brief	�\������HP��ݒ�
		 *
		 * @param 	_player_num	�v���C���[�ԍ�
		 * @param 	_hp				�\������HP
		 */
		void SetHP(const int _player_num, const int _hp);

	private:
		int m_graph_up; //!< �摜�n���h��
		int m_hp[2];	//!< �v���C���[��HP
	};
}