/**
 * @file	AMG_Summer_Co_Production_2020\script\ResultPoint.h.
 *
 * @brief	���U���g��ʂŃ|�C���g��\��
 * @author	Takuya Fujisawa
 */

#pragma once
#include "PointNumber_UI.h"
#include"../Effect/EffectComponent.h"

namespace illumism
{
	/**
	 * @class	ResultPoint
	 *
	 * @brief	���U���g��ʂŃ|�C���g��\������N���X
	 *
	 */
	class ResultPoint : public PointNumber_UI
	{
	public:
		ResultPoint();
		~ResultPoint();

		/**
		 * @fn	void ResultPoint::Draw(const int& _player1, const int& _player2, Game& _game);
		 *
		 * @brief	�`�揈��
		 *
		 * @param 		  	_player1	�v���C���[�P�̊l���|�C���g
		 * @param 		  	_player2	�v���C���[�Q�̊l���|�C���g
		 * @param [in,out]	_game  �Q�[���N���X�̎Q��
		 */
		void Draw(const int& _player1, const int& _player2, Game& _game);

		/**
		 * @fn	void ResultPoint::SetPointRank();
		 *
		 * @brief	�|�C���g�̌��̒l��ݒ�
		 *
		 */
		void SetPointRank();

		/**
		 * @fn	void ResultPoint::SetPoint(const int _player_num, const int _point);
		 *
		 * @brief	�\������|�C���g��ݒ�
		 *
		 * @param 	_player_num	�v���C���[�ԍ�
		 * @param 	_point			�l���|�C���g
		 */
		void SetPoint(const int _player_num, const int _point);

	private:
		int m_one_graph[10];	//!< �摜�n���h��
		int m_ten_graph[10];
		int m_hundred_graph[10];
		int m_thousand_graph[10];

		int m_point[2] = { 0 }; //!< �v���C���[�̃|�C���g���i�[

		int one_rank[2];	//!< �|�C���g�̈�A�\�A�S�A��̈ʂ̐��l���i�[
		int ten_rank[2];
		int hundred_rank[2];
		int thousand_rank[2];

		bool more_than_1000[2]; //!< �w�萔���|�C���g��������
		bool more_than_100[2];
		bool more_than_10[2];

		utility::EffectComponent m_move_win; //!< �A�j���[�V�����p�C�[�W���O
		utility::EffectComponent m_move_lose;
	};
}