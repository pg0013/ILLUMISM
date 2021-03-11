/**
 * @file	AMG_Summer_Co_Production_2020\script\Flybar_UI.h.
 *
 * @brief	��s�\���Ԃ�\������UI
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	class Game;//!<��d�C���N���[�h�h�~

	/**
	 * @class	Flybar_UI
	 *
	 * @brief	��s���ԕ\���N���X
	 *
	 */
	class Flybar_UI : public ObjectBase
	{
	public:
		Flybar_UI();
		~Flybar_UI();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE Flybar_UI::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::UI; }

		/**
		 * @fn	void Flybar_UI::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void Flybar_UI::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Flybar_UI::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void Flybar_UI::SetFlyTime(const int _player_num, int _time);
		 *
		 * @brief	�\�������s���Ԃ�ݒ�
		 *
		 * @param 	_player_num	�v���C���[�ԍ�
		 * @param 	_time			��s����
		 */
		void SetFlyTime(const int _player_num, int _time);

	private:
		int m_graph_up; //!< �摜�n���h��
		int m_flytime[2];   //!< ��s����
	};
}