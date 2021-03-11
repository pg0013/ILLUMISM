/**
 * @file	AMG_Summer_Co_Production_2020\script\BackGround.h.
 *
 * @brief	�Q�[�����[�h�̔w�i�I�u�W�F�N�g�N���X
 * @author	Takuya Fujisawa
 */

#pragma once
#include"ObjectBase.h"

namespace illumism
{
	class Game;//!<��d�C���N���[�h�h�~

	/**
	 * @class	BackGround
	 *
	 * @brief	�Q�[�����[�h�̔w�i�N���X
	 *
	 */
	class BackGround
	{
	public:
		BackGround();
		~BackGround();

		/**
		 * @fn	void BackGround::Draw(Game& _game);
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void Draw(Game& _game);

		/**
		 * @fn	void BackGround::DrawAudience(Game& _game);
		 *
		 * @brief	�ϋq�̃A�j���[�V������`��
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��
		 */
		void DrawAudience(Game& _game);

	private:
		int m_background_graph; //!< �摜�n���h��
		int m_arch_graph[4] = { 0 };
		int m_seat_graph[4] = { 0 };
		int m_penlight_graph[4] = { 0 };
		int m_stage_graph;
		int m_spot_graph[2];
		int m_audience_graph;
		int m_vignette_graph;

		int m_x, m_y;
		int m_width, m_height;
	};
}