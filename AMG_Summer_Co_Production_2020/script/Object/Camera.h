/**
 * @file	AMG_Summer_Co_Production_2020\script\Camera.h.
 *
 * @brief	ゲームシーンのカメラ処理
 * @author	Takuya Fujisawa
 */

#pragma once

namespace illumism
{
	class Game;//二重インクルード防止

	/**
	 * @class	Camera
	 *
	 * @brief	ゲームシーンのカメラクラス
	 *
	 */
	class Camera
	{
	public:
		Camera();
		~Camera();

		/**
		 * @fn	void Camera::Process(Game& _game);
		 *
		 * @brief	毎フレーム呼ばれる演算処理
		 *
		 * @param [in,out]	_game	ゲームクラスの参照
		 */
		void Process(Game& _game);

		/**
		 * @fn	void Camera::SetScreenPosition();
		 *
		 * @brief	画面内に表示する位置を設定
		 * @detail	各プレイヤーのx座標の中心にカメラが設定される
		 *
		 */
		void SetScreenPosition();

		/**
		 * @brief	プレイヤー被ダメージ時の画面ブレ処理
		 */
		void ScreenVibration();
		/**
		 * @fn	const int Camera::GetScreenX()
		 *
		 * @brief	カメラのx座標を返す
		 *
		 * @returns	x座標
		 */
		const int GetScreenX() { return m_scr_x; }

		/**
		 * @fn	const int Camera::GetScreenY()
		 *
		 * @brief	カメラのy座標を返す
		 *
		 * @returns	y座標
		 */
		const int GetScreenY() { return m_scr_y; }

		/**
		 * @fn	void Camera::SetPlayerPosX(int _player_num, int _player_x)
		 *
		 * @brief	プレイヤーのx座標を設定
		 *
		 * @param 	_player_num	プレイヤー番号
		 * @param 	_player_x  	x座標
		 */
		void SetPlayerPosX(int _player_num, int _player_x) { m_player_posx[_player_num] = _player_x; }

		/**
		 * @fn	void Camera::SetScreenY(int _y)
		 *
		 * @brief	カメラのy座標を設定
		 *
		 * @param 	_y		y座標
		 */
		void SetScreenY(int _y) { m_scr_y = _y; }

		/**
		 * @brief	画面ブレ時間を設定.
		 * 
		 * @param _count　画面ブレ有効フレーム
		 */
		void SetVibrationCount(int _count) { m_count = _count; }

		/**
		 * @brief　カメラ移動制限処理
		 * 
		 */
		void CameraLimit();

	private:
		int m_scr_x, m_scr_y;//!<	カメラ座標
		int m_player_posx[2] = { 0 }; //!< プレイヤー座標
		double m_camera_speed;  //!< カメラ移動速度
		int m_count;	//!<画面ブレ用カウンタ
	};
}