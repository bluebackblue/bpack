CALL ..\..\..\setting.bat

FOR /F %%C IN (configuration.txt) DO (
	FOR /F %%P IN (platform.txt) DO (
		@REM �r���h�B
		%MSBUILD% bpack.vcxproj /t:rebuild /p:Configuration=%%C;Platform=%%P

		@REM �ړ��B
		move .\bin\%%P\%%C\bpack.exe bpack_%%P_%%C.exe
	)
)
