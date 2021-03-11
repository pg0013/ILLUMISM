/**
 * @file	AMG_Summer_Co_Production_2020\script\Combo.h.
 *
 * @brief	�^�b�`�I�u�W�F�N�g�̃R���{��\��
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	/**
	 * @class	Combo
	 *
	 * @brief	�R���{��\������N���X
	 *
	 */
	class Combo : public ObjectBase
	{
	public:

		/**
		 * @fn	Combo::Combo(const int _player_num, const int _combo);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_player_num	�v���C���[�ԍ�
		 * @param 	_combo	   	�R���{��
		 */
		Combo(const int _player_num, const int _combo);
		~Combo();

		/**
		 * @fn	virtual OBJECT_TYPE Combo::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual OBJECT_TYPE GetType() { return OBJECT_TYPE::UI; }

		/**
		 * @fn	void Combo::Init();
		 *
		 * @brief ����������
		 *
		 */
		void Init();

		/**
		 * @fn	void Combo::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Combo::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void Combo::SetCombo();
		 *
		 * @brief	�R���{����ݒ�
		 *
		 */
		void SetCombo();

	private:
		int m_number_graph[10];	//!<�摜�n���h��
		int m_combo_graph;
		int m_combo;	//!< �v���C���[�R���{��
		int onerank, tenrank;//!<��̈ʁA�\�̈�
		int m_count;	//!<�R���{�\�����ԃJ�E���^
	};
}