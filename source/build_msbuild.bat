CALL ..\..\..\setting.bat

FOR /F %%C IN (configuration.txt) DO (
	FOR /F %%P IN (platform.txt) DO (
		@REM ビルド。
		%MSBUILD% bpack.vcxproj /t:rebuild /p:Configuration=%%C;Platform=%%P

		@REM 移動。
		move .\bin\%%P\%%C\bpack.exe bpack_%%P_%%C.exe
	)
)
