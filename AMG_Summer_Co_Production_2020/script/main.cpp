/**
 * @file	AMG_Summer_Co_Production_2020\script\main.cpp.
 *
 * @brief	プログラムのエントリーポイント
 */

#include"DxLib.h"
#include"Game.h"
#include"Sound/PlayWAVE.h"
#include"Server/ResourceServer.h"
#include"time.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//DXライブラリのアーカイブファイル読み込みを使用する
	SetUseDXArchiveFlag(TRUE);
	//Log.txtを出力しない
	SetOutApplicationLogValidFlag(FALSE);

	//ウィンドウに表示される名前の設定
	SetMainWindowText("ILLUMISM");
	//ウィンドウモードの設定
	ChangeWindowMode(TRUE);

	//画面設定
	SetGraphMode(illumism::SCREEN_WIDTH, illumism::SCREEN_HEIGHT, illumism::SCREEN_DEPTH);

	//DXライブラリの初期化
	if (DxLib_Init() == -1)
	{
		//エラーが起きたら終了
		return -1;
	}

	sound::PlayWAVE::Init();
	illumism::ResourceServer::Init();

	srand((unsigned int)time(NULL));
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.1);
	SetJoypadDeadZone(DX_INPUT_PAD2, 0.1);

	illumism::Game* game = new illumism::Game();

	//メインループ
	while (ProcessMessage() == 0)
	{
		game->Input();
		game->Process();
		game->Draw();

		if (game->GetExitFlag() == true)
			break;
	}

	delete game;

	illumism::ResourceServer::Release();
	sound::PlayWAVE::Release();

	DxLib_End();

	return 0;
}