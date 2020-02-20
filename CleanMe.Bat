REM cleanup root director

    rmdir /S /Q Debug
    rmdir /S /Q Release
    rmdir /S /Q ipch
    rmdir /S /Q .vs

    del /F /S /A:H *.suo
    del /F /S *.sdf
    del /F /S *.suo
    del /F *.db
  
REM walk through subdirectories delete Release & Debug subs

	cd src

for /d %%D in (*) do (
	echo %%~fD
	rmdir /S /Q %%~D\Debug
	rmdir /S /Q %%~D\Release
	del /F /S *.bin
)