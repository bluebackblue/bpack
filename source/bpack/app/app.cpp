

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#include "../entry.h"


/** NApp
*/
namespace NApp
{
	/** App
	*/
	class App
	{
	};


	/** App_Main
	*/
	void App_Main()
	{
		//バージョン。
		std::cout << "Bpack 1.0.0" " " __DATE__  << std::endl;

		//ライブラリバージョン。
		std::cout << BROWNIE_VERSION_STRING << std::endl;
		
		//ファイルシステム起動。
		NBsys::NFile::StartSystem(1);
		NBsys::NFile::SetRoot(0,L"./");

		{
			std::cout << "end" << std::endl;
		}

		//終了処理。
		NBsys::NFile::EndSystemRequest();
		NBsys::NFile::EndWaitSystem();
	}
}

