

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/bpack/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../entry.h"
#pragma warning(pop)


/** warning
*/
#pragma warning(disable:4710)


/** NApp
*/
namespace NApp
{
	/** App
	*/
	class App
	{
	private:
		/** filename_path
		*/
		STLWString filename_path;

		/** filename_output
		*/
		STLWString filename_output;
		
	public:
	
		/** パラメータ読み込み。
		*/
		bool LoadParam()
		{
			sharedptr<JsonItem> t_json = GetEntryParamReference().argument;
			
			STLWString t_path;
			STLWString t_output;

			if(t_json){
				if(t_json->IsAssociativeArray() == true){
					if(t_json->IsExistItem("-path",JsonItem::ValueType::StringData) == true){
						t_path = CharToWchar(*t_json->GetItem("-path")->GetStringData());
						if(t_path.length() <= 0){
							std::wcout << L"error : -path" << std::endl;
							return false;
						}
					}else{
						std::wcout << L"error : -path" << std::endl;
						return false;
					}
					if(t_json->IsExistItem("-output",JsonItem::ValueType::StringData) == true){
						t_output = CharToWchar(*t_json->GetItem("-output")->GetStringData());
						if(t_output.length() <= 0){
							std::wcout << L"error : -output" << std::endl;
							return false;
						}
					}else{
						std::wcout << L"error : -output" << std::endl;
						return false;
					}
				}else{
					std::wcout << L"error : parameter" << std::endl;
					return false;
				}
			}else{
				std::wcout << L"error : parameter" << std::endl;
				return false;
			}

			this->filename_path = t_path;
			this->filename_output = t_output;

			std::wcout << L"-path : " << this->filename_path << std::endl;
			std::wcout << L"-output : " << this->filename_output << std::endl;
			return true;
		}

		/** 作成。
		*/
		bool Make()
		{
			//作成開始。
			sharedptr<ThreadTemplate<NBsys::NFile::File_Pack_MakeThread>> t_pack_makethread = NBsys::NFile::Pack_Create(this->filename_path,this->filename_output,nullptr);
			
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

			return true;
		}
	};


	/** App_Main
	*/
	void App_Main()
	{
		//バージョン。
		std::cout << "Bpack 1.0.1" " " __DATE__  << std::endl;

		//ライブラリバージョン。
		std::cout << BROWNIE_VERSION_STRING << std::endl;
		
		//ファイルシステム起動。
		NBsys::NFile::StartSystem(1);
		NBsys::NFile::SetRoot(0,L"../");

		{
			App t_app;
			if(t_app.LoadParam()){
				if(t_app.Make()){
				}
			}
		}

		std::cout << "end" << std::endl;

		//終了処理。
		NBsys::NFile::EndSystemRequest();
		NBsys::NFile::EndWaitSystem();
	}


}

