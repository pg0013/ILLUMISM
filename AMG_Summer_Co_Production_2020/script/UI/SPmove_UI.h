/**
 * @file	AMG_Summer_Co_Production_2020\script\SPmove_UI.h.
 *
 * @brief	�K�E�Z�Q�[�W��\��
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	class Game;//��d�C���N���[�h�h�~

	/**
	 * @class	SPmove_UI
	 *
	 * @brief	�K�E�Z�Q�[�W��UI��\������N���X
	 *
	 */
	class SPmove_UI : public ObjectBase
	{
	public:
		SPmove_UI();
		~SPmove_UI();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE SPmove_UI::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::UI; }

		/**
		 * @fn	void SPmove_UI::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void SPmove_UI::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void SPmove_UI::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void SPmove_UI::DrawAura();
		 *
		 * @brief	�K�E�Z�����Ă邱�Ƃ�m�点��I�[����\������
		 *
		 */
		void DrawAura();

		/**
		 * @fn	void SPmove_UI::SetMP(const int _player_num, const int _mp);
		 *
		 * @brief	MP��ݒ�
		 *
		 * @param 	_player_num	�v���C���[�ԍ�
		 * @param 	_mp		   		MP
		 */
		void SetMP(const int _player_num, const int _mp);

	private:
		int m_mp[2];
		int m_graph_aura;
	};
}