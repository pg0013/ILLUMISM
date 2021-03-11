/**
 * @file	AMG_Summer_Co_Production_2020\script\PointNumber_UI.h.
 *
 * @brief	�v���C���[�����|�C���g��\��
 * @author	Takuya Fujisawa
 */

#pragma once
#include "../Object/ObjectBase.h"

namespace illumism
{
	class Game;	//��d�C���N���[�h�h�~

	/**
	 * @class	PointNumber_UI
	 *
	 * @brief	�v���C���[�����|�C���g��\������N���X
	 *
	 */
	class PointNumber_UI :public ObjectBase
	{
	public:
		PointNumber_UI();
		~PointNumber_UI();

		/**
		 * @fn	virtual ObjectBase::OBJECT_TYPE PointNumber_UI::GetType()
		 *
		 * @brief	�I�u�W�F�N�g�̎�ނ�Ԃ�
		 *
		 * @returns	�I�u�W�F�N�g�̎��
		 */
		virtual ObjectBase::OBJECT_TYPE GetType() { return ObjectBase::OBJECT_TYPE::UI; }

		/**
		 * @fn	void PointNumber_UI::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void PointNumber_UI::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Process(Game& _game);

		/**
		 * @fn	virtual void PointNumber_UI::Draw(Game& _game) override;
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		virtual void Draw(Game& _game) override;

		/**
		 * @fn	void PointNumber_UI::SetPoint(const int _player_num,const int _point);
		 *
		 * @brief	�\������|�C���g����ݒ�
		 *
		 * @param 	_player_num	�v���C���[�ԍ�
		 * @param 	_point	   		�\������|�C���g��
		 */
		void SetPoint(const int _player_num, const int _point);

		/**
		 * @fn	void PointNumber_UI::SetPointRank();
		 *
		 * @brief	�|�C���g�̌����̒l��ݒ�
		 *
		 */
		void SetPointRank();

	private:
		int m_graph[10];	//!< �摜�n���h��

		int m_one_graph[10];
		int m_ten_graph[10];
		int m_hundred_graph[10];
		int m_thousand_graph[10];

		int m_point[2] = { 0 }; //!< �v���C���[�̃|�C���g���i�[

		int one_rank[2];	//!< �|�C���g�̈�A�\�A�S�A��̈ʂ̐��l���i�[
		int ten_rank[2];
		int hundred_rank[2];
		int thousand_rank[2];

		bool more_than_1000[2]; //!< �w�萔���傫�����ǂ���
		bool more_than_100[2];
		bool more_than_10[2];
	};
}