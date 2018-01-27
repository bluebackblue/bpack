CALL ..\..\..\setting.bat

@ECHO bpack > log.txt

FOR /F %%C IN (configuration.txt) DO (
	FOR /F %%P IN (platform.txt) DO (

		@REM �R�����g
		@ECHO ��%%P_%%C >> log.txt

		@REM �r���h�B
		%MSBUILD% bpack.vcxproj /t:rebuild /p:Configuration=%%C;Platform=%%P >> log.txt

		@REM �ړ��B
		move .\bin\%%P\%%C\bpack.exe bpack_%%P_%%C.exe >> log.txt
	)
)

@PAUSE
