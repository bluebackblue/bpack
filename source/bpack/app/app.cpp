

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/bpack/blob/master/LICENSE.txt
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
		NBsys::NFile::SetRoot(0,L"../");

		{
			//作成開始。
			sharedptr<ThreadTemplate<NBsys::NFile::File_Pack_MakeThread>> t_pack_makethread = NBsys::NFile::Pack_Create(L"../to_pack_data/",L"../data.pack",nullptr);
			
			std::cout << "pack : start" << std::endl;

			//作成中。
			while(t_pack_makethread->IsEnd() == false){
				ThreadSleep(1000);
				std::cout << "pack : now" << std::endl;
			}
			
			//作成完了。
			t_pack_makethread->EndWait();
			t_pack_makethread.reset();

			std::cout << "pack : end" << std::endl;
		}

		{
			NBsys::NFile::Pack_LoadRequest(0,L"data.pack",L"test");

			//TODO:エラー処理。
			while(NBsys::NFile::Pack_IsExist(0,L"data.pack") == false){
				ThreadSleep(1000);
				//std::cout << "error : isexist" << std::endl;
			}

			sharedptr<NBsys::NFile::File_Object> t_object(new NBsys::NFile::File_Object(0,L"test/test1/data.txt",-1,nullptr,0));

			while(t_object->IsBusy()){
				ThreadSleep(1000);
			}

		}

		//終了処理。
		NBsys::NFile::EndSystemRequest();
		NBsys::NFile::EndWaitSystem();
	}
}

