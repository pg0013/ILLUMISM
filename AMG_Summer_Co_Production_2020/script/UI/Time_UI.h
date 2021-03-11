/**
 * @file	AMG_Summer_Co_Production_2020\script\Time_UI.h.
 *
 * @brief	�Q�[�����[�h�̃v���C���Ԃ�\��
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"
#include"DxLib.h"

namespace illumism
{
	class Game;//��d�C���N���[�h�h�~

	namespace
	{
		constexpr int GAMETIME = 3600 * 4 + 60 * 18 - 315;  //!< ��������
		constexpr int BOSSTIME = GAMETIME - (80 - 12) * 60; //!< �{�X�o�ꎞ��
	}

	/**
	 * @class	Time_UI
	 *
	 * @brief	�������Ԃ�\������UI�̃N���X
	 *
	 */
	class Time_UI : public ObjectBase
	{
	public:
		Time_UI();
		~Time_UI();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE Time_UI::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::UI; }

		/**
		 * @fn	void Time_UI::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void Time_UI::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Time_UI::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game) override;

		/**
		 * @fn	void Time_UI::GenerateBOSS(Game& _game);
		 *
		 * @brief	�{�X�𐶐�
		 *
		 * @param [in,out]	_game	The game.
		 */
		void GenerateBOSS(Game& _game);

	private:
		int m_graph[11];	//!< �摜�n���h��
		int m_frame_graph;

		int m_GameTime; //!< �v���C����
		int m_now_time; //!< �c�莞��

		int m_minutes;  //!<	�c�莞��[minutes]
		int m_second;   //!< �c�莞��[second]

		bool onceflag;  //!< ��x�����Ă΂�鏈���p�t���O
	};
}