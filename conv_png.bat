for %%A IN (*.jpg) DO (
	convert "%%~dpnA.jpg" "%%~dpnA.png"
)