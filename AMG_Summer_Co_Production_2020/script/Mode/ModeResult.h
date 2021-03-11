/**
 * @file	AMG_Summer_Co_Production_2020\script\ModeResult.h.
 *
 * @brief	���U���g��ʕ\�����[�h
 * @author	Takuya Fujisawa
 */

#pragma once
#include "ModeBase.h"
#include"../UI/ResultPoint.h"
#include"../Effect/EffectComponent.h"

namespace illumism
{
	namespace   //!<	�摜�\���p���W
	{
		constexpr int pos_x_P1P2 = 610;
		constexpr int pos_y_P1P2_win = 1080 / 4 + 55;
		constexpr int pos_y_P1P2_lose = 1080 / 2 + 55;
		constexpr int pos_x_banner = 0;
		constexpr int pos_y_banner_win = 1080 / 4 + 50;
		constexpr int pos_y_banner_lose = 1080 / 2 + 50;
		constexpr int pos_x_charaname = 230;
		constexpr int pos_y_charaname_win = 1080 / 4 + 135;
		constexpr int pos_y_charaname_lose = 1080 / 2 + 135;
	}

	/**
	 * @class	ModeResult
	 *
	 * @brief	���U���g��ʕ\���p���[�h
	 *
	 */
	class ModeResult : public ModeBase
	{
	public:
		/**
		 * @fn	ModeResult::ModeResult(const int _point1, const int _point2, const int _P1charactor, const int _P2charactor);
		 *
		 * @brief	Constructor
		 *
		 * @param 	_point1			�v���C���[�P�����|�C���g
		 * @param 	_point2			�v���C���[�Q�����|�C���g
		 * @param 	_P1charactor	�v���C���[�P�I���L����
		 * @param 	_P2charactor	�v���C���[�Q�I���L����
		 */
		ModeResult(const int _point1, const int _point2, const int _P1charactor, const int _P2charactor);

		/**
		 * @fn	virtual bool ModeResult::Initialize(Game& _game);
		 *
		 * @brief	����������
		 * @detail	ModeServer�ڑ����Ɉ�x�����Ă΂��
		 *
		 * @param [in,out]	_game	Game�N���X�̎Q��
		 *
		 * @returns	�����������̉�
		 */
		virtual bool Initialize(Game& _game);

		/**
		 * @fn	virtual bool ModeResult::Terminate(Game& _game);
		 *
		 * @brief	�I������
		 * @detail	ModeServer����폜�����ہA��x�����Ă΂��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	�I�����������̉�
		 */
		virtual bool Terminate(Game& _game);

		/**
		 * @fn	virtual bool ModeResult::Process(Game& _game);
		 *
		 * @brief	���t���[���Ă΂�鉉�Z����
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	���Z���������̉�
		 */
		virtual bool Process(Game& _game);

		/**
		 * @fn	virtual bool ModeResult::Draw(Game& _game);
		 *
		 * @brief	�`�揈��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 *
		 * @returns	�`�揈�������̉�
		 */
		virtual bool Draw(Game& _game);

	private:
		/**
		 * @fn	void ModeResult::Init();
		 *
		 * @brief	����������
		 *
		 */
		void Init();

		/**
		 * @fn	void ModeResult::Input(Game& _game);
		 *
		 * @brief	�R���g���[���[������͂����m���A��ʑJ�ڂ��s��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 */
		void Input(Game& _game);

		/**
		 * @fn	void ModeResult::State(Game& _game);
		 *
		 * @brief	��ԑJ�ڂ��Ǘ�
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 */
		void State(Game& _game);

		/**
		 * @fn	void ModeResult::Retry(Game& _game);
		 *
		 * @brief	�Q�[�����[�h�։�ʑJ�ڂ��s��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 */
		void Retry(Game& _game);

		/**
		 * @fn	void ModeResult::Menu(Game& _game);
		 *
		 * @brief�@���C�����j���[���[�h�։�ʑJ�ڂ��s��
		 *
		 * @param [in,out]	_game �Q�[���N���X�̎Q��
		 */
		void Menu(Game& _game);

		/**
		 * @fn	void ModeResult::DrawBanner();
		 *
		 * @brief	Draw banner
		 *
		 */
		void DrawBanner();

		/**
		 * @fn	void ModeResult::DrawButton();
		 *
		 * @brief	Draw button
		 *
		 */
		void DrawButton();

		/**
		 * @fn	void ModeResult::DrawWinner();
		 *
		 * @brief	Draw winner
		 *
		 */
		void DrawWinner();

		/**
		 * @fn	void ModeResult::SelectCharactorGraph(const int _point1, const int _point2, const int _P1charactor, const int _P2charactor);
		 *
		 * @brief	���U���g��ʂŕ\������L�����N�^�[�摜���v���C���[���Ƃɓǂݍ���
		 *
		 * @param 	_point1			�v���C���[�P�����|�C���g
		 * @param 	_point2			�v���C���[�Q�����|�C���g
		 * @param 	_P1charactor	�v���C���[�P�I���L����
		 * @param 	_P2charactor	�v���C���[�Q�I���L����
		 */
		void SelectCharactorGraph(const int _point1, const int _point2, const int _P1charactor, const int _P2charactor);

		/**
		 * @fn	void ModeResult::PlaySE(Game& _game);
		 *
		 * @brief	���ʉ��Đ�
		 *
		 * @param 		  	_filename	�����t�@�C����
		 * @param 		  	_pitch   	�Đ����x
		 * @param [in,out]	_game	 	�Q�[���N���X�̎Q��
		 */
		void PlaySE(const char* _filename, const float _pitch, Game& _game);

		/**
		 * @fn	void ModeResult::AnimationSE(Game& _game);
		 *
		 * @brief	���U���g��ʂ̓����ɍ����悤��SE���Đ�
		 *
		 * @param [in,out]	_game	�Q�[���N���X�̎Q��.
		 */
		void AnimationSE(Game& _game);

		/**
		 * @enum	MENU_STATE
		 *
		 * @brief
		 */
		enum MENU_STATE
		{
			RETRY, MENU
		};

		ResultPoint m_result_point; //!<�����|�C���g�\��

		utility::EffectComponent m_move_win; //!< �C�[�W���O�p
		utility::EffectComponent m_move_lose;
		utility::EffectComponent m_move_winner;

		int m_x, m_y;

		int m_num_graph[2]; //!< �摜�n���h��
		int m_winbanner_graph;
		int m_losebanner_graph;
		int m_drawbanner_graph;
		int m_draw_graph;
		int m_banner_icon_graph[2] = { 0 };
		int m_backGround;
		int m_player_point[2] = { 0 };
		int m_name_graph[2] = { 0 };
		int m_menu_graph[2] = { 0 };
		int m_retry_graph[2] = { 0 };
		int m_winner_graph;
		int m_loser_graph;
		int m_winner_win_graph;

		int m_menu_state;   //!<��ԑJ�ڗp�ϐ�
		bool m_selected_flag;   //!<	���j���[�I���ςݗp�t���O
		int m_press_count;   //!< <�{�^����������Ă���̌o�ߎ��ԃJ�E���^
		int m_player_charactor[2] = { 0 };  //!< �v���C���[�I���L�����ۑ��p�ϐ�
	};
}